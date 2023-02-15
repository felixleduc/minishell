/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <fleduc@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:58:41 by fleduc            #+#    #+#             */
/*   Updated: 2023/02/15 12:05:02 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_parse
{
	int	word;
	int	nb_arg;
}	t_parse;

typedef struct s_vars
{
	char			*cmd;
	char			**env;
	char			**piped;
	char			**args;
	char			*path;
	int				nb_piped;
	int				nb_pipes;
	t_parse			parse;
}	t_vars;

//minishell.c
int		main(int argc, char **argv, char **envp);
int		ft_readline(t_vars *vars);
void	free_garbage(t_vars *vars);

//parse.c
void    parse(t_vars *vars);
void    init_parse_struct(t_vars *vars);
void    separate_args(t_vars *vars);
void    trim_cmd(t_vars *vars);

//separate_args.c
void    other_args(t_vars *vars, int *i);
void    pipes_redirs(t_vars *vars, int *i, int start);
void    quotes(t_vars *vars, int *i, char quote);
void    allocate(t_vars *vars, int start, int end);
void    to_piped(t_vars *vars, char **tmp);

//variables.c
void	variables(t_vars *vars);
void    get_var(t_vars *vars, int index);
void    find_var(t_vars *vars, int start, int end);
void    change_var(t_vars *vars, int env_line, int start, int end);
void    delete_var(t_vars *vars, int start, int end);

//utils.c
void	rm_quotes(t_vars *vars, char *quotes);
void    free_doublearr(char **arr);

//pipes.c
void    do_pipes(t_vars *vars);
void    sep_pipes(t_vars *vars);
void    get_pipes(t_vars *vars);

#endif
