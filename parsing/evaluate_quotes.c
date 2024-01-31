/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:43:38 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/26 16:38:47 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_expand(char *c, int in_single_quotes, int re_type)
{
	return (*(c + 1) && *c == '$' && *(c + 1) != '$' && *(c + 1) != ' ' 
		&& *(c + 1) != '"' && *(c + 1) 
		!= '\'' && *(c + 1) != '+'
		&& (re_type == IS_INSIDE_HERDOC || (!in_single_quotes && re_type != REDIR_HEREDOC)));
}

int	expand(char	**word, int len, char **result, t_data *data)
{
	char	*variable_value;
	int		added_result_index;

	added_result_index = 0;
	variable_value = expand_variable(word, data->env_list);
	if (variable_value != NULL && ft_strlen(variable_value) > 0) 
		*result = free_and_join(*result, variable_value, len, 
				&added_result_index);
	(*word)--;
	return (added_result_index);
}

char	*init(char **result, int *result_index, t_quotes_status *qt, int len)
{
	init_qt(qt);
	*result_index = 0;
	*result = NULL;
	if (len)
		*result = (char *)malloc(sizeof(char) * (len + 1));
	if (*result)
		ft_bzero(*result, len);
	return (*result);
}

void	check_error(t_quotes_status *qt, t_data *data, int is_inside_herdoc)
{
	if(is_inside_herdoc == IS_INSIDE_HERDOC)
		return;
	if (qt->in_dobule || qt->in_single )
		unexpected_eof_error(data);
}

char	*evaluate_quotes(char	*word, t_data *data, int re_type)
{
	char			*result;
	t_quotes_status	qt;
	int				len;
	int				result_index;
	char			*current;

	len = ft_strlen(word);
	if (!word || !*word || !init(&result, &result_index, &qt, len))
		return (NULL);
	while (*word) 
	{
		current = word;
		proccess_both_quotes(*current, &qt);
		if (should_expand(current, qt.in_single, re_type)) 
			result_index += expand(&word, len, &result, data);
		if (!(*current == '"' && !qt.in_single) && 
			!(*current == '\'' && !qt.in_dobule) && 
			!should_expand(current, qt.in_single, re_type)) 
			copy_char_to_string(result, *word, &result_index);
		word++;
	}
	if(re_type != IS_INSIDE_HERDOC)
		check_error(&qt, data, re_type);
	result[result_index] = '\0';
	return (result);
}
