/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 17:53:35 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_data(char **env, t_data *data)
{
	char	**export;

	save_fds(data);
	data->cmds_pids = NULL;
	tcgetattr(STDIN_FILENO, &data->term_attr);
	data->input = NULL;
	data->prompt = ft_strdup("\x1b[1;34m""\x1b[1;34mMinishell v2.0$" "\x1b[0m"" ─> ");
	export = ft_strsdup(env);
	data->env_list = get_env_list(env);
	data->export_list = get_export_list(export);
	free_strs(export);
	increase_shlvl(data->env_list);
	increase_shlvl(data->export_list);
	add_env(&data->env_list, "?", "0");
	handle_signals();
}

static void	display_prompt(t_data *data)
{
	char		*line;

	line = readline(data->prompt);
	while (line != NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &data->term_attr);
		data->syntax_error = 0;
		data->input = parser(line, data);
		if (line[0])
			add_history(line);
		free(line);
		if (data->input)
			execution(data);
		parse_free(data->input);
		line = readline(data->prompt);
	}
	clear_history();
	data->input = NULL;
	free_all(data);
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if(ac != 1 || !av)
		return(ft_printf_fd(STDERR_FILENO, "Usage : <./minishell> \n"));
	init_data(env, &data);
	minishell_cycle(&data);	
	return (0);
}
