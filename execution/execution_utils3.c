/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:24:10 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:24:25 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	to_join_values(char *str, int equal_index)
{
	if (equal_index > 0 && str[equal_index - 1] == '+')
		return (1);
	return (0);
}

void	join_env(const char *key, const char *value, t_data *data, int to_join)
{
	char	*joined_value;

	if (!to_join)
	{
		if (value)
			add_env(&data->env_list, key, value);
		add_export(&data->export_list, key, value);
		return ;
	}
	joined_value = ft_strjoin(get_value_from_env(key, data->env_list), value);
	if (value)
		add_env(&data->env_list, key, joined_value);
	add_export(&data->export_list, key, joined_value);
	free(joined_value);
}

int	is_cmd_ehco(t_input *input)
{
	if (ft_strncmp(*input->args, "echo", CMD_LEN) == 0)
		return (1);
	return (0);
}

int	ft_pipe(int *pipe_fd, int *piped, t_input *current_cmd)
{
	if (*piped == 1)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		*piped = 0;
	}
	if (current_cmd->next != NULL )
	{
		pipe(pipe_fd);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		*piped = 1;
	}
	return (0);
}
