/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:21:00 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/21 10:28:53 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int    get_pipes(t_vars *vars)
{
    int i;

    i = -1;
    while (vars->piped[++i])
    {
        if ((i == 0 && ft_strcmp(vars->piped[i], "|") == 0)
            || (vars->piped[i + 1] && ft_strcmp(vars->piped[i], "|") == 0 && ft_strcmp(vars->piped[i + 1], "|") == 0)
            ||  (!vars->piped[i + 1] && ft_strcmp(vars->piped[i], "|") == 0))
        {
            printf("minishell: syntax error near unexpected token '|'\n");
            return (1);
        }
        if (ft_strcmp(vars->piped[i], "|") == 0)
            ++vars->nb_pipes;
    }
    return (0);
}

void    sep_pipes(t_vars *vars)
{
    int i;
    int j;
    int start;

    i = 0;
    j = -1;
    start = ++vars->nb_piped;
    while (vars->piped[vars->nb_piped]
        && ft_strcmp(vars->piped[vars->nb_piped], "|") != 0)
    {
        ++i;
        ++vars->nb_piped;
    }
    vars->args = ft_calloc(i + 1, sizeof(char *));
    while (++j < i)
        vars->args[j] = ft_strdup(vars->piped[j + start]);
    i = -1;
}

void    find_path(t_vars *vars)
{
    char    **sep_path;
    char    *slash_path;
    int     i;

    i = -1;
    if (vars->args[0][0] == '/')
    {
        vars->path = ft_strdup(vars->args[0]);
        return ;
    }
    while (vars->env[++i])
    {
		if (ft_strnstr(vars->env[i], "PATH=", 5) != NULL)
		{
            sep_path = ft_split(vars->env[i] + 5, ':');
            i = -1;
            while (sep_path[++i])
            {
                slash_path = ft_strjoin(sep_path[i], "/");
                vars->path = ft_strjoin(slash_path, vars->args[0]);
                free(slash_path);
                if (access(vars->path, F_OK) == 0)
                {
                    free_doublearr(sep_path);
                    return ;
                }
                free(vars->path);
                vars->path = NULL;
            }
            free_doublearr(sep_path);
            return ;
        }
    }
}

void    do_exec(t_vars *vars, int nb)
{
    int fd[2];

    if (pipe(fd) == -1)
        return ;
    vars->pids[nb] = fork();
    if (vars->pids[nb] < 0)
    {
        perror("fork");
        exit(1);
    }
    if (vars->pids[nb] == 0)
    {
        if (nb < vars->nb_pipes)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
        }
        execve(vars->path, vars->args, vars->env);
        perror(vars->args[0]);
        exit(1);
    }
    if (nb < vars->nb_pipes)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
    }
}

void    do_exec_solo(t_vars *vars)
{
    vars->pids[0] = fork();
    if (vars->pids[0] == 0)
    {
        execve(vars->path, vars->args, vars->env);
        perror(vars->args[0]);
        exit(1);
    }
    waitpid(vars->pids[0], &vars->status, 0);
}

void    do_pipes(t_vars *vars)
{
    int i;

    i = 0;
    if (get_pipes(vars))
        return ;
    vars->pids = ft_calloc(vars->nb_pipes + 2, sizeof(pid_t));
    while (i <= vars->nb_pipes)
    {
        sep_pipes(vars);
        if (redirections(vars))
        {
            free_doublearr(vars->args);
            ++i;
            continue ;
        }
        if (built_in(vars))
        {
            free_doublearr(vars->args);
            ++i;
            continue ;
        }
        find_path(vars);
        if (vars->nb_pipes == 0)
            do_exec_solo(vars);
        else
            do_exec(vars, i);
        if (vars->path != NULL)
            free(vars->path);
        free_doublearr(vars->args);
        ++i;
    }
    i = -1;
    while (++i <= vars->nb_pipes)
        waitpid(vars->pids[i], &vars->status, 0);
}

void    dup_for_exec(t_vars *vars)
{
    int save_in;
    int save_out;

    save_in = dup(STDIN_FILENO);
    save_out = dup(STDOUT_FILENO);
    do_pipes(vars);
    dup2(save_in, STDIN_FILENO);
    dup2(save_out, STDOUT_FILENO);
}
