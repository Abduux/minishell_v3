/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:37:21 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:37:22 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		return (128 + WTERMSIG(status));
	}
	else
	{
		return (WEXITSTATUS(status));
	}
}

int	set_exit_status(t_env **head, int exit_status)
{
	char	*value;

	value = ft_itoa(exit_status);
	add_env(head, "?", value);
	free(value);
	return (exit_status);
}
