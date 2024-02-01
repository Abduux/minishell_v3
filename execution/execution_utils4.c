/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:49:39 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:02:02 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_abs_path(char *cmd)
{
	if (cmd && cmd[0])
		return (cmd[0] == '/');
	return (0);
}

int	is_relative_path(char *cmd)
{
	if (cmd && cmd[0] && cmd[1])
		return (cmd[0] == '.' && cmd[1] == '/');
	return (0);
}

int	is_directory(const char *file_name)
{
	struct stat	statbuf;

	if (stat(file_name, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	update_last_excuted(t_input *cmd, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->args[0], data);
	if (!cmd->args[0] || ft_strlen(cmd->args[0]) == 0)
		add_env(&data->env_list, "_", "");
	else if (cmd_path != NULL && !is_builtin(cmd))
		add_env(&data->env_list, "_", cmd_path);
	else
		add_env(&data->env_list, "_", cmd->args[0]);
	free(cmd_path);
}
