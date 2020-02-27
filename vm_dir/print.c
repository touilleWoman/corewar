/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:39:09 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/27 12:05:11 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_bytes(t_vm *vm, int addr, int nb_bytes)
{
	int		i;
	uint8_t	p;

	if (nb_bytes < 1 || nb_bytes > 10)
		return ;
	i = 0;
	while (i < nb_bytes)
	{
		p = vm->arena[pos(addr + i)];
		i++;
		ft_printf(" %02x", p);
	}
	ft_printf("\n");
}