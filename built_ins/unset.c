#include "../minishell.h"

int unset(t_data *data, t_input *input)
{
    int index;

    index = 1;
    while (input->args[index])
    {
        if(valid_var_name(input->args[index]))
        {
            delete_env(&data->env_list, input->args[index]);
            delete_export(&data->export_list, input->args[index]);
        }
        else
            ft_printf("minishell: unset: `%s': not a valid identifier\n", input->args[index]);
        index++;
    }
    return (0);
}
