/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:18 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/16 15:57:26 by jleblond         ###   ########.fr       */
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
	vm->delta_cycle_counter = 0;
	if (vm->max_check_counter == MAX_CHECKS || vm->live_counter >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->live_counter = 0;
		vm->max_check_counter = 0;
		if (vm->flags & V_FLAG)
			ft_printf("=================cycle_to_die is now[%d]====================\n", vm->cycle_to_die);
	}
	else
		vm->max_check_counter++;

	clean_dead_cursor(vm);
}

char		*get_player_name(t_vm *vm, int id)
{
	int 	i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (id == vm->players[i].player_id)
			return (vm->players[i].prog_name);
		i++;
	}
	ft_putendl_fd("ERROR: Wrong player id", 2);
	return (NULL);
}

t_bool		run_vm(t_vm *vm)
{
	while (vm->cursor_nb && vm->cycle_to_die > 0)
	{
		ft_printf("It is now cycle %d\n", vm->cycle_total);

		run_cursor(vm);

		if ((vm->flags & D_FLAG) && vm->cycle_total == vm->dump)
		{
			dump_mem(vm->arena);
			break;
		}
		vm->cycle_total++;
		if (vm->delta_cycle_counter == vm->cycle_to_die)
			update_cycle_to_die(vm);
		else
			vm->delta_cycle_counter++;

	}
	ft_printf("Player %d (%s) has won\n", vm->winner, get_player_name(vm, vm->winner));
	return (TRUE);
}
