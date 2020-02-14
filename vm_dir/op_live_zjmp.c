/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_zjmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 10:09:02 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/09 16:12:31 by jleblond         ###   ########.fr       */
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

	printf("LIVE\n");
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
		ft_printf("Player %d (%s) is alive\n", player_id, get_player_name(vm, player_id));
	}
	c->pc = new_pc;
}

/*
**  {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
*/

void		op_zjmp(t_vm *vm, t_cursor *c)
{
	uint8_t	dir_len;
	int		jump;

	printf("zjmp\n");
	if (c->carry == 1)
	{
		dir_len = get_dir_len(c->op);
		jump = read_bytes(vm->arena + pos(c->pc + OPCODE_SIZE), dir_len);
		// jump = jump % IDX_MOD;
		c->pc += jump;
		printf("zjmp SUCESS\n");
	}
}
