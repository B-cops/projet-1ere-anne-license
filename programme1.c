#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char E[500 + 1], T[20], C1[500 + 1], C2[500 + 1], C3[500 + 1];
    int N1, N2, N3;
} question;
char purge, ch, baton[1] = "|";
/*  le signe | pour separer les champs et # pour marquer la fin de la ligne */
/* pour la suppression et la mise a jour des qst j ai copier le questionaire dans un autre fichier et lafficher
tout en demandant a lutilisateur ces choix*/
void vraiFaux(FILE *a);
void choixMultiple(FILE *a);
void choixUnique(FILE *a);
int nombreDeQuestion(FILE *a);
void ecrireQuestion(FILE *a, int b);
void copierLeQuestionaire(FILE *a, FILE *b);
void lectureDesQuestion(FILE *a, FILE *b);
void leChamps(int numero);

int main(void)
{

    char reponse[1];
    FILE *fichier = NULL;
    FILE *fichiercopy = NULL;

    printf("bonjour !\nsi vous voulez cree un questionaire tapez : c\nsi vous voulez ajouter des questions dans le fichier questionaire tapez : a\nsi vous voulez modifier le questionaire tapez : m\n");
    scanf("%s", reponse);

    if (strcmp(reponse, "a") == 0)
    {
        fichier = fopen("questionaire.txt", "a");
        if (fichier != NULL)
        {
            ecrireQuestion(fichier, 0);
            fclose(fichier);
        }
        else
        {
            printf("\nerreur lors de l ouverture du fichier \nre executer le programme et cree un nouveaux fichier\n");
            fclose(fichier);
            exit(1);
        }
    }
    else if (strcmp(reponse, "c") == 0)
    {
        fichier = fopen("questionaire.txt", "w");
        if (fichier != NULL)
        {
            ecrireQuestion(fichier, 0);
            fclose(fichier);
        }
        else
        {
            printf("\nerreur lors de la creation du fichier \nre executer le programme et cree un nouveaux fichier\n");
            fclose(fichier);
            exit(1);
        }
    }
    else if (strcmp(reponse, "m") == 0)
    {
        copierLeQuestionaire(fichier, fichiercopy);
        lectureDesQuestion(fichier, fichiercopy);
    }
    else
    {
        printf("\nune erreur s est produite \nre executer le programme et cree un nouveaux fichier\n");
        exit(1);
    }

    system("PAUSE");
    return 0;
}

void ecrireQuestion(FILE *a, int b)
{
    FILE *fichier = a;
    int typeDeQuestion;
    char ouiNon[3];
    printf("\nquelle type de question voulez-vous ajoutez \nvrai-faux      : tapez -1-\nchoix-multiple : tapez -2-\nchoix-unique   : tapez -3-\n");
    scanf("%d", &typeDeQuestion);
    switch (typeDeQuestion)
    {

    case 1:
        vraiFaux(fichier);
        break;
    case 2:
        choixMultiple(fichier);
        break;
    case 3:
        choixUnique(fichier);
        break;
    default:
        printf("\nune erreur s est produite relancez le programme\n");
        exit(1);
        break;
    }
    if (b == 1)
    {
        return;
    }
    printf("\nvoulez-vous ecrire une autre question :  oui  -  non\n");
    scanf("%s", ouiNon);
    if (strcmp(ouiNon, "oui") == 0)
    {
        ecrireQuestion(fichier, 0);
        char hashtag[3];
        strcpy(hashtag, "#");
        fprintf(fichier, "%s\n", hashtag);
    }
    else if (strcmp(ouiNon, "non") == 0)
    {
        fclose(fichier);
        return;
    }
    else
    {
        printf("\nles reponses sont : ---oui--- ---non--- en minuscule \nrelancer le programme\n");
        fclose(fichier);
        return;
    }
}

