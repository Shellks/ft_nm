/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:06:23 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/21 11:06:34 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_nm.h"

void ft_perror(char *file) {
	switch (errno)
	{
	case EACCES:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Permission denied\n", file);
		break;
	case EEXIST:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': File exists\n", file);
		break;
	case EFAULT:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Bad address\n", file);
		break;
	case EFBIG:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': File too large\n", file);
		break;
	case EINTR:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Interrupted system call\n", file);
		break;
	case EISDIR:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Is a directory\n", file);
		break;
	case ELOOP:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Too many symbolic links encountered\n", file);
		break;
	case EMFILE:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Too many open files\n", file);
		break;
	case ENAMETOOLONG:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': File name too long\n", file);
		break;
	case ENFILE:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Too many open files in system\n", file);
		break;
	case ENODEV:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': No such device\n", file);
		break;
	case ENOENT:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': No such file\n", file);
		break;
	case ENOMEM:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Cannot allocate memory\n", file);
		break;
	case ENOSPC:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': No space left on device\n", file);
		break;
	case ENOTDIR:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Not a directory\n", file);
		break;
	case ENXIO:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': No such device or address\n", file);
		break;
	case EPERM:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Operation not permitted\n", file);
		break;
	case EROFS:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Read-only file system\n", file);
		break;
	case ETXTBSY:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Text file busy\n", file);
		break;
	case EWOULDBLOCK:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Resource temporarily unavailable\n", file);
		break;
	default:
		ft_dprintf(STDERR_FILENO, "ft_nm: \'%s\': Failed to open file\n", file);
		break;
	}
}