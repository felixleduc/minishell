/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:50:10 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/20 10:41:05 by fleduc           ###   ########.fr       */
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

void    print_export(t_vars *vars)
{
    int     i;
    int     j;
    char    *tmp;

    i = -1;
    while (vars->export_env[++i])
    {
        j = 0;
        printf("declare -x ");
        while (vars->export_env[i][j]
            && vars->export_env[i][j] != '=')
            ++j;
        tmp = ft_substr(vars->export_env[i], 0, j);
        printf("%s", tmp);
        free(tmp);
        if (j != (int)ft_strlen(vars->export_env[i]))
        {
            tmp = ft_substr(vars->export_env[i], j + 1,
                ft_strlen(vars->export_env[i]) - j - 1);
            printf("=\"%s\"", tmp);
            free(tmp);
        }
        printf("\n");
    }
}

int check_export(t_vars *vars, int i)
{
    int j;

    j = 0;
    if ((vars->args[i][j] < 'a' || vars->args[i][j] > 'z')
        && (vars->args[i][j] < 'A' || vars->args[i][j] > 'Z')
        && vars->args[i][j] != '_')
        return (0);
    ++j;
    while (vars->args[i][j] && vars->args[i][j] != '=')
    {
        if ((vars->args[i][j] < 'a' || vars->args[i][j] > 'z')
            && (vars->args[i][j] < 'A' || vars->args[i][j] > 'Z')
            &&  (vars->args[i][j] < '0' || vars->args[i][j] > '9')
            && vars->args[i][j] != '_')
            return (0);
        ++j;
    }
    return (1);
}

int check_if_exist(t_vars *vars, char **arr, int i)
{
    char    *tmp;
    int     exist;
    int     j;

    exist = -1;
    j = 0;
    while (vars->args[i][j] && vars->args[i][j] != '=')
        ++j;
    if (j != (int)ft_strlen(vars->args[i]))
    {
        tmp = ft_substr(vars->args[i], 0, j);
        j = -1;
        while (arr[++j])
            if (ft_strncmp(tmp, arr[j], ft_strlen(tmp)) == 0)
                exist = j;
    }
    return (exist);
}

void    add_to_export_env(t_vars *vars, int env_i, int i)
{
    char    **tmp;
    int     j;

    j = 0;
    while (vars->args[i][j] && vars->args[i][j] != '=')
        ++j;
    if (j != (int)ft_strlen(vars->args[i]) && env_i != -1)
    {
        free(vars->export_env[env_i]);
        vars->export_env[env_i] = ft_strdup(vars->args[i]);
    }
    else
    {
        tmp = addback_doublearr(vars->export_env, vars->args[i]);
        free_doublearr(vars->export_env);
        vars->export_env = dup_doublearr(tmp);
        free_doublearr(tmp);
    }
}

void    add_to_env(t_vars *vars, int env_i, int i)
{
    char    **tmp;
    int     j;

    j = 0;
    while (vars->args[i][j] && vars->args[i][j] != '=')
        ++j;
    if (j != (int)ft_strlen(vars->args[i]))
    {
        if (env_i != -1)
        {
            free(vars->env[env_i]);
            vars->env[env_i] = ft_strdup(vars->args[i]);
        }
        else
        {
            tmp = addback_doublearr(vars->env, vars->args[i]);
            free_doublearr(vars->env);
            vars->env = dup_doublearr(tmp);
            free_doublearr(tmp);
        }
    }
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
            printf("export: %s: not a valid identifier\n", vars->args[i]);
    }
    if (!vars->args[1])
        print_export(vars);
}

int parse_flag(t_vars *vars, int i)
{
    int j;

    j = 0;
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
    while (vars->args[i + 1])
    {
        printf("%s ", vars->args[i]);
        ++i;
    }
    if (n)
        printf("%s", vars->args[i]);
    else
        printf("%s\n", vars->args[i]);
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
