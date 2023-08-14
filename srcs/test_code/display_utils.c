/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 05:20:42 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/14 05:22:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_map(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		printf("%s", (char *)(cur->data));
		cur = cur->next;
	}
}
