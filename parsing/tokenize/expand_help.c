/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:12:01 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:12:18 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_tokens_3(t_token *tmp, t_shell *sh, int is_heredoc)
{
	char	*line;

	if (!is_heredoc)
	{
		line = expand_line(&tmp->next->value, sh, tmp->next->next);
		tmp->next->value = line;
	}
}

int	is_ambg(int is_redir, char *line, char *tmp)
{
	if (is_redir && is_ambeguous(line))
	{
		free(line);
		printf("minishell: %s: ambiguous redirect\n", tmp);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

void	is_her_red(t_token *tmp, int *is_heredoc, int *is_redir)
{
	is_here_doc(tmp, is_heredoc);
	is_redir_tk(tmp->next, is_redir);
}

int	expand_tokens_2(t_token **token, t_shell *sh, int is_heredoc, int is_redir)
{
	t_token	*tmp;
	char	*tmp_2;
	char	*line;

	tmp = *token;
	while (tmp->next)
	{
		if (tmp->next->type == TOKEN_WORD && tmp->next->quote_type == -1)
		{
			if (!is_heredoc)
			{
				tmp_2 = ft_strdup(tmp->next->value);
				line = expand_line(&tmp->next->value, sh, tmp->next->next);
				if (is_ambg(is_redir, line, tmp_2))
					return (1);
				add_nodes(tmp, tmp->next->next, line, tmp->next->is_space);
				free(line);
			}
		}
		else if (tmp->next->type == TOKEN_WORD && tmp->next->quote_type == 2)
			expand_tokens_3(tmp, sh, is_heredoc);
		is_her_red(tmp, &is_heredoc, &is_redir);
		tmp = tmp->next;
	}
	return (0);
}

int	expand_tokens(t_token **token, t_shell *sh)
{
	char	*line;
	int		is_heredoc;
	int		is_redir;

	line = NULL;
	is_heredoc = 0;
	is_redir = 0;
	is_redir_tk(*token, &is_redir);
	if ((*token)->type == TOKEN_HEREDOC)
		is_heredoc = 1;
	else if ((*token)->type == TOKEN_WORD && (*token)->quote_type == -1)
	{
		line = expand_line(&(*token)->value, sh, (*token)->next);
		add_first_node(token, (*token)->next, line, (*token)->is_space);
		free(line);
	}
	else if ((*token)->type == TOKEN_WORD && (*token)->quote_type == 2)
	{
		line = expand_line(&(*token)->value, sh, (*token)->next);
		(*token)->value = line;
	}
	return (expand_tokens_2(token, sh, is_heredoc, is_redir));
}
