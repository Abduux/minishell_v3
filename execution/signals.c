#include "../minishell.h"

static void    ctrl_c_handler()
{
    printf("\n");
    // printf("╭─"ANSI_COLOR"Minishell v2.0$\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    dont_quit(pid_t pid)
{
    (void) pid;
}



void    handle_signals()
{
    signal(SIGINT , ctrl_c_handler);
    signal(SIGQUIT , SIG_IGN);
    return;
}