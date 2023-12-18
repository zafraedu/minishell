#include "minishell.h"

/**
 * @brief Simula el comando `env` de shell.
 *
 * Esta función maneja el comando "env", que puede mostrar las variables de
 * entorno del shell actual o ejecutar un comando en un entorno modificado
 * si se proporciona un comando adicional.
 *
 * @param msh Un puntero al contexto del shell.
 */
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
