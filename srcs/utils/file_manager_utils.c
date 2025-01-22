#include "../../include/ft_nm.h"

int get_fd(char *file_name) {
	int fd = open(file_name, O_RDONLY);
	if (fd == -1) {
		ft_perror(file_name);
		return ERROR;
	}
	return fd;
}

off_t get_file_size(int fd) {
	struct stat stat;

	if (fstat(fd, &stat) == -1) {
		ft_dprintf(STDERR_FILENO, "ft_nm: %s\n", strerror(errno));
		close(fd);
		return ERROR;
	}
	return stat.st_size;
}

void *get_mapped_file(int fd, off_t file_size) {
	void *mapped = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mapped == MAP_FAILED) {
		ft_dprintf(STDERR_FILENO, "ft_nm: %s\n", strerror(errno));
		close(fd);
		return MAP_FAILED;
	}
	close(fd);
	return mapped;
}

int get_file_arch_type(void *mapped) {
	unsigned char	*elf_hdr = (unsigned char *)mapped;

	if (elf_hdr[EI_CLASS] == ELFCLASS64)
		return ELFCLASS64;
	else if (elf_hdr[EI_CLASS] == ELFCLASS32)
		return ELFCLASS32;
	else
		return ELFCLASSNONE;
}

// TODO - Verifier si le 32bits to 64bits posent pas probleme pour ajouter un check dans le if ci-dessous
// TODO - Verifier si on doit check le e_machine avec le type d'archi de notre machine
// TODO - Check si on a besoin dajouter les verifs de e_type
bool check_magic_elf_word(void *mapped) {
	unsigned char	*elf_hdr = (unsigned char *)mapped;

	// ELF magic word files check
    if (elf_hdr[EI_MAG0] != 0x7f || elf_hdr[EI_MAG1] != 'E' || \
		elf_hdr[EI_MAG2] != 'L' || elf_hdr[EI_MAG3] != 'F') {
		return false;
    }
	return true;
}


bool check_64bits_file(Elf64_Ehdr *elf_hdr, t_files *file) {
	if (elf_hdr->e_type == ET_NONE) { // file type check
		return false;
	}
	if (file->size < elf_hdr->e_ehsize) {
		return false;	
	}
	if (elf_hdr->e_shentsize != sizeof(Elf64_Shdr)) {
		return false;
	}
	if (elf_hdr->e_type != ET_REL && elf_hdr->e_phentsize != sizeof(Elf64_Phdr)) {
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': file format not recognized\n", file->name);
		return false;
	}
	return true;
}

bool check_32bits_file(Elf32_Ehdr *elf_hdr, t_files *file) {
	if (elf_hdr->e_type == ET_NONE) { // file type check
		return false;
	}
	if (file->size < elf_hdr->e_ehsize) {
		return false;	
	}
	if (elf_hdr->e_shentsize != sizeof(Elf32_Shdr)) {
		return false;
	}
	if (elf_hdr->e_type != ET_REL && elf_hdr->e_phentsize != sizeof(Elf32_Phdr)) {
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': file format not recognized\n", file->name);
		return false;
	}
	return true;
}

void invalid_file(t_files *file) {
	ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': file format not recognized\n", file->name);
	if (file->mapped)
		munmap(file->mapped, file->size);
	return;
}