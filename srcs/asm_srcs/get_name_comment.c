/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 12:52:03 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 01:52:30 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
  VERIFIER LES INFOS APRES LE 2eme '\"'
*/

static int8_t		check_end_cn(char **str, int i)
{
	char		c;

	c = -1;
	while ((*str)[i] != '\"')
		i--;
	i++;
	while (((*str)[i] == ' ' || (*str)[i] == '\t')
		   && (*str)[i] != COMMENT_CHAR && (*str)[i] != '\0')
		i++;
	c = (*str)[i];
	ft_memdel((void**)str);
	return ((c == COMMENT_CHAR || c == '\0') ? ASM_SUCCESS : ASM_ERROR);
}

static int8_t		copy_quote_name(t_asm *a, char **str, int32_t i)
{
	while (*str && (*str)[i] != '\"' && a->size_name < PROG_NAME_LENGTH)
	{
		if ((*str)[i] != '\0')
		{
			a->header.prog_name[a->size_name] = (*str)[i++];
			a->size_name += 1;
		}
		else if ((*str)[i] == '\0')
		{
			i = 0;
			ft_memdel((void**)str);
			get_next_line(a->fd, str);
			a->line_nb += 1;
			a->header.prog_name[(a->size_name)++] = '\n';
		}
	}
	if (*str && (*str)[i++] == '\"' && (a->size_name < PROG_NAME_LENGTH))
		a->header.prog_name[a->size_name] = '\0';
	else
		return (ASM_ERROR);
	return (check_end_cn(str, ft_strlen(*str) - 1));
}

static int8_t		copy_quote_comment(t_asm *a, char **str, int32_t i)
{
	while (*str && (*str)[i] != '\"' && a->size_comment < COMMENT_LENGTH)
	{
		if ((*str)[i] != '\0')
		{
			a->header.comment[a->size_comment] = (*str)[i];
			a->size_comment += 1;
			i++;
		}
		else if ((*str)[i] == '\0')
		{
			i = 0;
			ft_memdel((void**)str);
			get_next_line(a->fd, str);
			a->line_nb += 1;
			a->header.comment[(a->size_comment)++] = '\n';
		}
	}
	if (*str && (*str)[i] == '\"' && (a->size_comment < COMMENT_LENGTH))
		a->header.comment[a->size_comment] = '\0';
	else
		return (ASM_ERROR);
	return (check_end_cn(str, ft_strlen(*str) - 1));
}

static int8_t		get_name(t_asm *a, char **str, int *flg)
{
	int32_t		i;

	i = 0;
	if (*flg & T_NAME)
		return (ASM_ERROR);
	*flg |= T_NAME;
	while ((*str)[i] != '\"' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\0')
		return (ASM_ERROR);
	i++;
	return (copy_quote_name(a, str, i));
}

static int8_t		get_comment(t_asm *a, char **str, int *flg)
{
	int32_t		i;

	i = 0;
	if (*flg & T_COMMENT)
		return (ASM_ERROR);
	*flg |= T_COMMENT;
	while ((*str)[i] != '\"' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\0')
		return (ASM_ERROR);
	i++;
	return (copy_quote_comment(a, str, i));
}

int8_t				choose_name_or_comment(t_asm *a, int *flg)
{
	int			size_name;
	int			size_comment;

	size_name = ft_strlen(NAME_CMD_STRING);
	size_comment = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strncmp(a->line, NAME_CMD_STRING, size_name) == 0)
	{
		if (get_name(a, &(a->line), flg) == ASM_ERROR)
			return (ASM_ERROR);
	}
	else if (ft_strncmp(a->line, COMMENT_CMD_STRING, size_comment) == 0)
	{
		if (get_comment(a, &(a->line), flg) == ASM_ERROR)
			return (ASM_ERROR);
	}
	else
		return (ASM_ERROR);
	return (ASM_SUCCESS);
}

int8_t				get_name_comment(t_asm *a)
{
	int			i;
	int			flg;

	i = 1;
	flg = 0;
	while (a->line != NULL && i == 1 && !(flg & T_NAME && flg & T_COMMENT))
	{
		i = 0;
		skip_empty(a);
		skip_start(a->line);
		if (choose_name_or_comment(a, &flg) == ASM_ERROR)
			return (ASM_ERROR);
		i = get_next_line(a->fd, &(a->line));
		a->line_nb += 1;
	}
	return ((flg & T_NAME && flg & T_COMMENT) ? ASM_SUCCESS : ASM_ERROR);
}
