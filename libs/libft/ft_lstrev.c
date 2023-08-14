/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 04:36:56 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/14 04:49:31 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Reverses a chained list
void	ft_lstrev(t_list **lst)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	if (lst == NULL || *lst == NULL)
		return ;
	prev = NULL;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*lst = prev;
}
