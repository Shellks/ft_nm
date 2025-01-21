# NOM
elf - format des fichiers ELF (Executable and Linking Format)

## SYNOPSIS
```c
#include <elf.h>
```

## DESCRIPTION
Le fichier d'en-tête `<elf.h>` définit le format des fichiers binaires exécutables ELF. Parmi ces fichiers, on trouve des fichiers exécutables classiques, des fichiers objets rélocalisables, des fichiers de core et des objets partagés.

Un fichier exécutable utilisant le format ELF se compose d'un en-tête ELF, suivi soit d'une table d'en-têtes de programme, soit d'une table d'en-têtes de sections, ou des deux. L'en-tête ELF se trouve toujours à l'offset zéro du fichier. Les offsets des tables d'en-têtes de programme et des tables d'en-têtes de sections dans le fichier sont définis dans l'en-tête ELF. Ces deux tables décrivent les particularités restantes du fichier.

Ce fichier d'en-tête décrit les en-têtes mentionnés ci-dessus sous forme de structures en C et inclut également des structures pour les sections dynamiques, les sections de relocation et les tables de symboles.

## Types de base
Les types suivants sont utilisés pour les architectures N bits (N=32, 64, ElfN fait référence à Elf32 ou Elf64, uintN_t fait référence à uint32_t ou uint64_t) :

```c
ElfN_Addr       Adresse de programme non signée, uintN_t
ElfN_Off        Décalage de fichier non signé, uintN_t
ElfN_Section    Index de section non signé, uint16_t
ElfN_Versym     Informations sur la version des symboles non signées, uint16_t
Elf_Byte        caractère non signé
ElfN_Half       uint16_t
ElfN_Sword      int32_t
ElfN_Word       uint32_t
ElfN_Sxword     int64_t
ElfN_Xword      uint64_t
```

