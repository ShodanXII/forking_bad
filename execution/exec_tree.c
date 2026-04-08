/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:29:39 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 17:06:03 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_command(t_ast *node, int infd, int outfd, int cs)
{
	node->pid = fork();
	if (!node->pid)
	{
		signal(SIGINT, ss);
		signal(SIGQUIT, SIG_DFL);
		is_dir(node->args);
		if (node->args && is_builtin(node->args[0]))
			exit(execute_builtin(node, infd, outfd, node->sh));
		if (cs != -1)
			close(cs);
		if (handle_redirection(node, &infd, &outfd))
			exit(1);
		if (infd)
		{
			dup2(infd, 0);
			close(infd);
		}
		if (outfd != 1)
		{
			dup2(outfd, 1);
			close(outfd);
		}
		run_execve(node, node->sh);
	}
	return (pid_fail(node->pid));
}

int	abs_execute(t_ast *node, int infd, int outfd, int cs)
{
	if (!node->args)
	{
		if (handle_redirection(node, &infd, &outfd))
			node->sh->exit_status = 1;
	}
	else if (node->is_pipe || (!is_builtin(node->args[0])))
	{
		if (execute_command(node, infd, outfd, cs))
			return (1);
	}
	else
	{
		node->sh->exit_status = execute_builtin(node, infd, outfd, node->sh);
	}
	return (0);
}

void	cls_pipe(t_ast *node)
{
	close(node->right->ar_pipe[0]);
	close(node->right->ar_pipe[1]);
}

int	exec_word(t_ast *node, int fd, int outfd, int cs)
{
	if (abs_execute(node, fd, outfd, cs))
	{
		close_all_herdocs(node->redirs);
		return (1);
	}
	close_all_herdocs(node->redirs);
	return (0);
}

int	execute_tree(t_ast *node, int fd, int outfd, int cs)
{
	if (!node)
		return (1);
	if (node->e_token_type == TOKEN_PIPE)
	{
		flaging_pipe(node);
		node->right->ar_pipe = malloc(2 * sizeof(int));
		pipe(node->right->ar_pipe);
		if (execute_tree(node->left, fd, node->right->ar_pipe[1],
				node->right->ar_pipe[0]))
		{
			cls_pipe(node);
			return (1);
		}
		if (execute_tree(node->right, node->right->ar_pipe[0], outfd,
				node->right->ar_pipe[1]))
		{
			cls_pipe(node);
			return (1);
		}
		cls_pipe(node);
	}
	else if (node->e_token_type == TOKEN_WORD)
		return (exec_word(node, fd, outfd, cs));
	return (0);
}
