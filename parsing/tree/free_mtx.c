/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mtx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:41:24 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:11 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	close_all_herdocs(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_HEREDOC)
		{
			close(redirs->fd[0]);
			close(redirs->fd[1]);
		}
		redirs = redirs->next;
	}
	return (0);
}

void	free_mtx(char **mtr)
{
	int	i;

	if (!mtr)
		return ;
	i = 0;
	while (mtr[i])
	{
		free(mtr[i]);
		i++;
	}
	free(mtr);
}
