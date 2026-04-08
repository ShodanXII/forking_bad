/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_help_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:44:27 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 15:56:54 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_execve(t_ast *node, t_shell *sh)
{
	if (!ft_strcmp(node->args[0], "env"))
		return (ft_env(sh->env_lst));
	else if (!ft_strcmp(node->args[0], "export"))
		return (ft_export(&sh->env_lst, node->args));
	else if (!ft_strcmp(node->args[0], "cd"))
		return (ft_cd(&sh->env_lst, node->args[1]));
	else if (!ft_strcmp(node->args[0], "unset"))
		return (ft_unset(&sh->env_lst, node->args));
	else if (!ft_strcmp(node->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(node->args[0], "echo"))
		return (ft_echo(node->args));
	else if (!ft_strcmp(node->args[0], "exit"))
		ft_exit(node->args, sh);
	return (1);
}

int	env_size(t_env *env_lst)
{
	int	i;

	i = 0;
	while (env_lst)
	{
		i++;
		env_lst = env_lst->next;
	}
	return (i);
}

int	execute_builtin(t_ast *node, int infd, int outfd, t_shell *sh)
{
	int	st;

	if (handle_redirection(node, &infd, &outfd))
		return (1);
	sh->stdinput_fl = dup(0);
	sh->stdout_fl = dup(1);
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
	st = my_execve(node, sh);
	dup2(sh->stdinput_fl, 0);
	dup2(sh->stdout_fl, 1);
	close(sh->stdinput_fl);
	close(sh->stdout_fl);
	return (st);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
