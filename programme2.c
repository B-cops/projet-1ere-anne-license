#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  le signe | pour separer les champs et # pour marquer la fin de la ligne */
void leChamps(int numero);
int maxDeuxNombre(int a, int b);
int nombreMax(int a, int b, int c);
int nombreDespace(char mot[500 + 1]);
int nombresPositives(int a, int b, int c);
int analyseDeLaReponse(int a, int note1, int note2, int note3);
void ecritureDesReponsesAchoixUnique(FILE *a, int num, int choix);
void ecritureDesReponsesAchoixMultiple(FILE *a, int num, int choix, int choix2);
int nombreDeQuestion(FILE *a);

int main()
{
    FILE *fichier = NULL;
    FILE *fichierReponses = NULL;
    int entier, compteur = 0, noteTotal = 0, note = 0, note1, note2, note3 = 0, choix, choix2, nombreDeQst = 0, finDuQuestionaire = 0, questionNumero = 1;
    char mot[500 + 1], typeDeQuest[30], hashtg[1] = "#";
    char nom[20], prenom[20], nomFichierReponses[50] = "reponses", underscore[] = "_", baton[1] = "|", txt[] = ".txt";
    printf("\ndonnez votre nom :\n");
    scanf("%s", nom);
    printf("\ndonnez votre prenom :\n");
    scanf("%s", prenom);
    strcat(nomFichierReponses, nom);
    strcat(nomFichierReponses, underscore);
    strcat(nomFichierReponses, prenom);
    strcat(nomFichierReponses, txt);

    int nombreDQ = nombreDeQuestion(fichier);

    fichierReponses = fopen(nomFichierReponses, "w");
    fichier = fopen("questionaire.txt", "r");

    strcpy(mot, "");

    if (fichier != NULL)
    {
        fscanf(fichier, "%s\t", mot);
        while (!feof(fichier) && !(strcmp(mot, "#") == 0))
        {
            if (compteur == 0)
            {
                printf("\n--------question numero %d--------\n", questionNumero);
            }
            leChamps(compteur);
            while ((!(strcmp(mot, "|") == 0)) && !(strcmp(mot, "#") == 0) && !(strcmp(mot, "fin") == 0))
            {
                printf("%s ", mot);
                if (compteur == 1)
                {
                    strcpy(typeDeQuest, mot);
                }
                fscanf(fichier, "%s", mot);
                finDuQuestionaire = finDuQuestionaire + nombreDespace(mot);
                if (finDuQuestionaire == 4)
                {
                    feof(fichier);
                    strcpy(mot, "fin");
                }
            }
            compteur = compteur + 1;
            if (compteur == 5)
            {
                if (strcmp(typeDeQuest, "vrai-faux") == 0)
                {
                    printf("\n\nquel reponse(s) choisissez vous\nchoix 1  tapez : 1\nchoix 2  tapez : 2\n");
                    scanf("%d", &choix);
                    fscanf(fichier, "\t%d\t%s\t%d\t%s\t%s\t%s\t%s", &note1, baton, &note2, baton, mot, baton, mot);
                    note = note + analyseDeLaReponse(choix, note1, note2, note3);
                    compteur = 0;
                    noteTotal = noteTotal + maxDeuxNombre(note1, note2);
                    ecritureDesReponsesAchoixUnique(fichierReponses, questionNumero, choix);
                    questionNumero = questionNumero + 1;
                    strcpy(mot, "");
                    finDuQuestionaire = 0;
                    nombreDeQst = nombreDeQst + 1;
                }
                else if ((strcmp(typeDeQuest, "choix-multiple") == 0) || (strcmp(typeDeQuest, "choix-unique") == 0))
                {
                    fscanf(fichier, "\t%d\t%s\t%d\t%s\t%d\t%s\t%s", &note1, baton, &note2, baton, &note3, baton, mot);
                    compteur = 0;
                    if ((strcmp(typeDeQuest, "choix-unique") == 0))
                    {
                        printf("\n\nquel reponse(s) choisissez vous\nchoix 1  tapez : 1\nchoix 2  tapez : 2\nchoix 3  tapez : 3\n");
                        scanf("%d", &choix);
                        note = note + analyseDeLaReponse(choix, note1, note2, note3);
                        noteTotal = noteTotal + nombreMax(note1, note2, note3);
                        ecritureDesReponsesAchoixUnique(fichierReponses, questionNumero, choix);
                        questionNumero = questionNumero + 1;
                        nombreDeQst = nombreDeQst + 1;
                    }
                    else
                    {
                        printf("\n\nquel reponse(s) choisissez vous\nchoix 1  tapez : 1\nchoix 2  tapez : 2\nchoix 3  tapez : 3\n");
                        scanf("%d", &choix);
                        note = note + analyseDeLaReponse(choix, note1, note2, note3);
                        printf("\n\nquel autre reponse(s) choisissez vous (choix-multiple)\nchoix 1  tapez : 1\nchoix 2  tapez : 2\nchoix 3  tapez : 3\n");
                        scanf("%d", &choix2);
                        if (choix == choix2)
                        {
                            printf("\nvous devez choisir deux choix differents\non relance le programme\n");
                            int main();
                            return 0;
                        }
                        noteTotal = noteTotal + nombresPositives(note1, note2, note3);
                        note = note + analyseDeLaReponse(choix2, note1, note2, note3);
                        ecritureDesReponsesAchoixMultiple(fichierReponses, questionNumero, choix, choix2);
                        questionNumero = questionNumero + 1;
                        nombreDeQst = nombreDeQst + 1;
                    }
                    strcpy(mot, "");
                    finDuQuestionaire = 0;
                }
            }
            else if (strcmp(mot, "#") == 0)
            {
                compteur = 0;
            }
            else if (!(strcmp(mot, "#") == 0))
            {
                fscanf(fichier, "\t%s", mot);
            }
            else
            {
                printf("\nune erreur est apparue\n");
            }
            if (nombreDeQst == nombreDQ)
            {
                fclose(fichier);
                fclose(fichierReponses);
                printf("\n***%d/%d***\n", note, noteTotal);
                system("PAUSE");
                return 0;
            }
        }
    }
    else
    {
        printf("\nle fichier questionaire.txt n existe pas\ncree un nouveaux fichier\nre executer le programme\n");
        return 0;
    }

    fclose(fichier);
    fclose(fichierReponses);
    printf("\n***%d/%d***\n", note, noteTotal);
    system("PAUSE");
    return 0;
}

