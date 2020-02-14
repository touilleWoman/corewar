/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_zjmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 10:09:02 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/14 15:54:14 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool		player_id_valid(t_vm *vm, int id, int *index)
{
	int 	i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (id == vm->players[i].player_id)
		{
			*index = i;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void		op_live(t_vm *vm, t_cursor *c)
{
	int 	player_id;
	int 	player_index;
	int 	new_pc;
	uint8_t dir_len;

	dir_len = get_dir_len(c->op);
	new_pc = pos(c->pc + OPCODE_SIZE);
	player_id = read_bytes(vm->arena + new_pc, dir_len);
	new_pc += dir_len;
	if (player_id_valid(vm, player_id, &player_index))
	{
		vm->players[player_index].live_counter++;
		vm->live_counter++;
		c->alive = TRUE;
		vm->winner = player_id;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | live %d\n", c->c_id, player_id);
		else
			ft_printf("Player %d (%s) is alive\n", player_id, get_player_name(vm, player_id));
	}
	c->pc = new_pc;
}

/*
**  {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
*/

void		op_zjmp(t_vm *vm, t_cursor *c)
{
	uint16_t	p;


	if (c->carry == 1)
	{
		p = read_bytes(vm->arena + pos(c->pc + OPCODE_SIZE), IND_SIZE);
		// p = p % IDX_MOD;
		c->pc += p;
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | zjmp %d\n", c->c_id, p);
	}
}
