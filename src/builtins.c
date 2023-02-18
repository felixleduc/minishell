/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:50:10 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/18 11:37:15 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	built_in(t_vars *vars)
{
    if (ft_strcmp("echo", vars->args[0]) == 0)
        return (1);
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
        return (1);
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
        free_doublearr(vars->args);
        exit(ft_atol(vars->args[1]));
    }
    free_doublearr(vars->args);
    exit(vars->status);
}

void    change_pwd(t_vars *vars, char *old, char *new)
{
    int i;

    i = -1;
    while (vars->env[++i])
    {
        if (ft_strncmp("OLDPWD", vars->env[i], 6) == 0)
        {
            free(vars->env[i]);
            vars->env[i] = ft_strjoin("OLDPWD=", old);
        }
        else if (ft_strncmp("PWD", vars->env[i], 3) == 0)
        {
            free(vars->env[i]);
            vars->env[i] = ft_strjoin("PWD=", new);
        }
    }
}

void    ft_cd(t_vars *vars)
{
    int ret;
    char    *old;
    char    *new;

    if (!vars->args[1])
        return ;
    old = ft_calloc(1000, sizeof(char));
    new = ft_calloc(1000, sizeof(char));
    getcwd(old, 1000);
    ret = chdir(vars->args[1]);
    change_pwd(vars, old, getcwd(new, 1000));
    free(old);
    free(new);
    if (ret != 0)
    {
        vars->status = errno;
        printf("cd: %s: No such file or directory\n", vars->args[1]);
    }
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

void    ft_env(t_vars *vars)
{
    int i;

    i = -1;
    if (vars->args[1])
    {
        vars->status = 127;
        printf("env: %s: No such file or directory\n", vars->args[1]);
    }
    else
        while (vars->env[++i])
            printf("%s\n", vars->env[i]);
}
