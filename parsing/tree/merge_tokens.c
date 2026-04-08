/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:49 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:39 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_args_to_cmd_node(t_ast *cmd_node, char **args, int count)
{
	int	i;

	i = 0;
	cmd_node->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_node->args)
		return ;
	while (i < count)
	{
		cmd_node->args[i] = args[i];
		i++;
	}
	cmd_node->args[count] = NULL;
	cmd_node->arg_count = count;
	cmd_node->cmd = ft_strdup(cmd_node->args[0]);
}

char	**grow_args_array(char **args, int *capacity)
{
	*capacity *= 2;
	return (ft_realloc(args, sizeof(char *) * (*capacity)));
}

static t_token	*handle_word_token(t_token *current, char ***args, int *count,
		int *capacity)
{
	if (*count >= *capacity - 1)
	{
		*args = grow_args_array(*args, capacity);
		if (!*args)
			return (NULL);
	}
	(*args)[(*count)++] = ft_strdup(current->value);
	return (current->next);
}

static t_token	*skip_redirection(t_token *current)
{
	current = current->next;
	if (current && current->type == TOKEN_WORD)
		current = current->next;
	return (current);
}

t_token	*merge_consecutive_words(t_token *tokens, t_ast *cmd_node)
{
	t_token	*current;
	int		word_count;
	int		capacity;
	char	**temp_args;

	current = tokens;
	word_count = 0;
	capacity = culc_words(tokens);
	temp_args = malloc(sizeof(char *) * capacity);
	if (!temp_args)
		return (tokens);
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
			current = handle_word_token(current, &temp_args, &word_count,
					&capacity);
		else if (is_redirection(current->type))
			current = skip_redirection(current);
		else
			current = current->next;
	}
	if (word_count > 0)
		copy_args_to_cmd_node(cmd_node, temp_args, word_count);
	free(temp_args);
	return (current);
}
