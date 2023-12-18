#include "minishell.h"

static void		ft_export_without_arg(t_shell *msh);
static t_env	*sort_list(t_env *lst);
static t_env	*copy_list(t_env *lst);
static int		check_export(char *arg);

/**
 * @brief Gestiona la exportación de variables de entorno en el shell.
 *
 * Esta función maneja el comando "export", que permite la exportación de
 * variables de entorno. Puede exportar variables específicas o, si no se
 * proporcionan argumentos, mostrar todas las variables exportadas.
 *
 * @param msh Un puntero al contexto del shell.
 */
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

/**
 * @brief Muestra todas las variables de entorno ordenadas y formateadas para
 * el comando "export".
 *
 * Esta función crea una copia ordenada de la lista de variables de entorno del
 * shell, y luego imprime cada variable en el formato adecuado para el comando
 * "export". Si el valor de la variable de entorno es una cadena no vacía, se
 * imprime en el formato "declare -x nombre=\"valor\""; de lo contrario, se
 * imprime "declare -x nombre".
 *
 * @param msh Un puntero al contexto del shell.
 */
static void	ft_export_without_arg(t_shell *msh)
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

/**
 * @brief Ordena la lista enlazada de variables de entorno por nombre de manera
 * ascendente.
 *
 * Esta función implementa el algoritmo de ordenación de burbuja para ordenar la
 * lista enlazada de variables de entorno por el nombre de las variables de
 * manera ascendente.
 *
 * @param lst Un puntero a la lista enlazada original de variables de entorno.
 * @return Un puntero a la lista enlazada ordenada por nombre de manera
 * ascendente.
 */
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

/**
 * @brief Devuelve una copia de la lista enlazada de variables de entorno.
 *
 * Esta función crea una nueva lista enlazada que es una copia exacta de la
 * lista original de variables de entorno, incluyendo la duplicación de cada
 * nodo y sus datos asociados.
 *
 * @param lst Un puntero a la lista enlazada original de variables de entorno.
 * @return Un puntero a la nueva lista enlazada que es una copia de la
 * lista original.
 */
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

/**
 * @brief Verifica si un argumento es válido.
 *
 * Esta función verifica si un argumento proporcionado al comando "export" es un
 * identificador válido, siguiendo las reglas de nomenclatura de variables de
 * entorno. Imprime un mensaje de error si el identificador no es válido.
 *
 * @param arg Una cadena que representa el argumento a verificar.
 * @return 1 si el argumento es un identificador válido, 0 si no lo es.
 */
static int	check_export(char *arg)
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
