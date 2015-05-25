# Driver UART0 Avec Interruption #

Dans ce document on s’intéresse à la mode asynchrone avec interruption qui correspond à la mode 0 avec 8 bits de donnée et un seul bit de stop et désactiver le bit de parité .



# Description des fonctions de driver : #

## Initialisation de l’UART : ##


|Prototype|  vUART0\_iInitUART(void)|
|:--------|:------------------------|
|Paramètres|  void E  -              |
|Renvoi   |  void  S  -             |
|Fonction |  Cette fonction initialise UART avec un mode 0 fonctionnement|
|Condition|  Cette fonction est appelée avant la manipulation de UART|

**Fonction :** void vUART0\_iInitUART(void)

**Algorithme :**

•  Configurer la forme de donnée
•  Configurer la longueur de donnée
•  Configurer le Baud rate
•  Configurer la longueur de bit de stop
•  Désactiver le bit de parité
•  Activé la transmission
•  Activé la réception
•  Activé les Pins SIN0 et SOT0 pour la réception et la transmission.


## Réception de donnée : ##


|Prototype|  void RX\_UART0(void)|
|:--------|:---------------------|
|Paramètres|  Void  E     -       |
|Renvoi   |  Void  S  - Donnée Recu|
|Fonction |  Cette fonction commande la réception des données|
|Condition|  Sans objet.         |
**Fonction :**void RX\_UART0(void)

**Algorithme:**

•	Contrôler les erreurs
•	Envoyer les données au registre RDR0 à l’aide du Buffer.
•	Incrémenter le pointeur du Buffer.



## Transmission de donnée : ##


|Prototype|  Void TX\_UART0(void)|
|:--------|:---------------------|
|Paramétres|  Void  E  - Donnée transmit|
|Renvoi   |  Void  S  -          |
|Fonction |  Cette fonction commande la transmission des données|
|Condition|  Sans objet.         |
**Fonction :**TX\_UART0(void)

**Algorithme :**

•	Envoyer les données au registre TDR0 à l’aide du Buffer.
•	Incrémenter le pointeur du Buffer.