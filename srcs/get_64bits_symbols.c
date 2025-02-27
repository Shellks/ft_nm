/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_64bits_symbols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:27:23 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/27 18:46:03 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

static char get_64bits_symbol_type_by_section_type(unsigned char binding, Elf64_Sym *symbol, Elf64_Shdr *section) {
	switch (section->sh_type) {
		case SHT_NOBITS: // check if symbol is in .bss section
			if (symbol->st_size <= sizeof(int)) // is considered as small data (<= int/char)
				return (binding == STB_GLOBAL) ? 'S' : 's';
			else // larger data
				return (binding == STB_GLOBAL) ? 'B' : 'b'; 
		case SHT_PROGBITS: // check if symbol is in .data section
			// if (symbol->st_size <= sizeof(int)) // is considered as small data (<= int/char)
			// 	return (binding == STB_GLOBAL) ? 'G' : 'g';
			// else // larger data
				return (binding == STB_GLOBAL) ? 'D' : 'd'; 
    	case SHT_DYNAMIC:  // check if symbol is dynamic
        	return 'd';
		default:
			return '?';
	}
}

static char get_64bits_symbol_type_by_section_name(unsigned char binding, char *strtab, Elf64_Shdr *section) {
	char *section_name = &strtab[section->sh_name]; // actual section name
	// printf("section_name : %s\n", section_name); // DEBUG PRINT
	if (!ft_strcmp(section_name, ".data") || !ft_strcmp(section_name, ".init_array") || !ft_strcmp(section_name, ".fini_array")) {
		return (binding == STB_GLOBAL) ? 'D' : 'd';
	}
	if (!ft_strcmp(section_name, ".bss")) {
		return (binding == STB_GLOBAL) ? 'B' : 'b';
	}
	if (!ft_strcmp(section_name, ".text") || !ft_strcmp(section_name, ".init") || !ft_strcmp(section_name, ".fini")) {
		return (binding == STB_GLOBAL) ? 'T' : 't';
	}
	else if (!ft_strcmp(section_name, ".debug")) {
		return 'N';
	}
	else if (!ft_strcmp(section_name, ".eh_frame") || !ft_strcmp(section_name, ".gcc_except_table") || !ft_strcmp(section_name, ".eh_frame_hdr")) { // check if symbol is in unwind section
	    if (!(section->sh_flags & SHF_WRITE)) // check read-only
			return 'r';
		else
			return 'p';
	}
	else if (!ft_strcmp(section_name, ".rodata") || !ft_strcmp(section_name, ".note.ABI-tag")) { // Check if symbol is in read-only section
	    return (binding == STB_GLOBAL) ? 'R' : 'r';
	}
	else {
		return '?';
	}
}

static char get_64bits_symbol_type_by_index_symbol(Elf64_Sym *symbol) {
	switch (symbol->st_shndx) {
		case SHN_ABS:
			return 'a'; // check absolute symbol
		case SHN_COMMON:
			return 'C'; // check common symbol
		case SHN_UNDEF:
			return 'U'; // check undefined symbol
		default:
			return '?';
	}
}

static char get_64bits_weak_symbol_type(Elf64_Sym *symbol) {
    if (symbol->st_shndx == SHN_UNDEF) {
        return 'w';  // Weak undefined symbol
    } else {
        return 'W';  // Weak defined symbol
    }
}

char get_64bits_symbol_type(Elf64_Sym *symbol, Elf64_Shdr *section_headers, char *strtab) {
    unsigned char type = ELF64_ST_TYPE(symbol->st_info);
    unsigned char binding = ELF64_ST_BIND(symbol->st_info);
    Elf64_Shdr *section = &section_headers[symbol->st_shndx]; // Section address of the actual symbol
    char symbol_type;
	
    // Check weak symbols
    if (binding == STB_WEAK) {
        return get_64bits_weak_symbol_type(symbol);
    }

    // Check special symbol indices first
    symbol_type = get_64bits_symbol_type_by_index_symbol(symbol);
    if (symbol_type != '?')
		return symbol_type;

    // Check section name
    symbol_type = get_64bits_symbol_type_by_section_name(binding, strtab, section);
    if (symbol_type != '?')
		return symbol_type;

    // Check section type
    symbol_type = get_64bits_symbol_type_by_section_type(binding, symbol, section);
    if (symbol_type != '?')
		return symbol_type;

    // Check special cases
    if (binding == STB_GLOBAL && (symbol->st_other == STV_HIDDEN)) // Unique global symbol
        return 'u';
    if (type == STT_GNU_IFUNC) // Indirect function symbol
        return 'i';

    return '?'; // Unknown symbol type
}