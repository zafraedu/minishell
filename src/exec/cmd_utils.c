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
