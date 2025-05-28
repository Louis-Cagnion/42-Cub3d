/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:47:14 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/28 16:49:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		if (cur->data && del)
			del(cur->data);
		prev = cur;
		cur = cur->next;
		free(prev);
	}
	*lst = NULL;
}
