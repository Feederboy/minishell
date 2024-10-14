/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 23:40:58 by mguerra           #+#    #+#             */
/*   Updated: 2022/06/29 10:30:20 by mguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/ft_printf.h"
# include "../lib/libft/includes/get_next_line.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

# define PROMPT "minishell: " 
# define CODE_GENERAL 1
# define READ_MODE 0
# define TRUNCATE_MODE 1
# define APPEND_MODE 2
# define DEFAULT_PATH_MSG "I've detected you launched me with an empty \
environment, I've made one for you.\n"
# define DEFAULT_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:\
/bin:/usr/games:/usr/local/games:/snap/bin"
# define PWD_ERROR "pwd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory"

typedef struct s_cmd
{
	int				index;
	t_list			*args;
	char			*input;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				heredoc;
	char			*output;
	int				pipe[2];
	int				append;
	char			*bin;
	int				builtin;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_cmd			*command;
	t_cmd			*prev;
	char			***commands;
	char			*line;
	int				c_count;
	int				last_exit_code;
	int				init;
	int				env_init;
	int				pid;
	char			*tmpcmd;
	int				merge;
	t_list			*parsing;
	t_list			*tmp;
	t_env			*env;
	char			**av;
}	t_data;

typedef enum e_builtin
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
}	t_builtin;

typedef void	(*t_builtin_exec)(t_cmd *cmd);

void		set_redirections(t_cmd *cmd);
char		**get_env_array_ft(void);
char		**get_env_array(void);
char		*check_io(t_cmd *cmd, char c, int next);
char		*expand_vars_heredoc(char *s);
char		*expand_vars(char *s);
char		*get_env_key(char *s);
char		*get_env(char *key);
char		*replace_vars(char *s);
char		*str_join_recursive(char **strs, char *sep);
char		*trim_space(char *s);
char		*join_previous(char *s);
int			builtin_bypass(t_cmd *command);
int			count_env(t_env *lst);
int			file_open(char *file, int flag);
int			is_allowed_redir_name(char *s);
int			is_builtin(t_cmd *cmd);
int			is_new_line_flag(char *s);
int			is_new_line_flag(char *s);
int			is_valid_key(char *s);
int			parse(void);
int			prompt_gnl(void);
int			prompt(void);
int			str_equals(char *s1, char *s2);
t_cmd		*create_command(void);
t_data		*data(void);
t_env		*create_env_list(char *env);
void		add_env_list(t_env **env, t_env *next);
void		cd(t_cmd *cmd);
void		clean_exit(void);
void		close_fd_command(t_cmd *cmd);
void		close_fds(void);
void		command_not_found(char *s);
void		echo(t_cmd *cmd);
void		env(t_cmd *cmd);
void		error_file(char*s);
void		error_prefix(char *s);
void		error_prompt(char *s, int code);
void		exec_builtin(t_cmd *cmd);
void		exec_command(t_cmd *command);
void		execute(void);
void		expand_var(char **res, char *s, int *i);
void		expand(void);
void		export_builtin(t_cmd *cmd);
void		export_error(char *key);
void		extract_data(t_cmd *cmd);
void		go_next(int i);
void		heredoc(t_cmd *cmd);
void		init_env(char	**envp);
void		init_handlers_child(void);
void		init_handlers(void);
void		minishell_exit(t_cmd *cmd);
void		parse_io(t_cmd *cmd, char c);
void		parse_redirections(t_cmd *cmd, char *s, char c, int mode);
void		prepare_command(t_cmd *command);
void		pwd(t_cmd *cmd);
void		set_append_mode(t_cmd *cmd, char *s, int mode);
void		set_defaults_env(void);
void		set_env(char *key, char *value);
void		set_heredoc_mode(t_cmd *cmd, char *s, int mode);
void		set_io(t_cmd *cmd);
void		sigint_handler(int code);
void		sigquit_handler(int code);
void		unset(t_cmd *cmd);
void		extract_commands(void);
void		extract_quotes(char *cmd, char c);
void		init_command(int i);
void		set_exit_code(int code);
void		get_next_quoted_string(void);
void		swap_fd(int fd1, int fd2);
char		*get_absolute_path(t_cmd *cmd);
void		closep(int fd, int i);
void		command_not_found(char *s);

#endif
