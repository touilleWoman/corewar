/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_body.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:50:49 by nabih             #+#    #+#             */
/*   Updated: 2020/02/11 19:45:22 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void			write_ocp(int fd, t_champ *c)
{
	int		i;
	int		pos;
	char	ocp;

	i = 7;
	pos = -1;
	ocp = 0;
	while (++pos < c->nb_arg)
	{
		if (c->type[pos] & T_REG)
		{
			ocp |= 1 << (--i);
			--i;
		}
		else if (c->type[pos] & T_DIR)
		{
			ocp |= 1 << i;
			i -= 2;
		}
		else if (c->type[pos] & T_IND)
		{
			ocp |= 1 << (i--);
			ocp |= 1 << (i--);
		}
	}
	write(fd, &ocp, 1);
}

static void			convert_label(t_label **l, t_champ **c, int pos)
{
	t_label		*tmpl;
	t_champ		*tmpc;
	char		*lab;

	lab = ((*c)->val[pos] == 1) ? (*c)->lab1 : (*c)->lab2;
	tmpl = lab_get(l, lab);
	if (tmpl->ptr && tmpl->ptr->id < (*c)->id)
	{
		tmpc = tmpl->ptr;
		while (tmpc->id != (*c)->id)
		{
			(*c)->val[pos] -= tmpc->size;
			tmpc = tmpc->next;
		}
		(*c)->val[pos] -= 1;
	}
	else if (tmpl->ptr && tmpl->ptr->id > (*c)->id)
	{
		tmpc = *c;
		while (tmpc->id != tmpl->ptr->id)
		{
			(*c)->val[pos] += tmpc->size;
			tmpc = tmpc->next;
		}
		(*c)->val[pos] -= 1;
	}
	else if (tmpl->ptr && tmpl->ptr->id == (*c)->id)
		(*c)->val[pos] = 0;
	else
	{
		tmpc = *c;
		while (tmpc)
		{
			(*c)->val[pos] += tmpc->size;
			tmpc = tmpc->next;
		}
		(*c)->val[pos] -= 1;
	}
}

void				write_body(t_asm *a, int fd, t_label **l, t_champ **c)
{
	int			pos;
	t_champ		*tmp;
	char		op;

	(void)a;
	if (c && *c)
	{
		tmp = *c;
		while (tmp != NULL)
		{
			pos = 0;
			op = ((char)(tmp->op + 1));
			write(fd, &op, 1);
			if (g_op_tab[tmp->op].ocp == true)
				write_ocp(fd, tmp);
			while (pos < tmp->nb_arg)
			{
				if (tmp->type[pos] & T_LAB)
					convert_label(l, &tmp, pos);
				if (tmp->type[pos] & T_REG)
					write_int_one_byte(fd, tmp->val[pos]);
				else if (tmp->type[pos] & T_DIR)
				{
					if (g_op_tab[tmp->op].dir_type == false)
						write_int_four_bytes(fd, tmp->val[pos]);
					else
						write_int_two_bytes(fd, tmp->val[pos]);
				}
				else if (tmp->type[pos] & T_IND)
					write_int_two_bytes(fd, tmp->val[pos]);
				pos++;
			}
			tmp = tmp->next;
		}
	}
}
