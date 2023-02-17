/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:50:10 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/17 11:42:49 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	built_in(t_vars *vars)
{
    if (ft_strncmp("echo", vars->args[0], ft_strlen(vars->args[0])) == 0)
        return (1);
    else if (ft_strncmp("cd", vars->args[0], ft_strlen(vars->args[0])) == 0)
        return (1);
    else if (ft_strncmp("pwd", vars->args[0], ft_strlen(vars->args[0])) == 0)
        return (1);
    else if (ft_strncmp("export", vars->args[0], ft_strlen(vars->args[0])) == 0)
        return (1);
    else if (ft_strncmp("unset", vars->args[0], ft_strlen(vars->args[0])) == 0)
    {
        ft_unset(vars);
        return (1);
    }
    else if (ft_strncmp("env", vars->args[0], ft_strlen(vars->args[0])) == 0)
    {
        ft_env(vars);
        return (1);
    }
    else if (ft_strncmp("exit", vars->args[0], ft_strlen(vars->args[0])) == 0)
        return (1);
    return (0);
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
        printf("env: %s: No such file or directory\n", vars->args[1]);
    else
        while (vars->env[++i])
            printf("%s\n", vars->env[i]);
}
