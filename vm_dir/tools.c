/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:39:11 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/21 17:47:08 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** tab[0] is not used
** opcode is already verified to be valid if one op_dispath is launched.
*/
uint8_t			get_dir_len(uint8_t opcode)
{
	static uint8_t tab[17] = {0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2 ,2, 4, 2 ,2, 4};

	return (tab[opcode]);
}

int16_t 		pos(int16_t pc)
{
	if (pc < 0)
		return (pc % MEM_SIZE + MEM_SIZE);
	else
		return (pc % MEM_SIZE);
}

t_bool			op_code_valid(uint8_t op)
{
	if (op >= 1 && op <= 16)
		return (TRUE);
	return (FALSE);
}

uint32_t		get_reg_size_value(t_vm *vm, t_cursor *c, t_type type, int32_t p)
{
	uint32_t	value;
	uint16_t	address;

	if (type == TYPE_REG)
		value = c->regs[p];
	if (type == TYPE_IND)
	{
		// address = pos(c->pc + p % IDX_MOD);
		address = c->pc + p % IDX_MOD;
		value = read_bytes(vm->arena + address, REG_SIZE);
	}
	if (type == TYPE_DIR)
		value = p;
	return (value);
}

uint16_t		get_ind_size_value(t_vm *vm, t_cursor *c, t_type type, int32_t p)
{
	int16_t		value;
	uint16_t	address;

	if (type == TYPE_REG)
		value = (int16_t)(c->regs[p]);
	if (type == TYPE_IND)
	{
		address = pos(c->pc + (int16_t)p % IDX_MOD);
		value = read_bytes(vm->arena + address, IND_SIZE);
	}
	if (type == TYPE_DIR)
		value = (int16_t)p;
	return (value);
}
