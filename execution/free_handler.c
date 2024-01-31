#include "../minishell.h"

void free_all(t_input *inp, t_data *data)
{
    free_env_list(data->env_list);
	free_env_list(data->export_list);
    parse_free(inp);
    if(data->cmds_pids)
    {
        free(data->cmds_pids);
        data->cmds_pids = NULL;
    }
    clear_history();
}

void    free_and_exit(unsigned char status, t_data *data , t_input *input)
{
    free_all(input, data);
    exit(status);
}

