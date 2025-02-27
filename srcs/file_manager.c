/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:55:33 by acarlott          #+#    #+#             */
/*   Updated: 2025/02/27 16:43:13 by acarlott         ###   ########.fr       */
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
	sort_symbols_by_name(symbols, symbol_count, strtab);
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