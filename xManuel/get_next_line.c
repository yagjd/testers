/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:57:26 by marhuber          #+#    #+#             */
/*   Updated: 2025/10/31 18:20:48 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char				buf[BUFFER_SIZE];
	static t_bufferstate	state = {buf, buf, buf};
	t_nl					nl;
	int						done;

	nl.cont = malloc(sizeof(*nl.cont));
	if (!nl.cont)
		return (0);
	*nl.cont = 0;
	nl.len = 0;
	done = 0;
	while (!done)
	{
		done = read_buf(fd, &state, &nl);
		if (done == -1)
			return (free(nl.cont), NULL);
	}
	if (done == 2 && *nl.cont == 0)
		return (free(nl.cont), NULL);
	return (nl.cont);
}
