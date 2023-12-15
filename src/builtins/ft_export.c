#include "minishell.h"

static t_env	*sort_list(t_env *lst)
{
	t_env	*tmp;
	t_env	*swap;

	tmp = lst;
	swap = ft_lstnew_env("", "", 0);
	while (lst->next != NULL)
	{
		if (lst->next && ft_strcmp(lst->var_name, lst->next->var_name) > 0)
		{
			swap->var_name = lst->var_name;
			swap->value_var = lst->value_var;
			lst->var_name = lst->next->var_name;
			lst->value_var = lst->next->value_var;
			lst->next->var_name = swap->var_name;
			lst->next->value_var = swap->value_var;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	ft_memfree(swap);
	return (lst);
}

static t_env	*copy_list(t_env *lst)
{
	t_env	*cpy;
	t_env	*tmp;

	tmp = lst;
	cpy = NULL;
	while (tmp)
	{
		if (!cpy)
			cpy = ft_lstnew_env(tmp->var_name, tmp->value_var, 1);
		else
			ft_lstadd_back_env(&cpy, ft_lstnew_env(tmp->var_name,
						tmp->value_var, 1));
		tmp = tmp->next;
	}
	return (cpy);
}

void	ft_export_without_arg(t_shell *msh)
{
	t_env	*tmp;
	t_env	*lst_cpy;

	lst_cpy = copy_list(msh->env);
	tmp = sort_list(lst_cpy);
	while (tmp)
	{
		if (!ft_strncmp(tmp->var_name, "_\0", 2))
			printf(" \r");
		else if (tmp->value_var[0])
			printf("declare -x %s=\"%s\"\n", tmp->var_name, tmp->value_var);
		else
			printf("declare -x %s\n", tmp->var_name);
		tmp = tmp->next;
	}
	ft_free_list(&lst_cpy);
}

int	check_export(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	name = get_env_name(arg);
	if (ft_isdigit(name[i]))
	{
		ft_printf("export: %s: not a valid identifier\n", arg);
		return (ft_memfree(name), 0);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
		{
			ft_printf("export: %s: not a valid identifier\n", arg);
			return (ft_memfree(name), 0);
		}
	}
	return (ft_memfree(name), 1);
}

int	check_variable(char *name, char *value, t_shell *info)
{
	t_env	*ptr;

	ptr = info->env;
	if (!ptr)
		return (0);
	while (ptr)
	{
		if (!ft_strcmp(ptr->var_name, name))
		{
			free(ptr->var_name);
			free(ptr->value_var);
			ptr->var_name = name;
			ptr->value_var = value;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	add_arg_to_env(char *var, t_shell *msh)
{
	t_env	*env;
	char	*name;
	char	*value;

	if (!ft_strrchr(var, '='))
		return ;
	name = get_env_name(var);
	value = get_env_value(var);
	if (!check_variable(name, value, msh))
	{
		env = ft_lstnew_env(name, value, 0);
		ft_lstadd_back_env(&msh->env, env);
	}
}

void	ft_export(t_shell *msh)
{
	int	i;

	msh->exit_status = 0;
	if (msh->count_cmd_args == 1)
		ft_export_without_arg(msh);
	else
	{
		i = 0;
		while (msh->cmd_args[++i])
		{
			if (check_export(msh->cmd_args[i]))
				add_arg_to_env(msh->cmd_args[i], msh);
			else
				msh->exit_status = 1;
		}
	}
}
