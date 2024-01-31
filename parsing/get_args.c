/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:54:02 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/12/02 22:18:25 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "stdbool.h"

char	**add_string(char **current_strs, char *new_str)
{
	int		i;
	char	**new_strs;

	i = 0;
	while (current_strs && current_strs[i])
		i++;
	new_strs = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (current_strs && current_strs[i])
	{
		new_strs[i] = current_strs[i];
		i++;
	}
	new_strs[i++] = new_str;
	new_strs[i] = 0;
	if (current_strs)
		free(current_strs);
	return (new_strs);
}

char	**new_arg(char **result, char *src, size_t size)
{
	char	*arg;

	arg = NULL;
	arg = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(arg, src, size + 1);
	result = add_string(result, arg); 
	return (result);
}

size_t	move_ptr_and_get_arg_len(char **input, t_quotes_status *qt)
{
	char	*start;

	start = *input;
	while (**input && !is_whit_sp(**input, qt->in_dobule, qt->in_single) && 
		!is_pipe(**input, qt->in_dobule, qt->in_single))
	{
		if (is_redirection(*input) && !qt->in_dobule && !qt->in_single)
			break ;
		proccess_both_quotes(**input, qt);
		(*input)++;
	}
	return ((size_t)(*input - start));
}

char	**get_args(char *input)
{
	char			**result;
	t_quotes_status	qt;
	char			*start;
	size_t			arg_len;

	init_qt(&qt);
	arg_len = 0;
	result = malloc(sizeof(char *) * (1));
	if (!result || !input)
		return (NULL);
	result[0] = NULL;
	while (*input)
	{
		skip_redirections(&input);
		while (*input == ' ' || *input == '\t')
			input++;
		if (is_pipe(*input, qt.in_dobule, qt.in_single))
			break ;
		start = input;
		arg_len = move_ptr_and_get_arg_len(&input, &qt);
		if (arg_len == 0)
			continue ;
		result = new_arg(result, start, (arg_len));
	}
	return (result);
}
