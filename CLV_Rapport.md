> # Driver CLV #




# Description du Driver CLV : #
## Initialisation : ##
> Dans ce document on s’intéresse au Driver Clavier , les fonctions de base du driver initialiser les boutons et définir les vecteurs d'interruption (Voir vector.c).

# Description des fonctions de driver : #

## Initialisation du clavier ##


|Prototype|  void vCLV\_iClvInitButtons\_Cmd(void)|
|:--------|:--------------------------------------|
|Paramètres|  void  E  -                           |
|Renvoi   |  void  S  -                           |
|Fonction |  Cette fonction initialise le Driver Clavier |
|Condition|  Sans objet.                          |
**Fonction :** void vCLV\_iClvInitButtons\_Cmd(void)

**Algorithme :**

•  Appel des fonctions d'initialisation de chaque Bouton sw2,sw3,sw4,sw5.



## Initialiser le bouton SW2 : ##


|Prototype| void vCLV\_InitExtInt0\_Cmd(void)|
|:--------|:---------------------------------|
|Paramètres|  Void  E     -                   |
|Renvoi   |  Void  S  -                      |
|Fonction |  Initialiser le Bouton sw2       |
|Condition|  Sans objet.                     |
**Fonction :** void vCLV\_InitExtInt0\_Cmd(void)

**Algorithme:**

•﻿  Activer le Pin43 PIER07\_IE0 .
•﻿  configurer le pin43 DDR07\_D0 Input.
•﻿  Activer l'interruption


## Initialiser le bouton SW3 : ##


|Prototype| void vCLV\_InitExtInt1\_Cmd(void)|
|:--------|:---------------------------------|
|Paramètres|  Void  E     -                   |
|Renvoi   |  Void  S  -                      |
|Fonction |  Initialiser le Bouton sw3       |
|Condition|  Sans objet.                     |
**Fonction :** void vCLV\_InitExtInt1\_Cmd(void)

**Algorithme:**

•﻿  Activer le Pin44 PIER07\_IE1 .
•﻿  configurer le pin44 DDR07\_D1 Input.
•﻿  Activer l'interruption.



## Initialiser le bouton SW4 : ##


|Prototype| void vCLV\_InitExtInt2\_Cmd(void)|
|:--------|:---------------------------------|
|Paramètres|  Void  E     -                   |
|Renvoi   |  Void  S  -                      |
|Fonction |  Initialiser le Bouton sw4       |
|Condition|  Sans objet.                     |
**Fonction :** void vCLV\_InitExtInt2\_Cmd(void)

**Algorithme:**

•﻿  Activer le Pin45 PIER07\_IE2 .
•﻿  configurer le pin45 DDR07\_D2 Input.
•﻿  Activer l'interruption.



## Initialiser le bouton SW5 : ##


|Prototype| void vCLV\_InitExtInt3\_Cmd(void)|
|:--------|:---------------------------------|
|Paramètres|  Void  E     -                   |
|Renvoi   |  Void  S  -                      |
|Fonction |  Initialiser le Bouton sw5       |
|Condition|  Sans objet.                     |
**Fonction :** void vCLV\_InitExtInt3\_Cmd(void)

**Algorithme:**

•﻿  Activer le Pin46 PIER07\_IE3 .
•﻿  configurer le pin46 DDR07\_D3 Input.
•﻿  Activer l'interruption.


## Traitement de l'interruption sur le bouton SW2 : ##


|Prototype|  :  void vCLV\_eSW2(void) |
|:--------|:--------------------------|
|Paramétres|  Void  E  -               |
|Renvoi   |  Void  S  -               |
|Fonction |  Definir l'interruption sur le bouton SW2|
|Condition|  Sans objet.              |
**Fonction :** void vCLV\_eSW2(void)

**Algorithme :**

•﻿  Exécution de l'interruption si le flag EIRR0\_ER0 sera 1.
•﻿  Mise à jour du flag.


## Traitement de l'interruption sur le bouton SW3 : ##


|Prototype|  :  void vCLV\_eSW3(void) |
|:--------|:--------------------------|
|Paramétres|  Void  E  -               |
|Renvoi   |  Void  S  -               |
|Fonction |  Definir l'interruption sur le bouton SW3|
|Condition|  Sans objet.              |
**Fonction :** void vCLV\_eSW3(void)

**Algorithme :**

•﻿  Exécution de l'interruption si le flag EIRR0\_ER1 sera 1.
•﻿  Mise à jour du flag.


## Traitement de l'interruption sur le bouton SW4 : ##


|Prototype|  :  void vCLV\_eSW4(void) |
|:--------|:--------------------------|
|Paramétres|  Void  E  -               |
|Renvoi   |  Void  S  -               |
|Fonction |  Definir l'interruption sur le bouton SW4|
|Condition|  Sans objet.              |
**Fonction :** void vCLV\_eSW4(void)

**Algorithme :**

•﻿  Exécution de l'interruption si le flag EIRR0\_ER2 sera 1.
•﻿  Mise à jour du flag.


## Traitement de l'interruption sur le bouton SW5 : ##


|Prototype|  :  void vCLV\_eSW5(void) |
|:--------|:--------------------------|
|Paramétres|  Void  E  -               |
|Renvoi   |  Void  S  -               |
|Fonction |  Definir l'interruption sur le bouton SW5|
|Condition|  Sans objet.              |
**Fonction :** void vCLV\_eSW5(void)

**Algorithme :**

•﻿  Exécution de l'interruption si le flag EIRR0\_ER3 sera 1.
•﻿  Mise à jour du flag.
