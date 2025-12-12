/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:56:57 by marhuber          #+#    #+#             */
/*   Updated: 2025/11/07 10:26:39 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include "main.h"

int	ft_printf(const char *s, ...);

static void	disp(int n)
{
	int	n0;

	n0 = n;
	FT("\n");
	while (n)
	{
		FT("-");
		n--;
	}
	FT("\t\t%d\n", n0);
}

int	main(void)
{
	int	k;
	int	i;
	int	*p;

	disp(FT("Hello and more, thats %d%% what I call %s!", 100, "amore"));
	i = 1;
	while (i < 6000)
	{
		disp(FT("Let's take %d (dec), it gives %X (hexa). Seemingly,  %d (dec) is %X (hexa) ", i, i, INT_MAX / i, INT_MAX / i));
		if (-10 < i && i < 10)
			i++;
		else if (-100 < i && i < 100)
			i += 10;
		else if (-1000 < i && i < 1000)
			i += 100;
		else
			i += 1000;
	}
	i = INT_MIN;
	disp(FT("Let's take %d (dec), it gives %X (hexa).", i, i));
	i = INT_MAX;
	disp(FT("Let's take %d (dec), it gives %X (hexa).", i, i));
	i = 0;
	disp(FT("Let's take %d (dec), it gives %u (u) and %X (hexa).", i, i, i));
	i = -1;
	disp(FT("Let's take %d (dec), it gives %u (u) and %X (hexa).", i, i, i));
	i = -9;
	disp(FT("Let's take %d (dec), it gives %u (u) and %X (hexa).", i, i, i));
	i = 32;
	while (i < 128)
	{
		FT("%c %i\t%x %X\t\t", i, i, i, i);
		i++;
		if (!(i % 4))
			FT("\n");
	}
	p = &i;
	disp(FT("i is stored at %p", p));
	p = &k;
	disp(FT("k is stored at %p", p));
	p = NULL;
	disp(FT("A NULL pointer gives %p and nothing else", p));
	disp(FT("A NULL string  gives %s and nothing else", (char *)p));
	disp(FT("how big? ull: %d, ptr: %d.", (int)sizeof(unsigned long long int), (int)sizeof(void *)));
}
