/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 08:55:18 by mtuomine          #+#    #+#             */
/*   Updated: 2019/10/17 09:16:52 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *head;
	t_list *node;

	if (!lst || !f)
		return (NULL);
	node = f(lst);
	if (!(res = ft_lstnew(node->content, node->content_size)))
		return (NULL);
	lst = lst->next;
	head = res;
	while (lst)
	{
		node = NULL;
		node = f(lst);
		if (!(res->next = ft_lstnew(node->content, node->content_size)))
			return (NULL);
		res = res->next;
		lst = lst->next;
	}
	return (head);
}
