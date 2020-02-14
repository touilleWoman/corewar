/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 01:55:13 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 08:29:03 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
  Print des lists
*/

void				print_lab(t_label **lst)
{
	t_label		*tmp;

	tmp = NULL;
	if (lst && *lst)
	{
		tmp = *lst;
		while (tmp != NULL)
		{
			ft_putstr(tmp->label);
			ft_putchar(' ');
			ft_putstr(g_op_tab[tmp->ptr->op].name);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
}

void				print_champ(t_champ **lst)
{
	t_champ		*tmp;

	tmp = NULL;
	if (lst && *lst)
	{
		tmp = *lst;
		while (tmp != NULL)
		{
			ft_putstr(g_op_tab[tmp->op].name);
			ft_putchar(' ');
			ft_putstr(tmp->lab1);
			ft_putchar(' ');
			ft_putstr(tmp->lab2);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
}

/*---------------*/

t_label				*sort_label(t_label **src)
{
	t_label		*dst;
	t_label		*tmp;

	dst = NULL;
	if (src && *src)
	{
		while (*src)
		{
			tmp = lab_pullfront(src);
			lab_pushfront(&dst, tmp);
		}
		tmp = NULL;
	}
	return (dst);
}

static int8_t		label_recheck(t_asm *a, t_champ **cmp, char *lab)
{
	t_champ		*tmp;

	if (lab_get(&(a->lab), lab) == NULL)
	{
		tmp = *cmp;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = a->champ;
		a->champ = *cmp;
		clear_all(a);
		return (ASM_ERROR);
	}
	return (ASM_SUCCESS);
}

static int8_t		check_label_exist(t_asm *a, t_champ **cmp)
{
	int8_t		flg;

	flg = ASM_SUCCESS;
	if ((*cmp)->lab1 != NULL)
		flg = label_recheck(a, cmp, (*cmp)->lab1);
	if (flg != ASM_ERROR && (*cmp)->lab2 != NULL)
		flg = label_recheck(a, cmp, (*cmp)->lab2);
	return (flg);
}

t_champ				*sort_champ(t_asm *a, t_champ **src)
{
	t_champ		*dst;
	t_champ		*tmp;

	dst = NULL;
	if (src && *src)
	{
		while (*src)
		{
			tmp = champ_pullfront(src);
			if (check_label_exist(a, &tmp) == ASM_ERROR)
				return (NULL);
			a->header.prog_size += champ_size_calc(tmp);
			champ_pushfront(&dst, tmp);
		}
		tmp = NULL;
	}
	return (dst);
}
