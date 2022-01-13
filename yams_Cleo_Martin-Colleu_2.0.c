/**
 * @file yams_Cleo_Martin-Colleu_2.0.c
 * @author Cléo Martin-Colleu
 * @brief Jeu de yams dans le terminal (il marche)
 * @version 2.0
 * @date 2021-11-20
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @def points du full house
 **/
#define FULL_HOUSE 25

/**
 * @def points de la petite suite
 **/
#define PETITE_SUITE 30

/**
 * @def points de la grande suite
 **/
#define GRANDE_SUITE 40

/**
 * @def points du yams
 **/
#define YAMS 50

/**
 * @def score minimum du bonus
 **/
#define SCORE_MIN_BONUS 62

/**
 * @def points de la grande suite
 **/
#define BONUS 35

/**
 * @def nombre de dés
 **/
#define NB_DE 5

/**
 * @def nombre de joueurs
 **/
#define NB_JOUEUR 2

/**
 * @def nombre de cases dans la feuille de marque
 **/
#define NB_CASE 17

/**
 * @def nombre de caracteres maximal dans le nom des joueurs
 **/
#define TAILLE_NOM 9

typedef int type_de[2][NB_DE];
typedef int type_score[NB_JOUEUR][NB_CASE];
typedef char nom[TAILLE_NOM+1];


int f_total(int table[7],int debut,int fin);
void majuscule(char *chaine);
void case_int(int nb);
void case_int_total(int nb);
void case_str(char chaine[10],int taille_case);
void ligne1 (nom j1,nom j2);
void ligne_global (char chaine[20], int nb1, int nb2);
void ligne_total (char chaine[20], int nb1, int nb2);
void separateur ();
void tableau (type_score score,nom j1,nom j2,int j_actif, type_score possibilitees);
int de_random();
void lancer_de(type_de de);
void valider_points(int de[NB_DE],int score[NB_CASE]);
void choix_de(type_de de);
void menu(type_de de,type_score score, int* nb_lancer,int joueur_actif, nom nom_joueur_actif,int* fin);
int total_nombre(int de[NB_DE],int nombre);
int brelan(int de[NB_DE]);
int carre(int de[NB_DE]);
int full_house (int de[NB_DE]);
int petite_suite(int de[NB_DE]);
int grande_suite(int de[NB_DE]);
int yams(int de[NB_DE]);
int chance(int de[NB_DE]);
void verif_nom(nom joueur,int j);
void afficher_de(char nom, int de);
void tri(int res[NB_DE]);

/**
 * @brief tri la liste par ordre croissant
 * 
 * @param res ,int[NB_DE], entrée/sortie
 */
void tri(int res[NB_DE])
{
    int min,temp;
    for (int i = 0; i < NB_DE-1; i++)
    {
        min = i;
        for (int a = i; a < NB_DE; a++)
        {
            if (res[a]<res[min])
            {
                min =a;
            }
        }
        temp = res[i];
        res[i]=res[min];
        res[min]=temp;
    }
}

/**
 * @brief permet de rentrer et de verifier  une chaine de caractère pour qu'elle fasse au maximum 10 caractere,
 * et que chaque caractère appartient à la table ASCII.
 * @param joueur , nom, sortie
 * @param j , int, entrée
 */
void verif_nom(nom joueur,int j)
{
    char nom_test[50];
    int valide = 0;
    printf("joueur %d, quel est votre nom :\n",j);
    while (valide == 0)
    {
        valide = 1;
        scanf("%s",nom_test);
        if (strlen(nom_test)>TAILLE_NOM || strlen(nom_test)<1)
        {
            valide = 0;
            printf("\033[31m");
            printf("erreur, trop de caracetres\n");
            printf("\033[00m");
        }
        else
        {
            for (int i = 0; i < strlen(nom_test)-1; i++)
            {
                if (nom_test[i] > 255 || nom_test[i] < 0)
                {
                    printf("\033[31m");
                    printf("erreur (pas d'accents et evitez certains caracteres)\n");
                    printf("\033[00m");
                    valide =0;
                }
            }
        }
    }
    for (int i = 0; i < TAILLE_NOM; i++)
    {
        joueur[i] = nom_test[i];
    }
    
}

