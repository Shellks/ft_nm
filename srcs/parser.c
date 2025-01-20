#include "../include/ft_nm.h"

static void handle_options_error(t_nm *nm);
void options_handler(t_nm *nm, char *option);
static bool files_handler(t_nm *nm, char *file);
static bool handle_flag_option(t_nm *nm, char flag);
static bool handle_word_option(t_nm *nm, char *option);

int args_parser(t_nm *nm, int argc, char **argv) {
    bool options_end = false;
    for (int i = 1; i < argc; i++) {
        ft_printf("args[%d] -> \'%s\'\n", i, argv[i]);
        if (!ft_strcmp(argv[i], "--")) {
            if (options_end) {
                if (files_handler(nm, argv[i]) == false)
                    return ERROR;
                continue;
            }
            options_end = true;
            continue;
        }
        if (!options_end && argv[i][0] == '-' && argv[i][1]) {
            options_handler(nm, argv[i]);
        } else {
            if (files_handler(nm, argv[i]) == false)
                return ERROR;
        }
    }
    return SUCCESS;
}

void print_file_list(t_nm *nm) {
    while (nm->files->next) {
        
    }
}

static bool files_handler(t_nm *nm, char *file) {
    (void)nm;
    t_files *node = lst_files_new_node(file);
    if (!node) {
        ft_dprintf(STDERR_FILENO, "Failed to create new list file node..");
        ft_exit(nm);
    }
    lst_files_add_back(&nm->files, node);
    ft_printf("File \'%s\' added to files chained list !\n", file);
    return true;
}

void options_handler(t_nm *nm, char *option) {
    if (option[1] && option[1] == '-') {
        if (handle_word_option(nm, option) == false) {
            ft_dprintf(STDERR_FILENO, "ft_nm: unrecognized option \'%s\'\n", option);
            handle_options_error(nm);
        } else {
            ft_printf("Options \'%s\' added to struct options !\n", option);
        }
    } else {
        for (size_t i = 1; i < ft_strlen(option); i++) {
            if (handle_flag_option(nm, option[i]) == false) {
                ft_dprintf(STDERR_FILENO, "ft_nm: unrecognized option \'%c\'\n", option[i]);
                handle_options_error(nm);
            } else {
                ft_printf("Options \'%c\' added to struct options !\n", option[i]);
            }
        }
    }
}

static bool handle_flag_option(t_nm *nm, char flag) {
    bool ret = true;
    if (flag == 'a')
        nm->options->a = true;
    else if (flag == 'g')
        nm->options->g = true;
    else if (flag == 'p')
        nm->options->p = true;
    else if (flag == 'r')
        nm->options->r = true;
    else if (flag == 'u')
        nm->options->u = true;
    else
        ret = false;
    return ret;
}

static bool handle_word_option(t_nm *nm, char *option) {
    (void)option;
    bool ret = true;
    if (!ft_strcmp(option, "--debug-syms"))
        nm->options->a = true;
    else if (!ft_strcmp(option, "--extern-only"))
        nm->options->g = true;
    else if (!ft_strcmp(option, "--no-sort"))
        nm->options->p = true;
    else if (!ft_strcmp(option, "--reverse-sort"))
        nm->options->r = true;
    else if (!ft_strcmp(option, "--undefined-only"))
        nm->options->u = true;
    else
        ret = false;
    return ret;
}

static void handle_options_error(t_nm *nm) {
    ft_dprintf(STDERR_FILENO, OPTION_ERROR);
    ft_exit(nm);
}