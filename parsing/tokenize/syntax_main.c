/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:08:14 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 16:15:13 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_token_string(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return ("<");
	else if (type == TOKEN_REDIR_OUT)
		return (">");
	else if (type == TOKEN_APPEND)
		return (">>");
	else if (type == TOKEN_HEREDOC)
		return ("<<");
	else if (type == TOKEN_PIPE)
		return ("|");
	return ("unknown");
}

int	check_syntax_errors(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (check_pipe_position(tokens))
		return (1);
	if (check_consecutive_pipes(tokens))
		return (1);
	if (check_consecutive_redirections(tokens))
		return (1);
	if (check_redir_without_file(tokens))
		return (1);
	if (check_trailing_redir(tokens))
		return (1);
	if (check_pipe_after_redir(tokens))
		return (1);
	if (check_empty_command(tokens))
		return (1);
	return (0);
}
