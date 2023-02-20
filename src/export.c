/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:02:22 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/20 13:03:05 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
