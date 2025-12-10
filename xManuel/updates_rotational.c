/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates_rotational.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:00:02 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/01 22:38:30 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "main.h"

t_2x3matrix	orthogonal_projection(t_param *pars);
t_2x3matrix	oblique_proj(t_param *pars);
t_2dv		mvm_3d_2d(t_2x3matrix proj, t_3dv vec);
void		factor(t_param *pars);
void		display(t_param *pars);

static void	update_angle(t_param *pars)
{
	t_2x3matrix	m;
	t_3dv		*v3;
	t_2dv		*v2;
	int			n;

	if (pars->oblique_mode)
		m = oblique_proj(pars);
	else
		m = orthogonal_projection(pars);
	n = pars->rows * pars->cols;
	v3 = pars->map;
	v2 = pars->plane;
	while (n--)
	{
		if (isfinite(v3->x))
			*v2 = mvm_3d_2d(m, *v3);
		else
			v2->u = NAN;
		v3++;
		v2++;
	}
	factor(pars);
	display(pars);
}

void	rotate(t_param *pars, char yaw, char sign)
{
	if (yaw)
	{
		if (pars->oblique_mode)
			pars->yaw_obl += sign;
		else
			pars->yaw += sign;
	}
	else
	{
		if (pars->oblique_mode)
			pars->roll_obl += sign;
		else
			pars->roll += sign;
	}
	update_angle(pars);
}

void	oblique(t_param *pars)
{
	pars->oblique_mode = !pars->oblique_mode;
	update_angle(pars);
}

void	upd_skew(t_param *pars, char sign)
{
	pars->skew += sign;
	update_angle(pars);
}

void	upd_depth(t_param *pars)
{
	if (pars->depth < 6)
		pars->depth++;
	else
		pars->depth = 0;
	update_angle(pars);
}
