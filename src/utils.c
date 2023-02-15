/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:21:43 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/14 21:28:03 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    rm_quotes(t_vars *vars, char *quotes)
{
    char    *tmp;

    tmp = ft_strtrim(vars->piped[vars->parse.nb_arg], quotes);
    free(vars->piped[vars->parse.nb_arg]);
    vars->piped[vars->parse.nb_arg] = ft_strdup(tmp);
    free(tmp);
}
