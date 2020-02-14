/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 11:59:11 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 01:44:17 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int8_t				get_info(t_asm *a)
{
	skip_empty(a);
	if (a->line == NULL || get_name_comment(a) == ASM_ERROR)
	{
		if (a->line == NULL)
			print_error(ASM_ERROR_OTHER, "File empty", 0);
		return (ASM_ERROR);
	}
	else
	{
		a->header.magic = COREWAR_EXEC_MAGIC;
		skip_empty(a);
		if (get_code(a) == ASM_ERROR)
			return (ASM_ERROR);
	}
	ft_memdel((void**)&(a->line));
	return (ASM_SUCCESS);
}