/**
 * @brief fonction qui retourne une valeur aléatoire comprise entre  1 et 6
 * 
 * @return int 
 */
int de_random()
{
    return (rand() % 6)+1;
}


/**
 * @brief remplace les minuscules d'une chaine par des majuscules
 * 
 * @param chaine[], char, entrée
 */
void majuscule(char *chaine)
{
    char min[27] = "abcdefghijklmnopqrstuvwxyz";
    char maj[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < strlen(chaine); i++)
    {
        for (int a = 0; a < 27; a++)
        {
            if(chaine[i] == min[a])
            {
                chaine[i] = maj[a];
            }
        }
        
    }
    
}


/**
 * @brief calcule la somme des valeur d'un tableau compris entre un indice 
 * de début et un indice de fin.
 * 
 * @param table , int[7], entrée
 * @param debut , int, entrée
 * @param fin , int, entrée
 * @return int 
 */

int f_total(int table[7],int debut,int fin)
{
    int t;
    t = 0;
    for (int i = debut; i <= fin; i++)
    {
        if (table[i] != -1)
        {
            t = t + table[i];
        }
    }
    return t;
    
    
}


/**
 * @brief adapte la taille de case d'un tableau à l'entier donné et l'affiche
 * (si nb = 0 alors affiche un X dans la case)
 * @param nb , int, entrée
 */

void case_int(int nb)
{
    if ( nb==0)
    {
        printf("   X     ");
    }
    else if (nb == -1)
    {
        printf("         ");
    }
    else if (nb>0 && nb<10)
    {
        printf("   %d     ",nb);
    }
    else if (nb>=10 && nb<100)
    {
        printf("   %d    ",nb);
    }
    else
    {
        printf("   %d   ",nb);
    }
    
}

/**
 * @brief adapte la taille de case d'un tableau à l'entier donné et l'affiche
 * (pour les totaux, n'affiche pas de X contrairement à case_int)
 * @param nb , int, entrée
 */
void case_int_total(int nb)
{
    if (nb == -1)
    {
        printf("         ");
    }
    else if (nb>=0 && nb<10)
    {
        printf("   %d     ",nb);
    }
    else if (nb>=10 && nb<100)
    {
        printf("   %d    ",nb);
    }
    else
    {
        printf("   %d   ",nb);
    }
    
}


/**
 * @brief adapte le nombre d'espace d'une case selon la taille de la chaine donnée
 * et  la taille de la case prévue
 * @param chaine , char[10], entrée
 * @param taille_case , int, entrée
 */

void case_str(char chaine[10],int taille_case)
{
    printf("%s",chaine);
    for (int i = 0; i < taille_case-strlen(chaine); i++)
    {
        printf(" ");
    } 
}


/**
 * @brief affiche la première ligne du tableau en y entrant le nom des joueurs
 * 
 * @param j1 , nom, entrée
 * @param j2 , nom, entrée
 */
void ligne1 (nom j1,nom j2)
{
    const int espace = 19;
    for (int i = 0; i < espace+1; i++)
    {
        printf(" ");
    }
    printf("___________________\n");

    for (int i = 0; i < espace; i++)
    {
        printf(" ");
    }
    printf("|");
    case_str(j1,9);
    printf("|");
    case_str(j2,9);
    printf("|\n");
    printf("___________________|_________|_________|\n");

    
}


/**
 * @brief affiche la plupart des autres lignes du tableau selon les paramètres donnés
 * (texte de la case 1, score du j1, score du j2)
 * @param chaine , char[20], entrée
 * @param nb1 , int, entrée
 * @param nb2 , int, entrée
 */

void ligne_global (char chaine[20], int nb1, int nb2)
{
    printf("|");
    case_str(chaine,18);
    printf("|");
    case_int(nb1);
    printf("|");
    case_int(nb2);
    printf("|\n");
}

/**
* @brief affiche affiche les lignes du tableau contenant un total 
 * (texte de la case 1, score du j1, score du j2)
 * pour afficher les totaux, car appel case_total_int())
 * @param chaine , char[20], entrée
 * @param nb1 , int, entrée
 * @param nb2 , int, entrée
 * */
