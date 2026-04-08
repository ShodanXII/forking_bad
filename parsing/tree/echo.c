/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:51:21 by marouane          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:00 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo_valide(char *line)
{
	int	i;

	i = 0;
	if (line[0] != '-')
		return (0);
	i++;
	while (line[i])
	{
		if (line[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (args[1] && echo_valide(args[1]))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		if ((i != 1 && !flag) || (i != 2 && flag))
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
