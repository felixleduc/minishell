/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:36:56 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/22 12:52:30 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    status_var(t_vars *vars, int index)
{
    char    *nb;
    char    *tmp1;
    char    *tmp2;
    char    *tmp3;

    nb = ft_itoa(vars->status);
    tmp1 = ft_substr(vars->piped[vars->parse.nb_arg], 0, index);
    tmp2 = ft_substr(vars->piped[vars->parse.nb_arg], index + 2, ft_strlen(vars->piped[vars->parse.nb_arg]) - index);
    tmp3 = ft_strjoin(tmp1, nb);
    free(tmp1);
    free(vars->piped[vars->parse.nb_arg]);
    vars->piped[vars->parse.nb_arg] = ft_strjoin(tmp3, tmp2);
    free(tmp3);
    free(tmp2);
    free(nb);
}
