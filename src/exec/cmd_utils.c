#include "minishell.h"

char	**env_to_array(t_shell *info)
{
	int		len;
	t_env	*tmp;
	char	**ret;
	char	*tmp_str;

	len = 0;
	tmp = info->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = malloc((sizeof(char *) * len) + 1);
	tmp = info->env;
	len = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->var_name, "=");
		ret[len] = ft_strjoin(tmp_str, tmp->value_var);
		ft_memfree(tmp_str);
		tmp = tmp->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	int		i;
	char	*tmp_str;
	char	*complete_path;

	while (env && ft_strncmp(env->var_name, "PATH", 4))
		env = env->next;
	if (!env)
		return (NULL);
	paths = ft_split(env->value_var, ':');
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
