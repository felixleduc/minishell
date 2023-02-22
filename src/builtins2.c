/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:04:03 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/22 13:50:41 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
        vars->status = 1;
        printf("cd: %s: No such file or directory\n", vars->args[1]);
    }
}

int parse_flag(t_vars *vars, int i)
{
    int j;

    j = 0;
    if (!vars->args[1])
        return (0);
    if (vars->args[i])
    {
        if (vars->args[i][0] != '-')
            return (0);
        while (vars->args[i][++j])
            if (vars->args[i][j] != 'n')
                return (0);
    }
    return (1);
}

void    ft_echo(t_vars *vars)
{
    int i;
    int n;
    int last;

    i = 1;
    n = parse_flag(vars, i);
    last = n;
    while (last && vars->args[++i])
    {
        if (last)
            last = parse_flag(vars, i);
        else
            break ;
    }
    while (vars->args[i])
    {
        printf("%s", vars->args[i]);
        if (vars->args[i + 1])
            printf(" ");
        ++i;
    }
    if (!n)
        printf("\n");
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
