/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:20:06 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/10 10:54:15 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "linalg.h"
#include "main.h"
#include "minilibx-linux/mlx.h"

t_2dv		mvm_3d_2d(t_2x3matrix proj, t_3dv vec);
t_2x3matrix	isometric_proj(void);
void		colorwheelpair(unsigned char n, t_color *a, t_color *b);
void		display(t_param *pars);
int			key_hook(int keycode, t_param *pars);
int			close_hook(t_param *pars);
/* Displays the string pointed to by s followed by a newline */
void		putendl(const char *s);

static void	upd_frame(t_param *pars, t_2dv *point)
{
	if (point == 0)
	{
		pars->u_min = INFINITY;
		pars->u_max = -INFINITY;
		pars->v_min = INFINITY;
		pars->v_max = -INFINITY;
	}
	else
	{
		if (point->u < pars->u_min)
			pars->u_min = point->u;
		if (point->u > pars->u_max)
			pars->u_max = point->u;
		if (point->v < pars->v_min)
			pars->v_min = point->v;
		if (point->v > pars->v_max)
			pars->v_max = point->v;
	}
}

static int	apply_first_proj(t_param *pars, t_2x3matrix m)
{
	t_3dv	*v3;
	t_2dv	*v2;
	int		n;

	n = pars->rows * pars->cols;
	pars->plane = malloc(sizeof(*pars->plane) * n);
	if (!pars->plane)
		return (putendl("Err malloc"), 1);
	v3 = pars->map;
	v2 = pars->plane;
	upd_frame(pars, 0);
	while (n--)
	{
		if (isfinite(v3->x))
		{
			*v2 = mvm_3d_2d(m, *v3);
			upd_frame(pars, v2);
		}
		else
			v2->u = NAN;
		v3++;
		v2++;
	}
	return (0);
}

static void	set_frame(t_param *pars)
{
	float	factor_hor;
	float	factor_ver;

	factor_hor = (float)(WWIDTH - 2 * PAD) / (pars->u_max - pars->u_min);
	factor_ver = (float)(WHEIGHT - 2 * PAD) / (pars->v_max - pars->v_min);
	pars->factor = fminf(factor_hor, factor_ver);
	pars->fr_center.u = 0.5 * (pars->u_max + pars->u_min);
	pars->fr_center.v = 0.5 * (pars->v_max + pars->v_min);
}

void	factor(t_param *pars)
{
	t_2dv	*v2;

	v2 = pars->plane;
	while (v2 < pars->plane + pars->cols * pars->rows)
	{
		if (isfinite(v2->u))
		{
			v2->u = fma(pars->factor, v2->u - pars->fr_center.u, 0.5 * WWIDTH);
			v2->v = fma(pars->factor, v2->v - pars->fr_center.v, 0.5 * WHEIGHT);
		}
		v2++;
	}
}

int	launch(t_param *pars)
{
	if (apply_first_proj(pars, isometric_proj()))
		return (1);
	set_frame(pars);
	factor(pars);
	colorwheelpair(pars->colorseed, &pars->lcolor, &pars->hcolor);
	pars->mlx = mlx_init();
	if (!pars->mlx)
		return (putendl("Err mlx_init"), free(pars->map), free(pars->plane), 1);
	pars->win = mlx_new_window(pars->mlx, WWIDTH, WHEIGHT, pars->title);
	display(pars);
	mlx_key_hook(pars->win, &key_hook, pars);
	mlx_hook(pars->win, 17, 1L << 0, &close_hook, pars);
	putendl("Use arrows to move, Z-X to zoom in and out, A-W-S-D to rotate.");
	putendl("Use C-V to change colors, ESC to exit.");
	putendl("Use O to change between orthogonal and oblique projection mode.");
	putendl("In oblique mode, use J-K and L to change skew angle and depth.");
	mlx_loop(pars->mlx);
	return (0);
}
