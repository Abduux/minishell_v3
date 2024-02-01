/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 16:34:37 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	init_data(char **env, t_data *data)
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

void	minishell_cycle(t_data *data, int ac, char **av)
{
	char		*line;

	(void)ac;
	(void)av;
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

	init_data(env, &data);
	minishell_cycle(&data, ac, av);
	return (0);
}
