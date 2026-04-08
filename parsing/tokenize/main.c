/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:34:59 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:15:03 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	sh;
	char	*input;

	(void)ac;
	(void)av;
	some_inits(&sh, env);
	get_env(&(sh.env_lst), env);
	while (1)
	{
		input = get_user_input();
		if (handle_input(input, &sh))
			continue ;
	}
	free_env(sh.env_lst);
	return (0);
}
