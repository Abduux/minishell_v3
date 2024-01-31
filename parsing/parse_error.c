/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:15:35 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/11/17 17:16:40 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unexpected_token_error(t_data *data, char *near)
{
	if (!data->syntax_error)
	{
		if (*near != '\n')
			ft_printf("bash: syntax error near unexpected token `%s'\n", near);
		else 
			ft_printf("bash: syntax error near unexpected token `newline'\n");
	}
	data->syntax_error = 1;
}

void	unexpected_eof_error(t_data *data)
{
	if (!data->syntax_error)
		ft_printf("bash: unexpected EOF while looking for matching\n");
	data->syntax_error = 1;
}
