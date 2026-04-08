/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_wdakxi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:22:29 by achat             #+#    #+#             */
/*   Updated: 2025/06/21 23:22:29 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*advance_token(t_token *token, int steps)
{
	while (token && steps-- > 0)
		token = token->next;
	return (token);
}

int	culc_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			count++;
		else if (is_redirection(token->type))
		{
			token = token->next;
			if (token && token->type == TOKEN_WORD)
				token = token->next;
			continue ;
		}
		token = token->next;
	}
	return (count + 1);
}

t_ast	*build_command_node(t_token **tokens, t_shell *sh)
{
	t_ast	*cmd_node;

	cmd_node = create_ast_node(TOKEN_WORD, sh);
	if (!cmd_node)
		return (NULL);
	cmd_node->redirs = handle_redir(tokens);
	*tokens = merge_consecutive_words(*tokens, cmd_node);
	return (cmd_node);
}

t_ast	*connect_pipe_nodes(t_token **tokens, t_shell *sh)
{
	t_ast	*left;
	t_ast	*pipe_node;

	left = build_command_node(tokens, sh);
	if (!left) 
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		pipe_node = create_ast_node(TOKEN_PIPE, sh);
		if (!pipe_node)
		{
			free_tree(left);
			return (NULL);
		}
		pipe_node->left = left;
		*tokens = (*tokens)->next;
		pipe_node->right = build_command_node(tokens, sh);
		if (!pipe_node->right)
		{
			free_tree(pipe_node);
			return (NULL);
		}
		left = pipe_node;
	}
	return (left);
}

t_ast	*build_ast(t_token *tokens, t_shell *sh)
{
	return (connect_pipe_nodes(&tokens, sh));
}
