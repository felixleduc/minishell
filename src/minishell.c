/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2023/02/16 08:39:11 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_garbage(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->piped)
	{
		while (vars->piped[i])
		{
			free(vars->piped[i]);
			++i;
		}
		free(vars->piped);
	}
	if (vars->pids)
		free(vars->pids);
	free(vars->cmd);
}

int	ft_readline(t_vars *vars)
{
	vars->cmd = readline("Minishell > ");
	if (vars->cmd == NULL)
		return (0);
	if (vars->cmd && *(vars->cmd))
		add_history(vars->cmd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void) argv;
	if (argc == 1)
	{
		int	i = -1;
		++i;
		while (1)
		{
			//signal_handling();
			vars.env = envp;
			vars.cmd = NULL;
			ft_readline(&vars);
			parse(&vars);
			free_garbage(&vars);
		}
	}
	else
		printf("Usage : ./minishell\n");
	return (0);
}
