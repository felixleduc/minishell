/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:05:23 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/15 10:53:18 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		ft_lstdelone(ptr, del);
		ptr = tmp;
	}
	*lst = NULL;
}
