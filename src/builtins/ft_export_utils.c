#include "minishell.h"

static int	check_variable(char *name, char *value, t_shell *info);

/**
 * @brief Agrega una variable de entorno al contexto del shell.
 *
 * Esta función extrae el nombre y el valor de una variable de entorno dada y la
 * agrega a la lista enlazada de variables de entorno del shell, si no existe
 * ya. La verificación se realiza mediante la función `check_variable`.
 *
 * @param var Una cadena que representa la variable de entorno en el formato
 * "nombre=valor".
 * @param msh Un puntero al contexto del shell.
 */
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

/**
 * @brief Verifica y actualiza una variable de entorno del shell.
 *
 * Esta función busca una variable de entorno con un nombre específico en la
 * lista enlazada de variables de entorno del shell. Si encuentra una
 * coincidencia, actualiza los valores de la variable; de lo contrario, no
 * realiza ninguna acción.
 *
 * @param name Una cadena que representa el nombre de la variable de entorno.
 * @param value Una cadena que representa el nuevo valor de la variable de
 * entorno.
 * @param info Un puntero al contexto del shell que contiene la lista de
 * variables de entorno actual.
 * @return 1 si la variable de entorno se actualiza correctamente,
 * 0 si no se encuentra la variable.
 */
static int	check_variable(char *name, char *value, t_shell *info)
{
	t_env	*ptr;

	ptr = info->env;
	if (!ptr)
		return (0);
	while (ptr)
	{
		if (!ft_strcmp(ptr->var_name, name))
		{
			ft_memfree(ptr->var_name);
			ft_memfree(ptr->value_var);
			ptr->var_name = name;
			ptr->value_var = value;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}
