#include "../minishell.h"

int    exit_shell(t_data *data, t_input *input)
{
    int count;
    int isdigit;
    int status;

    count = arg_count(input->args);
    isdigit = is_numric(input->args[1]);
    printf("exit\n");
    if(count == 1)
    {
        status = atoi(get_value_from_env("?", data->env_list)); 
        return(status);
    }

    if((isdigit && count == 2)) 
        return(ft_atoi(input->args[1]));
    else if(!isdigit)
    {
        ft_err_msg(ERR_NUMERIC_REQUI, 2, input->args[1]);
        return(2); // should check the exit value of this 1
    }
    else
    {
         ft_err_msg(ERR_TOO_MANY_ARGS, 1, NULL);
        return(1);
    }
}

int exit_(t_data *data, t_input *input, int flag)
{
    int exit_status;
    exit_status = exit_shell(data, input);
    if(flag == EXIT_MINISHELL)
        free_and_exit(exit_status, data, input);
    set_exit_status(&data->env_list, exit_status);
    return(exit_status);
}

void check_exit(t_input *input_list, t_data *data)
{
    if (input_list->args && input_list->args[0] && 
        ft_strncmp(input_list->args[0], "exit", CMD_LEN) == 0 && !input_list->next)
        exit_(data, input_list, EXIT_MINISHELL);
}


