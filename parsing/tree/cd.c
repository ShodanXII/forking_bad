/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:35:04 by marouane          #+#    #+#             */
/*   Updated: 2025/06/25 16:15:55 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	upd_help(t_env **env, char *pwd, int type)
{
	char	**mtr;

	mtr = malloc(3 * sizeof(char *));
	if (type == 1)
		mtr[0] = ft_strdup("PWD");
	else
		mtr[0] = ft_strdup("OLDPWD");
	mtr[1] = pwd;
	mtr[2] = NULL;
	add_back_env(env, new_env_node(mtr, 0));
	free_mtx(mtr);
}

void	update_old_new_help(t_env *env, char *pwd, int *flag)
{
	free(env->value);
	env->value = pwd;
	*flag = 1;
}

void	update_old_new(t_env **env, char *old_pwd, char *pwd)
{
	int		pwd_flag;
	int		o_pwd_flag;
	t_env	*head;

	pwd_flag = 0;
	o_pwd_flag = 0;
	head = *env;
	while (head)
	{
		if (!ft_strcmp("OLDPWD", head->key))
			update_old_new_help(head, old_pwd, &o_pwd_flag);
		else if (!ft_strcmp("PWD", head->key))
			update_old_new_help(head, pwd, &pwd_flag);
		head = head->next;
	}
	if (!pwd_flag)
		upd_help(env, pwd, 1);
	if (!o_pwd_flag)
		upd_help(env, old_pwd, 2);
}

int	to_home(t_env **env, char *old_pwd)
{
	char	*pwd;
	t_env	*head;

	pwd = NULL;
	head = *env;
	while (head)
	{
		if (!ft_strcmp(head->key, "HOME"))
			pwd = ft_strdup(head->value);
		head = head->next;
	}
	if (!pwd)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	chdir(pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	update_old_new(env, old_pwd, pwd);
	return (0);
}

int	ft_cd(t_env **head, char *path)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (!path)
		return (to_home(head, old_pwd));
	if (chdir(path) == -1)
		return (cd_err(old_pwd));
	pwd = getcwd(NULL, 0);
	update_old_new(head, old_pwd, pwd);
	return (0);
}
