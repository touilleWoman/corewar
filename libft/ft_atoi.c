/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:52:21 by naali             #+#    #+#             */
/*   Updated: 2020/01/26 16:01:47 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		ret;
	int		neg;

	neg = 1;
	i = 0;
	ret = 0;
	while (((str[i] <= 13) && (str[i] >= 9)) || (str[i] == 32))
	{
		i++;
	}
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
		{
			neg = -neg;
		}
		i++;
	}
	while ((str[i] != 0) && (str[i] >= '0') && (str[i] <= '9'))
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * neg);
}
