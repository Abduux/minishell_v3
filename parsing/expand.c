/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:48:41 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 22:42:03 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value_from_env(const char *name, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, INT_MAX) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*expand_variable(char **word, t_env *env )
{
	char	*variable_start;
	int		variable_length;
	char	*variable_name;
	char	*variable_value;

	(*word)++;
	variable_start = *word;
	while (**word && is_valid_identifier_char(**word, *word - variable_start))
	{
		if ((ft_isdigit(**word) && *word - variable_start == 0)
			|| should_stop_identifier(**word))
		{
			(*word)++;
			break ;
		}
		(*word)++;
	}
	variable_length = *word - variable_start;
	variable_name = (char *)malloc(sizeof(char) * (variable_length + 1));
	ft_strlcpy(variable_name, variable_start, variable_length + 1);
	variable_value = get_value_from_env(variable_name, env);
	free(variable_name);
	return (variable_value);
}
