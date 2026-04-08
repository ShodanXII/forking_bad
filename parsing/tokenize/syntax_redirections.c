/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:13:31 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 16:15:32 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_consecutive_redirections(t_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	curr = tokens;
	while (curr)
	{
		if (is_redir_token(curr->type))
		{
			next = curr->next;
			if (next && is_redir_token(next->type))
			{
				print_error(get_token_string(next->type));
				return (1);
			}
			if (next && next->type == TOKEN_PIPE)
			{
				print_error("|");
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	check_trailing_redir(t_token *tokens)
{
	t_token	*current;
	t_token	*last_token;

	current = tokens;
	last_token = NULL;
	while (current)
	{
		last_token = current;
		current = current->next;
	}
	if (last_token && is_redir_token(last_token->type))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_redir_without_file(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		if (is_redir_token(current->type))
		{
			next = current->next;
			if (!next || next->type != TOKEN_WORD)
			{
				if (next && is_operator_token(next->type))
					print_error(get_token_string(next->type));
				else
					print_error("newline");
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}
