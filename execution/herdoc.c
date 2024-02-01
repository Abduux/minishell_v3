/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:39:16 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:29:10 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	herdoc_signal_handler(pid_t signal)
{
	printf("\n");
	exit(signal + 128);
}

int	exec_herdoc(t_redirection *herdoc, t_data *data)
{
	char	*line;

	close(herdoc->pipe[0]);
	signal(SIGINT, herdoc_signal_handler);
	line = readline("> ");
	while (ft_strncmp(line, herdoc->file_name, INT_MAX) != 0)
	{
		line = evaluate(line, data, IS_INSIDE_HERDOC);
		write(herdoc->pipe[1], line, ft_strlen(line));
		write(herdoc->pipe[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(herdoc->pipe[1]);
	free_and_exit(0, data);
	printf("Exit Herdoc\n");
	return (0);
}

int	save_herdoc_data(t_redirection *herdoc, t_data *data)
{
	pid_t	pid;
	int		status;

	if (pipe(herdoc->pipe) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec_herdoc(herdoc, data);
	close(herdoc->pipe[1]);
	waitpid(pid, &status, 0);
	set_exit_status(&data->env_list, exit_status(status));
	if (WEXITSTATUS(status) != 0)
		return (-1);
	return (0);
}

int	open_herdocs(t_input *input, t_data *data)
{
	t_redirection	*tmp_red;

	tmp_red = input->redirect;
	while (tmp_red)
	{
		if (tmp_red->type == REDIR_HEREDOC)
		{
			if (save_herdoc_data(tmp_red, data) != 0)
				return (-1);
		}
		tmp_red = tmp_red->next;
	}
	return (0);
}

int	run_herdocs(t_input *inputs, t_data *data)
{
	signal(SIGINT, dont_quit);
	while (inputs)
	{
		if (open_herdocs(inputs, data) != 0)
		{
			handle_signals();
			return (-1);
		}
		inputs = inputs->next;
	}
	handle_signals();
	return (0);
}
