/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:41:51 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 02:30:12 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_export(char **env, int i)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->name = get_var_name(env[i]);
	new->value = get_var_value(env[i]);
	new->next = 0;
	return (new);
}

t_env	*get_export_list(char **env)
{
	t_env	*begin;
	t_env	*cur;
	int		i;
	t_env	*new;

	if (!env)
		return (NULL);
	i = 0;
	begin = new_export(env, i);
	cur = begin;
	i++;
	while (env[i] && cur)
	{
		if (ft_strncmp("_=", env[i], 2) == 0)
		{
			i++;
			continue ;
		}
		new = new_export(env, i);
		cur->next = new;
		cur = new;
		i++;
	}
	return (begin);
}

int	should_stop_identifier(char c)
{
	return (!(ft_isalnum(c) || c == '_'));
}

void	move_to_next_pipe(char **input, t_data *data)
{
	t_quotes_status	qt;
	int				arg_found;

	arg_found = 0;
	init_qt(&qt);
	while (**input)
	{
		proccess_both_quotes(**input, &qt);
		if (!is_whit_sp(**input, qt.in_dobule, qt.in_single)
			&& !is_pipe(**input, qt.in_dobule, qt.in_single))
			arg_found = 1;
		if (is_pipe(**input, qt.in_dobule, qt.in_single))
		{
			(*input)++;
			while (**input == ' ')
				(*input)++;
			if (!(**input) || !arg_found)
				unexpected_token_error(data, "|");
			break ;
		}
		(*input)++;
	}
}
