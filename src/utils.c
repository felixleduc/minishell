/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:21:43 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/20 09:54:52 by fleduc           ###   ########.fr       */
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

void    free_doublearr(char **arr)
{
    int i;

    i = 0;
    if (arr)
    {
        while (arr[i])
        {
            free(arr[i]);
            ++i;
        }
        free(arr);
    }
}

char    **dup_doublearr(char **arr)
{
    char    **new;
    int i;

    i = 0;
    while (arr[i])
        ++i;
    new = ft_calloc(i + 1, sizeof(char *));
    i = -1;
    while (arr[++i])
        new[i] = ft_strdup(arr[i]);
    return (new);
}

char    **addback_doublearr(char **arr, char *value)
{
    char    **new;
    int     i;
    
    i = 0;
    while (arr[i])
        ++i;
    new = ft_calloc(i + 2, sizeof(char *));
    i = -1;
    while (arr[++i])
        new[i] = ft_strdup(arr[i]);
    new[i] = ft_strdup(value);
    return (new);
}
