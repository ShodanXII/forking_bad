/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:18:03 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:18:03 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cleanup(t_token *tokens, t_ast *head, char *input)
{
	if (tokens)
		free_tokens(tokens);
	if (input)
		free(input);
	if (head)
		free_tree(head);
}

int	wai_st(t_ast *node)
{
	int	status;

	if (node->right && node->right->is_pipe)
	{
		waitpid(node->right->pid, &status, 0);
	}
	else if (node->e_token_type == TOKEN_WORD)
	{
		signal (SIGINT, SIG_IGN);
		waitpid(node->pid, &status, 0);
		signal(SIGINT, handle_sign);
	}
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

static int	handle_syntax_and_expand(char *input, t_shell *sh,
		t_token **tokens)
{
	*tokens = lexer(input);
	if (check_syntax_errors(*tokens))
	{
		sh->exit_status = 258;
		free_tokens(*tokens);
		free(input);
		return (1);
	}
	if (expand_tokens(tokens, sh))
	{
		free_tokens(*tokens);
		free(input);
		sh->exit_status = 1;
		return (1);
	}
	return (0);
}

static t_ast	*build_ast_from_tokens(t_token *tokens, t_shell *sh,
		char *input)
{
	t_token	*new;
	t_ast	*head;

	trim_first_last(tokens);
	new = joining_tokens(tokens);
	head = build_ast(new, sh);
	if (!head)
	{
		printf("Parser error!\n");
		cleanup(new, head, input);
		return (NULL);
	}
	sh->exit_status = prepare_herdoc(head, sh);
	if (sh->exit_status)
	{
		cleanup(tokens, head, input);
		free_tokens(new);
		return (NULL);
	}
	free_tokens(new);
	return (head);
}

int	execute_command_sequence(char *input, t_shell *sh)
{
	t_ast		*head;
	t_token		*tokens;

	tokens = NULL;
	if (handle_syntax_and_expand(input, sh, &tokens))
		return (1);
	head = build_ast_from_tokens(tokens, sh, input);
	if (!head)
		return (1);
	execute_tree(head, 0, 1, -1);
	if (head->e_token_type == TOKEN_PIPE || (head->args
			&& !is_builtin(head->args[0])))
		sh->exit_status = wai_st(head);
	cleanup(tokens, head, input);
	return (0);
}
