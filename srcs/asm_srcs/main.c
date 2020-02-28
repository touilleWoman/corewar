/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <nabih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:07:54 by nabih             #+#    #+#             */
/*   Updated: 2020/02/28 12:40:28 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int8_t		next_main_bis(t_asm *a)
{
	write_header(a->fd, &(a->header));
	write_body(a->fd, &(a->lab), &(a->champ));
	if (a->verbose == 1)
		print_champ(&(a->header), &(a->champ), &(a->lab));
	clear_all(a);
	return (ASM_SUCCESS);
}

static int8_t		next_main(t_asm *a)
{
	if (get_info(a) == ASM_ERROR)
	{
		clear_all(a);
		return (ASM_ERROR);
	}
	else
	{
		close(a->fd);
		a->lab = sort_label(&(a->lab));
		a->champ = sort_champ(a, &(a->champ));
		if ((a->fd = create_new_file(a, a->file)) == ASM_ERROR)
		{
			clear_all(a);
			if (a->fd < 0)
				print_error(ASM_ERROR_OTHER, "Failed to create .cor", 0);
			return (ASM_ERROR);
		}
		return (next_main_bis(a));
	}
	return (ASM_ERROR);
}

int					main(int ac, char **av)
{
	t_asm		a;

	ft_bzero(&a, sizeof(a));
	ft_bzero(&(a.header), sizeof(a.header));
	if (check_arguments(ac) == ASM_ERROR)
	{
		print_error(ASM_ERROR_AC, NULL, 0);
		return (ASM_ERROR);
	}
	if ((a.file = check_file(&a, ac, av)) == NULL)
	{
		print_error(ASM_ERROR_FILE, NULL, 0);
		return (ASM_ERROR);
	}
	if ((a.fd = open_file(a.file)) == ASM_ERROR)
	{
		print_error(ASM_ERROR_OTHER, "open_file", 0);
		return (ASM_ERROR);
	}
	return (next_main(&a));
}