void ligne_total (char chaine[20], int nb1, int nb2)
{
    printf("|");
    case_str(chaine,18);
    printf("|");
    case_int_total(nb1);
    printf("|");
    case_int_total(nb2);
    printf("|\n");
}


/**
 * @brief affiche une ligne du tableau mais mettant de la couleur sur la colonne du joueur actif.
 * (texte de la case 1, score du j1, score du j2)
 * @param chaine , char[20], entrée
 * @param nb1 , int, entrée
 * @param nb2 , int, entrée
 */

void ligne_possibilitees (char chaine[20], int nb1, int nb2,int j_actif)
{
    printf("|");
    case_str(chaine,18);
    printf("|");
    if (j_actif == 0)
    {
        printf("\033[32m");
        case_int(nb1);
        printf("\033[00m");
        printf("|");
        case_int(nb2);
        printf("|\n");
    }
    else
    {
        case_int(nb1);
        printf("|");
        printf("\033[32m");
        case_int(nb2);
        printf("\033[00m");
        printf("|\n");
    }
}


/**
 * @brief affiche une ligne de séparation
 */
void separateur ()
{
    printf("|__________________|_________|_________|\n");
}

/**
 * @brief calcul les differentes possibilitées de points selon la valeur des dés,
 * puis les places dans un tableau de type type_score, le joeur
 * @param p , type_score, sortie
 * @param de , int, entrée
 * @param j_actif , int, entrée
 */
void calcul_possibilitees(type_score p,int de[NB_DE], int j_actif)
{
    int autre_j;
    p[j_actif][0] = total_nombre(de,1);
    p[j_actif][1] = total_nombre(de,2);
    p[j_actif][2] = total_nombre(de,3);
    p[j_actif][3] = total_nombre(de,4);
    p[j_actif][4] = total_nombre(de,5);
    p[j_actif][5] = total_nombre(de,6);
    p[j_actif][6] = -1;
    p[j_actif][7] = -1;
    p[j_actif][8] = brelan(de);
    p[j_actif][9] = carre(de);
    p[j_actif][10] = full_house(de);
    p[j_actif][11] = petite_suite(de);
    p[j_actif][12] = grande_suite(de);
    p[j_actif][13] = yams(de);
    p[j_actif][14] = chance(de);

    if (j_actif == 0)
    {
        autre_j = 1;
    }
    else
    {
        autre_j = 0;
    }

    // met le tableau du joueur non actif à -1
    for (int i = 0; i < NB_CASE; i++)
    {
        p[autre_j][i] = -1;
    }
    
}

/**
 * @brief affiche le tableau des scores
 * 
 * @param score , type_score, entrée
 * @param j1 , nom, entrée
 * @param j2 , nom, entrée
 * @param j_actif ,int, entrée
 * @param possibilitees , type_score, entrée
 */
void tableau (type_score score,nom j1,nom j2, int j_actif, type_score possibilitees)
{
    char* colonne[18] = {"1 [total de 1]","2 [total de 2]","3 [total de 3]",
                    "4 [total de 4]","5 [total de 5]","6 [total de 6]",
                    "Bonus si > a 62","Total superieur",
                    "Brelan [total]","Carre [total]","Full House [25]",
                    "Petite suite [30]","Grande suite [40]","Yams [50]",
                    "Chance [total]","Total inferieur","Total"};
    
    printf("\n");
    ligne1(j1,j2);
    for (int i = 0; i < 6; i++)
    {
        if (score[j_actif][i] == -1 && j_actif == 0) // affiche les possibilitées du joueur actif si son score est à -1
        {
            ligne_possibilitees(colonne[i],possibilitees[0][i],score[1][i],j_actif);
        }
        else if (score[j_actif][i] == -1 && j_actif == 1)
        {
            ligne_possibilitees(colonne[i],score[0][i],possibilitees[1][i],j_actif);
        }
        else //affiche les score
        {
            ligne_global(colonne[i],score[0][i],score[1][i]);
        }
        
    }

    if (f_total(score[0],0,5) >= SCORE_MIN_BONUS)
    {
        score[0][6] = BONUS;
    }
    else if (f_total(score[1],0,5) >= SCORE_MIN_BONUS)
    {
        score[1][6] = BONUS;
    }

    ligne_global(colonne[6],score[0][6],score[1][6]);
    
    separateur();
    score[0][7] = f_total(score[0],0,6);
    score[1][7] = f_total(score[1],0,6);
    ligne_total(colonne[7],score[0][7],score[1][7]);
    separateur();
    for (int i = 8; i < 15; i++)
    {
        if (score[j_actif][i] == -1 && j_actif == 0)
        {
            ligne_possibilitees(colonne[i],possibilitees[0][i],score[1][i],j_actif);
        }
        else if (score[j_actif][i] == -1 && j_actif == 1)
        {
            ligne_possibilitees(colonne[i],score[0][i],possibilitees[1][i],j_actif);
        }
        else
        {
            ligne_global(colonne[i],score[0][i],score[1][i]);
        }
    }
    separateur();
    score[0][15] = f_total(score[0],8,14);
    score[1][15] = f_total(score[1],8,14);
    ligne_total(colonne[15],f_total(score[0],8,14),f_total(score[1],8,14));
    printf("|==================|=========|=========|\n");
    score[0][16] = score[0][7]+score[0][15];
    score[1][16] = score[1][7]+score[1][15];
    ligne_total(colonne[16],score[0][16],score[1][16]);
    separateur();
    printf("\n");

}


