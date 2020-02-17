/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:18 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/17 15:23:25 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_wait[0] is not used.
*/
int 		get_wait_cycle(unsigned char op)
{
	static int op_wait[17] = {-1, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25,
		25, 800, 10, 50, 1000, 2};

	if (op_code_valid(op) == FALSE)
		return (1);
	else
		return (op_wait[op]);
}

void		run_cursor(t_vm *vm)
{
	t_cursor 		*c;

	c = vm->cursor;
	while (c)
	{
		if (vm->cycle_total == 1 || c->moved)
		{
			c->op = vm->arena[c->pc];
			c->wait_cycle = get_wait_cycle(c->op);
		}
		if (c->wait_cycle > 0)
			c->wait_cycle--;
		if (c->wait_cycle == 0)
			execute_instruction(vm, c);
		else
			c->moved = FALSE;
		c = c->next;
	}
}

void		update_cycle_to_die(t_vm *vm)
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
	vm->delta_cycle_counter = 0;
	printf("cycle_total[%d] cycle_to_die[%d]\n", vm->cycle_total, vm->cycle_to_die );
	clean_dead_cursor(vm);
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
	ft_putendl_fd("ERROR: Winner id doesn't exist", 2);
	return (NULL);
}

void			run_vm(t_vm *vm)
{
	char *winner_name;

	// while (vm->cursor_nb && vm->cycle_to_die > 0)
	while (vm->cursor_nb)
	{
		run_cursor(vm);
		if ((vm->flags & D_FLAG) && vm->cycle_total == vm->dump)
		{
			dump_mem(vm->arena);
			return ;
		}
		if (vm->delta_cycle_counter == vm->cycle_to_die || vm->cycle_to_die < 0)
			update_cycle_to_die(vm);
		else
		{
			vm->delta_cycle_counter++;
		}
		vm->cycle_total++;
	}
	winner_name = get_player_name(vm, vm->winner);
	if (winner_name)
		ft_printf("Player %d (%s) has won\n", vm->winner, winner_name);
}
