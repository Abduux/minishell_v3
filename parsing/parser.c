/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:56:49 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/02/01 02:36:06 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input	*first_parse(char *input, t_data *data)
{
	t_input	*list;
	t_input	*list_begin;
	t_input	*tmp;

	list_begin = NULL;
	list = NULL;
	while (*input)
	{
		tmp = list;
		list = (t_input *)malloc(sizeof(t_input));
		if (list_begin)
			tmp->next = list;
		else
			list_begin = list;
		list->next = NULL;
		list->args = get_args(input);
		list->redirect = get_redirections(input, data);
		move_to_next_pipe(&input, data);
	}
	return (list_begin);
}

t_input	*secode_parse(t_input *list_cpy, t_data *data)
{
	int				i;
	t_input			*list_begin;
	t_redirection	*redir;

	list_begin = list_cpy;
	i = 0;
	while (list_cpy)
	{
		while (list_cpy->args[i])
		{
			list_cpy->args[i] = evaluate(list_cpy->args[i], data, 0);
			i++;
		}
		redir = list_cpy->redirect;
		while (redir)
		{
			redir->file_name = evaluate(redir->file_name, data,
					redir->type);
			redir = redir->next;
		}
		list_cpy = list_cpy->next;
		i = 0;
	}
	return (list_begin);
}

void	remove_empty_strings(char **strArray)
{
	int	i;
	int	j;

	i = 0;
	if (strArray == NULL)
		return ;
	while (strArray[i] != NULL)
	{
		if (strArray[i] == (char *)-1)
		{
			j = i;
			while (strArray[j] != NULL)
			{
				strArray[j] = strArray[j + 1];
				++j;
			}
			--i;
		}
		++i;
	}
}

t_input	*third_parse(t_input *list_begin)
{
	t_input			*lst_cpy;
	t_redirection	*red;

	lst_cpy = list_begin;
	while (lst_cpy)
	{
		remove_empty_strings(lst_cpy->args);
		red = lst_cpy->redirect;
		while (red)
		{
			if (red->file_name == (char *)-1)
				red->file_name = NULL;
			red = red->next;
		}
		lst_cpy = lst_cpy->next;
	}
	return (list_begin);
}

t_input	*parser(char *input, t_data *data)
{
	t_input	*input_lst;

	input_lst = first_parse(input, data);
	input_lst = secode_parse(input_lst, data);
	input_lst = third_parse(input_lst);
	if (data->syntax_error)
	{
		parse_free(input_lst);
		return (NULL);
	}
	return (input_lst);
}
