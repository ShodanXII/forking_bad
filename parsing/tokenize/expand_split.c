/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:56:57 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:12:34 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	word = malloc(sizeof(char) * (len + 1));
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

void	split_exp_help(char **buffer, char const *s, char is_space, int i)
{
	char	*tmp;

	buffer[i] = extract_word(s, ' ');
	if (is_space == ' ' && !i)
	{
		tmp = buffer[i];
		buffer[i] = ft_strjoin(" ", buffer[i]);
		free(tmp);
	}
}

void	split_exp_help_2(char **buffer, char const *s, int i)
{
	char	*tmp;

	if (*(s - 1) == ' ')
	{
		tmp = buffer[i - 1];
		buffer[i - 1] = ft_strjoin(buffer[i - 1], " ");
		free(tmp);
	}
	buffer[i] = NULL;
}

char	**ft_split_exp(char const *s, char c)
{
	char	**buffer;
	char	is_space;
	int		i;

	buffer = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!buffer)
		return (NULL);
	i = 0;
	is_space = *s;
	while (*s != '\0')
	{
		if (!(*s == c))
		{
			split_exp_help(buffer, s, is_space, i);
			if (!buffer[i++])
				return (free_buffer(buffer, i - 1));
			s += ft_strlen(buffer[i - 1]);
		}
		else
			s++;
	}
	split_exp_help_2(buffer, s, i);
	return (buffer);
}
