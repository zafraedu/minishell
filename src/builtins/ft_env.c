#include "minishell.h"

void	ft_env(t_shell *msh)
{
	t_env	*tmp;

	if (msh->count_cmd_args > 1)
	{
		printf("env: %s: No such file or directory\n", msh->cmd_args[1]);
		msh->exit_status = 127;
		return ;
	}
	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var_name, "_\0", 2))
			printf("_=/usr/bin/env\n");
		else
			printf("%s=%s\n", tmp->var_name, tmp->value_var);
		tmp = tmp->next;
	}
	msh->exit_status = 0;
}
