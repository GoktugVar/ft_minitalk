/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivar <ivar@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:09:02 by ivar              #+#    #+#             */
/*   Updated: 2025/02/03 16:00:04 by ivar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_error(char *e)
{
	write(1, e, ft_strlen(e));
	exit(EXIT_FAILURE);
}

char	*ft_stoa(size_t n)
{
	char	*str;
	int		len;
	size_t	temp;

	len = 0;
	temp = n;
	if (n == 0)
		len = 1;
	while (temp)
	{
		temp /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[--len] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

size_t	ft_atos(const char *str)
{
	size_t	res;

	res = 0;
	if (!str)
		return (0);
	while (*str >= '0' && *str <= '9')
		res = (*(str++) - '0') + (res * 10);
	return (res);
}
