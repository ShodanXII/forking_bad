/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:06:55 by achat             #+#    #+#             */
/*   Updated: 2025/06/25 16:15:25 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *s)
{
	printf("minishell: syntax error near unexpected token `%s'\n", s);
}

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || is_redir_token(type));
}

static void	update_quote_state(const char *str, int *s_quote, int *d_quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !(*d_quote))
			*s_quote = !(*s_quote);
		else if (str[i] == '"' && !(*s_quote))
			*d_quote = !(*d_quote);
		i++;
	}
}

int	check_unclosed_quotes(t_token *tokens)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (tokens)
	{
		if (tokens->value)
			update_quote_state(tokens->value, &sq, &dq);
		tokens = tokens->next;
	}
	if (sq || dq)
	{
		if (sq)
			printf("minishell: syntax error: unclosed single quote\n");
		else
			printf("minishell: syntax error: unclosed double quote\n");
		return (1);
	}
	return (0);
}
