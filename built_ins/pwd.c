#include "../minishell.h"

int pwd(void)
{
	char	cwdir[PATH_MAX];

	if(!getcwd(cwdir, PATH_MAX)){
		write(2 , "Error accured !\n", 17);
		return (1);
	}
	else
		printf("%s\n", cwdir);
	return (0);
}