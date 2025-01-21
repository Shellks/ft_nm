# nm(1) - Liste des symboles depuis les fichiers objets

## SYNOPSIS

```bash
nm [-a|--debug-syms]
   [-g|--extern-only]
   [-p|--no-sort]
   [-r|--reverse-sort]
   [-u|--undefined-only]
   [fichier_obj...]
```

## DESCRIPTION

`nm` de GNU liste les symboles des fichiers objets `fichier_obj...`. Si aucun fichier objet n'est spécifié, `nm` suppose le fichier `a.out`.

Pour chaque symbole, `nm` affiche :

- La valeur du symbole, dans la base choisie par les options (voir ci-dessous), ou en hexadécimal par défaut.
- Le type du symbole. Les types suivants sont utilisés au minimum, d'autres peuvent également être utilisés en fonction du format du fichier objet. Si le type est en minuscule, le symbole est généralement local ; si en majuscule, le symbole est global (externe). Cependant, quelques symboles en minuscule sont utilisés pour des symboles globaux spéciaux ("u", "v" et "w").

### Types de symboles

- **"A"** : La valeur du symbole est absolue et ne sera pas modifiée par un autre lien.
- **"B" / "b"** : Le symbole se trouve dans la section BSS. Cette section contient généralement des données non initialisées ou à zéro.
- **"C" / "c"** : Le symbole est commun. Les symboles communs sont des données non initialisées. Lors de la liaison, plusieurs symboles communs peuvent apparaître avec le même nom.
- **"D" / "d"** : Le symbole se trouve dans la section de données initialisées.
- **"G" / "g"** : Le symbole est dans une section de données initialisées pour de petits objets.
- **"i"** : Pour les fichiers au format PE, ce symbole indique qu'il se trouve dans une section spécifique à l'implémentation de DLLs.
- **"I"** : Le symbole est une référence indirecte vers un autre symbole.
- **"N"** : Le symbole est un symbole de débogage.
- **"n"** : Le symbole se trouve dans la section de données en lecture seule.
- **"p"** : Le symbole se trouve dans une section de désassemblage de pile.
- **"R" / "r"** : Le symbole se trouve dans une section de données en lecture seule.
- **"S" / "s"** : Le symbole se trouve dans une section de données non initialisées ou à zéro pour de petits objets.
- **"T" / "t"** : Le symbole se trouve dans la section texte (code).
- **"U"** : Le symbole est indéfini.
- **"u"** : Le symbole est un symbole global unique. Cette extension GNU garantit qu'il n'y aura qu'un seul symbole de ce type dans l'ensemble du processus.
- **"V" / "v"** : Le symbole est un objet faible.
- **"W" / "w"** : Le symbole est un symbole faible non marqué comme un objet faible. Lors de la liaison avec un symbole défini normalement, c'est ce dernier qui est utilisé sans erreur.
- **"-"** : Le symbole est un symbole stabs dans un fichier objet `a.out`. Les champs suivants sont affichés : champ "autre", champ "desc", et le type "stab".
- **"?"** : Le type du symbole est inconnu ou spécifique au format du fichier objet.

Le nom du symbole est également affiché. Si un symbole a des informations de version associées, elles sont affichées également. Si le symbole versionné est indéfini ou caché du linker, la version est affichée comme un suffixe au nom du symbole, précédée du caractère `@`.

### OPTIONS

Les formes longues et courtes des options, montrées ici comme des alternatives, sont équivalentes.

- **-a / --debug-syms** : Affiche tous les symboles, même ceux réservés au débogage (normalement, ils ne sont pas listés).
- **-g / --extern-only** : Affiche uniquement les symboles externes.
- **-p / --no-sort** : Ne trie pas les symboles, les affiche dans l'ordre où ils sont rencontrés.
- **-r / --reverse-sort** : Inverse l'ordre du tri (qu'il soit numérique ou alphabétique).
- **-u / --undefined-only** : Affiche uniquement les symboles indéfinis (externes à chaque fichier objet).
- **@file** : Lit les options de la ligne de commande depuis un fichier. Les options lues sont insérées à la place de l'option @file originale. Si le fichier n'existe pas ou ne peut pas être lu, l'option sera traitée littéralement et ne sera pas supprimée.

    Les options dans le fichier sont séparées par des espaces. Un caractère d'espace peut être inclus dans une option en entourant l'option entière par des guillemets simples ou doubles. N'importe quel caractère (y compris un antislash) peut être inclus en préfixant le caractère à inclure avec un antislash. Le fichier peut lui-même contenir des options @file supplémentaires ; ces options seront traitées de manière récursive.


!!!!!!!!!!!!!!!!!!!!!!!!!!!


Affichage des symboles du fichier ELF :

La principale fonctionnalité de nm est de lister les symboles (fonction, variable, etc.) définis dans le fichier ELF, ainsi que leurs types (comme T pour les symboles dans le code, D pour les symboles dans les données, etc.).
À ajouter dans ton code : Après avoir vérifié qu'il s'agit d'un fichier ELF valide, tu dois aussi extraire les symboles du fichier ELF. Cela nécessite de lire les entêtes de section et les tables de symboles à partir de l'offset et de la taille dans l'en-tête ELF.
Gestion des sections :

nm examine les sections du fichier ELF et se concentre principalement sur la section .text (code) et .data (données). Cela permet d'extraire des symboles qui sont dans ces sections.
À ajouter dans ton code : Tu devras analyser la table des sections (e_shoff et e_shnum dans l'en-tête ELF) et chercher les sections contenant des symboles.
Affichage du type et de la portée des symboles :

nm affiche les symboles en indiquant leur type (par exemple, T pour un symbole dans .text, D pour un symbole dans .data, etc.), ainsi que leur portée (local ou global).
À ajouter dans ton code : Pour extraire les symboles, tu devras analyser la table des symboles et en extraire les informations nécessaires (adresse, type, etc.). Cela implique d'analyser les sections contenant des symboles et d'utiliser le champ st_info pour déterminer leur type et leur liaison.
Gestion des fichiers objets et des fichiers statiques :

nm peut aussi lire des fichiers objets et des fichiers statiques .a, ce qui implique une gestion particulière des sections et des symboles dans ces fichiers.
Pas nécessaire pour le moment, mais si tu veux ajouter cette fonctionnalité, tu devras traiter les fichiers .a en parcourant leurs archives.