/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit_sign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zafraedu <zafraedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:19:59 by ezafra-r          #+#    #+#             */
/*   Updated: 2023/10/08 23:35:43 by zafraedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * Verifica si una cadena de caracteres es un número entero con signo.
 *
 * Esta función examina la cadena de caracteres 'str[i]' para determinar si
 * representa un número entero con signo válido. Comienza verificando el primer
 * carácter de 'str[i]' para detectar un signo ('+' o '-'). Si se encuentra un
 * signo, se avanza al siguiente carácter. Luego, verifica que todos los
 * caracteres subsiguientes sean dígitos válidos (0-9).
 *
 * @param str Un arreglo de cadenas de caracteres (strings).
 * @param i   El índice de la cadena de caracteres 'str' que se desea verificar.
 * @return 1 si 'str[i]' es un número entero con signo válido,
 *         0 en caso contrario.
 */
int	ft_is_digit_sign(char **str, int i)
{
	int	j;

	j = 0;
	if (ft_issign(str[i][j]))
		j++;
	while (str[i][j])
	{
		if (!ft_isdigit(str[i][j]))
			return (0);
		j++;
	}
	return (1);
}
