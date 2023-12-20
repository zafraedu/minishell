#include "minishell.h"

static t_lexer	*remove_node(t_lexer **lexer, t_lexer *tmp, t_lexer *prev);
static void		ft_next_dollar_pos(char **dol_pos, char **str, char **sufix);
static void		ft_no_next_dollar_pos(char **dol_pos, char **str, char **sufix);

/**
 * @brief Elimina nodos vacíos o nulos de una lista de tokens.
 *
 * Recorre la lista y elimina los nodos que cumplen con las condiciones
 * especificadas.
 *
 * @param lexer Un puntero al puntero de la lista de tokens.
 */
void	ft_erase_node(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*prev;

	tmp = *lexer;
	prev = NULL;
	while (tmp)
	{
		if (tmp->data == NULL || tmp->data[0] == '\0')
			tmp = remove_node(lexer, tmp, prev);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

/**
 * @brief Elimina un nodo de la lista de tokens.
 *
 * Si el nodo a eliminar es el primero de la lista, actualiza el puntero de la
 * lista. De lo contrario, ajusta los punteros de los nodos adyacentes.
 *
 * @param lexer Un puntero al puntero de la lista de tokens.
 * @param tmp El nodo que se va a eliminar.
 * @param prev El nodo anterior al nodo que se va a eliminar.
 *
 * @return Un puntero al siguiente nodo después de la eliminación.
 */
static t_lexer	*remove_node(t_lexer **lexer, t_lexer *tmp, t_lexer *prev)
{
	t_lexer	*next;

	next = NULL;
	if (prev == NULL)
	{
		*lexer = tmp->next;
		next = *lexer;
		ft_memfree(tmp);
	}
	else
	{
		prev->next = tmp->next;
		next = prev->next;
		ft_memfree(tmp);
	}
	return (next);
}

/**
 * @brief Procesa una subcadena de variables de entorno en una cadena dada.
 *
 * Esta función procesa una subcadena que comienza con el símbolo "$" y termina
 * en otro "$" o en el final de la cadena. Extrae la subcadena de la cadena
 * principal y busca el valor correspondiente en las variables de entorno del
 * intérprete de comandos.
 *
 * @param dol_pos Un puntero al puntero que apunta al símbolo "$" en la cadena.
 * @param sufix Un puntero a la cadena que contiene el sufijo después de la
 * subcadena de variables de entorno.
 * @param msh Puntero a la estructura que representa el intérprete de comandos.
 *
 * @return Puntero a la cadena que contiene el valor de la variable de entorno.
 */
char	*process_env_substring(char **dol_pos, char **sufix, t_shell *msh)
{
	char	*next_dollar_pos;
	char	*env_value;
	char	*str;

	next_dollar_pos = ft_strchr(*dol_pos + 1, '$');
	if (next_dollar_pos)
		ft_next_dollar_pos(dol_pos, &str, sufix);
	else
		ft_no_next_dollar_pos(dol_pos, &str, sufix);
	env_value = ft_find(str, msh);
	ft_memfree(str);
	return (env_value);
}

/**
 * @brief Encuentra la próxima posición del símbolo "$" en la cadena y separa la
 * subcadena y el sufijo.
 *
 * Esta función encuentra la próxima posición del símbolo "$" en la cadena dada,
 * separa la subcadena desde el símbolo "$" hasta la siguiente ocurrencia de "$"
 * o espacio, y asigna la subcadena y el sufijo a los punteros correspondientes.
 *
 * @param dol_pos Doble puntero que apunta al primer símbolo "$" en la cadena.
 * @param str Doble puntero donde se almacenará la subcadena encontrada.
 * @param sufix Doble puntero donde se almacenará el sufijo encontrado.
 */
static void	ft_next_dollar_pos(char **dol_pos, char **str, char **sufix)
{
	char	*next_dollar_pos;
	char	*next_space_pos;

	next_dollar_pos = ft_strchr(*dol_pos + 1, '$');
	next_space_pos = ft_strchr(*dol_pos + 1, ' ');
	if (next_dollar_pos)
	{
		if (next_space_pos && (next_dollar_pos > next_space_pos))
		{
			*str = ft_substr(*dol_pos, 1, next_space_pos - *dol_pos - 1);
			*sufix = ft_strdup(next_space_pos);
		}
		else
		{
			*str = ft_substr(*dol_pos, 1, next_dollar_pos - *dol_pos - 1);
			*sufix = ft_strdup(next_dollar_pos);
		}
	}
}

/**
 * @brief Maneja el caso en el que no hay próxima posición del símbolo "$".
 *
 * Esta función maneja el caso en el que no hay próxima posición del símbolo "$"
 * en la cadena, separa la subcadena desde el símbolo "$" hasta la siguiente
 * ocurrencia de espacio, y asigna la subcadena y el sufijo a los punteros
 * correspondientes.
 *
 * @param dol_pos Doble puntero que apunta al primer símbolo "$" en la cadena.
 * @param str Doble puntero donde se almacenará la subcadena encontrada.
 * @param sufix Doble puntero donde se almacenará el sufijo encontrado.
 */
static void	ft_no_next_dollar_pos(char **dol_pos, char **str, char **sufix)
{
	char	*next_space_pos;

	next_space_pos = ft_strchr(*dol_pos + 1, ' ');
	if (next_space_pos)
	{
		*str = ft_substr(*dol_pos, 1, next_space_pos - *dol_pos - 1);
		*sufix = ft_strdup(next_space_pos);
	}
	else
	{
		*str = ft_substr(*dol_pos, 1, ft_strlen(*dol_pos + 1));
		*sufix = "";
	}
}
