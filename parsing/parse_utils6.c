/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:49:09 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 02:23:59 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*evaluate(char *word, t_data *data, int r_type)
{
	char	*result;

	result = evaluate_quotes(word, data, r_type);
	if (result[0] == '\0' && !(!ft_strncmp(word, "\"\"", INT_MAX)
			|| !ft_strncmp(word, "\'\'", INT_MAX)))
	{
		free(result);
		result = (char *)-1;
	}
	free(word);
	return (result);
}

void	cpy(char **res_env, int at, t_env *current)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (current->name && current->name[j] != '\0')
	{
		res_env[at][j] = current->name[j];
		j++;
	}
	res_env[at][j++] = '=';
	while (current->value && current->value[k] != '\0')
	{
		res_env[at][j + k] = current->value[k];
		k++;
	}
	res_env[at][j + k] = '\0';
}

void	copy_to_array(char **res_env, t_env *env, int count)
{
	t_env	*current;
	int		i;

	i = 0;
	current = env;
	while (i < count)
	{
		res_env[i] = (char *)malloc(ft_strlen(current->name)
				+ ft_strlen(current->value) + 2);
		cpy(res_env, i, current);
		current = current->next;
		i++;
	}
}

char	**from_list_to_array(t_env *env)
{
	int		count;
	t_env	*current;
	char	**env_array;

	current = env;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	env_array = (char **)malloc((count + 1) * sizeof(char *));
	copy_to_array(env_array, env, count);
	env_array[count] = NULL;
	return (env_array);
}

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}
