/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:09:38 by marouane          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:42 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flaging_pipe(t_ast *sequence)
{
	if (!sequence)
		return ;
	sequence->is_pipe = 1;
	flaging_pipe(sequence->left);
	flaging_pipe(sequence->right);
}
