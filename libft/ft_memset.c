/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:00:14 by achat             #+#    #+#             */
/*   Updated: 2024/11/05 10:30:14 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr_tmp;

	ptr_tmp = (unsigned char *)b;
	while (len > 0)
	{
		*(ptr_tmp++) = (unsigned char)c;
		len--;
	}
	return (b);
}
