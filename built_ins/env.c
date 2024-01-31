#include "../minishell.h"

int env(t_env *env)
{
    print_env_list(env);
    return (0);
}