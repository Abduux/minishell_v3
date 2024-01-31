#include "../minishell.h"

static int   excute_builtin(t_input *input, t_data *data)
{   
    if (ft_strncmp(*input->args , "echo", CMD_LEN) == 0)
        return (echo(input->args));
    else if (ft_strncmp(*input->args , "cd", CMD_LEN) == 0)
        return (cd(*input, data));
    else if (ft_strncmp(*input->args , "pwd", CMD_LEN) == 0)
        return (pwd());
    else if (ft_strncmp(*input->args, "env", CMD_LEN) == 0)
    {
        add_env(&data->env_list, "_", "env");
        return (env(data->env_list));
    }
    else if (ft_strncmp(*input->args, "unset", CMD_LEN) == 0)
        return(unset(data, input));
    else if (ft_strncmp(*input->args, "export", CMD_LEN) == 0)
        return(export(input, data));
    else if (ft_strncmp(*input->args, "exit", CMD_LEN) == 0)
        return(exit_(data, input, EXIT_MINISHELL));
    return (-1);
}


int	run_a_builtin(t_input *input, t_data *data)
{
    int status;

    status = excute_builtin(input, data);
    add_env(&data->env_list, "_", *input->args);
	return(status);
}
