/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:43 by bperron           #+#    #+#             */
/*   Updated: 2023/02/22 13:37:15 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_garbage(t_vars *vars)
{
	if (vars->piped)
		free_doublearr(vars->piped);
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

	(void)argv;
	if (argc == 1)
	{
		vars.env = dup_doublearr(envp);
		vars.export_env = dup_doublearr(envp);
		vars.status = 0;
		while (1)
		{
			//signals();
			ft_readline(&vars);
			parse(&vars);
			free_garbage(&vars);
		}
		free_doublearr(vars.env);
		free_doublearr(vars.export_env);
	}
	else
		printf("Usage : ./minishell\n");
	return (0);
}
