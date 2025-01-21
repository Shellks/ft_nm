# Documentation de la fonction `mmap`

## Introduction

La fonction `mmap` permet de mapper un fichier ou une autre zone mémoire en mémoire virtuelle, ce qui permet un accès direct à la mémoire au lieu de recourir aux appels systèmes traditionnels comme `read()` ou `write()`. Cette technique peut améliorer les performances lorsqu'on travaille avec de gros fichiers ou des données volumineuses.

### Prototype de la fonction `mmap` :

```c
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

## Arguments de `mmap`

### 1. `addr` (type: `void*`)

- **Description** : L'adresse de départ où vous souhaitez que la zone mémoire soit mappée. Si cet argument est `NULL`, le noyau choisira une adresse appropriée pour le mappage.
- **Comportement** : Si l'adresse est non nulle, `mmap` tentera de mapper la zone mémoire à cette adresse exacte. Cependant, cela peut échouer si l'adresse est déjà utilisée.
- **Valeur typique** : `NULL` si vous voulez que le noyau choisisse l'adresse.

---

### 2. `length` (type: `size_t`)

- **Description** : La taille de la zone mémoire à mapper, en octets. Ce doit être un nombre positif et non nul.
- **Comportement** : Cette valeur détermine la quantité de mémoire qui sera allouée et mappée.
- **Exemple** : Si vous avez un fichier de 1000 octets et que vous souhaitez le mapper entièrement, vous passerez `length = 1000`.

---

### 3. `prot` (type: `int`)

- **Description** : Les protections d'accès pour la mémoire mappée. Vous pouvez combiner plusieurs protections avec un `|` (OU binaire).
- **Valeurs possibles** :
  - `PROT_READ` : Lecture seule.
  - `PROT_WRITE` : Écriture.
  - `PROT_EXEC` : Exécution.
  - `PROT_NONE` : Aucun accès.
- **Comportement** : Ces protections déterminent les droits d'accès à la mémoire mappée.

---

### 4. `flags` (type: `int`)

- **Description** : Les options du mappage. Vous pouvez combiner plusieurs valeurs avec un `|`.
- **Valeurs possibles** :
  - `MAP_PRIVATE` : Mappage privé (les modifications sont locales et ne sont pas répercutées dans le fichier).
  - `MAP_SHARED` : Mappage partagé (les modifications sont répercutées dans le fichier).
  - `MAP_ANONYMOUS` : Mappage anonyme (n'est pas lié à un fichier).
  - `MAP_FIXED` : Mappage à l'adresse spécifiée dans `addr` (attention, peut écraser des zones mémoire existantes).
- **Comportement** : Ces flags influencent la manière dont le mappage interagit avec la mémoire et le fichier.

---

### 5. `fd` (type: `int`)

- **Description** : Le descripteur de fichier d'un fichier ouvert via `open`. Cet argument est nécessaire si vous souhaitez mapper un fichier.
- **Comportement** : `fd` indique le fichier à mapper en mémoire. Il doit être un descripteur valide, obtenu via un appel à `open`.
  
---

### 6. `offset` (type: `off_t`)

- **Description** : L'offset dans le fichier à partir duquel le mappage doit commencer. L'offset doit être un multiple de la taille de la page mémoire du système (souvent 4096 octets).
- **Comportement** : Spécifie le point de départ du mappage dans le fichier. Si vous souhaitez mapper l'intégralité du fichier, vous pouvez définir `offset = 0`.
  
---