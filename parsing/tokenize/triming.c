/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triming.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:30:08 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:15:48 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	trim_first(t_token *tok)
{
	char	*tmp;

	tmp = tok->value;
	if (tmp[0] == ' ')
	{
		tok->value = ft_strdup(tmp + 1);
		free(tmp);
	}
}

void	trim_last(t_token *tok)
{
	char	*tmp;
	int		size;

	tmp = tok->value;
	size = ft_strlen(tmp);
	if (tmp[size - 1] == ' ')
	{
		tok->value = ft_calloc(1, size);
		ft_memcpy(tok->value, tmp, size - 1);
		free(tmp);
	}
}

void	trim_first_last(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if ((!i && lst->quote_type == -1) || (lst->is_space
				&& lst->quote_type == -1))
			trim_first(lst);
		if (!lst->next && lst->quote_type == -1)
			trim_last(lst);
		lst = lst->next;
		i++;
	}
}
