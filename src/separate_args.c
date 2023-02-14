/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:35:48 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/14 13:48:16 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    to_piped(t_vars *vars, char **tmp)
{
    int i;

    i = -1;
    if (vars->piped)
    {
        while (vars->piped[++i])
            free(vars->piped[i]);
        free(vars->piped);
    }
    vars->piped = ft_calloc(vars->parse.word + 1, sizeof(char *));
    i = 0;
    while (i < vars->parse.word)
    {
        vars->piped[i] = ft_strdup(tmp[i]);
        ++i;
    }
}

void    allocate(t_vars *vars, int start, int end)
{
    int     i;
    char    **tmp;

    tmp = ft_calloc(vars->parse.word + 1, sizeof(char *));
    i = 0;
    if (vars->piped)
    {
        while (vars->piped[i])
        {
            tmp[i] = ft_strdup(vars->piped[i]);
            ++i;
        }
    }
    while (i < vars->parse.word)
    {
        tmp[i] = ft_substr(vars->cmd, start, (end - start) + 1);
        ++i;
    }
    to_piped(vars, tmp);
    i = -1;
    while (tmp[++i])
        free(tmp[i]);
    free(tmp);
}

void    quotes(t_vars *vars, int *i, char quote)
{
    int start;

    start = *i;
    vars->parse.word += 1;
    while (vars->cmd[++(*i)])
    {
        if (vars->cmd[*i] == quote)
        {
            allocate(vars, start, *i);
            break ;
        }
    }
}

void    pipes_redirs(t_vars *vars, int *i, int start)
{
    if (vars->cmd[*i + 1] && (vars->cmd[*i] == '<' || vars->cmd[*i] == '>')
            && (vars->cmd[*i + 1] == '<' || vars->cmd[*i + 1] == '>'))
    {
        allocate(vars, start, *i + 1);
        ++(*i);
    }
    else if (vars->cmd[*i] == '<' || vars->cmd[*i] == '>' || vars->cmd[*i] == '|')
        allocate(vars, start, *i);
}

void    other_args(t_vars *vars, int *i)
{
    int start;

    start = *i;
    vars->parse.word += 1;
    if (vars->cmd[*i] == '|' || vars->cmd[*i] == '<' || vars->cmd[*i] == '>')
        pipes_redirs(vars, i, start);
    else
    {
        while (vars->cmd[*i + 1] && vars->cmd[*i + 1] != '|'
            && vars->cmd[*i + 1] != '>' && vars->cmd[*i + 1] != '<'
            && vars->cmd[*i + 1] != '$' && vars->cmd[*i + 1] != ' '
            && (vars->cmd[*i + 1] < 9 || vars->cmd[*i + 1] > 13))
            ++(*i);
        allocate(vars, start, *i);
    }
}
