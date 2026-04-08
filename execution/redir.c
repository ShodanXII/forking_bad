/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:54:12 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 15:56:59 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_err(char *line)
{
	char	*str;

	str = ft_strjoin("minishell: ", line);
	perror(str);
	free(str);
	return (1);
}

int	app_norm_red(t_redir *lst, int *outfd)
{
	if (lst->type == TOKEN_APPEND)
		*outfd = open(lst->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		*outfd = open(lst->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*outfd == -1)
		return (open_err(lst->file));
	return (0);
}

int	handle_redirection(t_ast *node, int *infd, int *outfd)
{
	t_redir	*lst;

	lst = node->redirs;
	while (lst)
	{
		if (lst->type == TOKEN_REDIR_IN)
		{
			*infd = open(lst->file, O_RDONLY);
			if (*infd == -1)
				return (open_err(lst->file));
		}
		else if (lst->type == TOKEN_APPEND || lst->type == TOKEN_REDIR_OUT)
		{
			if (app_norm_red(lst, outfd))
				return (1);
		}
		else if (lst->type == TOKEN_HEREDOC)
		{
			close(lst->fd[1]);
			*infd = lst->fd[0];
		}
		lst = lst->next;
	}
	return (0);
}
