/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:21:00 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/15 15:08:16 by fleduc           ###   ########.fr       */
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
            }
            free_doublearr(sep_path);
            return ;
        }
    }
}

void    do_exec(t_vars *vars)
{
    int fd[2];
    int pid;

    if (pipe(fd) == -1)
        return ;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        execve(vars->path, vars->args, vars->env);
        perror(vars->args[0]);
        exit(1);
    }
    waitpid(pid, 0, 0);
}

void    do_pipes(t_vars *vars)
{
    int i;

    i = 0;
    if (get_pipes(vars))
        return ;
    while (i <= vars->nb_pipes)
    {
        sep_pipes(vars);
        find_path(vars);
        do_exec(vars);

        free(vars->path);
        free_doublearr(vars->args);
        ++i;
    }
}