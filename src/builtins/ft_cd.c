#include "minishell.h"

static void	ft_change_oldpwd_env(t_shell *info);
static void	ft_change_pwd_env(t_shell *msh);


void	ft_cd(t_shell *msh)
{
	char	*path;

	path = NULL;
	if (msh->count_cmd_args > 2)
		return (printf("cd :too many arguments\n"), (void)NULL);
	ft_change_oldpwd_env(msh);
	if (msh->cmd_args[1])
		path = ft_strdup(msh->cmd_args[1]);
	else if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path))
		perror("cd");
	else
		ft_pwd(); //test
	ft_memfree(path);
	ft_change_pwd_env(msh);
}

static void	ft_change_oldpwd_env(t_shell *info)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("OLDPWD=", path);
	add_arg_to_env(to_send, info);
	free(to_send);
	free(path);
}

static void	ft_change_pwd_env(t_shell *msh)
{
	t_env	*tmp;
	char	*pwd;

	tmp = msh->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "PWD") == 0)
		{
			pwd = getcwd(NULL, 0);
			free(tmp->value_var);
			tmp->value_var = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
}
