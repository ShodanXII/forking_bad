/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 06:33:53 by achat             #+#    #+#             */
/*   Updated: 2025/04/07 06:34:09 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*new_str1;
	unsigned char	*new_str2;

	new_str1 = (unsigned char *)str1;
	new_str2 = (unsigned char *)str2;
	while (*new_str1 == *new_str2 && *new_str1 && *new_str2)
	{
		new_str1++;
		new_str2++;
	}
	return (*new_str1 - *new_str2);
}
