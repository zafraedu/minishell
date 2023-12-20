#include "minishell.h"

/**
 * @brief Asigna índices a cada nodo en una lista enlazada de tokens.
 *
 * Esta función asigna un índice único a cada nodo en una lista enlazada de
 * tokens (`t_lexer`). Los índices se utilizan para rastrear la posición de
 * cada token en la lista y facilitar el procesamiento posterior, como el
 * análisis sintáctico y la construcción de comandos.
 *
 * @param lex Un puntero al inicio de la lista enlazada de tokens (`t_lexer`).
 */
void	ft_index(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

/**
 * @brief Cuenta el número de tuberías en una lista enlazada de tokens.
 *
 * Esta función cuenta el número de nodos de tipo T_PIPE en una lista enlazada
 * de tokens (`t_lexer`). Se utiliza para determinar la cantidad de comandos
 * separados por tuberías en una entrada de usuario.
 *
 * @param lex Un puntero al inicio de la lista enlazada de tokens (`t_lexer`).
 * @return El número de tuberías en la lista enlazada de tokens.
 */
int	ft_count_pipes(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/**
 * @brief Obtiene el índice del último token antes de un pipe en (`t_lexer`).
 *
 * Esta función busca el último índice de un token antes de encontrar un nodo
 * de tipo T_PIPE en una lista enlazada de tokens (`t_lexer`). Se utiliza para
 * determinar el rango de tokens asociados con un comando específico separado
 * por tuberías.
 *
 * @param lex Un puntero al inicio de la lista enlazada de tokens (`t_lexer`).
 * @param start El índice de inicio desde el cual buscar el último token antes
 * de una tubería.
 * @return El índice del último token antes de la tubería o el último índice
 * disponible si no se encuentra ninguna tubería después de `start`.
 */
int	get_last(t_lexer *lex, int start)
{
	t_lexer	*tmp;
	int		last_index;

	last_index = -1;
	tmp = lex;
	while (tmp && tmp->next)
	{
		if (tmp->type == T_PIPE && tmp->index > start)
			return (tmp->index - 1);
		tmp = tmp->next;
	}
	last_index = tmp->index;
	return (last_index);
}
