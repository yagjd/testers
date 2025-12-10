/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates_linear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:16:10 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/01 10:54:15 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "main.h"

void	colorwheelpair(unsigned char n, t_color *a, t_color *b);
void	display(t_param *pars);

void	refactor_u(t_param *pars, char sign)
{
	t_2dv	*v2;

	pars->fr_center.u -= sign * STEP / pars->factor;
	v2 = pars->plane;
	while (v2 < pars->plane + pars->cols * pars->rows)
	{
		if (isfinite(v2->u))
		{
			v2->u += sign * STEP;
		}
		v2++;
	}
	display(pars);
}

void	refactor_v(t_param *pars, char sign)
{
	t_2dv	*v2;

	pars->fr_center.v -= sign * STEP / pars->factor;
	v2 = pars->plane;
	while (v2 < pars->plane + pars->cols * pars->rows)
	{
		if (isfinite(v2->u))
		{
			v2->v += sign * STEP;
		}
		v2++;
	}
	display(pars);
}

void	zoom(t_param *pars, char sign)
{
	float	change;
	t_2dv	*v2;

	change = 1 - sign * 0.1;
	pars->factor *= change;
	v2 = pars->plane;
	while (v2 < pars->plane + pars->cols * pars->rows)
	{
		if (isfinite(v2->u))
		{
			v2->u = fma(change, (v2->u - 0.5 * WWIDTH), 0.5 * WWIDTH);
			v2->v = fma(change, (v2->v - 0.5 * WHEIGHT), 0.5 * WHEIGHT);
		}
		v2++;
	}
	display(pars);
}

void	change_color(t_param *pars, char sign)
{
	pars->colorseed += sign * 16;
	colorwheelpair(pars->colorseed, &pars->lcolor, &pars->hcolor);
	display(pars);
}
