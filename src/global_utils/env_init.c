#include "minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*ft_lstnew_env(char *var_name, char *value_var)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	new_node->var_name = var_name;
	new_node->value_var = value_var;
	new_node->next = NULL;
	if (!new_node->var_name || !new_node->value_var)
	{
		free(new_node->var_name);
		free(new_node->value_var);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	ft_lst_env_init(t_env **env, char **envp)
{
	t_env	*new;
	int		i;
	char	*var_name;
	char	*var_value;
	char	*equal_sign;

	new = NULL;
	i = 0;
	while (i < ft_arraylen(envp))
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign != NULL)
		{
			var_name = ft_strldup(envp[i], equal_sign - envp[i]);
			var_value = ft_strdup(equal_sign + 1);
			new = ft_lstnew_env(var_name, var_value);
			ft_lstadd_back_env(env, new);
			free(var_name);
			free(var_value);
		}
		i++;
	}
}
