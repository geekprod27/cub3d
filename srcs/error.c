/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:39:49 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/22 14:30:26 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	errorrgb(t_data *data)
{
	ft_putstr_fd("Error : wrong RGB data", 2);
	ft_exit(data, 1);
}

void	puterrorline(char *line, t_data *ret)
{
	ft_putstr_fd("Error : unknown ID on line : ", 2);
	ft_putstr_fd(line, 2);
	free(line);
	ft_exit(ret, 1);
}

void	error(char *d, t_data *data)
{
	ft_putstr_fd("Error : Multiple ID : ", 2);
	ft_putstr_fd(d, 2);
	free(d);
	ft_exit(data, 3);
}

int	ft_error(char *msg)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(msg, 2);
	return (0);
}
