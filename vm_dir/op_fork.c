/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 10:06:08 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/14 12:57:01 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
*/

void		op_fork(t_vm *vm, t_cursor *c)
{
	t_cursor	*new;
	int16_t		p1;

	p1 = read_bytes(vm->arena + pos(c->pc) + 1, 2);
	if (c_lst_new(&new) == FALSE)
		return ;
	ft_memcpy(new, c, sizeof(t_cursor));
	new->pc = c->pc + p1 % IDX_MOD;
	new->next = NULL;
	new->prev = NULL;
	if (c_lst_add_top(&(vm->cursor), new) == FALSE)
		return ;
	vm->cursor_nb++;
	new->c_id = vm->cursor_nb;
	ft_printf("P    %d | fork P   %d at %%%d\n", c->c_id, new->c_id, p1);

}

void		op_lfork(t_vm *vm, t_cursor *c)
{
	t_cursor	*new;
	int16_t		p1;

	p1 = read_bytes(vm->arena + pos(c->pc + 1), 2);
	printf("lfork\n");
	if (c_lst_new(&new) == FALSE)
		return ;
	ft_memcpy(new, c, sizeof(t_cursor));
	new->pc = c->pc + p1;
	new->next = NULL;
	new->prev = NULL;
	if (c_lst_add_top(&(vm->cursor), new) == FALSE)
		return ;
	vm->cursor_nb++;
	new->c_id = vm->cursor_nb;
	ft_printf("P    %d | lfork P   %d at %%%d\n", c->c_id, new->c_id, p1);
}
