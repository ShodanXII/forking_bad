/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:27:27 by achat             #+#    #+#             */
/*   Updated: 2024/11/02 18:13:28 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_tmp;
	char	*src_tmp;
	size_t	i;

	if (dst == src || len == 0)
		return (dst);
	dst_tmp = (char *)dst;
	src_tmp = (char *)src;
	i = 0;
	if (dst_tmp > src_tmp)
	{
		while (len-- > 0)
		{
			dst_tmp[len] = src_tmp[len];
		}
	}
	else
	{
		while (i < len)
		{
			dst_tmp[i] = src_tmp[i];
			i++;
		}
	}
	return (dst);
}
