/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:55:33 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 18:58:34 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

void print_section(void *mapped) {
	Elf64_Ehdr *elf64_header = (Elf64_Ehdr *)mapped;
	Elf64_Shdr *section_headers = (Elf64_Shdr *)((char *)mapped + elf64_header->e_shoff);

	for (int i = 0; i < elf64_header->e_shnum; ++i) {
    	Elf64_Shdr *section = &section_headers[i];
    	printf("Section %d:\n", i);
    	printf("  Section name: %d\n", section->sh_name);
    	printf("  Section type: 0x%x\n", section->sh_type);
    	printf("  Section address: 0x%lx\n", section->sh_addr);
    	printf("  Section size: 0x%lx\n", section->sh_size);
	}
}

static void file_executor(char *file);
// static void print_stat(char *file, struct stat *stat);
static bool is_valid_elf_files(void *mapped);

void files_manager(t_nm *nm) {
	t_files *nm_files = nm->files;
	while (nm_files) {
		file_executor(nm_files->name);
		nm_files = nm_files->next;
	}
}

static void file_executor(char *file) {
	struct stat stat;
	
	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		ft_perror(file);
		return;
	}
	if (fstat(fd, &stat) == -1) {
		ft_dprintf(STDERR_FILENO, "ft_nm: %s\n", strerror(errno));
		close(fd);
		return;
	}
	void *mapped = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mapped == MAP_FAILED) {
		ft_dprintf(STDERR_FILENO, "ft_nm: %s\n", strerror(errno));
		close(fd);
		return;
	}
	if (is_valid_elf_files(mapped) == false) {
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': file format not recognized\n", file);
        munmap(mapped, stat.st_size);
		close(fd);
		return;
	}
	write(1, mapped, stat.st_size);
    munmap(mapped, stat.st_size);
	close(fd);
}


static bool is_valid_elf_files(void *mapped) {
	Elf64_Ehdr	*elf64_header = (Elf64_Ehdr *)mapped;

	// ELF magic word files check
    if (elf64_header->e_ident[EI_MAG0] != 0x7f || elf64_header->e_ident[EI_MAG1] != 'E' || \
		elf64_header->e_ident[EI_MAG2] != 'L' || elf64_header->e_ident[EI_MAG3] != 'F') {
		return false;
    }
	if (elf64_header->e_ident[EI_CLASS] == 0) // ELF arch type predestinated check
		return false;
	if (elf64_header->e_type == ET_NONE) // file type check
		return false;
	// TODO - Verifier si le 32bits to 64bits posent pas probleme pour ajouter un check dans le if ci-dessous
	// TODO - elf64_header->e_ident[EI_DATA] voir si needer pour endianness des octets
	// TODO - Verifier si on doit check le e_machine avec le type d'archi de notre machine
	// if (elf64_header->e_machine != 0x03 || elf64_header->e_machine != 0x03E) { // 64 bits architecture check
	// 	return false;
	// }
	if (elf64_header->e_ident[EI_CLASS] == 0) {
		printf("File Type: %d\n", elf64_header->e_type);
		printf("Machine: %d\n", elf64_header->e_machine);
		printf("Entry point address: 0x%lx\n", elf64_header->e_entry);
		printf("Program header offset: 0x%lx\n", elf64_header->e_phoff);
		printf("Section header offset: 0x%lx\n", elf64_header->e_shoff);
		printf("Number of sections: %d\n", elf64_header->e_shnum);
		printf("Number of program header: %d\n", elf64_header->e_phnum);
	} else {
		Elf32_Ehdr *elf32_header = (Elf32_Ehdr *)mapped;
    	printf("File Type: %d\n", elf32_header->e_type);
    	printf("Machine: %d\n", elf32_header->e_machine);
		printf("Entry point address: 0x%x\n", elf32_header->e_entry);
		printf("Program header offset: 0x%x\n", elf32_header->e_phoff);
		printf("Section header offset: 0x%x\n", elf32_header->e_shoff);
    	printf("Number of sections: %d\n", elf32_header->e_shnum);
		printf("Number of program header: %d\n", elf32_header->e_phnum);
	}
	print_section(mapped);
	return true;
}

// static void print_stat(char *file, struct stat *stat) {
// 	ft_printf("----------------->Stat - File: \'%s\'<----------------------\n", file);
//     ft_printf("Inode: %d\n", (long)stat->st_ino);
//     ft_printf("Device: %d\n", (long)stat->st_dev);
//     ft_printf("Number of hard links: %d\n", (long)stat->st_nlink);
//     ft_printf("User ID: %d\n", stat->st_uid);
//     ft_printf("Group ID: %d\n", stat->st_gid);
//     ft_printf("Device ID (if special file): %d\n", (long)stat->st_rdev);
//     ft_printf("File size: %d bytes\n", (long)stat->st_size);
//     ft_printf("Block size for filesystem I/O: %d bytes\n", (long)stat->st_blksize);
//     ft_printf("Number of blocks allocated: %d\n", (long)stat->st_blocks);
// 	ft_printf("---------------------------------------\n");
// }