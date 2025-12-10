/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:00:12 by marhuber          #+#    #+#             */
/*   Updated: 2025/11/17 23:46:34 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*re;

	re = malloc(sizeof(t_list));
	if (!re)
		return (0);
	re->content = content;
	re->next = 0;
	return (re);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*it;

	while (*lst)
	{
		it = *lst;
		*lst = (*lst)->next;
		(*del)(it->content);
		it->content = 0;
		free(it);
		it = 0;
	}
}

void	lstclfr(void *lst)
{
	ft_lstclear((t_list **)&lst, &free);
}
