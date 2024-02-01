/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:27:58 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 22:32:14 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_data *data, t_input *input)
{
	int	index;

	index = 1;
	while (input->args[index])
	{
		if (valid_var_name(input->args[index]))
		{
			delete_env(&data->env_list, input->args[index]);
			delete_export(&data->export_list, input->args[index]);
		}
		else
			ft_err_msg(ERR_UNSET_NOT_VALID_INDENTIFIER, 1, input->args[index]);
		index++;
	}
	return (0);
}
