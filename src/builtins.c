/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:50:10 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/22 13:53:29 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	built_in(t_vars *vars)
{
    if (ft_strcmp("echo", vars->args[0]) == 0)
    {
        ft_echo(vars);
        return (1);
    }
    else if (ft_strcmp("cd", vars->args[0]) == 0)
    {
        ft_cd(vars);
        return (1);
    }
    else if (ft_strcmp("pwd", vars->args[0]) == 0)
    {
        ft_pwd(vars);
        return (1);
    }
    else if (ft_strcmp("export", vars->args[0]) == 0)
    {
        ft_export(vars);
        return (1);
    }
    else if (ft_strcmp("unset", vars->args[0]) == 0)
    {
        ft_unset(vars);
        return (1);
    }
    else if (ft_strcmp("env", vars->args[0]) == 0)
    {
        ft_env(vars);
        return (1);
    }
    else if (ft_strcmp("exit", vars->args[0]) == 0)
    {
        ft_exit(vars);
        return (1);
    }
    return (0);
}

void    ft_export(t_vars *vars)
{
    int     i;

    i = 0;
    while (vars->args[++i])
    {
        if (check_export(vars, i))
        {
            add_to_env(vars, check_if_exist(vars, vars->env, i), i);
            add_to_export_env(vars, check_if_exist(vars, vars->export_env, i), i);
        }
        else
        {
            vars->status = 1;
            printf("export: %s: not a valid identifier\n", vars->args[i]);
        }
    }
    if (!vars->args[1])
        print_export(vars);
}

void    ft_exit(t_vars *vars)
{
    int     i;

    i = -1;
    printf("exit\n");
    if (vars->args[1] && vars->args[2])
    {
        vars->status = 1;
        printf("exit: too many arguments\n");
        return ;
    }
    if (vars->args[1])
    {
        while (vars->args[1][++i])
        {
            if ((vars->args[1][i] < '0' || vars->args[1][i] > '9')
                && vars->args[1][i] != '-')
            {
                printf("exit: %s: numeric argument required\n", vars->args[1]);
                free_doublearr(vars->args);
                exit(255);
            }
        }
        exit(ft_atol(vars->args[1]));
    }
    free_doublearr(vars->args);
    exit(vars->status);
}

void    ft_pwd(t_vars *vars)
{
    char    *buffer;

    buffer = ft_calloc(1000, sizeof(char));
    getcwd(buffer, 1000);
    if (buffer == NULL)
    {
        vars->status = errno;
        perror("pwd");
    }
    else
        printf("%s\n", buffer);
    free(buffer);
}

void    ft_unset(t_vars *vars)
{
    int i;
    int j;

    if (!vars->args[1])
        return ;
    i = 0;
    while (vars->args[++i])
    {
        j = -1;
        while (vars->env[++j])
        {
            if (ft_strncmp(vars->env[j], vars->args[i], ft_strlen(vars->args[i])) == 0
                && vars->env[j][ft_strlen(vars->args[i])] == '=')
            {
                free(vars->env[j]);
                while (vars->env[j + 1])
                {
                    vars->env[j] = vars->env[j + 1];
                    ++j;
                }
                vars->env[j] = NULL;
            }
        }
    }
}
