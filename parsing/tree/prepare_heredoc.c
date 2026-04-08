/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:46:47 by marouane          #+#    #+#             */
/*   Updated: 2025/06/25 16:33:44 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	exit(1);
}

void	read_froma_stdin(t_redir *redir, t_shell *sh)
{
	char	*line;
	char	*tmp;

	close(redir->fd[0]);
	line = readline("> ");
	while (line && ft_strcmp(redir->file, line))
	{
		if (redir->is_expand)
			line = expand_line(&line, sh, NULL);
		tmp = ft_strjoin(line, "\n");
		write(redir->fd[1], tmp, ft_strlen(tmp));
		free(line);
		free(tmp);
		line = readline("> ");
	}
	free(line);
	close(redir->fd[1]);
}

int	prepare_one_heredoc(t_redir *redir, t_shell *sh)
{
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			read_froma_stdin(redir, sh);
		}
		redir = redir->next;
	}
	return (0);
}

int	prepare_all_herdocs(t_ast *head, t_shell *sh)
{
	if (!head)
		return (0);
	if (head->e_token_type == TOKEN_WORD)
		prepare_one_heredoc(head->redirs, sh);
	prepare_all_herdocs(head->left, sh);
	prepare_all_herdocs(head->right, sh);
	return (0);
}

int	prepare_herdoc(t_ast *head, t_shell *sh)
{
	int	pid;
	int	st;

	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sigint_heredoc_handler);
		prepare_all_herdocs(head, sh);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else
	{
		waitpid(pid, &st, 0);
		if (WIFSIGNALED(st))
			return (1);
	}
	return (0);
}
