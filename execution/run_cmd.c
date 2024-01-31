#include "../minishell.h"

int is_abs_path(char *cmd)
{
    if(cmd && cmd[0])
        return (cmd[0] == '/');
    return 0;
}

int is_relative_path(char *cmd)
{
    if(cmd && cmd[0] && cmd[1])
        return (cmd[0] == '.' && cmd[1] == '/');
    return 0;
}

int is_directory(const char *file_name)
{
    struct stat statbuf;
    if (stat(file_name, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

char* get_cmd_path(const char *cmd, t_data *data)
{
    char**  paths;
    int     i;
    char*   path;
    char*   full_path;

    paths = ft_split(get_value_from_env("PATH", data->env_list), ':');
    i = -1;
    while (paths && paths[++i])
    {
        path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(path, cmd);
        free(path);
        if(access(full_path, F_OK) == 0)
        {
            free_strs(paths);
            return (full_path);
        }
        free(full_path);
    }
    free_strs(paths);
    return (NULL);
}

char* resovle_path(char *cmd, t_data *data, int *status)
{
    char* full_path;

    full_path = NULL;
    if(!is_abs_path(cmd) && !is_relative_path(cmd))
    {
        full_path = get_cmd_path(cmd , data);
        if(!full_path)
            *status =  ft_err_msg(ERR_CMD_NOT_FOUND, 127, cmd);
        else if (access(full_path, F_OK) == -1)
                 *status =  ft_err_msg(ERR_NO_SUCH_FILE, 127, cmd);
        else if(access(full_path, X_OK) == -1)
                *status = ft_err_msg(ERR_PERM_DENIED, 126, cmd);
    }
    else 
    {
        if(is_directory(cmd))
            *status = ft_err_msg(ERR_IS_DIR, 126, cmd);
        else if (access(cmd, F_OK) == -1)
              *status =  ft_err_msg(ERR_NO_SUCH_FILE, 127, cmd);
        else if(access(cmd, X_OK) == -1)
             *status = ft_err_msg(ERR_PERM_DENIED, 126, cmd);
        else
            full_path = ft_strdup(cmd);
    }
    return full_path;
}

int run_cmd(t_input *input, t_data *data)
{
    char*   cmd_path;
    int     status;
    char **env;
    
    if(!*input->args)
        return 0;
    status = 0;
    cmd_path = resovle_path(input->args[0], data, &status);
    if(status != 0)
    {
        if(cmd_path)
            free(cmd_path); 
        free_and_exit(status, data, input);
    }
    env = from_list_to_array(data->env_list);
    execve(cmd_path, input->args,env);
    ft_printf("Error Execve : '%s'\n", cmd_path);
    free(cmd_path);
    free_strs(env);
    free_and_exit(42, data, input);
    free(cmd_path);
    return (0);
} 

