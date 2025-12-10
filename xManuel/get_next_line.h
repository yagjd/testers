/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:00:12 by marhuber          #+#    #+#             */
/*   Updated: 2025/10/31 17:53:44 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif // # ifndef BUFFER_SIZE

typedef struct s_buffer_state
{
	char *const	start;
	const char	*pos;
	const char	*end;
}				t_bufferstate;

typedef struct s_new_line
{
	char	*cont;
	int		len;
}			t_nl;

char	*get_next_line(int fd);
int		read_buf(int fd, t_bufferstate *bs, t_nl *ptrnl);

#endif // #ifndef GET_NEXT_LINE
