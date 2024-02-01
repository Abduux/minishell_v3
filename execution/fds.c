/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:38:21 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:29:18 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_fds(t_data *data)
{
	data->stderr = dup(STDERR_FILENO);
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
}

void	reset_fds(t_data *data)
{
	dup2(data->stdin, STDIN_FILENO);
	dup2(data->stdout, STDOUT_FILENO);
	dup2(data->stderr, STDERR_FILENO);
}
