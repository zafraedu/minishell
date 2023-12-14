#include "minishell.h"

char	**get_paths(char **envp)
{
	char	*path;

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	path = (*envp + 5);
	return (ft_split(path, ':'));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	t_env	*tmp;
	char	**paths;
	int		i;
	char	*tmp_str;
	char	*complete_path;

	tmp = env;
	while (ft_strncmp(tmp->var_name, "PATH", 4))
		tmp = tmp->next;
	paths = ft_split(tmp->value_var, ':');
	i = -1;
	while (paths[++i])
	{
		tmp_str = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(tmp_str, cmd);
		ft_memfree(tmp_str);
		if (!access(complete_path, X_OK))
		{
			ft_memfree_all(paths);
			return (complete_path);
		}
		ft_memfree(complete_path);
	}
	ft_memfree_all(paths);
	return (NULL);
}
