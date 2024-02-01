/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:27:14 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:37:59 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_cmd(t_input *input_list, t_data *data)
{
	int	status;

	status = redir(input_list->redirect);
	if (status == 0)
	{
		if (input_list->args[0])
		{
			if (is_builtin(input_list))
			{
				status = run_a_builtin(input_list, data);
				free_and_exit(status, data);
			}
			else
				run_cmd(input_list, data);
		}
	}
	free_and_exit(1, data);
}

static void	run_one_cmd_continue(t_input *input_list, t_data *data)
{
	int	pid;
	int	status;

	pid = 0;
	status = 0;
	if (is_cmd_ehco(input_list) || !is_builtin(input_list))
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			if (is_cmd_ehco(input_list))
				free_and_exit(run_a_builtin(input_list, data), data);
			else
				run_cmd(input_list, data);
		}
		waitpid(pid, &status, 0);
		set_exit_status(&data->env_list, exit_status(status));
	}
	else if (is_builtin(input_list))
		set_exit_status(&data->env_list, run_a_builtin(input_list, data));
}

static void	run_one_cmd(t_input *input_list, t_data *data)
{
	int	status ;

	update_last_excuted(input_list, data);
	status = (redir(input_list->redirect));
	if (status == 0)
	{
		if (input_list->args[0])
		{
			run_one_cmd_continue(input_list, data);
		}
	}
	else
		set_exit_status(&data->env_list, 1);
}

static void	run_all_cmds(t_input *input_list, t_data *data)
{
	int	pipe_fd[2];
	int	piped;
	int	index;

	piped = 0;
	index = 0;
	while (input_list)
	{
		update_last_excuted(input_list, data);
		ft_pipe(pipe_fd, &piped, input_list);
		data->cmds_pids[index] = fork();
		if (data->cmds_pids[index] == -1)
			return ;
		if (data->cmds_pids[index] == 0)
		{
			(close(pipe_fd[0]));
			exec_cmd(input_list, data);
		}
		index++;
		reset_fds(data);
		input_list = input_list->next;
	}
	wait_pids(data, index);
}

void	execution(t_data *data)
{
	t_input	*tmp;

	tmp = data->input;
	if (allocate_pids(data->input, data) != 0)
		return ;
	if (run_herdocs(data->input, data) != 0)
		return ;
	signal(SIGINT, dont_quit);
	if (tmp->next == NULL)
		run_one_cmd(tmp, data);
	else
		run_all_cmds(tmp, data);
	reset_fds(data);
	handle_signals();
}
