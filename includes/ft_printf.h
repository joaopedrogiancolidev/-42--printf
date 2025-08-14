/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:29:39 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 15:41:08 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
#include <stdio.h>
#include <string.h>


typedef struct	s_format_info 
{
	int		total_len_printed;
	int		min_width;
	int		precision;
	char	type;

	int		flag_minus;
	int		flag_zero;
	int		flag_space;
	int		flag_hash;
	int		flag_plus;
	
	int		content_len;
	int		prefix_len;
	char	sign;
	char	*num_str;
	char	pad_char;
}					t_format_info;

int	ft_printf (const char *format, ...);

#endif