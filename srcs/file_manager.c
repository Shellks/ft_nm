/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:55:33 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/26 12:57:34 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

static void file_executor(t_nm *nm, t_files *files);
static void manage_64bits_file(t_nm *nm, t_files *files);
static void manage_32bits_file(t_nm *nm, t_files *files);

void files_manager(t_nm *nm) {
	t_files *nm_files = nm->files;
	while (nm_files) {
		file_executor(nm, nm_files);
		nm_files = nm_files->next;
	}
}

static void file_executor(t_nm *nm, t_files *file) {
	int fd = get_fd(file->name);
	if (fd == ERROR)
		return;
	file->size = get_file_size(fd);
	if (file->size == ERROR)
		return;
	file->mapped = get_mapped_file(fd, file->size);
	if (file->mapped == MAP_FAILED)
		return;
	if (check_magic_elf_word(file->mapped) == false)
		return invalid_file(nm, file);
	file->arch_type = get_file_arch_type(file->mapped);
	if (file->arch_type == ELFCLASS64)
		manage_64bits_file(nm, file);
	else if (file->arch_type == ELFCLASS32)
		manage_32bits_file(nm, file);
	else
		return invalid_file(nm, file);
	if (munmap(file->mapped, file->size) == ERROR) {
		ft_dprintf(STDERR_FILENO, "ft_nm: %s\n", strerror(errno));
		ft_exit(nm, errno);
	}
}

const char *get_symbol_type(unsigned char st_info) {
    switch (ELF64_ST_TYPE(st_info)) {
        case STT_NOTYPE:  return "NOTYPE";
        case STT_OBJECT:  return "OBJECT";
        case STT_FUNC:    return "FUNC";
        case STT_SECTION: return "SECTION";
        case STT_FILE:    return "FILE";
        default:          return "UNKNOWN";
    }
}


// Fonction pour décoder la liaison du symbole
const char *get_symbol_binding(unsigned char st_info) {
    switch (ELF64_ST_BIND(st_info)) {
        case STB_LOCAL:  return "LOCAL";
        case STB_GLOBAL: return "GLOBAL";
        case STB_WEAK:   return "WEAK";
        default:         return "UNKNOWN";
    }
}



char get_64bits_symbol_type(Elf64_Sym *symbol, Elf64_Shdr *section_headers, char *strtab, int section_count) {
    unsigned char type = ELF64_ST_TYPE(symbol->st_info);
    unsigned char binding = ELF64_ST_BIND(symbol->st_info);
	Elf64_Shdr *section = &section_headers[symbol->st_shndx]; // section adress of the actual symbol
	if (symbol->st_shndx == SHN_ABS) {
        return 'a';  // Symbole absolu
    }
	if (symbol->st_shndx >= section_count) { // Check if symbol index is valid
		return '?';
	}
	char *section_name = &strtab[section->sh_name]; // actual section name
	if (!ft_strcmp(section_name, ".text")) // check if symbol is in text section
		return (binding == STB_GLOBAL) ? 'T' : 't';
	if (!ft_strcmp(section_name, ".debug")) // check if symbol is in debug section
		return 'N';
	if (!ft_strcmp(section_name, ".eh_frame") || !ft_strcmp(section_name, ".gcc_except_table") || !ft_strcmp(section_name, ".frame")) { // check if symbol is in unwind section
	    return 'p';
	}
    if (!ft_strcmp(section_name, ".rodata")) { // Check if symbol is in read-only section
        return (binding == STB_GLOBAL) ? 'R' : 'r';
    }
    if (!ft_strcmp(section_name, ".init_array") || !ft_strcmp(section_name, ".fini_array")) {
        return (binding == STB_GLOBAL) ? 'D' : 'd';
    }
	if (!ft_strcmp(section_name, ".note.ABI-tag")) // check if symbol is in debug section
		return (binding == STB_GLOBAL) ? 'R' : 'r';
    if (!ft_strcmp(section_name, ".init_array") || !ft_strcmp(section_name, ".fini_array")) {
        return (binding == STB_GLOBAL) ? 'D' : 'd';
    }
	// printf("section_name : %s\n", section_name);
	switch (section->sh_type) {
		case SHT_NOBITS: // check if symbol is in .bss section
			if (symbol->st_size <= sizeof(int) || symbol->st_size <= sizeof(char)) // is considered as small data (<= int/char)
				return (binding == STB_GLOBAL) ? 'S' : 's';
			else // larger data
				return (binding == STB_GLOBAL) ? 'B' : 'b'; 
		case SHT_PROGBITS: // check if symbol is in .data section
			if (symbol->st_size <= sizeof(int) || symbol->st_size <= sizeof(char)) // is considered as small data (<= int/char)
				return (binding == STB_GLOBAL) ? 'G' : 'g';
			else // larger data
				return (binding == STB_GLOBAL) ? 'D' : 'd';
    	case SHT_DYNAMIC:  // check if symbol is dynamic
        	return 'd';
		default: break;
	}
	switch (symbol->st_shndx) {
		case SHN_ABS: return 'A'; // check absolute symbol
		case SHN_COMMON: return 'C'; // check common symbol
		case SHN_UNDEF: return 'U'; // check undifined symbol
		default: break;
	}
	if (binding == STB_GLOBAL && (symbol->st_other == STV_HIDDEN)) { // check if symbol is a unique global symbol
        return 'u';
    }
    switch (type) {
		case STT_GNU_IFUNC: return 'i'; // check indirect function symbol
        default:          break;
    }
    if (binding == STB_WEAK) {
        if (ELF64_ST_VISIBILITY(symbol->st_other) == STV_DEFAULT) { // check weak symbol with no link in the past verif
			if (symbol->st_size <= sizeof(int) || symbol->st_size <= sizeof(char))
            	return 'v';  // weak symbol with small default value
			else
				return 'V'; // weak symbol with larger default value
        } else {
			if (symbol->st_size <= sizeof(int) || symbol->st_size <= sizeof(char))
				return 'w';  // weak symbol with small default value
			else
            	return 'W';  // weak symbol with no default value
        }
    }
	return '?'; // Symbol type not found
}

