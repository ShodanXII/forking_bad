/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:18:43 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 15:19:35 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_first_node(t_token **token, t_token *next, char *line, int is_space)
{
	char	**mtx;
	t_token	*lst;

	lst = NULL;
	mtx = ft_split_exp(line, ' ');
	if (!mtx)
		return ;
	if (!mtx[0])
	{
		free((*token)->value);
		free(mtx);
		(*token)->value = ft_strdup("");
		return ;
	}
	add_help(mtx, &lst, is_space);
	free_mtx(mtx);
	free_node(*token);
	*token = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = next;
}

void	add_nodes(t_token *token, t_token *next, char *line, int is_space)
{
	char	**mtx;
	t_token	*lst;
	t_token	*tmp;

	lst = NULL;
	mtx = ft_split_exp(line, ' ');
	if (!mtx)
		return ;
	if (!mtx[0])
	{
		free(token->next->value);
		token->next->value = ft_strdup("");
		free(mtx);
		return ;
	}
	add_help(mtx, &lst, is_space);
	tmp = token->next;
	token->next = lst;
	while (lst->next)
		lst = lst->next;
	free_mtx(mtx);
	free_node(tmp);
	lst->next = next;
}

void	is_here_doc(t_token *tmp, int *is_heredoc)
{
	if (tmp->next->type == TOKEN_HEREDOC)
		*is_heredoc = 1;
	else
		*is_heredoc = 0;
}

void	is_redir_tk(t_token *token, int *flag)
{
	if (token->type == TOKEN_APPEND || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT)
		*flag = 1;
	else if (token->type != TOKEN_WORD && !token->is_space)
		*flag = 0;
}

int	is_ambeguous(char *line)
{
	if (!ft_strlen(line) || count_words(line, ' ') > 1)
		return (1);
	return (0);
}
