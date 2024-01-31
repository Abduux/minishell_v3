#include "../minishell.h"

int	arg_count(char **args)
{
	char	**tmp;
	int		i;

	tmp = args;
	i = 0;
	while (*tmp)
	{
		i++;
		tmp++;
	}
	return(i);
}

int is_numric(char *str)
{
    int i;

    i = 0;
    if(!str || !ft_strlen(str))
        return (0);
    if(str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
        if(!ft_isdigit(str[i++]))
            return (0);
    return (1);
}

int   is_builtin(t_input *input)
{
	if(!*input->args)
        return 0;
    if (ft_strncmp(*input->args , "echo", CMD_LEN) == 0 
		|| ft_strncmp(*input->args, "cd", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "pwd", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "env", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "unset", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "export", CMD_LEN) == 0
		|| ft_strncmp(*input->args, "exit", CMD_LEN) == 0)
		return (1);
    return (0);
}
int	valid_var_name(char *name)
{
	int i;

	i = 0;
	if(!name || (!ft_isalpha(name[i]) && name[i] != '_'))
		return (0); // should start with alpha and under score only
	while (name[i])
	{
		if(!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