/**
 * @brief modifie la valeur des dés (de[0]) si leur opposé (de[1]) = 1
 * 
 * @param de , type_de, entrée/sortie
 */

void lancer_de(type_de de)
{
    for (int i = 0; i < 5; i++)
    {
        if (de[1][i] == 1)
        {

            de[0][i] = de_random();
        }
    }
}

/**
 * @brief met chaque valeur du tableau de[1] à 1, pour que par la suite, tous les dés puissent êtres relancés
 * 
 * @param de ,type_de,sortie
 */
void initialise(type_de de)
{
    for (int i = 0; i < NB_DE; i++)
    {
        de[1][i] = 1;
    }
}


/**
 * @brief permet de choisir quels dés relancer en rentrant une chaine ce caractere
 * si le dé n'est pas relancé : de[1][indice du dé] = 0
 * @param de , type_de, entrée
 */

void choix_de(type_de de)
{
    int inconnue;
    int trouve;
    char choix[7];
    char possibilite[7] = "ABCDEX";
    // verification de l'entrée
    do
    {
        printf("choix des dés à garder (ex : dés A et B = AB, X = tout relancer)\n");
        scanf("%s",choix);
        majuscule(choix);
        inconnue = 0;
        for (int i = 0; i < strlen(choix); i++)
        {
            trouve =0;
            for (int a = 0; a < 7; a++)
            {
                if (choix[i] == possibilite[a])
                {
                    trouve = trouve+1;
                }
            }
            if (trouve==0)
            {
                inconnue = inconnue+1;
            }
            
        }
        if (inconnue!=0)
            {
                printf("\033[31m");
                printf("erreur veuillez n'entrer que la/les lettre(s) correspondant aux dés\n");
                printf("\033[00m");
            }
        
    } while (inconnue != 0);

    int i=0;
    // modification si nécessaire de de[1]
    while (i < strlen(choix) && choix[i-1] != 'X')
    {
        switch (choix[i])
        {
            case 'A':
                de[1][0] = 0;
                break;
            case 'B':
                de[1][1] = 0;
                break;
            case 'C':
                de[1][2] = 0;
                break;
            case 'D':
                de[1][3] = 0;
                break;
            case 'E':
                de[1][4] = 0;
                break;
            case 'X':
                initialise(de);
                break;

            default:
                break;
        }
        i = i+1;
    }
}
/**
 * @brief permet de verifier l'entrée de l'utilisateur et de rentrer le nombre de points dans 'score' à l'indice correspondant
 * 
 * @param de , int, entrée
 * @param score , int, entrée/sortie
 */

