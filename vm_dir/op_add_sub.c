/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 10:10:13 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/09 15:06:05 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
*/

void		op_add(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int 		value;

	printf("add\n");
	fill_params(&prm, vm->arena, c);
	if (is_reg_type(prm.p1_type, prm.p1) && is_reg_type(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3) && is_absent_type(prm.p4_type))
	{
		value = c->regs[prm.p1] + c->regs[prm.p2];
		c->regs[prm.p3] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		printf("add SUCCESS\n");
	}
	c->pc = prm.newpc;
}


/*
**    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
*/

void		op_sub(t_vm *vm, t_cursor *c)
{
	t_params			prm;
	uint32_t			value;

	printf("sub\n");
	fill_params(&prm, vm->arena, c);
	if (is_reg_type(prm.p1_type, prm.p1) && is_reg_type(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3) && is_absent_type(prm.p4_type))
	{
		
		value = c->regs[prm.p1] - c->regs[prm.p2];
		c->regs[prm.p3] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		printf("sub SUCESS\n");
	}
	c->pc = prm.newpc;
}
