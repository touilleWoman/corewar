/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:45:55 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/17 20:48:23 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t 	read_bytes(uint8_t *s, uint8_t nb_of_bytes)
{
	int32_t 	ret;

	ret = 0;
	if (nb_of_bytes == 4)
		ret = s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3];
	else if (nb_of_bytes == 2)
		ret = (int16_t)(s[0] << 8 | s[1]);
	else if (nb_of_bytes == 1)
		ret = (int8_t)(s[0]);
	else
	{
		printf("nb_of_bytes [%d] wrong\n", nb_of_bytes);
	}
	return (ret);
}

void		write_4_bytes(uint8_t *arena, uint32_t value)
{
	arena[0] = (value & 0xff000000) >> 24 ;
	arena[1] = (value & 0x00ff0000) >> 16 ;
	arena[2] = (value & 0x0000ff00) >> 8;
	arena[3] = (value & 0x000000ff);
}