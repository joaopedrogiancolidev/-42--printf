/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:10:31 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 02:21:17 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct s_format_info
{
	int total_len_printed;
	int min_width;
	int precision;
	char type;

	int flag_minus;
	int flag_zero;
	int flag_space;
	int flag_hash;
	int flag_plus;

	int content_len;
	int prefix_len;
	char sign;
	char *num_str;
	char pad_char;
}               t_format_info;

static void ft_putchar_and_count(char c, t_format_info *info)
{
	write(1, &c, 1);
	info->total_len_printed++;
}

static void ft_putstr_and_count(char *s, int len, t_format_info *info)
{
	if (!s) return;
	write(1, s, len);
	info->total_len_printed += len;
}
/*
static int ft_nbr_len(long long n, int base)
{
	int len = 0;
	if (n == 0) return 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return len;
}

static int ft_unbr_len(unsigned long long n, int base)
{
	int len = 0;
	if (n == 0) return 1;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return len;
}
*/
static char *ft_lltoa_base(long long n, int base, int is_upper_hex)
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

static char *ft_ulltoa_base(unsigned long long n, int base, int is_upper_hex)
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

static void ft_init_format_info(t_format_info *info)
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

static const char *ft_parse_flags(t_format_info *info, const char *format)
{
	while (*format)
	{
		if (*format == '-') info->flag_minus = 1;
		else if (*format == '0') info->flag_zero = 1;
		else if (*format == ' ') info->flag_space = 1;
		else if (*format == '#') info->flag_hash = 1;
		else if (*format == '+') info->flag_plus = 1;
		else break;
		format++;
	}
	return format;
}

static const char *ft_parse_width(t_format_info *info, const char *format)
{
	while (*format >= '0' && *format <= '9')
	{
		info->min_width = info->min_width * 10 + (*format - '0');
		format++;
	}
	return format;
}

static const char *ft_parse_precision(t_format_info *info, const char *format)
{
	if (*format == '.')
	{
		format++;
		info->precision = 0;
		while (*format >= '0' && *format <= '9')
		{
			info->precision = info->precision * 10 + (*format - '0');
			format++;
		}
	}
	return format;
}

static const char *ft_parse_format_specifier(t_format_info *info, const char *format)
{
	format = ft_parse_flags(info, format);
	format = ft_parse_width(info, format);
	format = ft_parse_precision(info, format);

	info->type = *format;
	return format + 1;
}

static void ft_print_padding_chars(int count, char pad_char, t_format_info *info)
{
	while (count-- > 0)
		ft_putchar_and_count(pad_char, info);
}

static void ft_handle_char(va_list arg, t_format_info *info)
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

static void ft_handle_string(va_list arg, t_format_info *info)
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

static void ft_print_formatted_number(t_format_info *info, long long nbr, int base, int is_unsigned, int is_upper_hex)
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

static void ft_handle_int(va_list arg, t_format_info *info)
{
	long long nbr = va_arg(arg, int);
	ft_print_formatted_number(info, nbr, 10, 0, 0);
}

static void ft_handle_unsigned_int(va_list arg, t_format_info *info)
{
	unsigned long long nbr = va_arg(arg, unsigned int);
	ft_print_formatted_number(info, nbr, 10, 1, 0);
}

static void ft_handle_hex(va_list arg, t_format_info *info, int is_upper)
{
	unsigned long long nbr = va_arg(arg, unsigned int);
	ft_print_formatted_number(info, nbr, 16, 1, is_upper);
}

static void ft_handle_pointer(va_list arg, t_format_info *info)
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

