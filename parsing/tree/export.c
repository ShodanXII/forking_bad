/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:13:35 by marouane          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:06 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_export(t_env *lst)
{
	while (lst)
	{
		if (!lst->ghost)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		else
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
	return (0);
}

int	export_valide(char *ptr)
{
	if (!ft_isalpha(ptr[0]) && ptr[0] != '_')
	{
		printf("bash: export: `%s': not a valid identifier\n", ptr);
		return (0);
	}
	return (1);
}

void	export_help_2(t_env **lst, char **mtr, int flag, int is_ghost)
{
	t_env	*temp;

	temp = *lst;
	while (temp)
	{
		if (!ft_strcmp(temp->key, mtr[0]))
		{
			free(temp->value);
			temp->value = ft_strdup(mtr[1]);
			flag = 1;
			break ;
		}
		temp = temp->next;
	}
	if (!flag)
		add_back_env(lst, new_env_node(mtr, is_ghost));
}

int	export_help(t_env **lst, char **export_param, int flag)
{
	int		i;
	char	**mtr;
	int		st;
	int		is_ghost;

	st = 0;
	i = 1;
	while (export_param[i])
	{
		is_ghost = 0;
		flag = 0;
		if (!ft_strchr(export_param[i], '='))
			is_ghost = 1;
		mtr = split_env(export_param[i]);
		if (!export_valide(mtr[0]))
		{
			st = 1;
			i++;
			continue ;
		}
		export_help_2(lst, mtr, flag, is_ghost);
		free_mtx(mtr);
		i++;
	}
	return (st);
}

int	ft_export(t_env **lst, char **export_param)
{
	int	flag;

	flag = 0;
	if (!export_param[1])
	{
		env_export(*lst);
		return (0);
	}
	return (export_help(lst, export_param, flag));
}
