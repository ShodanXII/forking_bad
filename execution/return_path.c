/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:50:31 by msaadaou          #+#    #+#             */
/*   Updated: 2025/06/25 15:57:02 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*helper_path_cmd(char **commands_path, char *cmd)
{
	int		i;
	char	*command_path;

	i = 0;
	while (commands_path[i])
	{
		command_path = ft_strjoin(ft_strjoin(commands_path[i], "/"), cmd);
		if (!command_path)
		{
			free(cmd);
			return (NULL);
		}
		if (!access(command_path, X_OK))
		{
			free(cmd);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free(cmd);
	return (NULL);
}

char	*helper_path(char *str, char *cmd, int size)
{
	char	*complete_path;
	char	**commands_path;

	complete_path = ft_substr(str, size, ft_strlen(str) - size);
	if (!complete_path)
		return (NULL);
	commands_path = ft_split(complete_path, ':');
	if (!commands_path)
	{
		free(complete_path);
		return (NULL);
	}
	free(complete_path);
	return (helper_path_cmd(commands_path, cmd));
}

char	*debug_okda(char **env, char *cmd)
{
	char	*str;
	char	*cmdr;
	int		i;

	if (!cmd)
		return (NULL);
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	if (cmd[0] == '.' || cmd[0] == '/')
		return (NULL);
	cmdr = ft_strjoin("/", cmd);
	if (!cmdr)
		return (NULL);
	i = 0;
	while (env[i])
	{
		str = ft_strnstr(env[i], "PATH=", ft_strlen("PATH="));
		if (str)
			return (helper_path(str, cmdr, ft_strlen("PATH=")));
		i++;
	}
	return (NULL);
}
