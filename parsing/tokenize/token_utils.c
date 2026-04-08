/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:30:06 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 16:15:39 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_tokens(t_token **head, char *value, int type, t_qu_sp *s_q)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	new_token->is_space = s_q->is_space;
	new_token->quote_type = s_q->quote_type;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_token;
}

bool	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}
