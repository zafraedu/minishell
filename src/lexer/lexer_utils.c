#include "minishell.h"

/**
 * @brief Determina el tipo de token en una posición dada en una cadena.
 *
 * @param str La cadena en la que buscar el tipo de token.
 * @param i La posición en la cadena donde se encuentra el carácter que
 * representa el token.
 * @return El tipo de token, que puede ser T_PIPE, T_APPEND, T_REDIR_OUT,
 * T_REDIR_IN, o T_GENERAL.
 */
int	get_type(char *str, int i)
{
	if (str[i] == '|')
		return (T_PIPE);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (T_APPEND);
		return (T_REDIR_OUT);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (T_HEREDOC);
		return (T_REDIR_IN);
	}
	return (T_GENERAL);
}

/**
 * @brief Agrega un tipo de token al final de la lista de tokens en el lexer.
 *
 * @param lexer Puntero al puntero al primer elemento de la lista de tokens(lex)
 * @param type El tipo de token que se va a agregar.
 */
void	lexer_add_type(t_lexer **lexer, int type)
{
	t_lexer	*current;

	current = *lexer;
	while (current->next != NULL)
		current = current->next;
	current->type = type;
}

/**
 * @brief Agrega un nuevo token al final de la lista de tokens en el lexer.
 *
 * @param lexer Puntero al puntero al primer elemento de la lista de tokens(lex)
 * @param input La cadena de entrada de la cual se extraerá el token.
 * @param i La posición en la cadena de entrada donde comienza el token.
 * @param size El tamaño del token a extraer.
 */
void	ft_add_token(t_lexer **lexer, char *input, int i, int size)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
	new->data = ft_substr(input, i, size);
	new->next = NULL;
	if (*lexer == NULL)
		*lexer = new;
	else
	{
		current = *lexer;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

/**
 * @brief Busca el valor asociado a un nombre de variable en la lista de entorno
 * del shell.
 *
 * @param str El nombre de la variable cuyo valor se busca.
 * @param msh Puntero a la estructura del shell que contiene la lista de entorno
 * @return Puntero a la cadena que representa el valor asociado a la variable,
 * o NULL si no se encuentra.
 */
char	*ft_find(char *str, t_shell *msh)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, str))
			return (tmp->value_var);
		tmp = tmp->next;
	}
	return (NULL);
}
