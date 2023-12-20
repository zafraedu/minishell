#include "minishell.h"

static void	ft_add_nodes(t_parser **cmd_node, t_lexer *lex);
static void	connect_pipes(t_parser **parser);

/**
 * @brief Analiza una lista enlazada de tokens y crea una estructura de datos
 * de tipo `t_parser`.
 *
 * Esta función realiza el análisis sintáctico de una lista enlazada de tokens
 * (`t_lexer`) y crea una estructura de datos de tipo `t_parser` que representa
 * la estructura lógica de los comandos. Además, establece las conexiones
 * necesarias entre los nodos que representan los comandos separados por pipes.
 *
 * @param parser Doble puntero de la estructura `t_parser`.
 * @param lex Un puntero al inicio de la lista enlazada de tokens (`t_lexer`).
 */
void	ft_parser(t_parser **parser, t_lexer *lex)
{
	t_parser	*cmd_node;

	if (lex == NULL)
		return ;
	ft_index(lex);
	if (*parser == NULL)
		*parser = ft_calloc(1, sizeof(t_parser));
	cmd_node = *parser;
	if (cmd_node)
		ft_add_nodes(&cmd_node, lex);
	connect_pipes(parser);
}

/**
 * @brief Agrega nodos a la estructura `t_parser`.
 *
 * Esta función agrega nodos a la estructura de datos `t_parser` para
 * representar comandos separados por tuberías. La función itera sobre la lista
 * enlazada de tokens (`t_lexer`) y crea nodos para cada comando individual.
 * Establece conexiones entre los nodos y avanza en la lista de tokens para
 * procesar los comandos sucesivos.
 *
 * @param cmd_node Un puntero al puntero de la estructura `t_parser`.
 * @param lex Un puntero al inicio de la lista enlazada de tokens (`t_lexer`).
 */
static void	ft_add_nodes(t_parser **cmd_node, t_lexer *lex)
{
	int	start;
	int	num_pipes;
	int	i;
	int	end;

	start = 0;
	num_pipes = ft_count_pipes(lex);
	i = 0;
	while (i <= num_pipes)
	{
		end = get_last(lex, start);
		ft_fill_node(lex, cmd_node, start, end);
		if (i < num_pipes)
		{
			(*cmd_node)->next = ft_calloc(1, sizeof(t_parser));
			*cmd_node = (*cmd_node)->next;
		}
		start = end + 2;
		i++;
	}
}

/**
 * @brief Conecta los descriptores de archivo (pipes) entre comandos en la
 * estructura `t_parser`.
 *
 * Itera sobre la lista de nodos `t_parser` y establece las conexiones entre las
 * salidas de un comando y las entradas del siguiente comando utilizando pipes.
 *
 * @param parser Un puntero al puntero de la estructura `t_parser`
 * que se va a conectar mediante pipes.
 */
static void	connect_pipes(t_parser **parser)
{
	t_parser	*current;
	int			fd[2];

	current = *parser;
	while (current->next)
	{
		pipe(fd);
		if (current->redir_out == 1)
			current->redir_out = fd[1];
		current->next->redir_in = fd[0];
		current = current->next;
	}
}
