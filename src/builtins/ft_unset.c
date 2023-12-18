#include "minishell.h"

static void	del_variable(t_env *node)
{
	ft_memfree(node->var_name);
	ft_memfree(node->value_var);
	ft_memfree(node);
}

static void	ft_eraser(char *name, t_env *ptr)
{
	if (!ft_strcmp(name, ptr->next->var_name))
		return ;
	while (ptr && ptr->next)
	{
		if (!ft_strcmp(name, ptr->next->var_name))
		{
			del_variable(ptr->next);
			ptr->next = ptr->next->next;
			return ;
		}
		ptr = ptr->next;
	}
}

void	ft_unset(t_shell *info)
{
	t_env	*ptr;
	int		i;

	i = 0;
	if (!info->cmd_args[i])
		return ;
	info->exit_status = 0;
	while (info->cmd_args[++i])
	{
		ptr = info->env;
		if (!ptr)
			return ;
		ft_eraser(info->cmd_args[i], ptr);
	}
}
