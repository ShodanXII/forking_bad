/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:17:13 by achat             #+#    #+#             */
/*   Updated: 2024/11/01 19:45:56 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*counter;
	char			target2;

	target2 = (char)c;
	counter = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == target2)
		{
			counter = (char *)&s[i];
		}
		i++;
	}
	if (s[i] == c)
	{
		counter = (char *)&s[i];
	}
	return (counter);
}
