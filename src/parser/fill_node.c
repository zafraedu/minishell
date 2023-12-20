#include "minishell.h"

static void	fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int end);
static void	ft_redirect(t_lexer *tmp, t_parser **cmd_node);
static void	fill_cmd(t_lexer *tmp, t_parser **cmd_node);
static int	ft_len_cmd(t_lexer *tmp);

/**
 * @brief Rellena un nodo de comando con información desde la lista de tokens.
 *
 * Esta función toma una lista de tokens (`t_lexer`), identifica el comando y
 * las redirecciones asociadas en el rango especificado por `start` y `end`, y
 * rellena un nodo de comando (`t_parser`) con la información correspondiente.
 *
 * @param lex Un puntero a la lista de tokens (`t_lexer`) que contiene la
 * información de la línea de comandos.
 * @param cmd_node Un puntero al puntero del nodo de comando (`t_parser`)
 * que se rellenará con la información del comando y las redirecciones.
 * @param start El índice que indica el comienzo del rango en la lista de tokens
 * @param end El índice que indica el final del rango en la lista de tokens.
 */
void	ft_fill_node(t_lexer *lex, t_parser **cmd_node, int start, int end)
{
	t_lexer	*tmp;

	tmp = lex;
	(*cmd_node)->redir_in = STDIN_FILENO;
	(*cmd_node)->redir_out = STDOUT_FILENO;
	fill_redir(lex, cmd_node, &start, end);
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	fill_cmd(tmp, cmd_node);
}

/**
 * @brief Rellena la info de redirección en un nodo de comando (`t_parser`).
 *
 * Esta función toma una lista de tokens (`t_lexer`) y busca redirecciones en el
 * rango especificado por `start` y `end`. Luego, rellena la información de
 * redirección en un nodo de comando (`t_parser`) con la información.
 *
 * @param lex Un puntero a la lista de tokens (`t_lexer`) que contiene
 * la información de la línea de comandos.
 * @param cmd_node Un puntero al puntero del nodo de comando (`t_parser`) que se
 * rellenará con la información de redirección.
 * @param start Un puntero al índice que indica el comienzo del rango en la
 * lista de tokens.
 * @param end El índice que indica el final del rango en la lista de tokens.
 */
static void	fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int end)
{
	t_lexer	*tmp;
	int		aux;

	tmp = lex;
	while (tmp && tmp->index != *start)
		tmp = tmp->next;
	aux = *start;
	while (tmp && aux <= end)
	{
		if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			if (tmp->index == *start)
				*start += 2;
			ft_redirect(tmp, cmd_node);
		}
		tmp = tmp->next;
		aux++;
	}
}

/**
 * @brief Realiza la redirección de entrada/salida para un nodo de comando.
 *
 * Esta función toma un nodo de token de redirección (`t_lexer`) y realiza la
 * redirección correspondiente en un nodo de comando (`t_parser`), actualizando
 * los descriptores de archivo según sea necesario.
 *
 * @param tmp Un puntero al nodo de token de redirección (`t_lexer`)
 * que contiene la información de la redirección.
 * @param cmd_node Un puntero al puntero del nodo de comando (`t_parser`)
 * en el que se realizará la redirección.
 */
static void	ft_redirect(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	if (tmp->type == T_REDIR_IN)
	{
		fd = open(tmp->next->data, O_RDONLY);
		(*cmd_node)->redir_in = fd;
	}
	else if (tmp->type == T_REDIR_OUT)
	{
		fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*cmd_node)->redir_out = fd;
	}
	else if (tmp->type == T_APPEND)
	{
		fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		(*cmd_node)->redir_out = fd;
	}
	else if (tmp->type == T_HEREDOC)
	{
		fd = ft_heredoc(tmp->next->data);
		(*cmd_node)->redir_in = fd;
		if (g_signal != S_CANCEL_EXEC)
			g_signal = S_BASE;
	}
}

/**
 * @brief Llena el campo de comando de un nodo de comando (`t_parser`).
 *
 * Esta función toma un nodo de token de comando (`t_lexer`) y llena el campo de
 * comando de un nodo de comando (`t_parser`) con los datos de los nodos de
 * comando (`t_lexer`) consecutivos, concatenándolos y separándolos con espacios
 * según sea necesario.
 *
 * @param tmp Un puntero al nodo de token de comando (`t_lexer`) que contiene la
 * información del comando.
 * @param cmd_node Un puntero al puntero del nodo de comando (`t_parser`) en el
 * que se llenará el campo de comando.
 */
static void	fill_cmd(t_lexer *tmp, t_parser **cmd_node)
{
	int	len;

	len = ft_len_cmd(tmp);
	(*cmd_node)->cmd = ft_calloc(len, sizeof(char));
	while (tmp && tmp->type == T_CMD)
	{
		ft_strlcat((*cmd_node)->cmd, tmp->data, len);
		if (tmp->next && tmp->next->type == T_CMD)
			ft_strlcat((*cmd_node)->cmd, " ", len);
		tmp = tmp->next;
	}
}

/**
 * @brief Calcula la longitud total del comando concatenando los datos de los
 * nodos de comando consecutivos.
 *
 * @param tmp Un puntero al nodo de token de comando (`t_lexer`).
 * @return La longitud total del comando.
 */
static int	ft_len_cmd(t_lexer *tmp)
{
	int	len;

	len = 0;
	while (tmp && tmp->type == T_CMD)
	{
		len += (ft_strlen(tmp->data) + 1);
		tmp = tmp->next;
	}
	return (len);
}
