/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:52:54 by nabih             #+#    #+#             */
/*   Updated: 2020/01/30 14:33:11 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int8_t		check_multi_nc(int *type, int flg)
{
	if (*type & flg)
		return (ASM_ERROR);
	*type |= flg;
	return (ASM_SUCCESS);
}

int8_t				header_checker(char *line, int flg)
{
	static int	type = 0;

	(void)line;
	if (check_multi_nc(&type, flg) == ASM_ERROR)
		return (ASM_ERROR);
	/*
	**-------**
	|   CODE  |
	**-------**
	*/
	return (ASM_SUCCESS);
}
