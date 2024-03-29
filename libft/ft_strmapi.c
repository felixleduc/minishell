/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:06:51 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/17 11:54:26 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (s == NULL || f == NULL)
		return (0);
	str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (str == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, (char)s[i]);
		i++;
	}
	return (str);
}
