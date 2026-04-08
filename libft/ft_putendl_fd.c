/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:29:27 by achat             #+#    #+#             */
/*   Updated: 2024/11/06 15:08:21 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	unsigned int	i;

	if (!str || fd < 0)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		++i;
	}
	write(fd, "\n", 1);
}
