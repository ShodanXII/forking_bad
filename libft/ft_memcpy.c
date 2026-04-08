/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:42:21 by achat             #+#    #+#             */
/*   Updated: 2024/11/01 19:14:55 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tmp_dst;
	char	*tmp_src;
	size_t	i;

	if ((dst == src) || !n)
		return (dst);
	tmp_src = (char *)src;
	tmp_dst = (char *)dst;
	i = 0;
	while (n > i)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dst);
}
