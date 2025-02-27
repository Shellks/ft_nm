/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_64bits_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:57:29 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/27 20:02:51 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

//TODO
static void undefined_only_64bits_symbols_print(int symbol_count, Elf64_Sym	*symbols, Elf64_Shdr *section_headers, char *shstrtab, char *strtab) {
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

//TODO
static void extern_only_64bits_symbols_print(int symbol_count, Elf64_Sym	*symbols, Elf64_Shdr *section_headers, char *shstrtab, char *strtab) {
	for (int i = 1; i < symbol_count; i++) {
		Elf64_Sym	*symbol = &symbols[i];
		char symbol_type = get_64bits_symbol_type(symbol, section_headers, shstrtab);
		
		if (symbol_type == 'a' || symbol_type == 'N')
			continue;
			
		if (symbol->st_shndx == SHN_UNDEF) {
            printf("                 ");
        } else {
            printf("%016lx ", symbol->st_value);
        }
		
		printf("%c %s\n", symbol_type, symbol->st_name + strtab);
	}
}

static void full_type_64bits_symbols_print(int symbol_count, Elf64_Sym	*symbols, Elf64_Shdr *section_headers, char *shstrtab, char *strtab) {
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

static void basic_type_64bits_symbols_print(int symbol_count, Elf64_Sym	*symbols, Elf64_Shdr *section_headers, char *shstrtab, char *strtab) {
	for (int i = 1; i < symbol_count; i++) {
		Elf64_Sym	*symbol = &symbols[i];
		char symbol_type = get_64bits_symbol_type(symbol, section_headers, shstrtab);
		if (symbol_type == 'a' || symbol_type == 'N')
			continue;
		if (symbol->st_shndx == SHN_UNDEF) {
            printf("                 ");
        } else {
            printf("%016lx ", symbol->st_value);
        }
		
		printf("%c %s\n", symbol_type, symbol->st_name + strtab);
	}
}

void print_64bits_symbols(t_files *file, Elf64_Shdr *section_headers, Elf64_Shdr *symtab_section, Elf64_Shdr *strtab_section, char *shstrtab, t_options *options) {
	Elf64_Sym	*symbols = (Elf64_Sym *)((char *)file->mapped + symtab_section->sh_offset); // address of symbols table
	char		*strtab = (char *)file->mapped + strtab_section->sh_offset; // address of strtab section (symbol name)
	int 		symbol_count = symtab_section->sh_size / sizeof(Elf64_Sym);

	// TODO - manage here different sort options
	if (!options->p)
		sort_symbols_by_name(symbols, symbol_count, strtab); // basic nm sort

	// TODO - manage print with options or not -- need to remove 'a' and 'N' symbol type with no options
	if (options->u)
		undefined_only_64bits_symbols_print(symbol_count, symbols, section_headers, shstrtab, strtab);
	else if (options->g)
		extern_only_64bits_symbols_print(symbol_count, symbols, section_headers, shstrtab, strtab);
	else if (options->a)
		full_type_64bits_symbols_print(symbol_count, symbols, section_headers, shstrtab, strtab);
	else
		basic_type_64bits_symbols_print(symbol_count, symbols, section_headers, shstrtab, strtab);
}