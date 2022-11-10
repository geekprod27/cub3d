/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:34:11 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/08 13:56:18 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	isnn(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

size_t	ft_strlen_gnl(const char *tab)
{
	int	i;

	i = 0;
	while (tab[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *s)
{
	int		i;
	int		lens;
	char	*ptr;

	i = 0;
	lens = ft_strlen_gnl(s);
	ptr = malloc(sizeof(char) * lens + 1);
	if (!ptr)
		return (0);
	while (i < lens)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (!s2)
		return (NULL);
	i = len(s2);
	if (s2[i] == '\n')
		++i;
	i += len(s1);
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	j = -1;
	while (s1[++j])
		ret[j] = s1[j];
	i = 0;
	while (s2[i] != '\n' && s2[i])
		ret[j++] = s2[i++];
	if (s2[i] == '\n')
		ret[j++] = '\n';
	ret[j] = '\0';
	free(s1);
	return (ret);
}
