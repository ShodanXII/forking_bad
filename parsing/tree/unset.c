/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:39:43 by marouane          #+#    #+#             */
/*   Updated: 2025/06/25 16:17:10 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rm_node(t_env **lst, char *str)
{
	t_env	*tmp;
	t_env	*env_lst;

	env_lst = *lst;
	if (!ft_strcmp(env_lst->key, str))
	{
		tmp = *lst;
		*lst = tmp->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
	}
	while (env_lst->next)
	{
		if (!ft_strcmp(env_lst->next->key, str))
		{
			tmp = env_lst->next;
			env_lst->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		env_lst = env_lst->next;
	}
}

int	ft_unset(t_env **lst, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		rm_node(lst, argv[i]);
		i++;
	}
	return (0);
}
