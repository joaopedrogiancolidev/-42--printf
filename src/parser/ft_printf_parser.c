/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:29:52 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 16:29:55 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char *ft_parse_flags(t_format_info *info, const char *format)
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

const char *ft_parse_width(t_format_info *info, const char *format)
{
	while (*format >= '0' && *format <= '9')
	{
		info->min_width = info->min_width * 10 + (*format - '0');
		format++;
	}
	return format;
}

const char *ft_parse_precision(t_format_info *info, const char *format)
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

const char *ft_parse_format_specifier(t_format_info *info, const char *format)
{
	format = ft_parse_flags(info, format);
	format = ft_parse_width(info, format);
	format = ft_parse_precision(info, format);

	info->type = *format;
	return format + 1;
}