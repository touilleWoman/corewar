/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 12:27:04 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/13 11:05:36 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// static unsigned int	char_to_unsigned_int(char *s)
// {
// 	unsigned int ret;

// 	ret = (unsigned char)s[0] << 24 | (unsigned char)s[1] << 16
// 	| (unsigned char)s[2] << 8 | (unsigned char)s[3];
// 	return (ret);
// }

// static t_bool		get_comment_and_name(t_player *p, t_header *h)
// {
// 	ft_memcpy(p->comment, h->comment, COMMENT_LENGTH + 1);
// 	if (p->comment[COMMENT_LENGTH] != 0)
// 	{
// 		ft_putendl_fd("ERROR: comment string not ended with 0\n" ,2);
// 		return (FALSE);
// 	}
// 	ft_memcpy(p->prog_name, h->prog_name, PROG_NAME_LENGTH + 1);
// 	if (p->prog_name[PROG_NAME_LENGTH] != 0)
// 	{
// 		ft_putendl_fd("ERROR: comment string not ended with 0\n" ,2);
// 		return (FALSE);
// 	}
// 	//d'autres exigences sur prog_name et comments ? A verifier !!!
// 	return (TRUE);
// }

static t_bool		get_name(uint8_t *s, t_player *p)
{
	ft_memcpy(p->prog_name, s, PROG_NAME_LENGTH + 1);
	s += PROG_NAME_LENGTH;
	if (s[0] || s[1] || s[2] || s[3])
	{
		ft_putendl_fd("ERROR: name string shold be followed \
by 4 bytes of 0\n" ,2);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool		get_comment(uint8_t *s, t_player *p)
{
	ft_memcpy(p->comment, s, COMMENT_LENGTH + 1);
	s += COMMENT_LENGTH;
	if (s[0] || s[1] || s[2] || s[3])
	{
		ft_putendl_fd("ERROR: name string shold be followed \
by 4 bytes of 0\n" ,2);
		return (FALSE);
	}
	return (TRUE);
}

/*
** parcourir header dans .cor, stock "prog_name" et "comments", 
** verifier "magic" et "prog_size".
** 
** typedef struct		header_s
** {
**   unsigned int		magic;
**   char				prog_name[PROG_NAME_LENGTH + 1];
**   unsigned int		prog_size;
**   char				comment[COMMENT_LENGTH + 1];
** }					t_header;
*/
static t_bool		parse_one_player_header(t_player *p)
{
	uint8_t 			*s;

	s = p->file;
	printf("string:%p\n", s);
	if (read_bytes(s, 4) != COREWAR_EXEC_MAGIC)
	{
		ft_putendl_fd("ERROR: wrong magic nb in header\n" ,2);
		return (FALSE);
	}
	s += sizeof(unsigned int);
	if (get_name(s, p) == FALSE)
		return (FALSE);
	s += PROG_NAME_LENGTH + 4;
	p->prog_size = read_bytes(s, 4);
	if (p->prog_size != p->file_size - sizeof(t_header))
	{
		ft_putendl_fd("ERROR: wrong prog_size in header\n" ,2);
		return (FALSE);
	}
	s += 4;
	if (get_comment(s, p) == FALSE)
		return (FALSE);
	return (TRUE);
}

// static t_bool		parse_one_player_header(t_player *p)
// {
// 	t_header		header;
// 	unsigned int	magic;

// 	ft_bzero(&header, sizeof(t_header));
// 	ft_memcpy(&header, p->file, sizeof(t_header));
// 	magic = char_to_unsigned_int((char *)(&header));
// 	if (magic != COREWAR_EXEC_MAGIC)
// 	{
// 		ft_putendl_fd("ERROR: wrong magic nb in header\n" ,2);
// 		return (FALSE);
// 	}
// 	p->prog_size = char_to_unsigned_int(header.comment - sizeof(unsigned int));
// 	if (p->prog_size != p->file_size - sizeof(t_header))
// 	{
// 		ft_putendl_fd("ERROR: wrong prog_size in header\n" ,2);
// 		return (FALSE);
// 	}
// 	if (get_comment_and_name(p, &header))
// 		return (TRUE);
// 	return (FALSE);
// }


static void				cp_prog_data(t_player *p)
{
	ft_memcpy(p->prog_data, p->file + sizeof(t_header), p->prog_size);
}

t_bool					parse_file(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->player_nb)
	{
		if (parse_one_player_header(&(vm->players[i])) == FALSE)
			return (FALSE);
		cp_prog_data(&(vm->players[i]));
		// vm->players[i].alive = TRUE;
		// int		x = 0;
		// while (x < vm->players[i].prog_size)
		// {
		// 	printf(" %hhx", vm->players[i].prog_data[x]);
		// 	x++;
		// }
		// printf("\n\n");
		i++;
	}
	return (TRUE);
}
