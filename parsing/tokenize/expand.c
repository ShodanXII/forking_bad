/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:21 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:12:41 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ret_env_v(t_shell *sh, char *str)
{
	t_env	*lst;

	if (!ft_strcmp(str, "?"))
	{
		free(str);
		return (ft_itoa(sh->exit_status));
	}
	lst = sh->env_lst;
	while (lst)
	{
		if (!ft_strcmp(lst->key, str))
		{
			free(str);
			return (ft_strdup(lst->value));
		}
		lst = lst->next;
	}
	free(str);
	return (ft_strdup(""));
}

char	*take_key(char *line, int *end, t_shell *sh)
{
	int		size;
	char	*key;

	size = 0;
	while (line[size] && (ft_isalnum(line[size]) || line[size] == '_'))
		size++;
	if (line[0] == '?')
		size = 1;
	key = ft_calloc(size + 1, sizeof(char));
	if (!key)
		return (NULL);
	ft_memcpy(key, line, size);
	key = ret_env_v(sh, key);
	*end = size;
	return (key);
}

int	is_valide(t_token *next, char *line, int i)
{
	if (line[i] == '$' && line[i + 1])
		return (1);
	if (line[i] == '$' && next)
	{
		if (!next->is_space)
			return (1);
	}
	return (0);
}

void	expand_line_help(t_expand *exp_var, int i)
{
	ft_memcpy(exp_var->return_value, exp_var->tmp, i);
	ft_memcpy(exp_var->return_value + i, exp_var->ptr, ft_strlen(exp_var->ptr));
	ft_memcpy(exp_var->return_value + i + ft_strlen(exp_var->ptr), exp_var->tmp
		+ i + exp_var->offset + 1, ft_strlen(exp_var->tmp + i + exp_var->offset
			+ 1));
}

char	*expand_line(char **line, t_shell *sh, t_token *next)
{
	t_expand	exp_var;
	int			i;

	i = 0;
	exp_var.tmp = ft_strdup(*line);
	free(*line);
	*line = NULL;
	while (exp_var.tmp[i])
	{
		if (is_valide(next, exp_var.tmp, i))
		{
			exp_var.ptr = take_key(exp_var.tmp + i + 1, &exp_var.offset, sh);
			exp_var.size = i + ft_strlen(exp_var.ptr) + ft_strlen(exp_var.tmp
					+ exp_var.offset + i);
			exp_var.return_value = ft_calloc(exp_var.size + 1, 1);
			expand_line_help(&exp_var, i);
			free(exp_var.tmp);
			exp_var.tmp = exp_var.return_value;
			i = i + ft_strlen(exp_var.ptr) - 1;
			free(exp_var.ptr);
		}
		i++;
	}
	return (exp_var.tmp);
}
