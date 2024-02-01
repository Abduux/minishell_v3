/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:34:21 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 00:36:18 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_shell(t_data *data, t_input *input)
{
	int	count;
	int	isdigit;

	count = arg_count(input->args);
	isdigit = is_numric(input->args[1]);
	printf("exit\n");
	if (count == 1)
		free_and_exit(atoi(get_value_from_env("?", data->env_list)), data);
	if ((isdigit && count == 2))
		free_and_exit(ft_atoi(input->args[1]), data);
	else if (!isdigit)
		free_and_exit(ft_err_msg(ERR_NUMERIC_REQUI, 2, input->args[1]), data);
	return (ft_err_msg(ERR_TOO_MANY_ARGS, 1, NULL));
}

int	exit_(t_data *data, t_input *input)
{
	int	exit_status;

	exit_status = exit_shell(data, input);
	set_exit_status(&data->env_list, exit_status);
	return (exit_status);
}
