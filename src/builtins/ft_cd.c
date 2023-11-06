#include "minishell.h"

char	*ft_getenv(char *var, char **env)
{
	int		i;
	int		len;
	char	*aux;

	len = 0;
	while (var[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		aux = ft_strchr(env[i], '=') + 1;
		if (len == aux - env[i] - 1)
			if (!ft_strncmp(var, env[i], len))
				return (ft_strdup(aux));
		i++;
	}
	return (ft_strdup(""));
}

void	ft_cd(t_shell *msh)
{
	char	*path;

	// char	*old_path;
	path = ft_strdup(msh->cmd_args[1]);
	// old_path = getcwd(NULL, 0);
	if (!path)
		path = ft_getenv("HOME", msh->envp);
	// else if (!ft_strncmp(path, "-", 2))
	// {
	// found_env (OLDPWD no está establecido);
	// path = ft_getenv("OLDPWD", msh->envp);
	// }
	if (chdir(path))
	{
		perror("cd");
	}
	//else
	//agregar add_oldpath();
	ft_memfree(path);
}
