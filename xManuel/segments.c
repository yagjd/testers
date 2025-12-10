/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:34:05 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/04 20:14:09 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "main.h"

t_color	gradient(t_param *pars, float relative_h);
int		shadecolor(t_color c, int count);
/* Displays the string pointed to by s followed by a newline */
void	putendl(const char *s);

static void	rot_pair(t_ppair *pair, int quarters)
{
	float	tmp;

	if (quarters == 2)
	{
		pair->rot = (pair->rot + quarters) % 4;
		pair->a.u *= -1;
		pair->a.v *= -1;
		pair->b.u *= -1;
		pair->b.v *= -1;
	}
	else if (quarters == 1)
	{
		pair->rot = (pair->rot + quarters) % 4;
		tmp = pair->a.u;
		pair->a.u = -pair->a.v;
		pair->a.v = tmp;
		tmp = pair->b.u;
		pair->b.u = -pair->b.v;
		pair->b.v = tmp;
	}
	else if (quarters == 3)
	{
		rot_pair(pair, 2);
		rot_pair(pair, 1);
	}
}

static void	rot_pix(t_pixel *pixel, int quarters)
{
	int	tmp;

	if (quarters == 2)
	{
		pixel->j *= -1;
		pixel->k *= -1;
	}
	else if (quarters == 1)
	{
		tmp = pixel->j;
		pixel->j = -pixel->k;
		pixel->k = tmp;
	}
	else if (quarters == 3)
	{
		rot_pix(pixel, 2);
		rot_pix(pixel, 1);
	}
}

static void	color_pixel(t_param *pars, t_ppair *pair, t_pixel *p, float z)
{
	int		m;
	int		n;
	int		count;
	int		segaxis;
	t_pixel	copy;

	copy = *p;
	rot_pix(&copy, 4 - pair->rot);
	if (!(0 <= copy.j && copy.j < WWIDTH && 0 <= copy.k && copy.k < WHEIGHT))
		return ;
	count = 0;
	m = DV * p->j;
	while (m < DV * p->j + DV)
	{
		segaxis = round(fma(pair->sl, m, DV * pair->ic));
		n = DV * p->k;
		while (n < DV * p->k + DV)
		{
			if (segaxis - DV / 2 * SEGW < n && n < segaxis + DV / 2 * SEGW)
				count++;
			n++;
		}
		m++;
	}
	p->c = shadecolor(gradient(pars, z), count);
}

static void	build(t_param *pars, t_ppair *pair)
{
	int		j;
	int		k;
	int		k_end;
	t_pixel	*p;
	float	rz;

	j = pair->j_start;
	p = pair->pixels;
	while (j < pair->j_end)
	{
		k = floor(fma(pair->sl, j, pair->ic) - 0.5 * SEGW);
		k_end = k + 1 + SEGW;
		rz = fma(pair->h_diff / pair->j_diff, j - pair->j_start, pair->h_start);
		rz = rz / pars->z_diff + 0.5;
		while (k < k_end)
		{
			p->j = j;
			p->k = k;
			color_pixel(pars, pair, p, rz);
			rot_pix(p, 4 - pair->rot);
			p++;
			k++;
		}
		j++;
	}
}

/* takes two points in frame, creates a list of pixels that make the segment */
int	build_seg(t_param *pars, t_ppair *pair)
{
	pair->rot = 0;
	if (fabs(pair->b.v - pair->a.v) > fabs(pair->b.u - pair->a.u))
		rot_pair(pair, 1);
	if (pair->b.u < pair->a.u)
		rot_pair(pair, 2);
	pair->sl = (pair->b.v - pair->a.v) / (pair->b.u - pair->a.u);
	pair->ic = pair->a.v - pair->sl * pair->a.u;
	pair->h_start = pars->map[pair->id_a].z;
	pair->h_end = pars->map[pair->id_b].z;
	pair->h_diff = pair->h_end - pair->h_start;
	pair->j_start = floor(pair->a.u);
	pair->j_end = ceil(pair->b.u);
	pair->j_diff = pair->j_end - pair->j_start;
	pair->nbr_p = (pair->j_end - pair->j_start) * (1 + SEGW);
	pair->pixels = malloc(sizeof(*pair->pixels) * pair->nbr_p);
	if (!pair->pixels)
		return (putendl("malloc err"), 1);
	build(pars, pair);
	return (0);
}
