> # Driver UART0 #




# Description de l’UART : #
## Initialisation : ##
> Dans ce document on s’intéresse à la mode asynchrone sans Interruption qui correspond à la mode 0 avec 8 bits de donnée et un seul bit de stop et désactiver la parité.

# Description des fonctions de driver : #

## Initialisation de l’UART : ##


|Prototype|  vUART0\_iInitUART(void)|
|:--------|:------------------------|
|Paramètres|  void  E  -             |
|Renvoi   |  void  S  -             |
|Fonction |  Cette fonction initialise UART avec un mode 0 fonctionnement|
|Condition|   Cette fonction est appelée avant la manipulation de UART|

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


|Prototype|  : unsigned char  u8UART0\_eRead\_Data(void)|
|:--------|:--------------------------------------------|
|Paramètres|  Void  E     -                              |
|Renvoi   |  Void  S  - Donnée Recu                    |
|Fonction |  Cette fonction commande la réception des données|
|Condition|  Sans objet.                                |
**Fonction :** unsigned char  u8UART0\_eRead\_Data(void)

**Algorithme:**

•	Réception des données dés l’apparition du flag de Réception.




## Transmission de donnée : ##


|Prototype|  :  :  Void vUART0\_eWrite\_Data(unsigned char u8Data) |
|:--------|:-------------------------------------------------------|
|Paramétres|  Void  E  - Donnée transmit                           |
|Renvoi   |  Void  S  -                                            |
|Fonction |  Cette fonction commande la transmission des données  |
|Condition|  Sans objet.                                           |
**Fonction :**:  :  Void vUART0\_eWrite\_Data(unsigned char u8Data)

**Algorithme :**

•	Transmission des données dés l’apparition du flag de Transmission.