/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:51:25 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/11/07 18:44:17 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_tex	*get_tex(char *file)
{
	int		fd;
	t_tex	*ret;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (NULL);
	ret = malloc(sizeof(t_tex));
	if (!ret)
		return (NULL);
	//todo : gnl -> setpath t_tex
	return (ret);
}
