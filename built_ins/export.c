
#include "../minishell.h"

static char *cutvalue(char *str, int value_index)
{
    int i;

    i = 0;
    char *value;
    if(!str[value_index])
        return (NULL);
    value = ft_calloc(sizeof(char), ft_strlen(str) - value_index);
    if(str[value_index] == '=')
        value_index++;
    while (str[i + value_index])
    {
        value[i] = str[i + value_index];
        i++;
    }
    return (value);
}

static char* cut_name(char *str , int *value_index)
{
    int     len;
    char*   name;
    int     i;

    len = 0;
    i = 0;
    while(str[len] == '=' || str[len] == '+')
        len++;
    while (str[len] && str[len] != '=')
        len++;
    *value_index = len;
    if(str[len] == '=' && len > 0 && str[len - 1] == '+')
        len--;
    name = (char *)ft_calloc(sizeof(char), len + 1);
    if(!name)
        return(NULL);
    while (str[i] && i < len)
    {
        name[i] = str[i];
        i++;
    }
    return (name);
}

static int add_variable(char *str , t_data *data)
{
    int     value_index;
    char    *name;
    char    *value;

    name = cut_name(str, &value_index);
    value = cutvalue(str , value_index);
    if (!valid_var_name(name))
    {
        ft_printf("minishell: export: `%s': not a valid identifier\n", str); // carefull
        free(name);
        free(value);
        return (1);
    }
    else
        join_env(name, value, data, to_join_values(str, value_index));
    free(name);
    free(value);
    return(0);
}

static void    display_export(t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp)
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(tmp->name, STDOUT_FILENO);
        if(tmp->value)
        {
            write(STDOUT_FILENO, "=\"", 2);
            write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value));
            write(STDOUT_FILENO, "\"", 1);
        }
        write(1, "\n", 1);
        tmp = tmp->next;
    }
}

int export(t_input *input, t_data *data)
{
    int i;
    int status;

    i = 1;
    if(arg_count(input->args) == 1)
        display_export(data->export_list);
    else 
    {
        while (input->args[i])
        {
            status = add_variable(input->args[i], data);
            i++;
        }
    }
    return (set_exit_status(&data->env_list, status));
}
