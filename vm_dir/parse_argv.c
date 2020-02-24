/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:15:04 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/21 14:01:11 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		check_max_player_nb(int player_nb, t_bool *ok) //Surement del
{
	if (player_nb > MAX_PLAYERS)
	{
		ft_putstr_fd("ERROR: number of Player surpassed ", 2);
		ft_putnbr_fd(MAX_PLAYERS, 2);
		ft_putchar_fd('\n', 2);
		*ok = FALSE;
	}
}


static void		activate_v_flag(t_vm *vm, int *i)
{
	vm->flags = vm->flags | V_FLAG;
	(*i)++;
}

static void		activate_p_flag(t_vm *vm, int *i)
{
	vm->flags = vm->flags | P_FLAG;
	(*i)++;
}

static t_bool	fill_id_tab(t_vm *vm, int *i, char const *argv, t_id_tab id_tab[MAX_PLAYERS]) //si pas check avant overflow dans id_tab
{
	if (vm->player_nb == 4)
	{
		ft_putstr_fd("ERROR: number of Player surpassed\n", 2);
		return (FALSE);
	}
	id_tab[vm->player_nb].argv = argv;
	id_tab[vm->player_nb].id = 0;
	(*i)++;
	vm->player_nb++;
	return (TRUE);
}

/*
** go through argv to :
** 1. get dump value, option n value, activate v flag if exist;
** 2. stock argv of player file in id_tab
*/

t_bool			parse_argv(t_vm *vm, int argc, char const **argv,
							t_id_tab id_tab[MAX_PLAYERS])
{
	t_bool		ok;
	int			i;

	i = 1;
	ok = TRUE;
	while (ok && i < argc)
	{
		if (ft_strcmp(argv[i], "-dump") == 0)
			ok = get_dump_value(argc, argv, &i, vm);
		else if (ft_strcmp(argv[i], "-v") == 0)
			activate_v_flag(vm, &i);
		else if (ft_strcmp(argv[i], "-p") == 0)
			activate_p_flag(vm, &i);
		else if (ft_strcmp(argv[i], "-n") == 0 && i + 2 < argc)
			ok = get_n_value(argv, &i, vm, id_tab);
		else if (is_valid_filename(argv[i]))
			ok = fill_id_tab(vm, &i, argv[i], id_tab);
		else
			ok = FALSE;
		check_max_player_nb(vm->player_nb, &ok);
	}
	return (ok);
}