static void manage_64bits_file(t_nm *nm, t_files *file) {
	Elf64_Ehdr *elf_hdr = (Elf64_Ehdr *)file->mapped; // cast mapped file in elf header format
	if (check_64bits_file(elf_hdr, file) == false)
		return invalid_file(nm, file);
	Elf64_Shdr *section_headers = (Elf64_Shdr *)((char *)file->mapped + elf_hdr->e_shoff); // adress of section headers
	Elf64_Shdr *shstrtab_section = &section_headers[elf_hdr->e_shstrndx]; // adress of shstrtab section
	char *shstrtab = (char *)file->mapped + shstrtab_section->sh_offset; // adress of section name
    Elf64_Shdr *symtab_section = NULL;
    Elf64_Shdr *strtab_section = NULL;
	for (int i = 0; i < elf_hdr->e_shnum; i++) {
		Elf64_Shdr *section = &section_headers[i];
		if (section->sh_type == SHT_SYMTAB) {
			symtab_section = section; // offset of symbols table
			strtab_section = &section_headers[section->sh_link]; // offset of strtab section (symbol name)
		}
	}
	if (!symtab_section || !strtab_section) {
		return invalid_file(nm, file);
	}
	Elf64_Sym	*symbols = (Elf64_Sym *)((char *)file->mapped + symtab_section->sh_offset); // address of symbols table
	char		*strtab = (char *)file->mapped + strtab_section->sh_offset; // address of strtab section (symbol name)
	int 		symbol_count = symtab_section->sh_size / sizeof(Elf64_Sym);
	for (int i = 0; i < symbol_count; i++) {
		Elf64_Sym	*symbol = &symbols[i];
		char symbol_type = get_64bits_symbol_type(symbol, section_headers, shstrtab, elf_hdr->e_shnum);
		if (symbol->st_shndx == SHN_UNDEF) {
            printf("                 ");
        } else {
            printf("%016lx ", symbol->st_value);
        }
		printf("%c %s\n", symbol_type, symbol->st_name + strtab);
	}
}

static void manage_32bits_file(t_nm *nm, t_files *file) {
	Elf32_Ehdr *elf_hdr = (Elf32_Ehdr *)file->mapped;
	if (check_32bits_file(elf_hdr, file) == false)
		return invalid_file(nm, file);
	Elf32_Shdr *section_headers = (Elf32_Shdr *)((char *)file->mapped + elf_hdr->e_shoff);
	// Elf32_Shdr *shstrtab_section = &section_headers[elf_hdr->e_shstrndx];
	// char *shstrtab = (char *)file->mapped + shstrtab_section->sh_offset;
	Elf32_Shdr *symtab_section;
    Elf32_Shdr *strtab_section;
	for (int i = 0; i < elf_hdr->e_shnum; i++) {
		Elf32_Shdr *section = &section_headers[i];
		if (section->sh_type == SHT_SYMTAB) {
			symtab_section = section;
			strtab_section = &section_headers[section->sh_link];
		}
	}
	if (!symtab_section || !strtab_section) {
		return invalid_file(nm, file);
	}
}