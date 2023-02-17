/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:56:23 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/17 10:16:28 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    remake_args2(t_vars *vars, int i, int red)
{
    char    **tmp;
    int j;
    int k;

    j = -1;
    k = 0;
    tmp = ft_calloc(i - red + 1, sizeof(char *));
    while (vars->args[k])
    {
        if (ft_strcmp(vars->args[k], ">") != 0 && ft_strcmp(vars->args[k], "<") != 0
            && ft_strcmp(vars->args[k], ">>") != 0 && ft_strcmp(vars->args[k], "<<") != 0)
            tmp[++j] = ft_strdup(vars->args[k]);
        else
        {
            if (vars->args[i + 1])
                ++k;
        }
        ++k;
    }
    free_doublearr(vars->args);
    vars->args = ft_calloc(i - red + 1, sizeof(char *));
    i = -1;
    while (tmp[++i])
        vars->args[i] = ft_strdup(tmp[i]);
    free_doublearr(tmp);
}

void    remake_args(t_vars *vars)
{
    int     i;
    int     red;

    i = -1;
    red = 0;
    while (vars->args[++i])
    {
        if (ft_strcmp(vars->args[i], ">") == 0 || ft_strcmp(vars->args[i], "<") == 0
            || ft_strcmp(vars->args[i], ">>") == 0 || ft_strcmp(vars->args[i], "<<") == 0)
        {
            if (vars->args[i + 1])
            {
                ++i;
                ++red;
            }
            ++red;
        }
    }
    remake_args2(vars, i, red);
}

void    duplicate(t_vars *vars)
{
    if (vars->redir_fd[0] != 0)
    {
        dup2(vars->redir_fd[0], STDIN_FILENO);
        close(vars->redir_fd[0]);
    }
    if (vars->redir_fd[1] != 1)
    {
        dup2(vars->redir_fd[1], STDOUT_FILENO);
        close(vars->redir_fd[1]);
    }
    remake_args(vars);
}

void    fd_redirs(t_vars *vars, int *redirs, int in_out)
{
    if (*redirs == -1)
        *redirs = 1;
    if (vars->redir_fd[in_out] != in_out)
        close(vars->redir_fd[in_out]);
}

int redirections(t_vars *vars)
{
    int i;
    int redirs;

    i = -1;
    redirs = -1;
    vars->redir_fd[0] = 0;
    vars->redir_fd[1] = 1;
    while (vars->args[++i])
    {
        if (ft_strcmp(vars->args[i], ">") == 0)
        {
            fd_redirs(vars, &redirs, 1);
            vars->redir_fd[1] = open(vars->args[i + 1],
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else if (ft_strcmp(vars->args[i], "<") == 0)
        {
            fd_redirs(vars, &redirs, 0);
            vars->redir_fd[0] = open(vars->args[i + 1],
                O_RDONLY);
            if (vars->redir_fd[0] == -1)
            {
                printf("%s: No such file or directory\n", vars->args[i + 1]);
                return (1);
            }
        }
        else if (ft_strcmp(vars->args[i], ">>") == 0)
        {
            fd_redirs(vars, &redirs, 1);
            vars->redir_fd[1] = open(vars->args[i + 1],
                O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
    }
    duplicate(vars);
    return (0);
}
