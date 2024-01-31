/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:24:56 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/11/17 17:27:42 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*free_and_join(char *s1, char *variable_name, int origin_len, 
		int *result_index)
{
	char	*result;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(variable_name);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + origin_len));
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, variable_name, s2_len + 1);
	(*result_index) += s2_len;
	free(s1);
	return (result);
}

int	is_pipe(char c, int inside_double_quotes, int inside_signle_quotes)
{
	return (c == '|' && !inside_double_quotes && !inside_signle_quotes);
}

int	is_whit_sp(char c, int in_dq, int in_sq)
{
	return ((c == ' ' || c == '\t') && !in_dq && !in_sq);
}

void	proccess_both_quotes(char c, t_quotes_status *qt)
{
	if (c == '\'')
		process_single_quotes(qt);
	else if (c == '"')
		process_double_quotes(qt);
}

char	**ft_strsdup(char **strs)
{
	int		size;
	char	**return_strs;

	size = 0;
	while (strs[size])
		size++;
	return_strs = (char **)malloc(sizeof(char *) * (size + 1));
	size = 0;
	while (strs[size])
	{
		return_strs[size] = ft_strdup(strs[size]);
		size++;
	}
	return_strs[size] = NULL;
	return (return_strs);
}
