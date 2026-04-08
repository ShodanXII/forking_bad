/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:44:03 by achat             #+#    #+#             */
/*   Updated: 2025/04/12 22:27:11 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	size_t	i;
	int		flag;
	int		counter;

	i = 0;
	flag = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!flag)
				counter++;
			flag = 1;
		}
		else
			flag = 0;
		i++;
	}
	return (counter);
}

static void	*free_buffer(char **buffer, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	return (NULL);
}

static char	*extract_word(char const *str, char c)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	i = 0;
	while (!(str[len] == c) && str[len] != '\0')
		len++;
	word = malloc(sizeof (char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**buffer;
	int		i;

	if (!s)
		return (NULL);
	buffer = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!buffer)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (!(*s == c))
		{
			buffer[i] = extract_word(s, c);
			if (!buffer[i++])
				return (free_buffer(buffer, i - 1));
			s += ft_strlen(buffer[i - 1]);
		}
		else
			s++;
	}
	buffer[i] = NULL;
	return (buffer);
}
