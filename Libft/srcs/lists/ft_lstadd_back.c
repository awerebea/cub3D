/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 18:36:15 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/09 15:23:08 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds the element ’new’ at the end of the list.
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*element;

	element = *lst;
	if (*lst && lst)
	{
		while (element->next)
			element = element->next;
		element->next = new;
	}
	else
		*lst = new;
}
