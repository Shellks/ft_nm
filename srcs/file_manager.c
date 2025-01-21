/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:55:33 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 11:49:09 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_nm.h"

static void file_executor(char *file);
static void print_stat(char *file, struct stat *stat);

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
	print_stat(file, &stat);
	close(fd);
}

static void print_stat(char *file, struct stat *stat) {
	ft_printf("----------------->Stat - File: \'%s\'<----------------------\n", file);
    ft_printf("Inode: %d\n", (long)stat->st_ino);
    ft_printf("Device: %d\n", (long)stat->st_dev);
    ft_printf("Number of hard links: %d\n", (long)stat->st_nlink);
    ft_printf("User ID: %d\n", stat->st_uid);
    ft_printf("Group ID: %d\n", stat->st_gid);
    ft_printf("Device ID (if special file): %d\n", (long)stat->st_rdev);
    ft_printf("File size: %d bytes\n", (long)stat->st_size);
    ft_printf("Block size for filesystem I/O: %d bytes\n", (long)stat->st_blksize);
    ft_printf("Number of blocks allocated: %d\n", (long)stat->st_blocks);
	ft_printf("---------------------------------------\n");
}