/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:16:49 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/12/02 19:43:43 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	parse_free(t_input *lst)
{
	t_input			*tmp;
	t_redirection	*red_lst;
	t_redirection	*red_tmp;

	while (lst)
	{
		tmp = lst->next;
		free_strs(lst->args);
		red_lst = lst->redirect;
		while (red_lst)
		{
			red_tmp = red_lst->next;
			if (red_lst->file_name)
				free(red_lst->file_name);
			free(red_lst);
			red_lst = red_tmp;
		}
		free(lst);
		lst = tmp;
	}
}
