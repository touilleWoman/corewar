/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:41:19 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/09 14:02:33 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


/*
**  {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
*/

void			op_ld(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int			value;

	printf("ld\n");
	fill_params(&prm, vm->arena, c);
	if (is_dir_or_ind(prm.p1_type) && is_reg_type(prm.p2_type, prm.p2) && is_absent_type(prm.p3_type))
	{
		if (prm.p1_type == TYPE_DIR)
			value = prm.p1;
		else
			value = get_reg_size_value(vm, c, prm.p1_type, prm.p1);
		c->regs[prm.p2] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		printf("ld SUCCESS\n");
	}
	c->pc = prm.newpc;
}

void		op_lld(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int 		address;
	int			value;

	printf("lld\n");
	fill_params(&prm, vm->arena, c);
	if (is_dir_or_ind(prm.p1_type) && is_reg_type(prm.p2_type, prm.p2) && is_absent_type(prm.p3_type))
	{
		if (prm.p1_type == TYPE_DIR)
			value = prm.p1;
		else
		{
			address = c->pc + ((uint16_t)prm.p1);
			value = read_bytes(vm->arena + pos(address), 4);
		}
		c->regs[prm.p2] = value;
		if (value == 0)
			c->carry = 1;
		else
			c->carry = 0;
		printf("lld SUCCESS\n");
	}
	c->pc = prm.newpc;
}

/*
**     {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**       "long load index", 1, 1},
**
** ca prend 2 index et 1 registre, additionne les 2 premiers, 
** traite ca comme une adresse, y lit une valeur de la taille 
** d’un registre et la met dans le 3eme.
*/


void		op_ldi(t_vm *vm, t_cursor *c)
{
	t_params			prm;
	uint32_t			value1;
	uint32_t			value2;
	uint16_t			address;

	printf("ldi\n");
	fill_params(&prm, vm->arena, c);
	if (is_3_types(prm.p1_type, prm.p1) && is_dir_or_reg(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value1 = get_ind_size_value(vm, c, prm.p1_type, prm.p1);
		value2 = get_ind_size_value(vm, c, prm.p2_type, prm.p2);
		address = c->pc + (value1 + value2) % IDX_MOD;
		c->regs[prm.p3] = read_bytes(vm->arena + pos(address), REG_SIZE);
		if (c->regs[prm.p3] == 0)
			c->carry = 1;
		else
			c->carry = 0;
		printf("ldi SUCESS\n");
	}
	c->pc = prm.newpc;
}

/*
** {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**    "long load index", 1, 1},
*/

void		op_lldi(t_vm *vm, t_cursor *c)
{
	t_params			prm;
	uint32_t			value1;
	uint32_t			value2;
	uint16_t			address;
	
	printf("lldi\n");
	fill_params(&prm, vm->arena, c);
	if (is_3_types(prm.p1_type, prm.p1) && is_dir_or_reg(prm.p2_type, prm.p2)
		&& is_reg_type(prm.p3_type, prm.p3))
	{
		value1 = get_ind_size_value(vm, c, prm.p1_type, prm.p1);
		value2 = get_ind_size_value(vm, c, prm.p2_type, prm.p2);
		address = c->pc + value1 + value2;
		c->regs[prm.p3] = read_bytes(vm->arena + pos(address), REG_SIZE);
		if (c->regs[prm.p3] == 0)
			c->carry = 1;
		else
			c->carry = 0;
		printf("lldi SUCESS\n");
	}
	c->pc = prm.newpc;
}




