/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:27:25 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 23:05:55 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	cwdir[PATH_MAX];

	if (!getcwd(cwdir, PATH_MAX))
	{
		write(STDERR_FILENO, "Error accured !\n", 17);
		return (1);
	}
	else
		printf("%s\n", cwdir);
	return (0);
}
