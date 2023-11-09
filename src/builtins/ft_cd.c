#include "minishell.h"

// problema con cd solo
void	ft_cd(t_shell *msh)
{
	char	*path;

	if (msh->cmd_args[1])
		path = ft_strdup(msh->cmd_args[1]);
	else
		path = NULL;
	// char	*old_path;
	// old_path = getcwd(NULL, 0);
	if (!path)
		path = getenv("HOME");
	// else if (!ft_strncmp(path, "-", 2))
	// {
	// found_env (OLDPWD no está establecido);
	// path = ft_getenv("OLDPWD", msh->envp);
	// }
	if (chdir(path))
		perror("cd");
	else
		ft_pwd(); //test
					// agregar add_oldpath();
}
