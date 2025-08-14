/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:30:28 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 16:30:42 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *ft_lltoa_base(long long n, int base, int is_upper_hex)
{
	char *res;
	int len;
	int is_neg = 0;
	unsigned long long temp_n;
	char *base_chars = is_upper_hex ? "0123456789ABCDEF" : "0123456789abcdef";

	if (n == 0) return (res = (char *)malloc(2)) ? (res[0] = '0', res[1] = '\0', res) : NULL;
	if (n < 0) { is_neg = 1; temp_n = -n; }
	else { temp_n = n; }

	len = 0;
	unsigned long long temp_n_for_len = temp_n;
	while (temp_n_for_len > 0) { temp_n_for_len /= base; len++; }
	if (is_neg) len++;

	if (!(res = (char *)malloc(len + 1))) return NULL;
	res[len] = '\0';

	if (is_neg) res[0] = '-';
	while (temp_n > 0)
	{
		res[--len] = base_chars[temp_n % base];
		temp_n /= base;
	}
	return res;
}

char *ft_ulltoa_base(unsigned long long n, int base, int is_upper_hex)
{
	char *res;
	int len;
	char *base_chars = is_upper_hex ? "0123456789ABCDEF" : "0123456789abcdef";

	if (n == 0) return (res = (char *)malloc(2)) ? (res[0] = '0', res[1] = '\0', res) : NULL;

	len = 0;
	unsigned long long temp_n_for_len = n;
	while (temp_n_for_len > 0) { temp_n_for_len /= base; len++; }

	if (!(res = (char *)malloc(len + 1))) return NULL;
	res[len] = '\0';

	while (n > 0)
	{
		res[--len] = base_chars[n % base];
		n /= base;
	}
	return res;
}

void ft_print_formatted_number(t_format_info *info, long long nbr, int base, int is_unsigned, int is_upper_hex)
{
	char *s;
	if (is_unsigned)
		s = ft_ulltoa_base((unsigned long long)nbr, base, is_upper_hex);
	else
		s = ft_lltoa_base(nbr, base, is_upper_hex);
	
	if (!s) return;

	int num_len = 0;
	while(s[num_len]) num_len++;

	if (!is_unsigned && nbr < 0) {
		info->sign = '-';
		num_len--;
	} else if (!is_unsigned && info->flag_plus) {
		info->sign = '+';
	} else if (!is_unsigned && info->flag_space) {
		info->sign = ' ';
	}
	if (info->sign) info->prefix_len++;

	if ((info->type == 'x' || info->type == 'X') && info->flag_hash && nbr != 0) {
		info->prefix_len += 2;
	} else if (info->type == 'p') {
		info->prefix_len += 2;
	}

	info->content_len = num_len;
	if (info->precision != -1 && info->precision > info->content_len) {
		info->content_len = info->precision;
	}
	if (nbr == 0 && info->precision == 0 && (info->type == 'd' || info->type == 'u' || info->type == 'x' || info->type == 'X')) {
		info->content_len = 0;
		if (info->type == 'p') info->content_len = 1;
	}

	if (info->flag_zero && !info->flag_minus && info->precision == -1) {
		info->pad_char = '0';
	} else {
		info->pad_char = ' ';
	}

	int total_content_and_prefix_len = info->content_len + info->prefix_len;
	int padding_needed = info->min_width - total_content_and_prefix_len;
	
	if (nbr == 0 && info->precision == 0 && (info->type == 'x' || info->type == 'X') && info->flag_hash) {
		info->content_len = 0;
	}

	if (!info->flag_minus && info->pad_char == ' ')
		ft_print_padding_chars(padding_needed, info->pad_char, info);

	if (info->sign)
		ft_putchar_and_count(info->sign, info);
	if ((info->type == 'x' || info->type == 'X') && info->flag_hash && nbr != 0) {
		ft_putstr_and_count("0", 1, info);
		ft_putstr_and_count(is_upper_hex ? "X" : "x", 1, info);
	} else if (info->type == 'p') {
		ft_putstr_and_count("0x", 2, info);
	}

	if (!info->flag_minus && info->pad_char == '0')
		ft_print_padding_chars(padding_needed, info->pad_char, info);
	else if (info->type != 's') {
		ft_print_padding_chars(info->precision - num_len, '0', info);
	}
	
	if (!(nbr == 0 && info->precision == 0 && (info->type != 'p' || info->min_width == 0))) {
		if (info->sign == '-') {
			ft_putstr_and_count(s + 1, num_len, info);
		} else {
			ft_putstr_and_count(s, num_len, info);
		}
	} else if (info->type == 'p' && nbr == 0 && info->precision == 0 && info->min_width == 0) {
		ft_putstr_and_count("0x0", 3, info);
	}
	
	if (nbr == 0 && info->precision == 0 && (info->type == 'd' || info->type == 'u' || info->type == 'x' || info->type == 'X') && !(info->flag_hash && (info->type == 'x' || info->type == 'X'))) {
	} else if (nbr == 0 && info->precision == 0 && info->type == 'p') {
	} else if (nbr == 0 && info->precision == 0 && info->type == 'd' && info->sign == ' ') {
		if (info->min_width == 0) {
		} else {
		}
	}

	if (info->flag_minus)
		ft_print_padding_chars(padding_needed, info->pad_char, info);
	
	free(s);
}