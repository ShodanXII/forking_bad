/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:07 by achat             #+#    #+#             */
/*   Updated: 2024/11/02 18:26:28 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_l;
	size_t	dst_l;

	src_l = ft_strlen(src);
	if (dstsize == 0)
	{
		return (src_l);
	}
	dst_l = ft_strlen(dst);
	if (dst_l >= dstsize)
		dst_l = dstsize;
	if (dst_l == dstsize)
		return (dstsize + src_l);
	if (src_l < dstsize - dst_l)
	{
		ft_memcpy(dst + dst_l, src, src_l + 1);
	}
	else
	{
		ft_memcpy(dst + dst_l, src, dstsize - dst_l - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dst_l + src_l);
}
