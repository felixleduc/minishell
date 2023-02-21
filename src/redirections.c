/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:56:23 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/21 10:44:09 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    remake_args2(t_vars *vars, int i)
{
    int j;

    j = i + 1;
    free(vars->args[i]);
    free(vars->args[i + 1]);
    while (vars->args[++j])
    {
        vars->args[i] = ft_strdup(vars->args[j]);
        free(vars->args[j]);
        ++i;
    }
    vars->args[i] = NULL;
}

void    remake_args(t_vars *vars)
{
    int i;

    i = -1;
    while (vars->args[++i])
    {
        if (ft_strcmp(vars->args[i], ">") == 0 || ft_strcmp(vars->args[i], "<") == 0
            || ft_strcmp(vars->args[i], ">>") == 0 ||ft_strcmp(vars->args[i], "<<") == 0)
        {
            remake_args2(vars, i);
            i = -1;
        }
    }
}

void    duplicate(t_vars *vars, int redirs)
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
    if (redirs != -1)
        remake_args(vars);
}

void    fd_redirs(t_vars *vars, int *redirs, int in_out)
{
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
        if (!vars->args[i + 1] && (ft_strcmp(vars->args[i], ">") == 0 
            || ft_strcmp(vars->args[i], ">>") == 0 || ft_strcmp(vars->args[i], "<") == 0
            || ft_strcmp(vars->args[i], "<<") == 0))
        {
            printf("minishell: parse error near '\\n'\n");
            return (1);
        }
        if (ft_strcmp(vars->args[i], ">") == 0)
        {
            redirs = 1;
            if (vars->redir_fd[1] != 1)
                close(vars->redir_fd[1]);
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
    duplicate(vars, redirs);
    return (0);
}