void valider_points(int de[NB_DE],int score[NB_CASE])
{
    int trouve;
    char choix[3];
    char* possibilite[13] = {"1","2","3","4","5","6","B","CA","F","P","G","Y","CH"};
    int i_score[13] = {0,1,2,3,4,5,8,9,10,11,12,13,14};
    int vide;
    //vérification de l'entrée
    do
    {
        printf("Où valider tes points : initial du choix sauf chance et carre \n(ex : total 1 = 1, brelan = b, full house = f, chance = ch, carre = ca)\n");
        scanf("%s",choix);
        majuscule(choix);
        trouve = 0;
        vide = 0;
        for (int i = 0; i < 13; i++)
        {
            if (strcmp(choix,possibilite[i]) == 0)
            {
                trouve = 1;
                if (score[i_score[i]] == -1)
                {
                    vide = 1;
                }
                else
                {
                    printf("\033[31m");
                    printf("Emplacement déjà occupé\n");
                    printf("\033[00m");
                }
            }
        }

    } while (trouve == 0 || vide == 0);
    //affectation des points
    
    if (strcmp(choix,"1")==0 && score[0] == -1)
    {
        score[0] = total_nombre(de,1);
    }
    else if (strcmp(choix,"2")==0 && score[1] == -1)
    {
        score[1] = total_nombre(de,2);
    }
    else if (strcmp(choix,"3")==0 && score[2] == -1)
    {
        score[2] = total_nombre(de,3);
    }
    else if (strcmp(choix,"4")==0 && score[3] == -1)
    {
        score[3] = total_nombre(de,4);
    }
    else if (strcmp(choix,"5")==0 && score[4] == -1)
    {
        score[4] = total_nombre(de,5);
    }
    else if (strcmp(choix,"6")==0 && score[5] == -1)
    {
        score[5] = total_nombre(de,6);
    }
    else if (strcmp(choix,"B")==0 && score[8] == -1)
    {
        score[8] = brelan(de);
    }
    else if (strcmp(choix,"CA")==0 && score[9] == -1)
    {
        score[9] = carre(de);
    }
    else if (strcmp(choix,"F")==0 && score[10] == -1)
    {
        score[10] = full_house(de);
    }
    else if (strcmp(choix,"P")==0 && score[11] == -1)
    {
        score[11] = petite_suite(de);
    }
    else if (strcmp(choix,"G")==0 && score[12] == -1)
    {
        score[12] = grande_suite(de);
    }
    else if (strcmp(choix,"Y")==0 && score[13] == -1)
    {
        score[13] = yams(de);
    }
    else if (strcmp(choix,"CH")==0 && score[14] == -1)
    {
        score[14] = chance(de);
    }
    
}
/**
 * @brief affiche un dés en y indiquant son nom et sa valeur
 * 
 * @param nom ,char,entrée
 * @param de ,int,entrée
 */
void afficher_de(char nom, int de)
{
    printf("       ┏━━━┓\n");
    printf("dé %c : ┃ %d ┃\n",nom,de);
    printf("       ┗━━━┛\n");
}



/**
 * @brief affiche le menu (score des dés, chois des possibilités) selon le nombre de lancés restant et fait appel
 * à d'autres fonction pour : choisir les dé, relancer les dés, valider ses points
 * @param de , type_de, entrée/sortie
 * @param score , type_score, entrée/sortie
 * @param nb_lancer , int, entrée/sortie
 * @param joueur_actif , int, entrée
 * @param nom_joueur_actif , int, entrée
 * @param fin , int, entrée/sortie
 */

void menu(type_de de,type_score score, int* nb_lancer,int joueur_actif, nom nom_joueur_actif,int* fin)
{
    char test_menu[5];
    //affiche les dés
    printf("dés de %s, lancer restant : %d\n",nom_joueur_actif,3-*nb_lancer);
    afficher_de('A',de[0][0]);
    afficher_de('B',de[0][1]);
    afficher_de('C',de[0][2]);
    afficher_de('D',de[0][3]);
    afficher_de('E',de[0][4]);
    printf("\n\n");

    if (3-*nb_lancer > 0)
    {
        printf("1 - relancer (dé(s) à garder)\n");
        printf("2 - valider ses points\n");
        printf("3 - quitter le jeu\n");
        do
        {
            scanf("%s",test_menu);
            switch (test_menu[0])
            {
                case '1':
                    choix_de(de);
                    lancer_de(de);
                    initialise(de);
                    *nb_lancer = *nb_lancer +1;
                    break;
                case '2':
                    valider_points(de[0],score[joueur_actif]);
                    *nb_lancer = 4;
                    break;
                case '3':
                    *fin = 1;
                    break;
                
                default:
                    printf("\033[31m");
                    printf("erreur, veuillez n'entrer que 1, 2 ou 3\n");
                    printf("\033[00m");
                    break;
            }
        } while (test_menu[0] != '1' && test_menu[0] != '2' && test_menu[0] != '3');
    }
    else
    {
        valider_points(de[0],score[joueur_actif]);
        *nb_lancer = 4;
    }
}


