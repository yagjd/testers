/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:23:50 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/10 10:54:15 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "main.h"
#include "minilibx-linux/mlx.h"

int	build_seg(t_param *pars, t_ppair *pair);

static void	disp_seg(t_image *im, t_ppair *builtseg)
{
	t_pixel	*p;
	char	*dst;

	p = builtseg->pixels;
	while (p < builtseg->pixels + builtseg->nbr_p)
	{
		if (0 <= p->j && p->j < WWIDTH && 0 <= p->k && p->k < WHEIGHT)
		{
			dst = im->addr + (p->k * im->line_len + p->j * im->bpp / 8);
			*(unsigned int *)dst = p->c;
		}
		p++;
	}
	free(builtseg->pixels);
}

static void	do_seg(t_param *pars, t_ppair *pair, t_image *im)
{
	pair->a = pars->plane[pair->id_a];
	pair->b = pars->plane[pair->id_b];
	if (pair->a.u > WWIDTH && pair->b.u > WWIDTH)
		return ;
	if (pair->a.u < 0 && pair->b.u < 0)
		return ;
	if (pair->a.v > WHEIGHT && pair->b.v > WHEIGHT)
		return ;
	if (pair->a.v < 0 && pair->b.v < 0)
		return ;
	if (build_seg(pars, pair))
		return ;
	disp_seg(im, pair);
}

static void	paint_in_image(t_param *pars, t_image *im)
{
	t_ppair	pair;
	t_2dv	*v2;
	int		it;

	v2 = pars->plane;
	it = -1;
	while (++it < pars->cols * pars->rows)
	{
		if (isfinite(v2->u))
		{
			if (it % pars->cols > 0)
			{
				pair.id_a = it - 1;
				pair.id_b = it;
				do_seg(pars, &pair, im);
			}
			if (it >= pars->cols && isfinite(v2[-pars->cols].u))
			{
				pair.id_a = it - pars->cols;
				pair.id_b = it;
				do_seg(pars, &pair, im);
			}
		}
		v2++;
	}
}

void	display(t_param *pars)
{
	t_image	im;
	int		endian;

	im.img = mlx_new_image(pars->mlx, WWIDTH, WHEIGHT);
	im.addr = mlx_get_data_addr(im.img, &im.bpp, &im.line_len, &endian);
	paint_in_image(pars, &im);
	mlx_put_image_to_window(pars->mlx, pars->win, im.img, 0, 0);
	mlx_destroy_image(pars->mlx, im.img);
}
