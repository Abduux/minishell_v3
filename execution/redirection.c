/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:33:20 by ali               #+#    #+#             */
/*   Updated: 2024/01/28 11:29:23 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void change_stdio(int newfd, int to_change)
{
    dup2(newfd, to_change);
    close(newfd);
}

static int redir_out(t_redirection *redir)
{
    int fd;
    
    fd = open(redir->file_name , O_CREAT  | O_RDWR | O_TRUNC, 0644);
    if(fd == -1)
    {
        if (!redir->file_name || !*redir->file_name)
            return ft_err_msg(ERR_NO_SUCH_FILE, 1, redir->file_name);
        if(access(redir->file_name, F_OK) == 0)
        {
            if (access(redir->file_name, W_OK) == -1)
			    return ft_err_msg(ERR_PERM_DENIED, 1, redir->file_name);
             return ft_err_msg(OK, 0, redir->file_name);
        }
        return ft_err_msg(ERR_NO_SUCH_FILE, 1, redir->file_name);
    }
    change_stdio(fd, STDOUT_FILENO);
    return 0;
}        


static int redir_in(t_redirection *redir)
{
    int fd;
    
    fd = open(redir->file_name , O_RDONLY, 0644);
    if(fd == -1)
    {
        if (!redir->file_name || !*redir->file_name)
            return (ft_err_msg(ERR_NO_SUCH_FILE, 1, redir->file_name));
        if(access(redir->file_name, F_OK) == 0)
        {
            if (access(redir->file_name, R_OK) == -1)
                return (ft_err_msg(ERR_PERM_DENIED, 1, redir->file_name));
		    return (ft_err_msg(ERR_PERM_DENIED, 42, redir->file_name));
        }
	   return ft_err_msg(ERR_NO_SUCH_FILE, 1, redir->file_name);
    }
    change_stdio(fd, STDIN_FILENO);
    return 0;
}

static int redir_append(t_redirection *redir)
{
    int fd;
    
    fd = open(redir->file_name , O_CREAT | O_WRONLY | O_APPEND, 0644);
    if(fd == -1)
    {
        if (!redir->file_name || !*redir->file_name)
            return ft_err_msg(ERR_NO_SUCH_FILE, 1, redir->file_name);
        if(access(redir->file_name, F_OK) == 0)
        {
            if (access(redir->file_name, W_OK) == -1)
			    return ft_err_msg(ERR_PERM_DENIED, 1, redir->file_name);
             return ft_err_msg(OK, 0, redir->file_name);
        }
        return ft_err_msg(ERR_NO_SUCH_FILE, 1, redir->file_name);
    }
    change_stdio(fd, STDOUT_FILENO);
    return 0;
}

int    redir(t_redirection *redirections)
{
    t_redirection   *redir;

    redir = redirections;
    while (redir)
    {
        if (redir->type == REDIR_HEREDOC)
            change_stdio(redir->pipe[0], STDIN_FILENO);
        else if(redir->type == REDIR_OUTPUT && redir_out(redir) != 0)
            return 1;
        else if (redir->type == REDIR_INPUT && redir_in(redir) != 0)
            return 1;
        else if(redir->type == REDIR_APPEND && redir_append(redir) != 0)
            return 1;
        redir = redir->next;
    }
    return (0);
}
