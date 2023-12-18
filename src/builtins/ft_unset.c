#include "minishell.h"

static void	ft_eraser(char *name, t_env *ptr);
static void	del_variable(t_env *node);

/**
 * @brief Elimina variables de entorno específicas en el contexto del shell.
 *
 * Esta función elimina variables de entorno específicas, cuyos nombres se
 * proporcionan como argumentos al comando "unset", de la lista enlazada de
 * variables de entorno del shell.
 *
 * @param info Un puntero al contexto del shell.
 */
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

/**
 * @brief Elimina una variable de entorno específica de la lista enlazada.
 *
 * Esta función busca y elimina una variable de entorno específica de la lista
 * enlazada de variables de entorno.
 *
 * @param name Una cadena que representa el nombre de la variable de entorno que
 * se va a eliminar.
 * @param ptr Un puntero al nodo de la lista enlazada desde el cual comenzará la
 * búsqueda.
 */
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

/**
 * @brief Libera la memoria asociada a una variable de entorno.
 *
 * Esta función libera la memoria asignada a un nodo de la lista enlazada que
 * representa una variable de entorno, incluyendo el nombre y el valor de la
 * variable.
 *
 * @param node Un puntero al nodo de la lista enlazada que representa una
 * variable de entorno.
 */
static void	del_variable(t_env *node)
{
	ft_memfree(node->var_name);
	ft_memfree(node->value_var);
	ft_memfree(node);
}
