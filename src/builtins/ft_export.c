#include "minishell.h"

void	ft_export(t_shell *msh)
{
	size_t	v_len;
	char	*var_name;
	int		pos;
	int		i;

	i = 1;
	if (!msh->cmd_args[i])
		return (ft_env(msh));
	while (msh->cmd_args[i])
	{
		if (!ft_isalpha(msh->cmd_args[i][0]) && msh->cmd_args[i][0] != '_')
		{
			printf("export: %s: not a valid identifier\n", msh->cmd_args[i]);
			i++;
		}
		else if (!ft_strchr(msh->cmd_args[i], '='))
			i++;
		else
		{
			v_len = 0;
			while (msh->cmd_args[i][v_len] && msh->cmd_args[i][v_len] != '=')
				v_len++;
			var_name = ft_substr(msh->cmd_args[i], 0, v_len);
			pos = ft_foundenv(var_name, msh->envp);
			ft_memfree(var_name);
			if (pos < 0)
				msh->envp = ft_arrayadd(ft_strdup(msh->cmd_args[i]), msh->envp);
			else
			{
				msh->envp = ft_arraydelete(pos, msh->envp);
				msh->envp = ft_arrayadd(msh->cmd_args[i], msh->envp);
			}
			i++;
		}
	}
}
