/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <nabih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:07:54 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 08:21:18 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int8_t		next_main_bis(t_asm *a)
{
//	print_champ(&(a->champ));
//	print_lab(&(a->lab));
	write_header(a->fd, &(a->header));
	write_body(a->fd, &(a->lab), &(a->champ));
	clear_all(a);
	return (ASM_SUCCESS);
}

static int8_t		next_main(t_asm *a)
{
	if (get_info(a) == ASM_ERROR)
	{
		clear_all(a);
		print_error(ASM_ERROR_CODE, NULL, a->line_nb);
		return (ASM_ERROR);
	}
	else
	{
		close(a->fd);
		a->lab = sort_label(&(a->lab));
		if ((a->champ = sort_champ(a, &(a->champ))) == NULL)
			return (ASM_ERROR);
		if (a->header.prog_size == 0 || (a->fd = create_new_file(a, a->file)) == ASM_ERROR)
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

int                 main(int ac, char **av)
{
    t_asm       a;

	ft_bzero(&a, sizeof(a));
	ft_bzero(&(a.header), sizeof(a.header));
    if (check_arguments(ac) == ASM_ERROR)
    {
        print_error(ASM_ERROR_AC, NULL, 0);
        return (ASM_ERROR);
    }
    if ((a.file = check_file(ac, av)) == NULL)
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
