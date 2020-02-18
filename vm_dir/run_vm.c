/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:18 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/18 11:51:15 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_wait[0] is not used.
*/
static int 		get_wait_cycle(unsigned char op)
{
	static int op_wait[17] = {-1, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25,
		25, 800, 10, 50, 1000, 2};

	return (op_wait[op]);
}

void			run_cursor(t_vm *vm)
{
	t_cursor 		*c;

	c = vm->cursor;
	while (c)
	{
		if (vm->cycle_total == 1 || c->wait_cycle == -1)
		{
			c->op = vm->arena[pos(c->pc)];
			if (op_code_valid(c->op))
				c->wait_cycle = get_wait_cycle(c->op);
			else
				c->pc++;
		}
		if (c->wait_cycle > 0)
			c->wait_cycle--;
		if (c->wait_cycle == 0 && op_code_valid(c->op))
		{
			execute_instruction(vm, c);
			c->wait_cycle = -1;
		}
		c = c->next;
	}
}

void		check(t_vm *vm)
{
	if (vm->max_check_counter == MAX_CHECKS - 1 || vm->live_counter >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->max_check_counter = 0;
		if (vm->flags & V_FLAG)
			ft_printf("cycle_to_die is now[%d]\n", vm->cycle_to_die);
	}
	else
		vm->max_check_counter++;
	vm->live_counter = 0;
	// printf("cycle_total[%d] cycle_to_die[%d]\n", vm->cycle_total, vm->cycle_to_die );
	update_cursor(vm);
}

static char		*get_player_name(t_vm *vm, int id)
{
	int 	i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (id == vm->players[i].player_id)
			return (vm->players[i].prog_name);
		i++;
	}
	ft_printf("ERROR: Winner id(%d) doesn't exist\n", id);
	return (NULL);
}

void			run_vm(t_vm *vm)
{
	char	*winner_name;

	vm->delta_cycle_counter = 0;
	while (vm->cursor_nb)
	{
		while (vm->delta_cycle_counter < vm->cycle_to_die)
		{
			// printf("cycle[%d]\n", vm->cycle_total);
			run_cursor(vm);
			if ((vm->flags & D_FLAG) && vm->cycle_total == vm->dump)
			{
				dump_mem(vm->arena);
				return ;
			}
			vm->delta_cycle_counter++;
			vm->cycle_total++;
		}
		check(vm);
		vm->delta_cycle_counter = 0;
	}
	winner_name = get_player_name(vm, vm->winner);
	if (winner_name)
		ft_printf("Contestant %d, \"%s\", has won !\n", vm->winner, winner_name);
}
