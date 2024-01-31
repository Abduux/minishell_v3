/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:37:03 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/12/24 19:57:34 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env_list(char **env)
{
	t_env	*begin;
	t_env	*cur; 
	t_env	*new;

	if (!env)
		return (NULL);
	begin = (t_env *)malloc(sizeof(t_env));
	if (!begin)
		return (NULL);
	begin->name = get_var_name(*env);
	begin->value = get_var_value(*env);
	begin->next = 0;
	env++;
	cur = begin;
	while (*env)
	{
		new = (t_env *)malloc(sizeof(t_env));
		new->name = get_var_name(*env);
		new->value = get_var_value(*env);
		new->next = 0;
		cur->next = new;
		cur = new;
		env++;
	}
	return (begin);
}

void	init_qt(t_quotes_status *qt)
{
	qt->in_dobule = 0;
	qt->in_single = 0;
}

void	copy_char_to_string(char *str, char c, int *at)
{
	str[(*at)++] = c;
	str[*at] = '\0';
}

char	*get_redirection_string(int type)
{
	if (type == REDIR_HEREDOC)
		return ("<<");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_INPUT)
		return ("<");
	if (type == REDIR_OUTPUT)
		return (">");
	return ("no redir");
}
