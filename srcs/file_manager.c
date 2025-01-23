/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:55:33 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/23 09:48:17 by acarlott         ###   ########.fr       */
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
	Elf64_Ehdr *elf_hdr = (Elf64_Ehdr *)file->mapped;
	if (check_64bits_file(elf_hdr, file) == false)
		return invalid_file(nm, file);
	printf("File Type: %d\n", elf_hdr->e_type);
	printf("Machine: %d\n", elf_hdr->e_machine);
	printf("Entry point address: 0x%lx\n", elf_hdr->e_entry);
	printf("Program header offset: 0x%lx\n", elf_hdr->e_phoff);
	printf("Section header offset: 0x%lx\n", elf_hdr->e_shoff);
	printf("Number of sections: %d\n", elf_hdr->e_shnum);
	printf("Number of program header: %d\n", elf_hdr->e_phnum);
	return;
}

static void manage_32bits_file(t_nm *nm, t_files *file) {
	Elf32_Ehdr *elf_hdr = (Elf32_Ehdr *)file->mapped;
	if (check_32bits_file(elf_hdr, file) == false)
		return invalid_file(nm, file);
	printf("File Type: %d\n", elf_hdr->e_type);
	printf("Machine: %d\n", elf_hdr->e_machine);
	printf("Entry point address: 0x%x\n", elf_hdr->e_entry);
	printf("Program header offset: 0x%x\n", elf_hdr->e_phoff);
	printf("Section header offset: 0x%x\n", elf_hdr->e_shoff);
	printf("Number of sections: %d\n", elf_hdr->e_shnum);
	printf("Number of program header: %d\n", elf_hdr->e_phnum);
	return;
}