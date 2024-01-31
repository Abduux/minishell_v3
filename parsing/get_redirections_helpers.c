/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:10:02 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/12/02 22:24:38 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_ptr_to_redir(char **input, int *redir, t_quotes_status *qt)
{
	while (**input && !is_pipe(**input, qt->in_dobule, qt->in_single))
	{
		*redir = is_redirection(*input);
		if ((*redir && !(qt->in_dobule) && !(qt->in_single)))
			break ;
		proccess_both_quotes(**input, qt);
		(*input)++;
	}
}

int	move_ptr_to_filename(char **input, int redir, t_quotes_status *qt, 
	t_data *data)
{
	if (redir == REDIR_APPEND || redir == REDIR_HEREDOC)
		(*input) += 2;
	else 
		(*input)++;
	while (**input == ' ' || **input == '\t')
		(*input)++;
	if (**input == '\0' || is_pipe(**input, qt->in_dobule, qt->in_single))
	{
		if (**input == '\0')
			unexpected_token_error(data, "\n");
		else 
			unexpected_token_error(data, "|");
		return (0);
	}
	return (1);
}

void	move_ptr_to_endfilename(char **input, t_quotes_status *qt)
{
	while (**input && !is_whit_sp(**input, qt->in_dobule, qt->in_single) 
		&& !is_pipe(**input, qt->in_dobule, qt->in_single))
	{
		if ((is_redirection(*input) && !qt->in_dobule && !qt->in_single))
			break ;
		proccess_both_quotes(**input, qt);
		(*input)++;
	}
}

int	alloc_new_redir(t_redirection **begin, t_redirection **red_list, int redir)
{
	t_redirection	*tmp;

	if (*begin)
	{
		tmp = *red_list;
		*red_list = (t_redirection *)malloc(sizeof(t_redirection));
		tmp->next = *red_list;
	}
	else
	{
		*red_list = (t_redirection *)malloc(sizeof(t_redirection));
		*begin = *red_list;
	}
	if (!(*red_list))
		return (0);
	(*red_list)->type = redir;
	(*red_list)->next = 0;
	(*red_list)->file_name = NULL;
	return (1);
}

char	*move_ptr_and_alloc(char **input, int redir, t_quotes_status *qt,
		t_data *data)
{
	char	*start;
	char	*end;
	char	*filename;
	int		red;

	filename = NULL;
	if (**input && !is_pipe(**input, qt->in_dobule, qt->in_dobule))
	{
		if (!move_ptr_to_filename(input, redir, qt, data))
			return (NULL);
		start = *input;
		move_ptr_to_endfilename(input, qt);
		end = *input;
		if (end - start == 0)
		{
			red = is_redirection(*input);
			if (red && !qt->in_dobule && !qt->in_single)
				unexpected_token_error(data, get_redirection_string(red));
			return (NULL);
		}
		filename = (char *)malloc(sizeof(char) * (size_t)((end - start) + 1));
		ft_strlcpy(filename, start, (size_t)((end - start) + 1));
		return (filename);
	}
	return (NULL);
}
