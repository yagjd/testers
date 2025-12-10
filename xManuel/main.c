/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:20:09 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/06 11:26:41 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "main.h"

int		read_input(t_param *pars, int fd);
int		launch(t_param *pars);

static void	putstr(const char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

void	putendl(const char *s)
{
	putstr(s);
	putstr("\n");
}

static int	read_arg(int *fd, int argc, const char **argv)
{
	if (argc == 2)
	{
		*fd = open(argv[1], O_RDONLY);
		if (*fd < 0)
			return (putendl("Error opening:"), putendl(argv[1]), 1);
	}
	else
		return (putendl("This needs a .fdf file as first argument."), 1);
	return (0);
}

static void	set_parameters(t_param *pars, const char *ft)
{
	pars->colorseed = 0;
	pars->z_min = INFINITY;
	pars->z_max = -INFINITY;
	pars->yaw = DE / 4;
	pars->roll = DE / 5;
	pars->oblique_mode = 0;
	pars->yaw_obl = 0;
	pars->roll_obl = 0;
	pars->depth = 4;
	pars->skew = DE / 4;
	pars->title = (char *)ft;
}

int	main(const int argc, const char **argv)
{
	t_param	pars;
	int		fd;

	if (read_arg(&fd, argc, argv))
		return (close(fd), 1);
	set_parameters(&pars, argv[1]);
	if (read_input(&pars, fd))
		return (putendl("Error creating map"), close(fd), 1);
	close(fd);
	launch(&pars);
}
