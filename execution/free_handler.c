/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:38:40 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:37:12 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *data)
{
	free_env_list(data->env_list);
	free_env_list(data->export_list);
	parse_free(data->input);
	if (data->cmds_pids)
	{
		free(data->cmds_pids);
		data->cmds_pids = NULL;
	}
	clear_history();
}

void	free_and_exit(unsigned char status, t_data *data)
{
	free_all(data);
	exit(status);
}
