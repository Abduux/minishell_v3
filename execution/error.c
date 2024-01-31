#include "../minishell.h"

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
	return (0);
}