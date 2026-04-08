/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:32:29 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 15:56:56 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pid_fail(int pid)
{
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

void	is_dir(char **args)
{
	DIR	*dir;

	dir = opendir(args[0]);
	if (dir)
	{
		printf("minishell: %s is a directory\n", args[0]);
		closedir(dir);
		exit(126);
	}
}

void	cmd_nt_found(char *line)
{
	write(2, line, ft_strlen(line));
	write(2, ": command not found\n", 21);
	exit(127);
}

char	**create_mtr_env(t_env *env_lst)
{
	char	**mtr;
	char	*tmp;
	int		size;
	int		i;

	i = 0;
	size = env_size(env_lst);
	mtr = malloc((size + 1) * sizeof(char *));
	while (i < size)
	{
		tmp = ft_strjoin("=", env_lst->value);
		mtr[i] = ft_strjoin(env_lst->key, tmp);
		free(tmp);
		i++;
		env_lst = env_lst->next;
	}
	mtr[i] = NULL;
	return (mtr);
}

int	run_execve(t_ast *node, t_shell *sh)
{
	char	**env;
	char	*path;

	env = create_mtr_env(sh->env_lst);
	if (!env)
		return (0);
	path = debug_okda(env, node->args[0]);
	if (!path)
		cmd_nt_found(node->args[0]);
	execve(path, node->args, env);
	exit(1);
}
