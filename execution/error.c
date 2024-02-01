/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:21:16 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/01/31 23:11:55 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_unset(int err, int err_code, char *file)
{
	if (err == ERR_EXPORT_NOT_VALID_INDENTIFIER)
		return (ft_putstr_fd("minishell: export: ", 2),
			ft_putstr_fd(file, 2),
			ft_putstr_fd(": not a valid identifier\n", 2), err_code);
	if (err == ERR_UNSET_NOT_VALID_INDENTIFIER)
		return (ft_putstr_fd("minishell: unset: ", 2),
			ft_putstr_fd(file, 2),
			ft_putstr_fd(": not a valid identifier\n", 2), err_code);
	return (0);
}

int	ft_err_msg(int err, int err_code, char *file)
{
	if (err == ERR_CMD_NOT_FOUND)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(file, 2),
			ft_putstr_fd(": command not found\n", 2), err_code);
	else if (err == ERR_NO_SUCH_FILE)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(file, 2),
			ft_putstr_fd(": No such file or directory\n", 2), err_code);
	else if (err == ERR_IS_DIR)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(file, 2),
			ft_putstr_fd(": Is a directory\n", 2), err_code);
	else if (err == ERR_PERM_DENIED)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(file, 2),
			ft_putstr_fd(": Permission denied\n", 2), err_code);
	else if (err == ERR_TOO_MANY_ARGS)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
			err_code);
	else if (err == ERR_NUMERIC_REQUI)
		return (ft_putstr_fd("minishell: exit: ", 2),
			ft_putstr_fd(file, 2),
			ft_putstr_fd(": numeric argument required\n", 2), err_code);
	else if (err == ERR_EXPORT_NOT_VALID_INDENTIFIER
		|| err == ERR_UNSET_NOT_VALID_INDENTIFIER)
		return (export_unset(err, err_code, file));
	return (0);
}
