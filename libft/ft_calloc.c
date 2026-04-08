/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:07:13 by achat             #+#    #+#             */
/*   Updated: 2024/11/03 17:26:50 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;
	size_t			tottal;

	i = 0;
	if (!count || !size)
		return (malloc(0));
	tottal = size * count;
	if (count != 0 && count != tottal / size)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
	{
		return (NULL);
	}
	while (i < count * size)
	{
		tmp[i++] = 0;
	}
	return (tmp);
}
