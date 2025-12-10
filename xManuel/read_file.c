/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:54:12 by marhuber          #+#    #+#             */
/*   Updated: 2025/12/03 09:43:48 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "main.h"

/* returns the next line or NULL if error or end of file */
char	*get_next_line(int fd);
/* populates map with the vectors implied by the input table */
int		fill_map(t_param *pars, t_list *line);
/* Displays the string pointed to by s followed by a newline */
void	putendl(const char *s);

/* tests whether a caracter is space, tab or newline */
static int	space_like(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

static char	*strdupse(const char *start, const char *end)
{
	char	*dup;
	char	*it;

	dup = malloc(sizeof(*dup) * (end - start + 1));
	if (dup == 0)
		return (0);
	it = dup;
	while (start < end)
	{
		*it = *start;
		it++;
		start++;
	}
	*it = 0;
	return (dup);
}

/* Walks through a string and copies substrings into a list */
static int	list_entries(t_list **ptrsublist, int *x, char *str)
{
	t_list	e0;
	t_list	*list_end;
	char	*entry_start;

	e0.next = 0;
	list_end = &e0;
	while (*str)
	{
		while (space_like(*str))
			str++;
		entry_start = str;
		while (*str && !space_like(*str))
			str++;
		if (str > entry_start)
		{
			list_end->next = ft_lstnew(strdupse(entry_start, str));
			if (!list_end->next || !list_end->next->content)
				return (1);
			list_end = list_end->next;
			++*x;
		}
	}
	*ptrsublist = e0.next;
	return (0);
}

/* walks through the file reading line by line, creating a new sublist */
static int	read_lines_into_list(t_param *pars, t_list **ptrlines, int fd)
{
	t_list	e0;
	t_list	*list_end;
	char	*new_line;
	t_list	*sublist;
	int		x;

	e0.next = 0;
	list_end = &e0;
	new_line = get_next_line(fd);
	while (new_line)
	{
		x = 0;
		if (list_entries(&sublist, &x, new_line))
			return (1);
		list_end->next = ft_lstnew(sublist);
		if (!list_end->next)
			return (1);
		list_end = list_end->next;
		pars->rows++;
		if (x > pars->cols)
			pars->cols = x;
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (*ptrlines = e0.next, 0);
}

int	read_input(t_param *pars, int fd)
{
	t_list		*lines;

	pars->cols = 0;
	pars->rows = 0;
	if (read_lines_into_list(pars, &lines, fd))
		return (putendl("malloc err"), ft_lstclear(&lines, &lstclfr), 1);
	pars->map = malloc(sizeof(*pars->map) * pars->cols * pars->rows);
	if (!pars->map)
	{
		free(pars->map);
		return (putendl("malloc err"), ft_lstclear(&lines, &lstclfr), 1);
	}
	if (fill_map(pars, lines))
	{
		free(pars->map);
		return (putendl("format err"), ft_lstclear(&lines, &lstclfr), 1);
	}
	ft_lstclear(&lines, &lstclfr);
	return (0);
}
