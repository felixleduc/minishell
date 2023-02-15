/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:52:30 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/15 10:55:49 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_d_i(int nb)
{
	int		n;
	int		ret;

	ret = 0;
	n = nb;
	if (nb < 0)
		ret++;
	else if (nb == 0)
		ret++;
	while (nb > 0 || nb < 0)
	{
		++ret;
		nb /= 10;
	}
	ft_putnbr_fd(n, 1);
	return (ret);
}
