/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:22 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/27 14:44:15 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

static int ft_strcmp_symbol(const char *s1, const char *s2)
{
    while (*s1 == '_') s1++;
    while (*s2 == '_') s2++;

    while (*s1 && *s2 && ft_tolower(*s1) == ft_tolower(*s2)) {
        s1++;
        s2++;
    }

    return ft_tolower(*s1) - ft_tolower(*s2);
}

void sort_symbols_by_name(Elf64_Sym *symbols, int symbol_count, char *strtab) {
    for (int i = 0; i < symbol_count - 1; i++) {
        for (int j = i + 1; j < symbol_count; j++) {
            if (ft_strcmp_symbol(&strtab[symbols[i].st_name], &strtab[symbols[j].st_name]) > 0) {
                Elf64_Sym temp = symbols[i];
                symbols[i] = symbols[j];
                symbols[j] = temp;
            }
        }
    }
}