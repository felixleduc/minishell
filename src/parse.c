/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:33:34 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/22 12:53:06 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    trim_cmd(t_vars *vars)
{
    char    *tmp;

    tmp = ft_strdup(vars->cmd);
    vars->cmd = ft_strtrim(tmp, "   ");
    free(tmp);
}

void    separate_args(t_vars *vars)
{
    int i;

    i = -1;
    while (vars->cmd[++i])
    {
        while (vars->cmd[i + 1] && (vars->cmd[i] == 32
                || (vars->cmd[i] >= 9 && vars->cmd[i] <= 13)))
            ++i;
        if (vars->cmd[i] == '\'')
            quotes(vars, &i, '\'');
        else if (vars->cmd[i] == '"')
            quotes(vars, &i, '"');
        else
            other_args(vars, &i);
    }
}

void    init_parse_struct(t_vars *vars)
{
    vars->piped = NULL;
    vars->parse.word = 0;
    vars->nb_piped = -1;
    vars->nb_pipes = 0;
    vars->pids = NULL;
}

void    parse(t_vars *vars)
{
    trim_cmd(vars);
    init_parse_struct(vars);
    separate_args(vars);
    if (!vars->piped)
        return ;
    variables(vars);
    vars->status = 0;
    dup_for_exec(vars);
}
