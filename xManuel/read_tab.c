/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:30:10 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/04 19:35:49 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "main.h"
#include "list.h"

static unsigned int	atoi_s(const char **str)
{
	int	n;

	n = 0;
	while ('0' <= **str && **str <= '9')
	{
		n = 10 * n + **str - '0';
		++*str;
	}
	return (n);
}

static int	atofloat(const char *str, float *f)
{
	int			sign;
	const char	*commaplace;
	int			decimal_part;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	*f = sign * (float)atoi_s(&str);
	if (*str == ',' || *str == '.')
	{
		str++;
		commaplace = str;
		decimal_part = atoi_s(&str);
		while (commaplace++ < str)
			sign *= 10;
		*f += (float)decimal_part / (float)sign;
	}
	if (*str)
		return (1);
	return (0);
}

static int	creat_v_e(t_param *pars, t_pos *pos, char *str)
{
	float	newz;

	if (atofloat(str, &newz))
		return (1);
	if (newz < pars->z_min)
		pars->z_min = newz;
	if (newz > pars->z_max)
		pars->z_max = newz;
	pos->v3->z = newz;
	pos->v3->x = pos->x - 0.5 * pars->cols + 0.5;
	pos->v3->y = pos->y - 0.5 * pars->rows + 0.5;
	pos->v3++;
	pos->x++;
	return (0);
}

static void	center(t_param *pars)
{
	float	z_middle;
	t_3dv	*v3;

	if (pars->z_max == pars->z_min)
	{
		pars->z_diff = 1;
		return ;
	}
	pars->z_diff = pars->z_max - pars->z_min;
	z_middle = pars->z_min + 0.5 * pars->z_diff;
	v3 = pars->map;
	while (v3 < pars->map + pars->rows * pars->cols)
	{
		if (isfinite(v3->x))
			v3->z -= z_middle;
		v3++;
	}
}

/* populates map with the vectors implied by the input table */
int	fill_map(t_param *pars, t_list *line)
{
	t_pos	pos;
	t_list	*entry;

	pos.v3 = pars->map;
	pos.y = 0;
	while (line)
	{
		pos.x = 0;
		entry = line->content;
		while (entry)
		{
			if (creat_v_e(pars, &pos, entry->content))
				return (1);
			entry = entry->next;
		}
		while (pos.x < pars->cols)
		{
			pos.v3++->x = NAN;
			pos.x++;
		}
		line = line->next;
		pos.y++;
	}
	center(pars);
	return (0);
}
