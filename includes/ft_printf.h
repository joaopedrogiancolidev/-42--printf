/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:29:39 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 16:34:56 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>


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

/* ft_printf.c */
int ft_printf(const char *format, ...);

/* utils/ft_printf_utils.c */
void ft_putchar_and_count(char c, t_format_info *info);
void ft_putstr_and_count(char *s, int len, t_format_info *info);
void ft_print_padding_chars(int count, char pad_char, t_format_info *info);
void ft_init_format_info(t_format_info *info);

/* parser/ft_printf_parser.c */
const char *ft_parse_flags(t_format_info *info, const char *format);
const char *ft_parse_width(t_format_info *info, const char *format);
const char *ft_parse_precision(t_format_info *info, const char *format);
const char *ft_parse_format_specifier(t_format_info *info, const char *format);

/* handlers/ft_printf_handlers.c */
void ft_handle_char(va_list arg, t_format_info *info);
void ft_handle_string(va_list arg, t_format_info *info);
void ft_handle_int(va_list arg, t_format_info *info);
void ft_handle_unsigned_int(va_list arg, t_format_info *info);
void ft_handle_hex(va_list arg, t_format_info *info, int is_upper);
void ft_handle_pointer(va_list arg, t_format_info *info);

/* number_utils/ft_printf_number_utils.c */
char *ft_lltoa_base(long long n, int base, int is_upper_hex);
char *ft_ulltoa_base(unsigned long long n, int base, int is_upper_hex);
void ft_print_formatted_number(t_format_info *info, long long nbr, int base, int is_unsigned, int is_upper_hex);

#endif