int recherche_nb(int chaine[NB_DE],int indice_debut, int nb)
{
    for (int i = indice_debut; i < NB_DE; i++)
    {
        if(chaine[i] == nb)
        {
            return 1;
        }
    }
    return 0;
    
}

/**
 * @brief (pas fini) recherche le nombre de repétions d'un nombre donné dans une liste
 * et retourne (nombre de repetition du nombre)*(le nombre)
 * @param de , int[NB_DE], entrée
 * @param nombre , int, entrée
 * @return int 
 */

int total_nombre(int de[NB_DE],int nombre)
{
    int res = 0;
    for (int i = 0; i < NB_DE; i++)
    {
        if (de[i] == nombre)
        {
            res = res+nombre;
        }
    }
    return res;
}



/**
 * @brief cherche la presence d'un brelan dans le tableau donné
 * et retourne 3*(nombre le plus present dans le tableau) si brelan il y a, 0 sinon
 * @param de , int[NB_DE], entrée
 * @return int 
 */
int brelan(int de[NB_DE])
{
    const int REQUIS = 3;
    for (int i = 0; i < NB_DE; i++)
    {
        if (total_nombre(de,de[i])/de[i] >= REQUIS)
        {
            return REQUIS*de[i];
        }
        
    }
    return 0; 
}

/**
 * @brief cherche la presence d'un carre dans le tableau donné
 * et retourne 4*(nombre le plus present dans le tableau) si carre il y a, 0 sinon
 * @param de , int[NB_DE], entrée
 * @return int 
 */

int carre(int de[NB_DE])
{
    const int REQUIS = 4;
    for (int i = 0; i < NB_DE; i++)
    {
        if (total_nombre(de,de[i])/de[i] >= REQUIS)
        {
            return REQUIS*de[i];
        }
    }
    return 0; 
}

/**
 * @brief cherche la presence d'un full house et retourne FULL_HOUSE s'il y en a 1,
 * 0 sinon.
 * @param de , int[NB_DE], entrée
 * @return int 
 */

int full_house (int de[NB_DE])
{
    const int REQUIS1 = 3;
    const int REQUIS2 = 2;
    for (int i = 0; i < NB_DE; i++)
    {
        if (total_nombre(de,de[i])/de[i] >= REQUIS1) // total_nombre(de,de[i])/de[i] == nombre de repetitions de de[i] dans dé
        {
            for (int a = 0; a < NB_DE; a++)
            {
                if (total_nombre(de,de[a])/de[a] >= REQUIS2 && de[a] != de[i])
                {
                    return FULL_HOUSE;
                }   
            }   
        }
    }
    return 0; 
}

/**
 * @brief tri la liste des dés pour y rechercher une petite suite, retourne PETITE_SUITE si trouvé, 0 sinon
 * 
 * @param de , int[NB_DE], entrée/sortie
 * @return int 
 */
int petite_suite(int de[NB_DE])
{
    int res[NB_DE];
    for (int i = 0; i < NB_DE; i++)
    {
        res[i] = de[i];
    }
    tri(res);
    int resultat = PETITE_SUITE;
    int compteur = 1;
    for (int i = 1; i < NB_DE; i++)
    {
        if (res[i-1]+1 == res[i])
        {
            compteur = compteur +1;
        }
        else if (res[i-1] == res[i] || compteur >= 3)
        {
            compteur = compteur;
        }
        else
        {
            compteur = 1;
        }
    }
    if (compteur < 4)
    {
        resultat = 0;
    }
    
    return resultat;
}



/**
 * @brief tri la liste des dés pour y rechercher une grande suite, retourne GRANDE_SUITE si trouvé, 0 sinon
 * 
 * @param de , int[NB_DE], entrée/sortie
 * @return int 
 */
