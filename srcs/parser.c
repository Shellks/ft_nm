#include "../include/ft_nm.h"

static bool handle_option(t_nm *nm, char *option) {
    if (option == "-a" || option == "--debug-syms")
        nm->options->a = true;
    else if (option == "-g" || option == "--extern-only")
        nm->options->g = true;
    else if (option == "-p" || option == "--no-sort")
        nm->options->p = true;
    else if (option == "-r" || option == "--reverse-sort")
        nm->options->r = true;
    else if (option == "-u" || option == "--undefined-only")
        nm->options->u = true;
    else {
        //Handle bad option here
        printf("nm: invalid option -- \'%s\'\n", option);
    }
    return true;
}

void options_parser(t_nm *nm, int argc, char **argv) {
    (void)nm;
    for (int i = 0; i < argc; ++i) {
        ft_printf("args: \'%s\'\n", argv[i]);
        if (argv[i][0] == '-')
            if (handle_option(nm, argv[i]) == false) {
                ft_printf("nm: unrecognized option \'%s\'\n", argv[i]);
                // Quit properly here
                break;
            }
    }
    // Parse options here
}

int binary_parser(t_nm *nm, int argc, char **argv) {
    (void)nm;
    (void)argc;
    (void)argv;
    // Parse binary here
    return SUCCESS;
}

int args_parser(t_nm *nm, int argc, char **argv) {
    options_parser(nm, argc, argv);
    if (binary_parser(nm, argc, argv) == ERROR)
        return ERROR;
    return SUCCESS;
}