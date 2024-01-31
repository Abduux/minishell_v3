#include "../minishell.h"

static int get_cmds_count(t_input *input)
{
    int count;

    count = 0;
    if(!input)
        return 0;
    while (input)
    {
        count++;
        input = input->next;
    }
    return count;
}


int allocate_pids(t_input *input_list, t_data *data)
{
    int cmd_count;

    cmd_count = 0;
    if(data->cmds_pids)
    {
        free(data->cmds_pids);
        data->cmds_pids = NULL;
    }
    cmd_count = get_cmds_count(input_list);
    if(cmd_count == 0)
        return 0;
    data->cmds_pids = (pid_t*)malloc(sizeof(pid_t) * (cmd_count));
    if(!data->cmds_pids)
       return -1;
    return 0;
}

void wait_pids(t_data* data, int running_cmds)
{
    int i;
    int status;

    status = 0;
    i = 0;
    while (i < running_cmds)
    {
        waitpid(data->cmds_pids[i], &status, 0);
        set_exit_status(&data->env_list, exit_status(status));
        i++;
    }
}