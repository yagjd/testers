/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:39:35 by marhuber          #+#    #+#             */
/*   Updated: 2025/11/05 16:38:20 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

// walks throuh the buffer
// ret: 1 means found nl
int	walk(t_bufferstate *buf)
{
	while (*buf->pos != '\n' && buf->pos < buf->end)
	{
		buf->pos++;
	}
	if (buf->pos < buf->end)
	{
		buf->pos++;
		return (1);
	}
	else
		return (0);
}

int	append(t_nl *nl, const char	*src, size_t n)
{
	char	*tmp;
	char	*itnew;
	char	*itold;

	tmp = malloc(sizeof(*tmp) * (nl->len + n + 1));
	if (!tmp)
		return (1);
	itnew = tmp;
	itold = nl->cont;
	while (*itold)
	{
		*itnew = *itold;
		itnew++;
		itold++;
	}
	nl->len += n;
	while (n)
	{
		*itnew++ = *src++;
		n--;
	}
	*itnew = 0;
	free(nl->cont);
	nl->cont = tmp;
	return (0);
}

// ret 2 means, it reached end of file, -1 error while reading or malloc
int	read_buf(int fd, t_bufferstate *buf, t_nl *nl)
{
	int			nb_read;
	const char	*begin;
	int			nl_found;

	nb_read = -1;
	if (buf->pos == buf->start)
	{
		nb_read = read(fd, buf->start, BUFFER_SIZE);
		if (nb_read == 0)
			return (2);
		else if (nb_read == -1)
			return (-1);
		buf->end = buf->start + nb_read;
	}
	begin = buf->pos;
	nl_found = walk(buf);
	if (append(nl, begin, buf->pos - begin))
		return (-1);
	if (buf->pos == buf->end)
		buf->pos = buf->start;
	return (nl_found);
}
