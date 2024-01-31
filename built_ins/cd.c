#include "../minishell.h"

static int	change_dir(const char* path_name, t_data *data)
{
	char	olddir[PATH_MAX];

	getcwd(olddir, PATH_MAX);
	if (access(path_name , F_OK) != 0)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path_name);
		return (1);
	}
	else if (access(path_name, X_OK) != 0)
	{
		ft_printf("minishell: cd: %s: Permission denied\n", path_name);
		return(1);
	}
	chdir(path_name);
	add_env(&data->env_list, "OLDPWD", olddir);
	add_export(&data->export_list, "OLDPWD", olddir);
	getcwd(olddir, PATH_MAX);
	add_env(&data->env_list, "PWD", olddir);
	add_export(&data->export_list, "PWD", olddir);
	return (0);
}

int	cd(t_input cmd, t_data *data)
{
	char	*newdir;

	if (arg_count(cmd.args) == 1)
	{
		newdir =  get_value_from_env("HOME" , data->env_list); // get the home value to navigate to it 
		if(!newdir)
		{
			ft_printf("minishell: cd: HOME not set\n"); // if the HOME variable not set
			return (1);
		}
		else
			return(change_dir(newdir, data)); // if it set
	}
	else if (arg_count(cmd.args) > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	else
		return(change_dir(cmd.args[1], data));
	return (0);
}