int nombreMax(int a, int b, int c)
{
    if ((a >= c >= b) || (a >= b >= c))
    {
        return a;
    }
    else if ((c >= a >= b) || (c >= b >= a))
    {
        return c;
    }
    else
    {
        return b;
    }
}

int nombresPositives(int a, int b, int c)
{
    if ((a > 0) && (b > 0))
    {
        return a + b;
    }
    else if ((c > 0) && (a > 0))
    {
        return c + a;
    }
    else
    {
        return b + c;
    }
}

int maxDeuxNombre(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void leChamps(int numero)
{
    switch (numero)
    {
    case 0:
        printf("\n\nquestion : ");
        break;
    case 1:
        printf("\ntype : ");
        break;
    case 2:
        printf("\nchoix 1 : ");
        break;
    case 3:
        printf("\nchoix 2 : ");
        break;
    case 4:
        printf("\nchoix 3 : ");
        break;

    default:
        break;
    }
}

int nombreDespace(char mot[500 + 1])
{
    if (strcmp(mot, "") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int analyseDeLaReponse(int a, int note1, int note2, int note3)
{
    switch (a)
    {
    case 1:
        return note1;
        break;
    case 2:
        return note2;
        break;
    case 3:
        return note3;
        break;
    default:
        printf("\nles choix sont 1 2 3 faites attention relancer le programme\n");
        exit(1);
        break;
    }
}

void ecritureDesReponsesAchoixUnique(FILE *a, int num, int choix)
{
    FILE *b = a;
    fprintf(b, "\nreponse a la question numero %d : choix %d\n", num, choix);
}

void ecritureDesReponsesAchoixMultiple(FILE *a, int num, int choix, int choix2)
{
    FILE *b = a;
    fprintf(b, "\nreponses a la question numero %d: choix %d  ---  choix %d\n", num, choix, choix2);
}

int nombreDeQuestion(FILE *a)
{
    FILE *fichier = a;
    char ch, hashtag = '#';
    int nombreDeQst = 0;
    fichier = fopen("questionaire.txt", "r");
    if (!fichier)
    {
        printf("\nerreur lors de louverture du fichier questionaire.txt\n");
    }
    else
    {
        ch = fgetc(fichier);
        do
        {
            ch = fgetc(fichier);
            if (ch == hashtag)
            {
                nombreDeQst = nombreDeQst + 1;
            }
        } while (ch != EOF);
    }
    fclose(fichier);
    return nombreDeQst;
}