/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:00:40 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 17:00:41 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	fr_rdi_lst(t_redir *tokens)
{
	t_redir	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_node(t_token *token)
{
	free(token->value);
	free(token);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	free_tree(t_ast *head)
{
	if (!head)
		return ;
	free_tree(head->left);
	free_tree(head->right);
	free(head->ar_pipe);
	free(head->cmd);
	free_mtx(head->args);
	fr_rdi_lst(head->redirs);
	free(head);
}
