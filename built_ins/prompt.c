/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:19:44 by ali               #+#    #+#             */
/*   Updated: 2024/02/01 16:58:04 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int change_prompt(t_data *data, t_input *input)
{
    char *tmp;
    char *prompt;

    if (arg_count(input->args) != 2)
    {
        ft_printf_fd(STDERR_FILENO, "Usage: < prompt [PROMPT] >\n");
        return (1);
    }
    tmp = ft_strjoin("\x1b[1;34m""\x1b[1;34m", input->args[1]);
    prompt = ft_strjoin(tmp, " -> \x1b[0m");
    free(tmp);
    free(data->prompt);
    data->prompt = prompt;
    return(0);
}