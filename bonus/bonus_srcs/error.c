/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:39:49 by llepiney          #+#    #+#             */
/*   Updated: 2022/11/22 14:42:46 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	errorrgb(t_data *data)
{
	ft_putstr_fd("Error\nWrong RGB data\n", 2);
	ft_exit(data, 1);
}

void	puterrorline(char *line, t_data *ret)
{
	ft_putstr_fd("Error\nUnknown ID on line : ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	free(line);
	ft_exit(ret, 1);
}

void	error(char *d, t_data *data)
{
	ft_putstr_fd("Error\nMultiple ID : ", 2);
	ft_putstr_fd(d, 2);
	ft_putstr_fd("\n", 2);
	free(d);
	ft_exit(data, 3);
}

int	ft_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return (0);
}