(Note : la terminologie *BSD est un peu différente. Là, Elf64_Half est deux fois plus grand qu'Elf32_Half, et Elf64Quarter est utilisé pour uint16_t. Pour éviter toute confusion, ces types sont remplacés par des types explicites ci-dessous.)

Toutes les structures de données que définit le format de fichier suivent les lignes directrices de taille et d'alignement "naturelles" pour la classe concernée. Si nécessaire, des espacements explicites sont ajoutés pour garantir un alignement de 4 octets pour les objets de 4 octets, afin de forcer la taille des structures à être un multiple de 4, et ainsi de suite.

## En-tête ELF (Ehdr)
L'en-tête ELF est décrit par le type `Elf32_Ehdr` ou `Elf64_Ehdr` :

```c
#define EI_NIDENT 16

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    uint16_t      e_type;
    uint16_t      e_machine;
    uint32_t      e_version;
    ElfN_Addr     e_entry;
    ElfN_Off      e_phoff;
    ElfN_Off      e_shoff;
    uint32_t      e_flags;
    uint16_t      e_ehsize;
    uint16_t      e_phentsize;
    uint16_t      e_phnum;
    uint16_t      e_shentsize;
    uint16_t      e_shnum;
    uint16_t      e_shstrndx;
} ElfN_Ehdr;
```

Les champs ont les significations suivantes :

- `e_ident` : Ce tableau de bytes spécifie comment interpréter le fichier, indépendamment du processeur ou du contenu restant du fichier. Dans ce tableau, tout est désigné par des macros qui commencent par le préfixe `EI_` et peuvent contenir des valeurs qui commencent par le préfixe `ELF`. Les macros suivantes sont définies :
    - `EI_MAG0` : Premier byte du numéro magique (0 : 0x7f)
    - `EI_MAG1` : Deuxième byte du numéro magique (1 : 'E')
    - `EI_MAG2` : Troisième byte du numéro magique (2 : 'L')
    - `EI_MAG3` : Quatrième byte du numéro magique (3 : 'F')
    - `EI_CLASS` : Le cinquième byte identifie l'architecture pour ce binaire.
    - `EI_DATA` : Le sixième byte spécifie le codage des données pour le processeur spécifique dans le fichier.
    - `EI_VERSION` : Le septième byte est le numéro de version de la spécification ELF.
    - `EI_OSABI` : Le huitième byte identifie le système d'exploitation et l'ABI pour lequel l'objet est ciblé.
    - `EI_ABIVERSION` : Le neuvième byte identifie la version de l'ABI.
    - `EI_PAD` : Début du remplissage. Ces bytes sont réservés et définis à zéro.

- `e_type` : Ce membre identifie le type de fichier objet.
    - `ET_NONE` : Type inconnu.
    - `ET_REL` : Fichier rélocalisable.
    - `ET_EXEC` : Fichier exécutable.
    - `ET_DYN` : Objet partagé.
    - `ET_CORE` : Fichier de core.

- `e_machine` : Ce membre spécifie l'architecture requise pour un fichier particulier.
    - Par exemple : `EM_NONE` pour une machine inconnue, `EM_386` pour Intel 80386, `EM_X86_64` pour AMD x86-64, etc.

- `e_version` : Ce membre identifie la version du fichier.
    - `EV_NONE` : Version invalide.
    - `EV_CURRENT` : Version actuelle.

- `e_entry` : Ce membre donne l'adresse virtuelle où le système transfère d'abord le contrôle, démarrant ainsi le processus.

- `e_phoff` : Ce membre contient l'offset de la table d'en-têtes de programme dans le fichier.

- `e_shoff` : Ce membre contient l'offset de la table d'en-têtes de sections dans le fichier.

- `e_flags` : Ce membre contient des flags spécifiques au processeur associés au fichier.

- `e_ehsize` : Taille de l'en-tête ELF en octets.

- `e_phentsize` : Taille en octets d'une entrée dans la table des en-têtes de programme.

- `e_phnum` : Nombre d'entrées dans la table des en-têtes de programme.

- `e_shentsize` : Taille d'une entrée d'en-tête de section.

- `e_shnum` : Nombre d'entrées dans la table des en-têtes de section.

- `e_shstrndx` : Index de la table des en-têtes de section associée à la table des noms de section.

## En-tête de programme (Phdr)
La table des en-têtes de programme d'un fichier exécutable ou d'un objet partagé est un tableau de structures, chacune décrivant un segment ou une autre information nécessaire au système pour préparer le programme à l'exécution. Un segment de fichier contient une ou plusieurs sections.

Un en-tête de programme est décrit par les types `Elf32_Phdr` ou `Elf64_Phdr` :

```c
typedef struct {
    uint32_t   p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    uint32_t   p_filesz;
    uint32_t   p_memsz;
    uint32_t   p_flags;
    uint32_t   p_align;
} Elf32_Phdr;

typedef struct {
    uint32_t   p_type;
    uint32_t   p_flags;
    Elf64_Off  p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    uint64_t   p_filesz;
    uint64_t   p_memsz;
    uint64_t   p_align;
} Elf64_Phdr;
```

Les membres les plus importants sont :
- `p_type` : Indique le type de segment (par exemple, `PT_LOAD` pour un segment chargeable).
- `p_offset` : L'offset à partir du début du fichier où se trouve le premier byte du segment.
- `p_vaddr` : L'adresse virtuelle à laquelle le premier byte du segment se trouve en mémoire.
- `p_paddr` : L'adresse physique (utile pour certaines architectures).
- `p_filesz` : Taille du segment dans le fichier.
- `p_memsz` : Taille du segment en mémoire.
- `p_flags` : Masque de flags pertinents pour le segment.
- `p_align` : Valeur d'alignement des segments en mémoire et dans le fichier.

## En-tête de section (Shdr)
La table des en-têtes de section d'un fichier permet de localiser toutes les sections du fichier. Chaque entrée de la table d'en-têtes de section est une structure `Elf32_Shdr` ou `Elf64_Shdr`.

```c
typedef struct {
    uint32_t   sh_name;
    uint32_t   sh_type;
    uint32_t   sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    uint32_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint32_t   sh_addralign;
    uint32_t   sh_entsize;
} Elf32_Shdr;

typedef struct {
    uint32_t   sh_name;
    uint32_t   sh_type;
    uint64_t   sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off  sh_offset;
    uint64_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint64_t   sh_addralign;
    uint64_t   sh_entsize;
} Elf64_Shdr;
```

Les membres les plus importants sont :
- `sh_name` : Nom de la section, indexé dans la table des chaînes de noms des sections.
- `sh_type` : Type de la section (par exemple, `SHT_PROGBITS` pour une section de données du programme).
- `sh_flags` : Flags de la section.
- `sh_offset` : Offset de la section dans le fichier.
- `sh_size` : Taille de la section.
- `sh_addralign` : Alignement de la section en mémoire.
- `sh_entsize` : Taille d'une entrée dans la section.

Les sections sont utilisées pour organiser les données et le code dans un fichier ELF.

## **SHT_STRTAB**  
Cette section contient une **table de chaînes de caractères**. Un fichier objet peut avoir **plusieurs** sections de tables de chaînes.

---

## **SHT_RELA**  
Cette section contient des **entrées de relocation** avec des addends explicites, comme le type `Elf32_Rela` pour la classe des fichiers objets 32 bits. Un fichier objet peut avoir **plusieurs sections de relocation**.

---

## **SHT_HASH**  
Cette section contient une **table de hachage des symboles**. Un fichier objet participant à la **liaison dynamique** doit contenir une table de hachage des symboles. Un fichier objet peut avoir **une seule** table de hachage.

---

## **SHT_DYNAMIC**  
Cette section contient des informations pour la **liaison dynamique**. Un fichier objet peut avoir **une seule** section dynamique.

---

## **SHT_NOTE**  
Cette section contient des **notes** (ElfN_Nhdr).

---

## **SHT_NOBITS**  
Une section de ce type **n'occupe pas d'espace** dans le fichier mais ressemble autrement à une section de type `SHT_PROGBITS`. Bien que cette section ne contienne pas de données, le membre `sh_offset` contient l'**offset conceptuel** du fichier.

---

## **SHT_REL**  
Cette section contient des **offsets de relocation** sans addends explicites, comme le type `Elf32_Rel` pour la classe des fichiers objets 32 bits. Un fichier objet peut avoir **plusieurs sections de relocation**.

---

## **SHT_SHLIB**  
Cette section est **réservée**, mais ses sémantiques ne sont pas spécifiées.

---

## **SHT_DYNSYM**  
Cette section contient un **ensemble minimal de symboles** pour la liaison dynamique. Un fichier objet peut également contenir une section `SHT_SYMTAB`.

---

## **SHT_LOPROC, SHT_HIPROC**  
Les valeurs dans la plage inclusive [**SHT_LOPROC**, **SHT_HIPROC**] sont réservées pour des sémantiques spécifiques au processeur.

---

## **SHT_LOUSER**  
Cette valeur spécifie la **borne inférieure** de la plage d'indices réservée aux programmes applicatifs.

---

## **SHT_HIUSER**  
Cette valeur spécifie la **borne supérieure** de la plage d'indices réservée aux programmes applicatifs. Les types de sections compris entre `SHT_LOUSER` et `SHT_HIUSER` peuvent être utilisés par l'application sans entrer en conflit avec les types de sections définis par le système.

---

# 🏷️ `sh_flags`

Les sections supportent des **indicateurs** (flags) qui décrivent des attributs divers. Si un bit d'indicateur est activé dans `sh_flags`, l'attribut est **actif** pour la section. Sinon, il est **inactif**.

## **SHF_WRITE**  
Cette section contient des **données modifiables** pendant l'exécution du processus.

## **SHF_ALLOC**  
Cette section **occupe de la mémoire** pendant l'exécution du processus. Certaines sections de contrôle ne résident pas dans l'image mémoire d'un fichier objet. Cet attribut est désactivé pour ces sections.

## **SHF_EXECINSTR**  
Cette section contient des **instructions exécutables** de la machine.

## **SHF_MASKPROC**  
Tous les bits dans ce masque sont **réservés pour des sémantiques spécifiques au processeur**.

---

# 🗂️ **Attributs des sections ELF**

## **sh_addr**  
Si cette section apparaît dans l'image mémoire d'un processus, ce membre contient l'**adresse** où le premier octet de la section doit résider. Sinon, il contient zéro.

## **sh_offset**  
La valeur de ce membre contient l'**offset en octets** du début du fichier jusqu'au premier octet de la section.

## **sh_size**  
Ce membre contient la **taille** de la section en octets. Sauf si le type de la section est `SHT_NOBITS`, la section occupe `sh_size` octets dans le fichier.

## **sh_link**  
Ce membre contient un indice vers une **table d'en-têtes de section**. L'interprétation de cet indice dépend du type de la section.

## **sh_info**  
Ce membre contient des informations supplémentaires, dont l'interprétation dépend du type de la section.

## **sh_addralign**  
Certaines sections ont des **contraintes d'alignement d'adresse**. La valeur de `sh_addr` doit être congruente à zéro, modulo la valeur de `sh_addralign`.

## **sh_entsize**  
Certaines sections contiennent une **table d'entrées** de taille fixe. Pour de telles sections, ce membre donne la **taille en octets** de chaque entrée.

---

# 📦 Sections communes dans les fichiers ELF

## `.bss`  
Contient des **données non initialisées** qui contribuent à l'image mémoire du programme. Cette section est de type `SHT_NOBITS`. Les attributs utilisés sont `SHF_ALLOC` et `SHF_WRITE`.

## `.comment`  
Contient des informations de **contrôle de version**. De type `SHT_PROGBITS`, aucun attribut n'est utilisé.

## `.ctors`  
Contient des **pointeurs initialisés vers les fonctions de constructeur C++**. Cette section est de type `SHT_PROGBITS`. Les attributs utilisés sont `SHF_ALLOC` et `SHF_WRITE`.

## `.data`  
Contient des **données initialisées** qui contribuent à l'image mémoire du programme. Elle est de type `SHT_PROGBITS`. Les attributs utilisés sont `SHF_ALLOC` et `SHF_WRITE`.

## `.dynamic`  
Contient des informations pour la **liaison dynamique**. Les attributs incluront `SHF_ALLOC`. La présence de `SHF_WRITE` dépend du processeur. Cette section est de type `SHT_DYNAMIC`.

## `.strtab`  
Contient des **chaînes de caractères** liées aux symboles. Cette section est de type `SHT_STRTAB`.

## `.symtab`  
Contient la **table des symboles**. Si elle fait partie d'un segment chargeable, l'attribut `SHF_ALLOC` est activé. Cette section est de type `SHT_SYMTAB`.

---

# 🧑‍💻 Tables de chaînes et symboles

Les sections de **table de chaînes** contiennent des chaînes de caractères **null-terminées**. Un fichier objet utilise ces chaînes pour représenter les noms des symboles et des sections.

Exemple de structure d'un symbole ELF :

```c
typedef struct {
    uint32_t      st_name;
    Elf32_Addr    st_value;
    uint32_t      st_size;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t      st_shndx;
} Elf32_Sym;

typedef struct {
    uint32_t      st_name;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t      st_shndx;
    Elf64_Addr    st_value;
    uint64_t      st_size;
} Elf64_Sym;
```

---

## 🛠️ Relocalisation

Les **entrées de relocation** (Rel & Rela) connectent les références symboliques avec leurs définitions. Les structures de relocation se présentent comme suit :

### Structure sans addend :

```c
typedef struct {
    Elf32_Addr r_offset;
    uint32_t   r_info;
} Elf32_Rel;
```

### Structure avec addend :

```c
typedef struct {
    Elf32_Addr r_offset;
    uint32_t   r_info;
    int32_t    r_addend;
} Elf32_Rela;
```

# 📜 Relocation and Dynamic Tags in ELF

## 🔧 `r_info` - Symbol Table Index and Relocation Type
Le membre **`r_info`** donne à la fois l'**index de la table des symboles** par rapport auquel la relocalisation doit être effectuée et le **type de relocalisation** à appliquer. Les types de relocalisation sont spécifiques au processeur.

- **Application des types**:  
   Lorsque le texte se réfère au type de relocalisation ou à l'index de la table des symboles, il signifie le résultat de l'application des macros **`ELF[32|64]_R_TYPE`** ou **`ELF[32|64]_R_SYM`**, respectivement, sur le membre **`r_info`** de l'entrée de relocalisation.

---

## ➕ `r_addend` - Constant Addend
Le membre **`r_addend`** spécifie un **ajustement constant** utilisé pour calculer la valeur à stocker dans le champ relocalisable.

- **Description**: Ce champ est utilisé dans les types de relocalisation qui nécessitent un ajout direct.

---

## 🏷️ Dynamic Tags (`d_tag`)

La section **`.dynamic`** contient une série de structures qui détiennent des informations importantes pour la **liaison dynamique**. Le membre **`d_tag`** détermine l'interprétation du champ **`d_un`**.

### Structure Elf32_Dyn

```c
typedef struct {
    Elf32_Sword    d_tag;
    union {
        Elf32_Word d_val;
        Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;
extern Elf32_Dyn _DYNAMIC[];
Structure Elf64_Dyn
c
Copy
typedef struct {
    Elf64_Sxword    d_tag;
    union {
        Elf64_Xword d_val;
        Elf64_Addr  d_ptr;
    } d_un;
} Elf64_Dyn;
extern Elf64_Dyn _DYNAMIC[];

Types de d_tag:
DT_NULL: Marque la fin de la section dynamique.
DT_NEEDED: L'offset de la chaîne de caractères du nom d'une bibliothèque nécessaire.
DT_PLTRELSZ: Taille en octets des entrées de relocalisation PLT.
DT_PLTGOT: Adresse du PLT et/ou GOT.
DT_HASH: Adresse de la table de hachage des symboles.
DT_STRTAB: Adresse de la table de chaînes de caractères.
DT_SYMTAB: Adresse de la table des symboles.
DT_RELA: Adresse de la table de relocalisation Rela.
DT_RELASZ: Taille en octets de la table de relocalisation Rela.
DT_RELAENT: Taille en octets d'une entrée de la table Rela.
DT_STRSZ: Taille en octets de la table des chaînes de caractères.
DT_SYMENT: Taille en octets d'une entrée de la table des symboles.
DT_INIT: Adresse de la fonction d'initialisation.
DT_FINI: Adresse de la fonction de terminaison.
DT_SONAME: L'offset de la chaîne de caractères du nom de l'objet partagé.
DT_RPATH: L'offset de la chaîne de caractères pour le chemin de recherche de bibliothèque (obsolète).
DT_SYMBOLIC: Alerte l'éditeur de liens pour rechercher cet objet partagé avant l'exécutable pour les symboles.
DT_REL: Adresse de la table de relocalisation Rel.
DT_RELSZ: Taille en octets de la table de relocalisation Rel.
DT_RELENT: Taille en octets d'une entrée de la table Rel.
DT_PLTREL: Type d'entrée de relocalisation auquel le PLT fait référence (Rela ou Rel).
DT_DEBUG: Utilisation indéfinie pour le débogage.
DT_TEXTREL: L'absence de cette entrée indique qu'aucune entrée de relocalisation ne doit être appliquée à un segment non modifiable.
DT_JMPREL: Adresse des entrées de relocalisation associées uniquement au PLT.
DT_BIND_NOW: Instructe le lien dynamique à traiter toutes les relocalisations avant de transférer le contrôle à l'exécutable.
DT_RUNPATH: L'offset de la chaîne de caractères pour le chemin de recherche de bibliothèque.
DT_LOPROC, DT_HIPROC: Ces valeurs dans la plage [DT_LOPROC, DT_HIPROC] sont réservées pour des sémantiques spécifiques au processeur.
Description des champs:
d_val: Ce membre représente des valeurs entières, qui peuvent avoir diverses interprétations en fonction de d_tag.
d_ptr: Ce membre représente des adresses virtuelles du programme. Lorsque ces adresses sont interprétées, l'adresse réelle doit être calculée en fonction de la valeur du fichier original et de l'adresse de base en mémoire.
📝 Notes ELF (Nhdr)
Les notes ELF permettent d'ajouter des informations arbitraires que le système peut utiliser. Elles sont principalement utilisées par les fichiers de core (lorsque e_type est ET_CORE), mais de nombreux projets définissent leurs propres extensions. Par exemple, la chaîne d'outils GNU utilise des notes ELF pour transmettre des informations du linker vers la bibliothèque C.

Structure Elf32_Nhdr
c
Copy
typedef struct {
    Elf32_Word n_namesz;
    Elf32_Word n_descsz;
    Elf32_Word n_type;
} Elf32_Nhdr;
Structure Elf64_Nhdr
c
Copy
typedef struct {
    Elf64_Word n_namesz;
    Elf64_Word n_descsz;
    Elf64_Word n_type;
} Elf64_Nhdr;
Champs:
n_namesz: La longueur du champ nom en octets. Le nom est nul-terminé.
n_descsz: La longueur du champ descripteur en octets. Les informations suivent immédiatement le nom en mémoire.
n_type: En fonction de la valeur du champ nom, ce membre peut avoir diverses valeurs, par exemple :
Core files (e_type = ET_CORE) :
NT_PRSTATUS: Structure prstatus.
NT_FPREGSET: Structure fpregset.
NT_PRPSINFO: Structure prpsinfo.
Et bien d'autres.
Namespace par défaut/ inconnu (e_type != ET_CORE) :
NT_VERSION: Une chaîne de version.
NT_ARCH: Information d'architecture.
Exemple d'utilisation des notes:
Les notes permettent de gérer des structures spécifiques selon le système, l'architecture ou le programme en cours. Le format exact varie en fonction de la namespace définie par n_namesz, ce qui permet à divers outils de traiter les données en fonction de leur contexte d'exécution.

📚 Exemple de parsing des notes ELF:
c
Copy
void *memory, *name, *desc;
Elf64_Nhdr *note, *next_note;

/* Le buffer pointe vers le début de la section/segment */
note = memory;

/* Si le nom est défini, il suit immédiatement la note */
name = note->n_namesz == 0 ? NULL : memory + sizeof(*note);

/* Si le descripteur est défini, il suit immédiatement le nom (avec alignement) */
desc = note->n_descsz == 0 ? NULL : memory + sizeof(*note) + ALIGN_UP(note->n_namesz, 4);

/* La prochaine note suit les deux (avec alignement) */
next_note = memory + sizeof(*note) + ALIGN_UP(note->n_namesz, 4) + ALIGN_UP(note->n_descsz, 4);
---