/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:31:55 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 16:15:10 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*create_redir_node(t_token_type type, char *file, int is_expnd)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->type = type;
	new_redir->next = NULL;
	if (type == TOKEN_HEREDOC)
		pipe(new_redir->fd);
	if (is_expnd == 2 || is_expnd == 1)
		new_redir->is_expand = 0;
	else
		new_redir->is_expand = 1;
	return (new_redir);
}

static void	append_redir(t_redir **head, t_redir **tail, t_redir *new_redir)
{
	if (!*head)
	{
		*head = new_redir;
		*tail = new_redir;
	}
	else
	{
		(*tail)->next = new_redir;
		*tail = new_redir;
	}
}

t_redir	*handle_redir(t_token **tokens)
{
	t_token	*curr;
	t_redir	*redirs;
	t_redir	*redir_tail;
	t_redir	*new_redir;

	curr = *tokens;
	redirs = NULL;
	redir_tail = NULL;
	while (curr && curr->next && curr->type != TOKEN_PIPE)
	{
		if (is_redirection(curr->type))
		{
			new_redir = create_redir_node(curr->type, curr->next->value,
					curr->next->quote_type);
			append_redir(&redirs, &redir_tail, new_redir);
			curr = curr->next->next;
		}
		else
			curr = curr->next;
	}
	return (redirs);
}
