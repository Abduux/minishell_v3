#include "../minishell.h"

void    update_last_excuted(t_input *cmd, t_data *data)
{
    char *cmd_path;
    cmd_path = get_cmd_path(cmd->args[0], data);
    if(!cmd->args[0] || ft_strlen(cmd->args[0]) == 0)
         add_env(&data->env_list, "_", "");
    else if (cmd_path != NULL && !is_builtin(cmd))
        add_env(&data->env_list, "_", cmd_path);
    else
        add_env(&data->env_list, "_", cmd->args[0]);
    free(cmd_path);
}

static void exec_cmd(t_input *input_list, t_data *data)
{
    int status;

    status = redir(input_list->redirect);
    if(status == 0)
    {
        if(input_list->args[0])
        {
            if(is_builtin(input_list))
            {
                status = run_a_builtin(input_list, data);
                free_and_exit(status, data);
            }
            else
                run_cmd(input_list, data);
        }
    }
    free_and_exit(1, data);
}


static void run_one_cmd(t_input *input_list, t_data *data)
{
    int status ;
    int pid;

    update_last_excuted(input_list, data);
    status = (redir(input_list->redirect));
    if(status == 0)
    {
        if(input_list->args[0])
        {
            if(is_cmd_ehco(input_list))
            {
                pid = fork();
                if(pid == 0)
                    free_and_exit(run_a_builtin(input_list, data), data);
                waitpid(pid, &status, 0);
                set_exit_status(&data->env_list, exit_status(status));
            }
            else if(is_builtin(input_list))
                set_exit_status(&data->env_list, run_a_builtin(input_list, data));
            else
            {
                pid = fork();
                if(pid == 0)
                    run_cmd(input_list, data);
                waitpid(pid, &status, 0);
                set_exit_status(&data->env_list, exit_status(status));
            }
        }

    }
    else
        set_exit_status(&data->env_list, 1);  
}

 void run_all_cmds(t_input *input_list, t_data *data)
{
    int pipe_fd[2];
    int piped;
    int index;

   piped = 0;
    index = 0;
    while (input_list)
    {
        update_last_excuted(input_list, data);
        ft_pipe(pipe_fd, &piped, input_list);
        data->cmds_pids[index] = fork();
        if(data->cmds_pids[index] == 0)
        {
            (close(pipe_fd[0]));
            exec_cmd(input_list, data);
        }
        index++; 
		reset_fds(data);
        input_list = input_list->next;
    }
    wait_pids(data, index);
}

int handle_execution(t_input *input_list, t_data *data)
{
    t_input *tmp = input_list;

    signal(SIGINT, dont_quit);
    if (tmp->next == NULL)
        run_one_cmd(tmp, data);
    else 
        run_all_cmds(tmp, data);
    reset_fds(data);
    return 0;
}


void execution(t_data *data)
{
    if(allocate_pids(data->input, data) != 0)
        return;
    if(run_herdocs(data->input, data) != 0)
        return;
    handle_execution(data->input, data);
    handle_signals();
}
