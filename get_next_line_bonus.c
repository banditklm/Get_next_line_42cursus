/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 23:05:49 by kelmounj          #+#    #+#             */
/*   Updated: 2023/12/03 23:05:58 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*alloc_buf(void)
{
	char	*buff;
	size_t	i;

	buff = (char *)malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		*(buff + i) = 0;
		i++;
	}
	*(buff + i) = '\0';
	return (buff);
}

static int	check_new_line(char *res)
{
	int	i;
	int	v_bool;

	i = 0;
	v_bool = 0;
	while (res[i])
	{
		if (res[i] == '\n')
			v_bool = 1;
		i++;
	}
	return (v_bool);
}

static char	*read_buf(int fd, char *res)
{
	char	*buff;
	int		r;

	r = 1;
	while (r > 0)
	{
		buff = alloc_buf();
		if (!buff)
			return (free(res), res = NULL, NULL);
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
			return (free(buff), buff = NULL, NULL);
		if (r == 0)
			return (free(buff), buff = NULL, res);
		res = ft_strjoin(res, buff);
		free(buff);
		if (!res)
			return (NULL);
		if (check_new_line(res) == 1)
			break ;
	}
	return (res);
}

static char	*get_line(char *s_str)
{
	char	*res;
	size_t	i;

	i = 0;
	while (s_str[i] != '\n' && s_str[i])
		i++;
	if (s_str[i] == '\n')
		i++;
	res = (char *)malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s_str[i] != '\n' && s_str[i])
	{
		res[i] = s_str[i];
		i++;
	}
	if (s_str[i] == '\n')
	{
		res[i] = '\n';
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*s_str[OPEN_MAX];
	char		*res;
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(s_str[fd]), s_str[fd] = NULL, NULL);
	s_str[fd] = read_buf(fd, s_str[fd]);
	if (!s_str[fd] || !*s_str[fd])
		return (free(s_str[fd]), s_str[fd] = NULL, NULL);
	res = get_line(s_str[fd]);
	if (!res)
		return (free(s_str[fd]), s_str[fd] = NULL, NULL);
	if (!*s_str[fd])
		return (free(res), free(s_str[fd]), s_str[fd] = NULL, NULL);
	tmp = ft_strdup(s_str[fd] + ft_strlen(res));
	free(s_str[fd]);
	s_str[fd] = NULL;
	if (!tmp)
		return (free(s_str[fd]), s_str[fd] = NULL, free(res), NULL);
	s_str[fd] = ft_strdup(tmp);
	if (!s_str[fd])
		return (free(res), free(tmp), tmp = NULL, NULL);
	return (free(tmp), tmp = NULL, res);
}
