#include "../minishell.h"

int     add_export(t_env **head, const char *name, const char *value)
{
    return add_env(head, name, value);
}

void delete_export(t_env **head, const char *name)
{
    delete_env(head, name);
}

int    add_env(t_env **head, const char *name, const char *value)
{
    t_env *new_env;
    t_env *last;

    new_env = (t_env *)malloc(sizeof(t_env));
    last = *head;
    if (!new_env)
        return(ft_printf("Memory allocation failed\n"));
    new_env->name = ft_strdup(name);
    if(!value)
        new_env->value = NULL;
    else
        new_env->value = ft_strdup(value);
    new_env->next = NULL;
    delete_env(head, name);
    if (*head == NULL)
        *head = new_env;
    else 
    {
        while (last->next != NULL)
            last = last->next;
        last->next = new_env;
    }
    return 0;
}

void delete_env(t_env **head, const char *name)
{
    t_env *current = *head;
    t_env *prev = NULL;

    while (current != NULL && ft_strncmp(current->name, name, INT_MAX) != 0)
    {
        prev = current;
        current = current->next;
    }
    if (current != NULL)
    {
        if (prev != NULL)
            prev->next = current->next;
        else
            *head = current->next;
        free(current->name);
        free(current->value);
        free(current);
    }
}

void increase_shlvl(t_env *list)
{
    int current_value;

    while (list != NULL)
    {
        if (ft_strncmp(list->name, "SHLVL", INT_MAX) == 0)
        {
            current_value = ft_atoi(list->value);
            current_value++;
            free(list->value);
            list->value = ft_itoa(current_value);
            return;
        }
        list = list->next;
    }
    //add it manually if not found
}