int grande_suite(int de[NB_DE])
{
    int res[NB_DE];
    for (int i = 0; i < NB_DE; i++)
    {
        res[i] = de[i];
    }
    tri(res);
    int resultat = GRANDE_SUITE;
    int compteur = 1;
    for (int i = 1; i < NB_DE; i++)
    {
        if (res[i-1]+1 == res[i])
        {
            compteur = compteur +1;
        }
        else
        {
            compteur = 1;
        }
    }
    if (compteur < 5)
    {
        resultat = 0;
    }
    
    return resultat;
}

/**
 * @brief recherche la présence d'un yams (5 dés identiques) dans la liste des dés,
 * retourne YAMS si trouvé, 0 sinon
 * @param de , int[NB_DE], entrée
 * @return int 
 */
int yams(int de[NB_DE])
{
    const int REQUIS = 5;
    if (total_nombre(de,de[0])/de[0] >= REQUIS)
    {
        return YAMS;
    }
    return 0; 
}


/**
 * @brief retourne la somme des valeurs de la liste des dés
 * 
 * @param de , int[NB_DE], entrée
 * @return int 
 */
int chance(int de[NB_DE])
{
    int somme = 0;
    for (int i = 0; i < NB_DE; i++)
    {
        somme = somme + de[i];
    }
    return somme;
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////   PROGRAMME PRINCIPAL   ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int MAX_LANCER = 3;
const int MAX_TOURS = 26;

int main(){
    /*
    initialisation et affection des variables, et des tableaux
    */
    srand(time(NULL));
    int fin, essai, tours, joueur_actif;
    nom j1,j2,nom_joueur_actif;
    verif_nom(j1,1);
    do
    {
        verif_nom(j2,2);
        if (strcmp(j1,j2) == 0)
        {
            printf("\033[31m\n");
            printf("erreur, le joueur 2 ne peut pas avoir le même nom que le joueur 1,\n");
            printf("\033[00m\n");
        }
        
    }
    while(strcmp(j1,j2) == 0);
    
    type_de de = {{0,0,0,0,0},{1,1,1,1,1}};
    fin = 0;
    tours = 0;
    type_score possibilitees;
    type_score score = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
    while (tours < MAX_TOURS && fin == 0)
    {
        essai = 1;

        joueur_actif = tours%2;
        if (joueur_actif == 0)
        {
            strcpy(nom_joueur_actif,j1);
        }
        else
        {
            strcpy(nom_joueur_actif,j2);
        }

        lancer_de(de);

        while (essai <= 3 && fin == 0)
        {
            calcul_possibilitees(possibilitees,de[0],joueur_actif);
            tableau(score,j1,j2,joueur_actif,possibilitees);
            menu(de,score,&essai,joueur_actif,nom_joueur_actif,&fin);
        }
        tours = tours+1;
    }
    
    if (fin != 0)
    {
        printf("Au revoir =,) ... \n");
    }
    else
    {
        printf("\n ______     __     ______     __   __          __     ______     __  __     ______    \n/\\  == \\   /\\ \\   /\\  ___\\   /\\ \"-.\\ \\        /\\ \\   /\\  __ \\   /\\ \\/\\ \\   /\\  ___\\   \n\\ \\  __<   \\ \\ \\  \\ \\  __\\   \\ \\ \\-.  \\      _\\_\\ \\  \\ \\ \\/\\ \\  \\ \\ \\_\\ \\  \\ \\  __\\   \n \\ \\_____\\  \\ \\_\\  \\ \\_____\\  \\ \\_\\\"\\__\\    /\\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ \n  \\/_____/   \\/_/   \\/_____/   \\/_/ \\/_/    \\/_____/   \\/_____/   \\/_____/   \\/_____/ \n\n");
        if(score[0][16]>score[1][16]) // affiche le gagnant
        {
            printf("%s a gagné avec %d contre %d ! \n",j1,score[0][16],score[1][16]);
        }
        else if (score[0][16]<score[1][16])
        {
            printf("%s a gagné avec %d contre %d ! \n",j2,score[1][16],score[0][16]);
        }
        else
        {
            printf("il y a égalité \n");
        }
    }
    
    return EXIT_SUCCESS;
}
