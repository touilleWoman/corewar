/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:15:04 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/14 14:34:12 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bool	is_digit_string(char const *s)
{
	while (*s)
	{
		if (ft_isdigit(*s))
			s+= 1;
		else
			return (FALSE);
	}
	return (TRUE);
}

t_bool			get_dump_value(int argc, char const **argv, int *i, t_vm *vm)
{
	int		dump;

	vm->flags = vm->flags | D_FLAG;
	if (*i + 1 < argc && is_digit_string(argv[*i + 1]))
	{
		dump = ft_atoi(argv[*i + 1]);
		if (dump <= 0)
		{
			ft_putendl_fd("ERROR: dump value must > 0\n", 2);
			return (FALSE);
		}
		vm->dump = dump;
		*i += 2;
		return (TRUE);
	}
	ft_putendl_fd("ERROR: wrong dump value\n", 2);
	return (FALSE);
}


t_bool			get_n_value(char const **argv, int *i, t_vm *vm, t_id_tab id_tab[MAX_PLAYERS])
{
	int		n_value;

	vm->flags = vm->flags | N_FLAG;
	if (is_digit_string(argv[*i + 1]) == FALSE || is_valid_filename(argv[*i + 2]) == FALSE)
	{
		ft_putendl_fd("ERROR: wrong player id or wrong file name\n", 2);
		return (FALSE);
	}
	n_value = ft_atoi(argv[*i + 1]);
	if (n_value <= 0 || n_value > MAX_PLAYERS )
	{
		ft_putendl_fd("ERROR: player id must '> 0' and '<= nb of players'", 2);
		return (FALSE);
	}
	id_tab[vm->player_nb].id = n_value;
	id_tab[vm->player_nb].argv = argv[*i + 2];
	vm->player_nb++;
	*i += 3;
	return (TRUE);
}

static void		check_max_player_nb(int player_nb, t_bool *ok)
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

static void		fill_id_tab(t_vm *vm, int *i, char const *argv, t_id_tab id_tab[MAX_PLAYERS])
{
	id_tab[vm->player_nb].argv = argv;
	id_tab[vm->player_nb].id = 0;
	(*i)++;
	vm->player_nb++;
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
		else if (ft_strcmp(argv[i], "-n") == 0 && i + 2 < argc)
			ok = get_n_value(argv, &i, vm, id_tab);
		else if (is_valid_filename(argv[i]))
			fill_id_tab(vm, &i, argv[i], id_tab);
		else
			ok = FALSE;
		check_max_player_nb(vm->player_nb, &ok);
	}
	return (ok);
}
