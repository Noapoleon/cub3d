/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:22:02 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/14 04:35:33 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*tmp;

	if (lst && *lst && del)
	{
		curr = *lst;
		while (curr != NULL)
		{
			tmp = curr;
			curr = curr->next;
			(*del)(tmp->data);
			free(tmp);
		}
		*lst = NULL;
	}
}
