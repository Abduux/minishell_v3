/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:17:55 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/26 15:56:00 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_double_quotes(t_quotes_status *qt)
{
	if (!qt->in_single)
		qt->in_dobule = !qt->in_dobule;
}

void	process_single_quotes(t_quotes_status *qt)
{
	if (!qt->in_dobule)
		qt->in_single = !qt->in_single;
}

int	is_redirection(char *input)
{
	if (ft_strncmp(input, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (ft_strncmp(input, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (ft_strncmp(input, "<", 1) == 0)
		return (REDIR_INPUT);
	if (ft_strncmp(input, ">", 1) == 0)
		return (REDIR_OUTPUT);
	return (0);
}

void	skip_redirections(char **input)
{
	t_quotes_status	qt;

	init_qt(&qt);
	while (**input && is_redirection(*input))
	{
		while (**input == '>' || **input == '<')
			(*input)++;
		while (**input == ' ' || **input == '\t')
			(*input)++;
		proccess_both_quotes(**input, &qt);
		if(**input)
			(*input)++;
		while (**input && !is_whit_sp(**input, qt.in_dobule, qt.in_single) 
			&& **input != '<' && **input != '>')
		{
			proccess_both_quotes(**input, &qt);
			(*input)++;
		}
		while (**input == ' ' || **input == '\t')
			(*input)++;
	}
}

int should_stop_identifier(char c)
{
	return (!(ft_isalnum(c) || c == '_'));
}

int	is_valid_identifier_char(char c, int cur_i)
{
	return ((ft_isalnum(c) || c == '_') ||
		((c == '@' || c == '!' || c == '?') && cur_i == 0));
}
