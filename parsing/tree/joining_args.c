/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:16:27 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:30 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cp_lbakiya(t_token *old, t_token *new)
{
	new->is_space = 1;
	new->type = old->type;
	new->next = NULL;
	new->quote_type = old->quote_type;
	new->prev = old->prev;
}

void	token_join_help(t_token *new_tk, t_token *tmp, char *rt_tmp)
{
	if (tmp->quote_type == 2 || tmp->quote_type == 1)
		new_tk->quote_type = 2;
	free(rt_tmp);
}

t_token	*token_join(t_token **start)
{
	t_token	*tmp;
	t_token	*new_tk;
	char	*rt_tmp;

	new_tk = malloc(sizeof(t_token));
	if (!new_tk)
		return (NULL);
	tmp = *start;
	new_tk->value = ft_strdup(tmp->value);
	cp_lbakiya(tmp, new_tk);
	if (new_tk->type != TOKEN_WORD)
	{
		*start = tmp->next;
		return (new_tk);
	}
	tmp = tmp->next;
	while (tmp && !tmp->is_space && (tmp->type == TOKEN_WORD))
	{
		rt_tmp = new_tk->value;
		new_tk->value = ft_strjoin(new_tk->value, tmp->value);
		token_join_help(new_tk, tmp, rt_tmp);
		tmp = tmp->next;
	}
	*start = tmp;
	return (new_tk);
}

void	add_f_lkhr(t_token **head, t_token *new)
{
	t_token	*tmp;

	tmp = *head;
	if (!*head)
	{
		new->next = *head;
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*joining_tokens(t_token *old_lst)
{
	t_token	*new_lst;
	t_token	*new_node;

	new_lst = NULL;
	while (old_lst)
	{
		new_node = token_join(&old_lst);
		add_f_lkhr(&new_lst, new_node);
	}
	return (new_lst);
}
