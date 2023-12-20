#include "minishell.h"

static void	process_quotes(t_shell *msh, t_lexer *tmp);
static void	process_env_var(char **data, char **dollar_pos, t_shell *msh);
static void	replace_env_var(char **data, char *p_fix, char *s_fix, char *value);

/**
 * @brief Reemplaza las variables de entorno en los tokens de comando.
 *
 * Esta función reemplaza las variables de entorno presentes en los tokens de
 * comando, archivo de entrada y archivo de salida de la lista de tokens (lexer)
 *
 * @param msh Un puntero a la estructura del shell.
 */
void	ft_replace(t_shell *msh)
{
	t_lexer	*tmp;

	if (!msh || !msh->lexer)
		return ;
	tmp = msh->lexer;
	while (tmp)
	{
		if (tmp->type == T_CMD || tmp->type == T_INFILE
			|| tmp->type == T_OUTFILE)
		{
			process_quotes(msh, tmp);
		}
		tmp = tmp->next;
	}
	ft_erase_node(&(msh->lexer));
}

/**
 * @brief Procesa las comillas y las variables de entorno en el token.
 *
 * Esta función procesa las comillas y las variables de entorno en el token
 * dado. Elimina las comillas si son comillas dobles y procesa las variables
 * de entorno presentes en el token.
 *
 * @param msh Un puntero a la estructura del shell (t_shell).
 * @param tmp Un puntero al nodo del token (t_lexer) que se está procesando.
 */
static void	process_quotes(t_shell *msh, t_lexer *tmp)
{
	char	*str;
	int		aux;
	char	*dollar_pos;

	aux = 0;
	if (tmp->data[0] == '\"')
	{
		str = ft_strtrim(tmp->data, "\"");
		ft_memfree(tmp->data);
		tmp->data = ft_strdup(str);
		ft_memfree(str);
		aux = 1;
	}
	dollar_pos = ft_strchr(tmp->data, '$');
	while (tmp->data[0] != '\'' && dollar_pos)
		process_env_var(&(tmp->data), &dollar_pos, msh);
	if (aux == 1 && tmp->type == T_CMD)
	{
		str = ft_strjoin("\"", tmp->data);
		ft_memfree(tmp->data);
		tmp->data = ft_strjoin(str, "\"");
		ft_memfree(str);
	}
}

/**
 * @brief Procesa una variable de entorno en una cadena de datos.
 *
 * Esta función procesa una variable de entorno en la cadena de datos
 * proporcionada. Extrae el prefijo, el sufijo y el valor de la variable de
 * entorno, y reemplaza la variable en la cadena de datos.
 *
 * @param data Un puntero al puntero de la cadena de datos que contiene la
 * variable de entorno.
 * @param dollar_pos Un puntero al puntero que apunta a la posición del símbolo
 * '$' en la cadena de datos.
 * @param msh Un puntero a la estructura del shell (t_shell).
 */
static void	process_env_var(char **data, char **dollar_pos, t_shell *msh)
{
	char	*prefix;
	char	*sufix;
	char	*env_value;

	prefix = ft_substr(*data, 0, *dollar_pos - *data);
	if (*((*dollar_pos) + 1) != '?')
	{
		env_value = process_env_substring(dollar_pos, &sufix, msh);
		replace_env_var(data, prefix, sufix, env_value);
	}
	else
	{
		if (*((*dollar_pos) + 2) != '\0')
			sufix = ft_strdup(*dollar_pos + 2);
		else
			sufix = "";
		env_value = ft_itoa(msh->exit_status);
		replace_env_var(data, prefix, sufix, env_value);
		ft_memfree(env_value);
	}
	*dollar_pos = ft_strchr(*data, '$');
}

/**
 * @brief Reemplaza una variable de entorno en una cadena de datos con su valor
 * correspondiente, toma el prefijo, el sufijo y el valor proporcionados, y crea
 * una nueva cadena de datos resultante.
 *
 * @param data Un puntero al puntero de la cadena de datos que contiene la
 * variable de entorno.
 * @param prefix El prefijo de la variable de entorno en la cadena de datos.
 * @param sufix El sufijo de la variable de entorno en la cadena de datos.
 * @param value El valor de la variable de entorno.
 */
static void	replace_env_var(char **data, char *prefix, char *sufix, char *value)
{
	char	*tmp;

	ft_memfree(*data);
	if (value)
	{
		tmp = ft_strjoin(prefix, value);
		ft_memfree(prefix);
		*data = ft_strjoin(tmp, sufix);
		ft_memfree(tmp);
	}
	else
	{
		if (prefix[0] != '\0' && sufix[0] != '\0')
			*data = ft_strjoin(prefix, sufix);
		else if (prefix[0] != '\0')
			*data = ft_strdup(prefix);
		else if (sufix[0] != '\0')
			*data = ft_strdup(sufix);
		else
			*data = "";
		ft_memfree(prefix);
	}
	if (sufix[0] != '\0')
		ft_memfree(sufix);
}
