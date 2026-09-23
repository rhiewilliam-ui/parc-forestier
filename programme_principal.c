#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
/*************
ici on définit une structure Arbre avec plusieurs champs pour
stocker les informations du fichier csv les champs sont
-id =identifiant de l'arbre sous forme de chaine de charactères
-espece = espece de l'arbre sous forme de chaine de charactères
-age = age de l'arbre sous forme d'entier
-hauteur = hauteur de l'arbre sous forme de nombre à virgule
-diametre = diametre de l'arbre sous forme de nombre à virgule
-volume = volume de l'arbre sous forme de nombre à virgule
-sante = etat de sante de l'arbre sous forme d'entier
*********************/
{
    char id[10];
    char espece[20];
    int age;
    double hauteur;
    double diametre;
    double volume;
    int sante;
} Arbre;

void afficher(Arbre *a, int count)
/**************************
 cette procedure prend en parametre un tableau de structure Arbre et le nombre d'elements total de ce tableau
 et affiche ensuite son contenue de maniére graphique dans la console
**************************/
{
    printf("*-------------------------------------------------------------------------*\n"); // haut du tableau
    for (int i = 0; i < count; i++)                                                          // boucle pour parcourir tout le tableau en utilisant le count pour savoir le nombre d'elements
    {
        printf("| %6s | %7s | %4d ans | %6.2f m | %6.2f cm |%6.2f m3 | %3d/10 |\n", // affichage des elements du tableau en donnant a chaque case une taille fixe pour un affichage propre grace au % 6s ou ici le 6 indique la taille de la case
               a[i].id, a[i].espece, a[i].age,
               a[i].hauteur, a[i].diametre,
               a[i].volume, a[i].sante);
    }
    printf("*-------------------------------------------------------------------------*\n");
}

void recherche(Arbre a[], char espece_chercher[20], int count)
/**************************
 cette procedure prend en parametre une structure de donnée de type Arbre, une chaine de caractere representant l'espece a chercher
 et le nombre d'elements total de ce tableau et affiche ensuite les arbres correspondant a l'espece cherchée de maniére graphique
 *************************/
{
    printf("*-----------------------------------------------------------------------*\n");
    for (int i = 0; i < count; i++)
    {
        if (strcmp(a[i].espece, espece_chercher) == 0) // on utilise strcmp pour comparer les deux chaines de caractéres
        {
            printf("| %6s | %7s | %4d ans | %6.2f m | %6.2f cm |%6.2f m3 | %3d/10 |\n",
                   a[i].id, a[i].espece, a[i].age,
                   a[i].hauteur, a[i].diametre,
                   a[i].volume, a[i].sante);
        }
    }
    printf("*-----------------------------------------------------------------------*\n");
}

void trie_age(Arbre *a, int count)
/**************************
 cette procedure prend en parametre une structure de donnée de type Arbre et le nombre 
 d'elements total de ce tableau et trie ensuite ce tableau par age croissant en utilisant 
 l'algorithme d'insertion
 *************************/
{
    Arbre tmp[1]; // tableau temporaire pour stocker l'element en cours de tri
    int i, indice;
    for (i = 1; i < count; i++)
    {
        tmp[0] = a[i]; // on stocke l'element en cours de tri dans le tableau temporaire
        indice = i;
        while ((indice > 0) && (a[indice - 1].age > tmp[0].age)) // on compare l'age de l'element en cours de tri avec les elements precedents
        {
            a[indice] = a[indice - 1]; // on decale l'element precedent vers la droite
            indice = indice - 1;       // on decremente l'indice pour continuer a comparer avec les elements precedents:
        }
        a[indice] = tmp[0]; // on place l'element en cours de tri a sa place definitive
    }
}

void trie_sante(Arbre *a, int count)
/**************************
 cette procedure prend en parametre une structure de donnée de type Arbre et le 
 nombre d'elements total de ce tableau et trie ensuite ce tableau par etat de 
 sante croissant en utilisant l'algorithme de selection
 *************************/
{
    Arbre tmp[1]; // tableau temporaire pour stocker l'element en cours de tri
    int j, i, indice_max;
    for (i = 0; i < count; i++) // boucle pour parcourir tout le tableau
    {
        indice_max = i; // on initialise l'indice du minimum

        for (j = i + 1; j < count; j++) // boucle pour trouver l'element minimum dans le reste du tableau
        {
            if (a[j].sante < a[indice_max].sante) // on compare l'element i avec le minimum
            {
                indice_max = j; // on met a jour l'indice du minimum
            }
        }
        tmp[0] = a[i];          // on stocke l'element i dans le tableau temporaire
        a[i] = a[indice_max];   // on place le minimum a la position i
        a[indice_max] = tmp[0]; // on place l'element i a la position du minimum
    }
}

