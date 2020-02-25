/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:39:09 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/25 15:43:37 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print(unsigned int id, char *s, t_params *p)
{
	ft_printf("P    %u | %s", id, s);
	if (p->p1_type == TYPE_REG)
		ft_printf(" r%d", p->p1);
	else if (p->p1_type == TYPE_DIR)
		ft_printf(" %%%d", p->p1);
	else if (p->p1_type == TYPE_IND)
		ft_printf(" %d", p->p1);
	if (p->p2_type == TYPE_REG)
		ft_printf(" r%d", p->p2);
	else if (p->p2_type == TYPE_DIR)
		ft_printf(" %%%d", p->p2);
	else if (p->p2_type == TYPE_IND)
		ft_printf(" %d", p->p2);
	if (p->p3_type == TYPE_REG)
		ft_printf(" r%d", p->p3);
	else if (p->p3_type == TYPE_DIR)
		ft_printf(" %%%d", p->p3);
	else if (p->p3_type == TYPE_IND)
		ft_printf(" %d", p->p3);
	ft_printf("\n");
}
