/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:21:22 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 15:21:56 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_help(char **mtx, t_token **lst, int is_space)
{
	int		i;
	t_qu_sp	q_s_1;
	t_qu_sp	q_s_2;

	q_s_1.is_space = is_space;
	q_s_1.quote_type = -1;
	q_s_2.is_space = 1;
	q_s_2.quote_type = -1;
	i = 0;
	while (mtx[i])
	{
		if (!i)
			add_tokens(lst, mtx[i], TOKEN_WORD, &q_s_1);
		else
			add_tokens(lst, mtx[i], TOKEN_WORD, &q_s_2);
		i++;
	}
}
