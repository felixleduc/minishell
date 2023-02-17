/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:49:20 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/17 11:53:40 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	char		*lastdest;
	const char	*source;
	const char	*lastsource;

	if (dst == NULL && src == NULL)
		return (0);
	dest = dst;
	source = src;
	lastdest = dest + (len - 1);
	lastsource = source + (len - 1);
	if (dest < source)
	{
		while (len-- > 0)
			*dest++ = *source++;
	}
	else
	{
		while (len-- > 0)
			*lastdest-- = *lastsource--;
	}
	return (dst);
}
