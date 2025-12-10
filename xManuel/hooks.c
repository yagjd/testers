/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:32:29 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/10 11:42:25 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "main.h"
#include "minilibx-linux/mlx.h"

void	refactor_u(t_param *pars, char sign);
void	refactor_v(t_param *pars, char sign);
void	zoom(t_param *pars, char sign);
void	rotate(t_param *pars, char yaw, char sign);
void	change_color(t_param *pars, char sign);
void	oblique(t_param *pars);
void	upd_skew(t_param *pars, char sign);
void	upd_depth(t_param *pars);

static void	end(t_param *pars)
{
	mlx_destroy_window(pars->mlx, pars->win);
	mlx_destroy_display(pars->mlx);
	free(pars->mlx);
	free(pars->map);
	free(pars->plane);
	exit(0);
}

static void	other_key_hooks(int keycode, t_param *pars)
{
	if (keycode == 65307)
		end(pars);
	if (keycode == 65361)
		refactor_u(pars, 1);
	else if (keycode == 65363)
		refactor_u(pars, -1);
	else if (keycode == 65362)
		refactor_v(pars, 1);
	else if (keycode == 65364)
		refactor_v(pars, -1);
}

static void	obl_key_hooks(int keycode, t_param *pars)
{
	if (keycode == 106)
		upd_skew(pars, 1);
	else if (keycode == 107)
		upd_skew(pars, -1);
	else if (keycode == 108)
		upd_depth(pars);
}

int	key_hook(int keycode, t_param *pars)
{
	if (keycode > 1000)
		other_key_hooks(keycode, pars);
	else if (keycode == 120)
		zoom(pars, 1);
	else if (keycode == 122)
		zoom(pars, -1);
	else if (keycode == 97)
		rotate(pars, 1, 1);
	else if (keycode == 100)
		rotate(pars, 1, -1);
	else if (keycode == 119)
		rotate(pars, 0, 1);
	else if (keycode == 115)
		rotate(pars, 0, -1);
	else if (keycode == 99)
		change_color(pars, 1);
	else if (keycode == 118)
		change_color(pars, -1);
	else if (keycode == 111)
		oblique(pars);
	else if (pars->oblique_mode)
		obl_key_hooks(keycode, pars);
	return (0);
}

int	close_hook(t_param *pars)
{
	end(pars);
	return (0);
}
