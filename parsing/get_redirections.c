/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:59:57 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/11/17 17:41:13 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*get_redirections(char *input, t_data *data)
{
	t_redirection	*red_list;
	t_redirection	*begin;
	int				redir;
	char			*filename;
	t_quotes_status	qt;

	init_qt(&qt);
	redir = 0;
	red_list = NULL;
	begin = NULL;
	while (*input && !is_pipe(*input, qt.in_dobule, qt.in_single))
	{
		move_ptr_to_redir(&input, &redir, &qt);
		if (!*input)
			break ;
		filename = move_ptr_and_alloc(&input, redir, &qt, data);
		if (!filename)
			break ;
		if (!alloc_new_redir(&begin, &red_list, redir))
			break ;
		red_list->file_name = filename;
	}
	return (begin);
}