int main() // programme principal
/**************************
cette fonction principale gere le menu et les appels aux autres fonctions
elle pezrmet a l'utilisateur de choisir une action a effectuer sur les données des arbres
*************************/
{
    int choix;                                 // variable pour stocker le choix de l'utilisateur
    char espece_chercher[20];                  // variable pour stocker l'espece a chercher
    FILE *f = fopen("test_fichiers.csv", "r"); // ouverture du fichier en mode lecture grace au parametre "r"
    if (!f)                                    // verification de l'ouverture du fichier
    {
        perror("Erreur ouverture fichier");
        return 1;
    }
    Arbre arbres[100]; // tableau pour stocker jusqu’à 100 arbres
    int count = 0;
    char ligne[256];                       // variable pour stocker chaque ligne du fichier
    fgets(ligne, sizeof(ligne), f);        // on lit la premiere ligne (entete) et on l'ignore ce qui permet de passer dirrectement aux données
    while (fgets(ligne, sizeof(ligne), f)) // boucle pour lire chaque ligne du fichier jusqu'a la fin
    {
        for (char *p = ligne; *p; p++) // boucle pour parcourir chaque caractere de la ligne
        {
            if (*p == ',') // on remplace les virgules par des points pour les nombres a virgule
                *p = '.';
        }
        sscanf(ligne, "%[^;];%[^;];%d;%lf;%lf;%lf;%d%*[^ \n]", // on utilise sscanf pour extraire les données de chaque ligne en utilisant le ";" comme separateur
               arbres[count].id,
               arbres[count].espece,
               &arbres[count].age,
               &arbres[count].hauteur,
               &arbres[count].diametre,
               &arbres[count].volume,
               &arbres[count].sante); // on stocke les données extraites dans le tableau de structure Arbre grace au count qui nous sert d'indice et qui est incrémenté a chaque itération

        count++; // on incrémente le compteur d'arbres pour avoir le nombre d'arbre entregistrés
    }
    fclose(f);

    do // boucle pour afficher le menu et traiter les choix de l'utilisateur
    {
        printf("\n Que souhaiter vous faire ? \n");
        printf("1. Afficher la liste des arbres \n");       // choix 1 qui permet d'afficher la liste des arbres
        printf("2. Rechercher des arbres par espece \n");   // choix 2 qui permet de rechercher des arbres par espece
        printf("3. Trier les arbres par age \n");           // choix 3 qui permet de trier les arbres par age
        printf("4. Trier les arbres par etat de sante \n"); // choix 4 qui permet de trier les arbres par etat de sante
        printf("5. Quitter \n");                            // choix 5 qui permet de quitter le programme
        printf("Votre choix : ");
        scanf("%d", &choix); // on lit le choix de l'utilisateur

        if (choix == 1) // si l'utilisateur choisit 1
        {
            afficher(arbres, count);
        }
        else if (choix == 2) // si l'utilisateur choisit 2
        {
            printf("Entrez l'espece a chercher : ");
            scanf("%s", espece_chercher);
            recherche(arbres, espece_chercher, count);
        }
        else if (choix == 3) // si l'utilisateur choisit 3
        {
            trie_age(arbres, count);
            printf("Arbres tries par age : \n");
            afficher(arbres, count);
        }
        else if (choix == 4) // si l'utilisateur choisit 4
        {
            trie_sante(arbres, count);
            printf("Arbres tries par etat de sante : \n");
            afficher(arbres, count);
        }
        else if (choix == 5) // si l'utilisateur choisit 5
        {
            printf("Au revoir !\n");
        }
        else // si l'utilisateur entre un choix invalide
        {
            printf("Choix invalide. Veuillez reessayer.\n");
        }

    } while (choix != 5); // on continue la boucle tant que l'utilisateur n'a pas choisi de quitter
    return 0;
}
