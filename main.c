/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:29:52 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 15:40:25 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int main()
{
	int	res_ft, res_std;

	printf("--- Testes Basicos ---\n");
	res_ft = ft_printf("Char: %c, String: %s, Int: %d, UInt: %u, Hex: %x, HexCap: %X, Pointer: %p, Literal: %%\n",
						'A', "Hello", -123, 45678, 255, 255, (void *)0xDEADBEEF, 0);
	res_std = printf("Char: %c, String: %s, Int: %d, UInt: %u, Hex: %x, HexCap: %X, Pointer: %p, Literal: %%\n",
						'A', "Hello", -123, 45678, 255, 255, (void *)0xDEADBEEF, 0);
	ft_printf("ft_printf retornou: %d\n", res_ft);
	printf("printf retornou: %d\n", res_std);

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
	return 0;
}