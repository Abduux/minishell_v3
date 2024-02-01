/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:15:17 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 22:17:28 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	n_option(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[i] != '-')
		return (0);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	if (i == 1)
		return (0);
	return (1);
}

int	echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (n_option(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (ft_strlen(args[i]) > 0 && args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
