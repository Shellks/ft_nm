#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
    // Création du fichier ELF simulé
    FILE *file = fopen("fake_elf_file", "wb");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // En-tête ELF de base (pour un fichier ELF 64 bits)
    unsigned char elf_header[64] = {
        0x7f, 'E', 'L', 'F',           // Magic number
        2,                            // 64-bit architecture
        1,                            // Little Endian
        1,                            // ELF version
        0,                            // OS/ABI (system V)
        0,                            // ABI version
        0, 0, 0, 0,                   // Padding
        2, 0, 0, 0,                   // File type (Executable)
        0, 0, 0, 0,                   // Machine type (x86_64)
        1, 0, 0, 0,                   // Version
        0, 0, 0, 0,                   // Entry point address (just a placeholder)
        0, 0, 0, 0,                   // Program header offset
        0, 0, 0, 0,                   // Section header offset
        0, 0, 0, 0,                   // Flags
        64, 0, 0, 0,                  // ELF header size (64 bytes)
        0, 0, 0, 0,                   // Program header size
        0, 0, 0, 0,                   // Number of program headers
        0, 0, 0, 0,                   // Section header size
        0, 0, 0, 0,                   // Number of section headers
        0, 0, 0, 0                    // String table index
    };

    // Écriture de l'en-tête ELF dans le fichier
    fwrite(elf_header, 1, sizeof(elf_header), file);

    // Ajout d'autres données fictives ou réelles selon vos besoins
    const char *fake_content = "yo";
    fwrite(fake_content, 1, strlen(fake_content), file);

    // Fermer le fichier
    fclose(file);
    
    printf("Fichier ELF simulé créé : fake_elf_file\n");
    return 0;
}