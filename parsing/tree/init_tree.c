/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:48:19 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:14 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	initialize_ast_fields(t_ast *node, t_token_type type, t_shell *sh)
{
	node->e_token_type = type;
	node->cmd = NULL;
	node->args = NULL;
	node->sh = sh;
	node->arg_count = 0;
	node->ar_pipe = NULL;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	node->pid = 0;
	node->is_pipe = 0;
}

t_ast	*create_ast_node(t_token_type type, t_shell *sh)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	initialize_ast_fields(node, type, sh);
	return (node);
}
