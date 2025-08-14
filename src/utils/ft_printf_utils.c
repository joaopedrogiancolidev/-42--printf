/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:29:12 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 16:29:23 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_putchar_and_count(char c, t_format_info *info)
{
	write(1, &c, 1);
	info->total_len_printed++;
}

void ft_putstr_and_count(char *s, int len, t_format_info *info)
{
	if (!s) return;
	write(1, s, len);
	info->total_len_printed += len;
}

void ft_print_padding_chars(int count, char pad_char, t_format_info *info)
{
	while (count-- > 0)
		ft_putchar_and_count(pad_char, info);
}

void ft_init_format_info(t_format_info *info)
{
	info->min_width = 0;
	info->precision = -1;
	info->type = 0;
	info->flag_minus = 0;
	info->flag_zero = 0;
	info->flag_space = 0;
	info->flag_hash = 0;
	info->flag_plus = 0;

	info->content_len = 0;
	info->prefix_len = 0;
	info->sign = 0;
	info->num_str = NULL;
	info->pad_char = ' ';
}