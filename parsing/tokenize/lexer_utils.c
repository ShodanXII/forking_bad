/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:53:07 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 16:12:54 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_operator_type(char c, char next, int *type, int *len)
{
	*type = TOKEN_WORD;
	*len = 1;
	if (c == '>' && next == '>')
	{
		*type = TOKEN_APPEND;
		*len = 2;
	}
	else if (c == '<' && next == '<')
	{
		*type = TOKEN_HEREDOC;
		*len = 2;
	}
	else if (c == '>')
		*type = TOKEN_REDIR_OUT;
	else if (c == '<')
		*type = TOKEN_REDIR_IN;
	else if (c == '|')
		*type = TOKEN_PIPE;
}
