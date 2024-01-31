/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:27:49 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/28 04:43:45 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_name(char *env_var)
{
	int	i;

	i = 0;
	if (!env_var)
		return (NULL);
	while (env_var[i] && env_var[i] != '=')
		i++;
	if (!env_var[i])
		return (NULL);
	env_var[i] = '\0';
	return (ft_strdup(env_var));
}

char	*get_var_value(char *env_var)
{
	int	i;

	i = 0;
	if (!env_var)
		return (NULL);
	while (env_var[i])
		i++;
	i++;
	if (!env_var[i])
		return (NULL);
	return (ft_strdup(env_var + i));
}
void print_env_list(t_env *env)
{
	while (env)
	{
		if(strncmp(env->name, "?", INT_MAX) != 0)
		{
			printf("%s=", env->name);
			if(env->value)
				printf("%s",env->value);
			printf("\n");

		}
		env = env->next;
	}
}

void print_env_array(char** env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;	
	}
}