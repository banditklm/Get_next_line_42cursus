/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 03:48:45 by kelmounj          #+#    #+#             */
/*   Updated: 2023/12/04 03:48:49 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (!s2)
	{
		free(s2);
		return (NULL);
	}
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len_total;
	size_t	i;
	size_t	j;

	if (!s2)
		return (str = ft_strdup(s1), free(s1), s1 = NULL, str);
	if (!s1)
		return (ft_strdup(s2));
	len_total = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len_total + 1);
	if (!str)
		return (free(s1), s1 = NULL, NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	return (free(s1), s1 = NULL, str[i] = '\0', str);
}
