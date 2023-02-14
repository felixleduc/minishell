/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:58:48 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/14 08:43:10 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_s;
	size_t		max;
	size_t		str_len;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start < str_len)
		max = str_len - start;
	if (start >= str_len)
		max = 0;
	if (max > len)
		max = len;
	new_s = (char *)ft_calloc(max + 1, sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s + start, max + 1);
	return (new_s);
}
