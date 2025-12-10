/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:06:35 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/01 22:34:15 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINALG_H
# define LINALG_H

typedef struct s_2d_vector
{
	float	u;
	float	v;
}				t_2dv;
// [u]
// [v]

typedef struct s_3d_vector
{
	float	x;
	float	y;
	float	z;
}				t_3dv;
// [x]
// [y]
// [z]

typedef struct s_2x3_matrix
{
	float	m11;
	float	m12;
	float	m13;
	float	m21;
	float	m22;
	float	m23;
}			t_2x3matrix;
// [m11 m12 m13]
// [m21 m22 m23]

#endif // #ifndef LINALG_H
