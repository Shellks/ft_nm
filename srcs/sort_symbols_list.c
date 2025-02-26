/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:22 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/26 18:48:04 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

static int ft_strcmp_symbol(const char *s1, const char *s2)
{
    while (*s1 == '_')
        s1++;
    while (*s2 == '_')
        s2++;

    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}

void sort_symbols_by_name(Elf64_Sym *symbols, int symbol_count, char *strtab, Elf64_Shdr *strtab_section) {
    printf("TEST - strtab \'%s\'\n", strtab);

    for (int i = 0; i < symbol_count - 1; i++) {  // commence à i = 0 pour le tri
        int min_idx = i;

        printf("TEST : - ft_strlen(strtab) = %ld -- symbols[i].st_name = %d\n", ft_strlen(strtab), symbols[i].st_name);
        if (symbols[i].st_name == 0 || &strtab[symbols[i].st_name] == NULL ||  symbols[i].st_name > strtab_section->sh_size) {
            printf("Erreur : st_name invalide pour symboles[i] à l'indice %d\n", i);
            continue;
        }

        for (int j = i + 1; j < symbol_count; j++) {
            if (symbols[j].st_name == 0 || &strtab[symbols[j].st_name] == NULL || symbols[j].st_name > strtab_section->sh_size) {
                printf("Erreur : st_name invalide pour symboles[j] à l'indice %d\n", j);
                continue;
            }
            // printf("&strtab[symbols[j].st_name] : %s\n", &strtab[symbols[j].st_name]);
            // printf("&strtab[symbols[min_idx].st_name] : %s\n", &strtab[symbols[min_idx].st_name]);

            if (ft_strcmp_symbol(&strtab[symbols[j].st_name], &strtab[symbols[min_idx].st_name]) < 0) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            Elf64_Sym temp = symbols[i];
            symbols[i] = symbols[min_idx];
            symbols[min_idx] = temp;

            printf("min_idx : %d - i : %d\n", min_idx, i);
        }
    }
}