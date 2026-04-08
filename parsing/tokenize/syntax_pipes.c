/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:09:10 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 16:15:20 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_position(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current && current->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	check_consecutive_pipes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
	{
		if (current->type == TOKEN_PIPE && current->next->type == TOKEN_PIPE)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	is_pipe_with_no_command(t_token *current)
{
	if (current->next && is_operator_token(current->next->type))
		print_error(get_token_string(current->next->type));
	else
		print_error("newline");
	return (1);
}

int	check_empty_command(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;
	int		has_command;

	current = tokens;
	prev = NULL;
	has_command = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!has_command)
				return (is_pipe_with_no_command(current));
			has_command = 0;
		}
		else if (current->type == TOKEN_WORD)
			has_command = 1;
		prev = current;
		current = current->next;
	}
	if (prev && prev->type == TOKEN_PIPE)
		return (print_error("newline"), 1);
	return (0);
}

int	check_pipe_after_redir(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_APPEND)
		{
			next = current->next;
			if (next && next->type == TOKEN_WORD)
				next = next->next;
			else if (next && next->type == TOKEN_PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}
