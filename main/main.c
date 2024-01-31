/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:16:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 17:54:15 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	init_data(char **env, t_data *data)
{
	char **export;

	save_fds(data);
	data->cmds_pids = NULL;
	tcgetattr(STDIN_FILENO , &data->term_attr);
	data->env = env;
	export = ft_strsdup(env);
	data->env_list = get_env_list(env);
	data->export_list = get_export_list(export);
	free_strs(export);
	increase_shlvl(data->env_list);
	increase_shlvl(data->export_list);
	add_env(&data->env_list, "?", "0");
	handle_signals();
}

void minishell_cycle(t_data *data, int ac , char **av)
{
	char	*line;
	t_input	*input_list;

	(void)ac;
	(void)av;
	line = readline(PROMPT);
	while (line != NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &data->term_attr);
		data->syntax_error = 0;
		input_list = parser(line, data);
		if(line[0])
			add_history(line);
		free(line);
		if (input_list)
			execution(input_list, data);
		parse_free(input_list);
		line = readline(PROMPT);
	}
	clear_history();
	free_all(input_list, data);
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	init_data(env, &data);
	minishell_cycle(&data, ac, av);
	return (0);
}
