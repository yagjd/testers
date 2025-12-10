/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:06:10 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/06 09:48:35 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_color	gradient(t_param *pars, float relative_h)
{
	t_color	c;

	c.r = relative_h * pars->hcolor.r + (1 - relative_h) * pars->lcolor.r;
	c.g = relative_h * pars->hcolor.g + (1 - relative_h) * pars->lcolor.g;
	c.b = relative_h * pars->hcolor.b + (1 - relative_h) * pars->lcolor.b;
	return (c);
}

int	shadecolor(t_color c, int count)
{
	c.r = c.r * count / (DV * DV);
	c.g = c.g * count / (DV * DV);
	c.b = c.b * count / (DV * DV);
	return (c.r << 16 | c.g << 8 | c.b);
}

static unsigned char	red(unsigned char n)
{
	if (n >= 170)
		return (255);
	if (n <= 85)
		return (255 - 3 * n);
	else
		return ((n - 85) * 3);
}

void	colorwheelpair(unsigned char n, t_color *a, t_color *b)
{
	a->r = red(n);
	a->g = red(n + 85);
	a->b = red(n + 171);
	b->r = red(n + 128);
	b->g = red(n + 213);
	b->b = red(n + 43);
}
