#include "../minishell.h"

int exit_status(int status)
{
    if(WIFSIGNALED(status))
    {
        return(128 + WTERMSIG(status));
    }
    else
    {
        return (WEXITSTATUS(status));
    }
}

int set_exit_status(t_env **head, int exit_status)
{
    char *value ;

    value = ft_itoa(exit_status);
    add_env(head, "?", value);
    free(value);
    return (exit_status);
}