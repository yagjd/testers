/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:02:47 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/01 22:12:23 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "linalg.h"
#include "main.h"

/* matrix vector multiplication taking a 3d vector and giving a 2d vector */
t_2dv	mvm_3d_2d(t_2x3matrix proj, t_3dv vec)
{
	t_2dv	ret;

	ret.u = proj.m11 * vec.x + proj.m12 * vec.y + proj.m13 * vec.z;
	ret.v = proj.m21 * vec.x + proj.m22 * vec.y + proj.m23 * vec.z;
	return (ret);
}

/* compute the matrix for the orthogonal projection  multiplying:

Yaw rotation around Z-axis
	[ cos_α  -sin_α   0 ]
	[ sin_α   cos_α   0 ]
	[   0       0     1 ]
Roll rotation around X-axis
	[  1      0        0    ]
	[  0    cos_γ   -sin_γ  ]
	[  0    sin_γ    cos_γ  ]
Simple projection on the xz-plane
	[ 1 0 0 ]
	[ 0 1 0 ]

Result
	[ cos_α                 -sin_α                    0   ]
	[ cos_γ * sin_α         cos_γ * cos_α            -sin_γ ]

this represents an */
t_2x3matrix	orthogonal_projection(t_param *pars)
{
	t_2x3matrix	ret;
	float		sin_gamma;
	float		cos_gamma;
	float		sin_alpha;
	float		cos_alpha;

	sin_gamma = sinf(pars->roll * PIFR);
	cos_gamma = cosf(pars->roll * PIFR);
	sin_alpha = sinf(pars->yaw * PIFR);
	cos_alpha = cosf(pars->yaw * PIFR);
	ret.m11 = cos_alpha;
	ret.m12 = -sin_alpha;
	ret.m13 = 0;
	ret.m21 = cos_gamma * sin_alpha;
	ret.m22 = cos_gamma * cos_alpha;
	ret.m23 = -sin_gamma;
	return (ret);
}

/*  evaluate matrix above with γ = arcsin(1/√3) and α = π/4 to obtain an */
t_2x3matrix	isometric_proj(void)
{
	t_2x3matrix	ret;

	ret.m11 = sqrtf(2) / 2;
	ret.m12 = -sqrtf(2) / 2;
	ret.m13 = 0;
	ret.m21 = 1 / sqrtf(3);
	ret.m22 = 1 / sqrtf(3);
	ret.m23 = -1 / sqrtf(3);
	return (ret);
}

/* compute the matrix for the orthogonal projection  multiplying:

Yaw rotation around Z-axis
	[ cos_α  -sin_α   0 ]
	[ sin_α   cos_α   0 ]
	[   0       0     1 ]
Roll rotation around X-axis
	[  1      0        0    ]
	[  0    cos_γ   -sin_γ  ]
	[  0    sin_γ    cos_γ  ]
oblique projection 
	[   1       0     λ·cos(φ) ]
	[   0       1     λ·sin(φ) ] 

Result
	[ cos(α)+λcos(φ)sin(γ)sin(α)		-sin(α)+λcos(φ)sin(γ)cos(α)
													λcos(φ)cos(γ)			]
	[ cos(γ)sin(α)+λsin(φ)sin(γ)sin(α)	cos(γ)cos(α)+λsin(φ)sin(γ)cos(α)
													-sin(γ)+λsin(φ)cos(γ)	]
*/
t_2x3matrix	oblique_proj(t_param *p)
{
	t_2x3matrix	r;
	float		s_ga;
	float		c_ga;
	float		si_al;
	float		co_al;

	s_ga = sinf(p->roll_obl * M_PI / 2);
	c_ga = cosf(p->roll_obl * M_PI / 2);
	si_al = sinf(p->yaw_obl * M_PI / 2);
	co_al = cosf(p->yaw_obl * M_PI / 2);
	r.m11 = co_al + p->depth / 6. * cosf(p->skew * PIFR) * s_ga * si_al;
	r.m12 = -si_al + p->depth / 6. * cosf(p->skew * PIFR) * s_ga * co_al;
	r.m13 = p->depth / 6. * cosf(p->skew * PIFR) * c_ga;
	r.m21 = c_ga * si_al + p->depth / 6. * sinf(p->skew * PIFR) * s_ga * si_al;
	r.m22 = c_ga * co_al + p->depth / 6. * sinf(p->skew * PIFR) * s_ga * co_al;
	r.m23 = -s_ga + p->depth / 6. * sinf(p->skew * PIFR) * c_ga;
	return (r);
}