int ft_printf (const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	t_format_info info;
	info.total_len_printed = 0;

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ft_init_format_info(&info);
			format = ft_parse_format_specifier(&info, format);
			if (info.type == 'c')
				ft_handle_char(arg, &info);
			else if (info.type == 's')
				ft_handle_string(arg, &info);
			else if (info.type == 'd' || info.type == 'i')
				ft_handle_int(arg, &info);
			else if (info.type == 'u')
				ft_handle_unsigned_int(arg, &info);
			else if (info.type == 'x')
				ft_handle_hex(arg, &info, 0);
			else if (info.type == 'X')
				ft_handle_hex(arg, &info, 1);
			else if (info.type == 'p')
				ft_handle_pointer(arg, &info);
			else if (info.type == '%')
				ft_putchar_and_count('%', &info);
			else
			{
				ft_putchar_and_count('%', &info);
				ft_putchar_and_count(info.type, &info);
			}
		}
		else
		{
			ft_putchar_and_count(*format, &info);
			format++;
		}
	}
	va_end(arg);
	return (info.total_len_printed);
}


#include <stdio.h>
#include <string.h>

int main()
{
	int res_ft, res_std;

	printf("--- Testes Basicos ---\n");
	res_ft = ft_printf("Char: %c, String: %s, Int: %d, UInt: %u, Hex: %x, HexCap: %X, Pointer: %p, Literal: %%\n",
						'A', "Hello", -123, 45678, 255, 255, (void *)0xDEADBEEF, 0);
	res_std = printf("Char: %c, String: %s, Int: %d, UInt: %u, Hex: %x, HexCap: %X, Pointer: %p, Literal: %%\n",
						'A', "Hello", -123, 45678, 255, 255, (void *)0xDEADBEEF, 0);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

	/*
	printf("\n--- Testes de Flags e Largura ---\n");
	res_ft = ft_printf("Int + Space: % d, Int + Plus: %+d, Int Capped: %.2d, String Prec: %.3s, Zero Pad: %05d, Left Align: %-5d\n",
						123, 123, 5, "HelloWorld", 42, 123);
	res_std = printf("Int + Space: % d, Int + Plus: %+d, Int Capped: %.2d, String Prec: %.3s, Zero Pad: %05d, Left Align: %-5d\n",
						123, 123, 5, "HelloWorld", 42, 123);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

	res_ft = ft_printf("Hex Hash: %#x, Hex Hash Cap: %#X, Hex Zero Pad: %08x\n", 255, 255, 1234);
	res_std = printf("Hex Hash: %#x, Hex Hash Cap: %#X, Hex Zero Pad: %08x\n", 255, 255, 1234);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

	printf("\n--- Testes de Casos Especiais ---\n");
	res_ft = ft_printf("String Nula: %s, Int MIN: %d, Int 0 Prec 0: %.0d, Hex 0 Prec 0: %.0x\n",
						(char *)NULL, INT_MIN, 0, 0);
	res_std = printf("String Nula: %s, Int MIN: %d, Int 0 Prec 0: %.0d, Hex 0 Prec 0: %.0x\n",
						(char *)NULL, INT_MIN, 0, 0);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);
	
	res_ft = ft_printf("Pointer Nulo: %p, Pointer 0x0: %p\n", (void *)NULL, (void *)0);
	res_std = printf("Pointer Nulo: %p, Pointer 0x0: %p\n", (void *)NULL, (void *)0);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

	printf("\n--- Combinacoes de Flags ---\n");
	res_ft = ft_printf("Zero and Minus: %-05d, Zero and Precision: %0.5d\n", 123, 123);
	res_std = printf("Zero and Minus: %-05d, Zero and Precision: %0.5d\n", 123, 123);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

	res_ft = ft_printf("Plus and Space: %+ d, Space and Plus: % +d\n", 10, 10);
	res_std = printf("Plus and Space: %+ d, Space and Plus: % +d\n", 10, 10);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

	res_ft = ft_printf("Large width: %10s, Large precision: %.10s\n", "short", "verylongstring");
	res_std = printf("Large width: %10s, Large precision: %.10s\n", "short", "verylongstring");
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

	printf("\n--- Formato Invalido ---\n");
	res_ft = ft_printf("Invalido: %k%y\n");
	res_std = printf("Invalido: %k%y\n");
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);
		*/
	return 0;
}