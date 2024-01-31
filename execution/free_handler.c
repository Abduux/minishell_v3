#include "../minishell.h"

void free_all(t_data *data)
{
    free_env_list(data->env_list);
	free_env_list(data->export_list);
    parse_free(data->input);
    if(data->cmds_pids)
    {
        free(data->cmds_pids);
        data->cmds_pids = NULL;
    }
    clear_history();
}

void    free_and_exit(unsigned char status, t_data *data)
{
    free_all(data);
    exit(status);
}

