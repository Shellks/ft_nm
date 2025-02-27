/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_64bits_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:57:29 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/27 19:09:51 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

void print_64bits_symbols(t_files *file, Elf64_Shdr *section_headers, Elf64_Shdr *symtab_section, Elf64_Shdr *strtab_section, char *shstrtab) {
	Elf64_Sym	*symbols = (Elf64_Sym *)((char *)file->mapped + symtab_section->sh_offset); // address of symbols table
	char		*strtab = (char *)file->mapped + strtab_section->sh_offset; // address of strtab section (symbol name)
	int 		symbol_count = symtab_section->sh_size / sizeof(Elf64_Sym);

	// TODO - manage here different sort options
	sort_symbols_by_name(symbols, symbol_count, strtab); // basic nm sort

	// TODO - manage print with options or not -- need to remove 'a' and 'N' symbol type with no options
	for (int i = 1; i < symbol_count; i++) {
		Elf64_Sym	*symbol = &symbols[i];
		char symbol_type = get_64bits_symbol_type(symbol, section_headers, shstrtab);
		
		if (symbol->st_shndx == SHN_UNDEF) {
            printf("                 ");
        } else {
            printf("%016lx ", symbol->st_value);
        }
		
		printf("%c %s\n", symbol_type, symbol->st_name + strtab);
	}
}