void vraiFaux(FILE *a)
{
    FILE *fichier = a;
    char vraifaux[10] = "vrai-faux";
    question questn;

    purge = getchar();
    printf("\nposez la question : \n");
    fgets(questn.E, 500 + 1, stdin);
    questn.E[strlen(questn.E) - 1] = 0;
    printf("\ndonnez le premier choix de reponse (vrai/faux): \n");
    scanf("%s", questn.C1);
    if (strcmp(questn.C1, "vrai") == 0)
    {
        strcpy(questn.C2, "faux");
    }
    else if (strcmp(questn.C1, "faux") == 0)
    {
        strcpy(questn.C2, "vrai");
    }
    else
    {
        printf("\nles reponses sont soit ---vrai--- soit ---faux--- \n");
        vraiFaux(fichier);
        return;
    }
    printf("\ndonnez la note pour le premier choix de reponse : \n");
    scanf("%d", &questn.N1);
    printf("\ndonnez la note pour le deuxieme choix de reponse : \n");
    scanf("%d", &questn.N2);
    if (!((questn.N1 > 0 && questn.N2 <= 0) || (questn.N2 > 0 && questn.N1 <= 0)))
    {
        printf("\nla valuer des reponses correctes doit etre positif ou null et la valeur des reponses incorrectes doit etre negatif ou null\nchanger de bareme\n");
        vraiFaux(fichier);
    }
    strcpy(questn.T, "vrai-faux");
    strcpy(questn.C3, "*");
    fprintf(fichier, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t", questn.E, baton, questn.T, baton, questn.C1, baton, questn.C2, baton, questn.C3, baton);
    fprintf(fichier, "%d\t%s\t%d\t%s\t*\t%s\t", questn.N1, baton, questn.N2, baton, baton);
    char hashtag[3];
    strcpy(hashtag, "#");
    fprintf(fichier, "%s\n", hashtag);
}

void choixMultiple(FILE *a)
{
    FILE *fichier = a;
    question questn;

    purge = getchar();
    printf("\nposez la question : \n");
    fgets(questn.E, 500 + 1, stdin);
    questn.E[strlen(questn.E) - 1] = 0;
    printf("\ndonnez le premier choix de reponse : \n");
    fgets(questn.C1, 500 + 1, stdin);
    questn.C1[strlen(questn.C1) - 1] = 0;
    printf("\ndonnez le deuxieme choix de reponse : \n");
    fgets(questn.C2, 500 + 1, stdin);
    questn.C2[strlen(questn.C2) - 1] = 0;
    printf("\ndonnez le troisieme choix de reponse : \n");
    fgets(questn.C3, 500 + 1, stdin);
    questn.C3[strlen(questn.C3) - 1] = 0;
    printf("\ndonnez la note pour le premier choix de reponse : \n");
    scanf("%d", &questn.N1);
    printf("\ndonnez la note pour le deuxieme choix de reponse : \n");
    scanf("%d", &questn.N2);
    printf("\ndonnez la note pour le troisieme choix de reponse : \n");
    scanf("%d", &questn.N3);
    if (!(((questn.N3 > 0) && (questn.N2 > 0) && (questn.N1 <= 0)) || ((questn.N2 > 0) && (questn.N1 > 0) && (questn.N3 <= 0)) || ((questn.N3 > 0) && (questn.N1 > 0) && (questn.N2 <= 0))))
    {
        printf("\nune question à choix multiple doit avoir au moins deux réponses notées par une valeur positive \nchangez de questions ou changez de bareme\n");
        choixMultiple(fichier);
    }
    strcpy(questn.T, "choix-multiple");
    fprintf(fichier, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t", questn.E, baton, questn.T, baton, questn.C1, baton, questn.C2, baton, questn.C3, baton);
    fprintf(fichier, "%d\t%s\t%d\t%s\t%d\t%s\t", questn.N1, baton, questn.N2, baton, questn.N3, baton);
    char hashtag[3];
    strcpy(hashtag, "#");
    fprintf(fichier, "%s\n", hashtag);
}

void choixUnique(FILE *a)
{
    FILE *fichier = a;
    question questn;

    purge = getchar();
    printf("\nposez la question : \n");
    fgets(questn.E, 500 + 1, stdin);
    questn.E[strlen(questn.E) - 1] = 0;
    printf("\ndonnez le premier choix de reponse : \n");
    fgets(questn.C1, 500 + 1, stdin);
    questn.C1[strlen(questn.C1) - 1] = 0;
    printf("\ndonnez le deuxieme choix de reponse : \n");
    fgets(questn.C2, 500 + 1, stdin);
    questn.C2[strlen(questn.C2) - 1] = 0;
    printf("\ndonnez le troisieme choix de reponse : \n");
    fgets(questn.C3, 500 + 1, stdin);
    questn.C3[strlen(questn.C3) - 1] = 0;
    printf("\ndonnez la note pour le premier choix de reponse : \n");
    scanf("%d", &questn.N1);
    printf("\ndonnez la note pour le deuxieme choix de reponse : \n");
    scanf("%d", &questn.N2);
    printf("\ndonnez la note pour le troisieme choix de reponse : \n");
    scanf("%d", &questn.N3);
    if (!(((questn.N1 > 0) && (questn.N2 <= 0) && (questn.N3 <= 0)) || ((questn.N3 > 0) && (questn.N2 <= 0) && (questn.N1 <= 0)) || ((questn.N1 > 0) && (questn.N2 <= 0) && (questn.N3 <= 0))))
    {
        printf("\nune question a choix unique doit avoir exactement une valeut positive\nchangez de questions ou changez de bareme\n");
        choixUnique(fichier);
    }
    strcpy(questn.T, "choix-unique");
    fprintf(fichier, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t", questn.E, baton, questn.T, baton, questn.C1, baton, questn.C2, baton, questn.C3, baton);
    fprintf(fichier, "%d\t%s\t%d\t%s\t%d\t%s\t", questn.N1, baton, questn.N2, baton, questn.N3, baton);
    char hashtag[3];
    strcpy(hashtag, "#");
    fprintf(fichier, "%s\n", hashtag);
}

void copierLeQuestionaire(FILE *a, FILE *b)
{
    FILE *fichier = a;
    FILE *fichiercopy = b;
    fichier = fopen("questionaire.txt", "r");
    fichiercopy = fopen("questionairecopy.txt", "w");

    if (!fichier)
    {
        printf("\nerreur lors de louverture du fichier questionaire.txt\n");
    }
    else if (!fichiercopy)
    {
        printf("\nerreur lors de la creation du fichier questionaire.txt\n");
    }
    else
    {
        ch = fgetc(fichier);
        do
        {
            fputc(ch, fichiercopy);
            ch = fgetc(fichier);
        } while (ch != EOF);
    }
    fclose(fichier);
    fclose(fichiercopy);
}

void lectureDesQuestion(FILE *a, FILE *b)
{
    FILE *fichier = a;
    FILE *fichiercopy = b;
    int nombreDQ = nombreDeQuestion(fichier);
    fichier = fopen("questionaire.txt", "w");
    fichiercopy = fopen("questionairecopy.txt", "r");
    int arret = 1, entier, compteur = 0, choix, choix2, finDuQuestionaire = 0, questionNumero = 1, nombreDeQst = 0;
    char mot[500 + 1], repnse[1], typeDeQuest[30], note1[50], note2[50], note3[50], underscore[] = "_", baton[1] = "|", phrase[3000] = "", fin[] = "|\t#", hashtg[1], etoile[1] = "*", tabulation[] = "\t";
    fscanf(fichiercopy, "%s\t", mot);
    strcat(phrase, mot);
    while (!feof(fichiercopy) && !(strcmp(mot, "#") == 0))
    {
        if (compteur == 0)
        {
            printf("\n--------question numero %d--------", questionNumero);
        }
        leChamps(compteur);
        while ((!(strcmp(mot, "|") == 0)) && !(strcmp(mot, "#") == 0) && !(strcmp(mot, "fin") == 0))
        {
            printf("%s ", mot);
            if (compteur == 1)
            {
                strcpy(typeDeQuest, mot);
            }
            fscanf(fichiercopy, "%s", mot);
            strcat(phrase, " ");
            strcat(phrase, mot);
        }
        compteur = compteur + 1;
        if (compteur == 5)
        {
            if (strcmp(typeDeQuest, "vrai-faux") == 0)
            {
                fscanf(fichiercopy, "\t%s\t%s\t%s\t%s\t%s\t%s\t%s", note1, baton, note2, baton, mot, baton, hashtg);
                printf("\nnote 1 : %s\nnote 2 : %s", note1, note2);
                printf("\nsi vous voulez changer la question numero %d tapez   : c\nsi vous voulez supprimer la question numero %d tapez : s\nsi vous ne voulez ni changer ni supprimer la question numero %d tapez : n\n", questionNumero, questionNumero, questionNumero);
                scanf("%s", repnse);
                if (strcmp(repnse, "c") == 0)
                {
                    ecrireQuestion(fichier, arret);
                    if (nombreDQ == 1)
                    {
                        fclose(fichier);
                        fclose(fichiercopy);
                        exit(1);
                    }
                }
                else if (strcmp(repnse, "n") == 0)
                {
                    fprintf(fichier, "%s", phrase);
                    fprintf(fichier, "\t%s\t%s\t%s\t%s\t*\t%s\t%s\n", note1, baton, note2, baton, baton, hashtg);
                }
                else if (strcmp(repnse, "s") == 0)
                {
                    printf("\nla question a bien ete supprimer !\n");
                }
                else
                {
                    printf("\nles choix possible sont ---c--- ---s--- ---n--- !\n");
                }
                compteur = 0;
                questionNumero = questionNumero + 1;
                strcat(phrase, fin);
                strcpy(mot, "");
                strcpy(phrase, "");
                nombreDeQst = nombreDeQst + 1;
            }
            else if ((strcmp(typeDeQuest, "choix-multiple") == 0) || (strcmp(typeDeQuest, "choix-unique") == 0))
            {
                fscanf(fichiercopy, "\t%s\t%s\t%s\t%s\t%s\t%s\t%s", note1, baton, note2, baton, note3, baton, mot);
                printf("\nnote 1 : %s\nnote 2 : %s\nnote 3 : %s", note1, note2, note3);
                printf("\nsi vous voulez changer la question numero %d tapez   : c\nsi vous voulez supprimer la question numero %d tapez : s\nsi vous ne voulez pas changer ni supprimer la question numero %d tapez : n\n", questionNumero, questionNumero, questionNumero);
                scanf("%s", repnse);
                if (strcmp(repnse, "c") == 0)
                {
                    ecrireQuestion(fichier, arret);
                    if (nombreDQ == 1)
                    {
                        fclose(fichier);
                        fclose(fichiercopy);
                        exit(1);
                    }
                }
                else if (strcmp(repnse, "n") == 0)
                {
                    fprintf(fichier, "%s", phrase);
                    fprintf(fichier, "\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", note1, baton, note2, baton, note3, baton, hashtg);
                }
                else if (strcmp(repnse, "s") == 0)
                {
                    printf("\nla question a bien ete supprimer !\n");
                }
                else
                {
                    printf("\nles choix possible sont ---c--- ---s--- ---n--- !\n");
                }
                compteur = 0;
                questionNumero = questionNumero + 1;
                strcat(phrase, fin);
                strcpy(mot, "");
                strcpy(phrase, "");
                nombreDeQst = nombreDeQst + 1;
            }
        }
        else if (!(strcmp(mot, "#") == 0))
        {
            fscanf(fichiercopy, "\t%s", mot);
            strcat(phrase, tabulation);
            strcat(phrase, mot);
        }
        else
        {
            printf("\nle fichier questionaire.txt n existe pas\ncree un nouveaux fichier\nre executer le programme\n");
            return;
        }
        if (nombreDeQst == nombreDQ)
        {
            strcpy(mot, hashtg);
        }
    }
    printf("\nfin du questionaire !\n");
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
