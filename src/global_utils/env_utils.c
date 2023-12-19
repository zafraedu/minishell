#include "minishell.h"

/**
 * @brief Obtiene el nombre de la variable de entorno.
 *
 * @param fullenv La cadena completa de variable de entorno que contiene el
 * nombre y el valor de la variable.
 * @return Un puntero a una nueva cadena que representa el nombre de la variable
 * de entorno.
 */
char	*get_env_name(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, 0, i));
}

/**
 * @brief Obtiene el valor de la variable de entorno.
 *
 * @param fullenv La cadena completa de variable de entorno que contiene el
 * nombre y el valor de la variable.
 * @return Un puntero a una nueva cadena que representa el valor de la variable
 * de entorno.
 */
char	*get_env_value(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	if (fullenv[i + 1] == '\"')
		return (ft_substr(fullenv, i + 2, ft_strlen(fullenv) - i));
	else
		return (ft_substr(fullenv, i + 1, ft_strlen(fullenv) - i));
}

/**
 * @brief Agrega un nuevo nodo al final de la lista de variables de entorno.
 *
 * @param lst Puntero al puntero al inicio de la lista de variables de entorno.
 * @param new El nuevo nodo que se va a agregar al final de la lista.
 */
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

/**
 * @brief Crea un nuevo nodo de la lista de variables de entorno.
 *
 * @param name El nombre de la variable de entorno.
 * @param value El valor de la variable de entorno.
 * @param alloc Un indicador que especifica si se debe asignar memoria para
 * las cadenas de nombre y valor.
 * @return Un puntero al nuevo nodo de la lista de variables de entorno.
 */
t_env	*ft_lstnew_env(char *name, char *value, int alloc)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	new_node->var_name = name;
	new_node->value_var = value;
	if (alloc)
	{
		new_node->var_name = ft_strdup(name);
		new_node->value_var = ft_strdup(value);
		if (!new_node->var_name || !new_node->value_var)
		{
			ft_memfree(new_node->var_name);
			ft_memfree(new_node->value_var);
			ft_memfree(new_node);
			return (NULL);
		}
	}
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Inicializa la lista de variables de entorno a partir de `envp`.
 *
 * @param env Puntero al puntero al inicio de la lista de variables de entorno.
 * @param envp El array de cadenas de entorno.
 */
void	ft_lst_env_init(t_env **env, char **envp)
{
	t_env	*new;
	int		i;
	char	*var_name;
	char	*var_value;

	new = NULL;
	i = -1;
	while (++i < ft_arraylen(envp))
	{
		var_name = get_env_name(envp[i]);
		var_value = get_env_value(envp[i]);
		new = ft_lstnew_env(var_name, var_value, 1);
		ft_lstadd_back_env(env, new);
		ft_memfree(var_name);
		ft_memfree(var_value);
	}
}
