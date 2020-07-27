/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:01:40 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/09 15:28:24 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Iterates the list ’lst’ and applies the function ’f’ to the content of each
** element. Creates a new list resulting of the successive applications of
** the function ’f’. The ’del’ function is used to delete the content
** of an element if needed.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*element;

	if (!lst || !f || !del)
		return (NULL);
	if (!(element = ft_lstnew(f(lst->content))))
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	lst_new = element;
	lst = lst->next;
	while (lst)
	{
		if (!(element = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&lst_new, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&lst_new, element);
	}
	return (lst_new);
}
