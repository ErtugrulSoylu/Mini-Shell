/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoylu <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 05:52:32 by esoylu            #+#    #+#             */
/*   Updated: 2022/01/10 06:28:59 by esoylu           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*head;

	if (!lst)
		return (0);
	head = ft_lstnew(f(lst->content));
	node = head;
	while (lst)
	{
		if (node == 0)
		{
			while (head)
			{
				del(head->content);
				free(head);
				head = head->next;
			}
			return (0);
		}
		lst = lst->next;
		if (lst)
			node->next = ft_lstnew(f(lst->content));
		node = node->next;
	}
	return (head);
}
