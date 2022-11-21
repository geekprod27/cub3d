#include "../cub3D.h"

void	errorrgb(t_data *data)
{
	ft_putstr_fd("Error\nRGB", 2);
	ft_exit(data, 1);
}

void	puterrorline(char *line, t_data *ret)
{
	ft_putstr_fd("Error\nID inconue sur la ligne :\n", 2);
	ft_putstr_fd(line, 2);
	free(line);
	ft_exit(ret, 1);
}

void	error(char *d, t_data *data)
{
	ft_putstr_fd("Error\nMultiple ID :\n", 2);
	ft_putstr_fd(d, 2);
	free(d);
	ft_exit(data, 3);
}
