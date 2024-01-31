/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:13:51 by ali               #+#    #+#             */
/*   Updated: 2024/01/31 17:54:21 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <linux/limits.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
# include <termios.h>
#include <fcntl.h>

extern int	g_signal;

#define ANSI_COLOR "\x1b[1;34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define IS_INSIDE_HERDOC -1
#define REDIR_INPUT 1
#define REDIR_OUTPUT 2
#define REDIR_HEREDOC 3
#define REDIR_APPEND 4
#define CMD_LEN 10
#define PROMPT ANSI_COLOR"Minishell v2.0$" ANSI_COLOR_RESET" ─> "
#define EXIT_MINISHELL 1
#define OK 0
#define ERR_CMD_NOT_FOUND 1
#define ERR_NO_SUCH_FILE 2
#define ERR_TOO_MANY_ARGS 3
#define ERR_PERM_DENIED 4
#define ERR_NUMERIC_REQUI 5
#define ERR_IS_DIR 6


typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_quotes_status
{
	int in_dobule;
	int in_single;
} t_quotes_status;

typedef struct s_redirection
{
	int				type;
	char			*file_name;
	int				pipe[2];
	struct s_redirection	*next;
}					t_redirection;

typedef struct s_input
{
	char			**args;
	t_redirection	*redirect;
	struct s_input	*next;
}					t_input;

typedef struct s_data
{
	struct termios	term_attr;
	t_env			*env_list;
	t_env			*export_list;
	pid_t			*cmds_pids;
	t_input			*input;
	int 			syntax_error;
	int				stdin;
	int 			stdout;
	int 			stderr;
}	t_data;

char*	get_cmd_path(const char *cmd, t_data *data);
void	execution(t_data *data);
int		allocate_pids(t_input *input_list, t_data *data);
void 	wait_pids(t_data* data, int running_cmds);
void    reset_fds(t_data *data);
void    save_fds(t_data *data);
void    handle_signals();
void    dont_quit(pid_t pid);
void	free_all(t_data *data);
void    free_and_exit(unsigned char status, t_data *data);
int		set_exit_status(t_env **head, int exit_status);
int		exit_status(int status);
int		allocate_pids(t_input *input_list, t_data *data);
int		run_herdocs(t_input *inputs, t_data *data);
int		ft_err_msg(int err, int err_code, char *file);
int		redir(t_redirection *redirections);
int		run_cmd(t_input *input, t_data *data);
int		is_builtin(t_input *input);
int		run_a_builtin(t_input *input, t_data *data);
int		ft_pipe(int *pipe_fd, int *piped, t_input *current_cmd);
int		arg_count(char **args);
int		is_numric(char *str);
int		valid_var_name(char *name);
int		to_join_values(char *str, int equal_index);
void	join_env(const char* key,const char* value, t_data *data , int to_join);
int		cd(t_input cmd, t_data *data);
int		echo(char **args);
int		env(t_env *env);
int		export(t_input *input, t_data *data);
int		pwd(void);
int		unset(t_data *data, t_input *input);
int		exit_(t_data *data, t_input *input);
int		is_cmd_ehco(t_input *input);

t_env *get_env_list(char **env);
t_input *parser(char *input, t_data *data);
char **get_args(char *input);
int is_whit_sp(char c, int in_dq, int in_sq);
char* evaluate_quotes(char* word, t_data *data, int re_type);
int is_pipe(char c, int inside_double_quotes, int inside_signle_quotes);
char* get_value_from_env(const char *name, t_env *env);
char* expand_variable(char** word, t_env *env);
char *get_redirection_string(int type);
t_redirection* get_redirections(char *input, t_data *data);
void process_double_quotes(t_quotes_status *qt);
void process_single_quotes(t_quotes_status *qt);
int is_redirection(char *input);
void skip_redirections(char **input);
int	is_valid_identifier_char(char c, int cur_i);
char *free_and_join(char *s1, char *variable_name, int origin_len, int* result_index);
void proccess_both_quotes(char c, t_quotes_status *qt);
char **ft_strsdup(char **strs);
char *get_var_name(char *env_var);
char *get_var_value(char *env_var);
t_env *get_env_list(char **env);
t_env *get_export_list(char **env);
void parse_free(t_input *lst);
void unexpected_token_error (t_data *data, char* near);
void unexpected_eof_error(t_data *data);
void init_qt(t_quotes_status *qt);
void copy_char_to_string(char *str, char c, int *at);
void	move_ptr_to_redir(char **input, int *redir, t_quotes_status *qt);
int	move_ptr_to_filename(char **input, int redir, t_quotes_status *qt, 
	t_data *data);
void	move_ptr_to_endfilename(char **input, t_quotes_status *qt);
int	alloc_new_redir(t_redirection **begin, t_redirection **red_list, int redir);
char	*move_ptr_and_alloc(char **input, int redir, t_quotes_status *qt,
		t_data *data);
char *evaluate(char *word, t_data *data, int r_type);
char	**from_list_to_array(t_env *env);
void	free_strs(char **strs);
void	print_env_list(t_env *env);
void	print_export_list(t_env *export);
void	print_env_array(char** env);
int		add_env(t_env **head, const char *name, const char *value);
void	delete_env(t_env **head, const char *name);
int     add_export(t_env **head, const char *name, const char *value);
void	delete_export(t_env **head, const char *name);
void	increase_shlvl(t_env *list);
void	free_env_list(t_env *head);
int should_stop_identifier(char c);

#endif
