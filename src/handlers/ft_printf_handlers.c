/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:31:17 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 16:31:36 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_handle_char(va_list arg, t_format_info *info)
{
	char c = (char)va_arg(arg, int);

	info->content_len = 1;
	int padding_needed = info->min_width - info->content_len;

	if (!info->flag_minus)
		ft_print_padding_chars(padding_needed, info->pad_char, info);

	ft_putchar_and_count(c, info);

	if (info->flag_minus)
		ft_print_padding_chars(padding_needed, info->pad_char, info);
}

void ft_handle_string(va_list arg, t_format_info *info)
{
	char *s = va_arg(arg, char *);
	if (!s) s = "(null)";

	int str_len = 0;
	while (s[str_len]) str_len++;

	info->content_len = str_len;
	if (info->precision != -1 && info->precision < info->content_len)
		info->content_len = info->precision;

	int padding_needed = info->min_width - info->content_len;

	if (!info->flag_minus)
		ft_print_padding_chars(padding_needed, info->pad_char, info);

	ft_putstr_and_count(s, info->content_len, info);

	if (info->flag_minus)
		ft_print_padding_chars(padding_needed, info->pad_char, info);
}

void ft_handle_int(va_list arg, t_format_info *info)
{
	long long nbr = va_arg(arg, int);
	ft_print_formatted_number(info, nbr, 10, 0, 0);
}

void ft_handle_unsigned_int(va_list arg, t_format_info *info)
{
	unsigned long long nbr = va_arg(arg, unsigned int);
	ft_print_formatted_number(info, nbr, 10, 1, 0);
}

void ft_handle_hex(va_list arg, t_format_info *info, int is_upper)
{
	unsigned long long nbr = va_arg(arg, unsigned int);
	ft_print_formatted_number(info, nbr, 16, 1, is_upper);
}

void ft_handle_pointer(va_list arg, t_format_info *info)
{
	uintptr_t ptr = (uintptr_t)va_arg(arg, void *);
	if (ptr == 0) {
		info->content_len = 5;
		int padding_needed = info->min_width - info->content_len;
		if (!info->flag_minus)
			ft_print_padding_chars(padding_needed, info->pad_char, info);
		ft_putstr_and_count("(nil)", 5, info);
		if (info->flag_minus)
			ft_print_padding_chars(padding_needed, info->pad_char, info);
	} else {
		info->flag_hash = 1;
		ft_print_formatted_number(info, (long long)ptr, 16, 1, 0);
	}
}
