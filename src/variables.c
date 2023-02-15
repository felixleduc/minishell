/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:42 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/15 14:45:05 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    delete_var(t_vars *vars, int start, int end)
{
    char    *tmp1;
    char    *tmp2;

    tmp1 = ft_substr(vars->piped[vars->parse.nb_arg], 0, start);
    tmp2 = ft_substr(vars->piped[vars->parse.nb_arg], end + 1, ft_strlen(vars->piped[vars->parse.nb_arg]) - 1);
    free(vars->piped[vars->parse.nb_arg]);
    vars->piped[vars->parse.nb_arg] = ft_strjoin(tmp1, tmp2);
    free(tmp1);
    free(tmp2);
}

void    change_var(t_vars *vars, int env_line, int start, int end)
{
    int     i;
    char    *tmp1;
    char    *tmp2;
    char    *tmp3;

    i = 0;
    while (vars->env[env_line][i] != '=')
        ++i;
    ++i;
    tmp1 = ft_substr(vars->piped[vars->parse.nb_arg], 0, start);
    tmp2 = ft_substr(vars->env[env_line], i, ft_strlen(vars->env[env_line]) - i);
    tmp3 = ft_strjoin(tmp1, tmp2);
    free(tmp1);
    free(tmp2);
    tmp1 = ft_substr(vars->piped[vars->parse.nb_arg], end + 1, ft_strlen(vars->piped[vars->parse.nb_arg]) - 1);
    free(vars->piped[vars->parse.nb_arg]);
    vars->piped[vars->parse.nb_arg] = ft_strjoin(tmp3, tmp1);
    free(tmp1);
    free(tmp3);
}

void    find_var(t_vars *vars, int start, int end)
{
    char    *var;
    char    *tmp;
    int     x;

    tmp = ft_substr(vars->piped[vars->parse.nb_arg], start + 1, end - start);
    var = ft_strjoin(tmp, "=");
    free(tmp);
    x = -1;
    while (vars->env[++x])
    {
        if (ft_strnstr(vars->env[x], var, ft_strlen(var)))
        {
            change_var(vars, x, start, end);
            return ;
        }
    }
    delete_var(vars, start, end);
}

void    get_var(t_vars *vars, int index)
{
    int start;

    start = index;
    if (vars->piped[vars->parse.nb_arg][index + 1]
        && (vars->piped[vars->parse.nb_arg][index + 1] >= '0'
        && vars->piped[vars->parse.nb_arg][index + 1] <= '9'))
    {
        delete_var(vars, start, index);
        return ;
    }
    while (vars->piped[vars->parse.nb_arg][index + 1]
        && ((vars->piped[vars->parse.nb_arg][index + 1] >= 'a' && vars->piped[vars->parse.nb_arg][index + 1] <= 'z')
        || (vars->piped[vars->parse.nb_arg][index + 1] >= 'A' && vars->piped[vars->parse.nb_arg][index + 1] <= 'Z')
        || (vars->piped[vars->parse.nb_arg][index + 1] >= '0' && vars->piped[vars->parse.nb_arg][index + 1] <= '9')
        || vars->piped[vars->parse.nb_arg][index + 1] == '_'))
        ++index;
    find_var(vars, start, index);
}

void    variables(t_vars *vars)
{
    int j;

    vars->parse.nb_arg = -1;
    while (vars->piped[++vars->parse.nb_arg])
    {
        j = -1;
        if (vars->piped[vars->parse.nb_arg][j + 1] == '\'')
        {
            rm_quotes(vars, "'");
            continue ;
        }
        if (vars->piped[vars->parse.nb_arg][j + 1] == '"')
            rm_quotes(vars, "\"");
        while (vars->piped[vars->parse.nb_arg][++j])
        {
            if ((vars->piped[vars->parse.nb_arg][j] == '$' && !vars->piped[vars->parse.nb_arg][j + 1])
                || (vars->piped[vars->parse.nb_arg][j] == '$' && vars->piped[vars->parse.nb_arg][j + 1]
                && (vars->piped[vars->parse.nb_arg][j + 1] == 32 || (vars->piped[vars->parse.nb_arg][j] >= 9
                && vars->piped[vars->parse.nb_arg][j] <= 13))))
                break ;
            else if (vars->piped[vars->parse.nb_arg][j + 1] && vars->piped[vars->parse.nb_arg][j] == '$'
                && vars->piped[vars->parse.nb_arg][j + 1] == '?')
            {
                get_var(vars, j);
                j = -1;
            }
            else if (vars->piped[vars->parse.nb_arg][j] == '$')
            {
                get_var(vars, j);
                j = -1;
            }
        }
    }
}
