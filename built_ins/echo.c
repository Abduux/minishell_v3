#include "../minishell.h"

static int    n_option(char *arg)
{
	int	i;
	
	i = 0;
    if (!arg || arg[i] != '-')
		return (0);
	while (arg[++i])
    {
        if(arg[i] != 'n')
            return (0);
	}
	if(i == 1)
		return (0);
    return (1);
}

int	echo(char **args)
{
	int	new_line;
	int	i;

    new_line = 1;
	i = 1;
    while (n_option(args[i]))
    {
        new_line = 0;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if(ft_strlen(args[i]) > 0 && args[i + 1])
            printf(" ");
        i++;
    }
    if(new_line == 1)
    {
        printf("\n");
    }
	return (0);
}
