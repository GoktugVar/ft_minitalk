/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivar <ivar@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:11:20 by ivar              #+#    #+#             */
/*   Updated: 2025/02/04 13:11:46 by ivar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stddef.h>

void	ft_error(char *e);
size_t	ft_strlen(const char *str);
char	*ft_stoa(size_t n);
size_t	ft_atos(const char *str);

#endif