#include <stdio.h>
#include <string.h>

#define MAX_ETU 50
#define MAX_MAT 10
#define STR 30

int main() {

    char nom[MAX_ETU][STR], prenom[MAX_ETU][STR];
    int id[MAX_ETU];

    char matNom[MAX_MAT][STR];
    int coef[MAX_MAT];

    float note[MAX_ETU][MAX_MAT];
    float moyenne[MAX_ETU];

    int nbEtu = 0;
    int nbMat = -1;
    int choix , j , i , existe , ok ,sc , rid , pos , mode , found ,k , max , min ;

    float s ;

    /* ======================= MENU ======================= */
    do {
        printf("\n========= MENU =========\n");
        printf("1. Saisie matieres \n");
        printf("2. Ajouter etudiant\n");
        printf("3. Mettre a jour etudiant \n");
        printf("4. Supprimer etudiant\n");
        printf("5. Rechercher etudiant \n");
        printf("6. Affichage \n");
        printf("7. Classement par moyenne\n");
        printf("8. Affichage alphabetique\n");
        printf("9. Moyenne par matiere\n");
        printf("10. Moyenne globale\n");
        printf("11. meilleure/pire par etudiant\n");
        printf("12. Meilleure/pire par matiere\n");
        printf("13. Etudiants n'ayant pas la moyenne\n");
        printf("0. Quitter\n");
        printf("Choix: ");

        if (scanf("%d", &choix) != 1) {
            printf("Erreur: choix invalide.\n");
            while (getchar() != '\n'){
                // nettoyage du buffer d'entrée
            }
            continue;
        }

        /* ======================= 1) SAISIE MATIERES ======================= */
        if (choix == 1) {

            do {
                printf("Nombre de matieres (1..10): ");
                if (scanf("%d", &nbMat) != 1) {
                    printf("Erreur: entrez un nombre.\n");
                    while (getchar() != '\n');
                    nbMat = -1;
                    continue;
                }
            } while (nbMat < 1 || nbMat > MAX_MAT);

            for (j = 0; j < nbMat; j++) {
                printf("Nom matiere %d: ", j + 1);
                scanf("%s", matNom[j]);

                do {
                    printf("Coefficient (1..5): ");
                    if (scanf("%d", &coef[j]) != 1) {
                        printf("Erreur: entrez un entier.\n");
                        while (getchar() != '\n'){

                        }
                            coef[j] = 0;
                            continue;
                    }
                    if (coef[j] < 1 || coef[j] > 5) { printf("Erreur: coef (1..5).\n"); }
                } while (coef[j] < 1 || coef[j] > 5);
            }

            printf("OK: matieres configurees.\n");
        }

        /* ======================= 2) AJOUT ETUDIANT ======================= */
        else if (choix == 2) {

            if (nbMat == -1) {
                printf("Erreur: saisissez les matieres d'abord (choix 1).\n");
                continue;
            }
            if (nbEtu >= MAX_ETU) {
                printf("Erreur: maximum 50 etudiants atteint.\n");
                continue;
            }

            /* Nom  */
            do {
                printf("Nom: ");
                scanf("%s", nom[nbEtu]);
                ok = 1;
                for (i = 0; nom[nbEtu][i]; i++) {
                    if (!((nom[nbEtu][i] >= 'A' && nom[nbEtu][i] <= 'Z') ||
                          (nom[nbEtu][i] >= 'a' && nom[nbEtu][i] <= 'z'))) {
                        ok = 0;
                        break;
                    }
                }
                if (!ok) printf("Erreur: nom = lettres seulement.\n");
            } while (!ok);

            /* Prenom */
            do {
                printf("Prenom: ");
                scanf("%s", prenom[nbEtu]);
                ok = 1;
                for (i = 0; prenom[nbEtu][i]; i++) {
                    if (!((prenom[nbEtu][i] >= 'A' && prenom[nbEtu][i] <= 'Z') ||
                          (prenom[nbEtu][i] >= 'a' && prenom[nbEtu][i] <= 'z'))) {
                        ok = 0;
                        break;
                    }
                }
                if (!ok) printf("Erreur: prenom = lettres seulement.\n");
            } while (!ok);

            /* ID */
            do {
                printf("ID : ");
                if (scanf("%d", &id[nbEtu]) != 1) {
                    printf("Erreur: entrez un entier.\n");
                    while (getchar() != '\n');
                    id[nbEtu] = 0;
                }
                ok = (id[nbEtu] > 0);
                existe = 0;
                for (i = 0; i < nbEtu; i++)
                    if (id[i] == id[nbEtu]) existe = 1;

                if (!ok) printf("Erreur: ID doit etre > 0.\n");
                if (existe) printf("Erreur: ID deja utilise.\n");
            } while (!ok || existe);

            /* Notes */
            s = 0; sc = 0;
            for (j = 0; j < nbMat; j++) {
                do {
                    printf("Note %s (0..20): ", matNom[j]);
                    if (scanf("%f", &note[nbEtu][j]) != 1) {
                        printf("Erreur: entrez un nombre.\n");
                        while (getchar() != '\n');
                        note[nbEtu][j] = -1;
                        continue;
                    }
                    if (note[nbEtu][j] < 0 || note[nbEtu][j] > 20)
                        printf("Erreur: note (0..20).\n");
                } while (note[nbEtu][j] < 0 || note[nbEtu][j] > 20);

/*---------------------- Calculs 1) Moyenne ponderée par etudiant ------------------------- */

                s += note[nbEtu][j] * coef[j];
                sc += coef[j];
            }

            moyenne[nbEtu] = (sc != 0) ? (s / sc) : 0;
            nbEtu++;

/*---------------------------------------------------------------------------------------------*/

            printf("OK: etudiant ajoute.\n");
        }

        /* ======================= 3) Mettre a jour un etudiant ======================= */
        else if (choix == 3) {
            pos = -1;


            if (nbMat == -1) { printf("Erreur: saisissez les matieres d'abord.\n"); continue; }
            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }

            printf("ID a modifier: ");
            if (scanf("%d", &rid) != 1) { printf("Erreur: entier.\n"); while (getchar()!='\n'); continue; }

            for (i = 0; i < nbEtu; i++) if (id[i] == rid) pos = i;
            if (pos == -1) { printf("Introuvable.\n"); continue; }

            do {
                printf("Nouveau nom: ");
                scanf("%s", nom[pos]);
                ok = 1;
                for (i = 0; nom[pos][i]; i++) {
                    if (!((nom[pos][i] >= 'A' && nom[pos][i] <= 'Z') ||
                          (nom[pos][i] >= 'a' && nom[pos][i] <= 'z'))) { ok = 0; break; }
                }
                if (!ok) printf("Erreur: lettres seulement.\n");
            } while (!ok);


            do {
                printf("Nouveau prenom: ");
                scanf("%s", prenom[pos]);
                ok = 1;
                for (i = 0; prenom[pos][i]; i++) {
                    if (!((prenom[pos][i] >= 'A' && prenom[pos][i] <= 'Z') ||
                          (prenom[pos][i] >= 'a' && prenom[pos][i] <= 'z'))) { ok = 0; break; }
                }
                if (!ok) printf("Erreur: lettres seulement.\n");
            } while (!ok);

            s = 0; sc = 0;
            for (j = 0; j < nbMat; j++) {
                do {
                    printf("Nouvelle note %s (0..20): ", matNom[j]);
                    if (scanf("%f", &note[pos][j]) != 1) {
                        printf("Erreur: entrez un nombre.\n");
                        while (getchar() != '\n');
                        note[pos][j] = -1;
                        continue;
                    }
                    if (note[pos][j] < 0 || note[pos][j] > 20)
                        printf("Erreur: note (0..20).\n");
                } while (note[pos][j] < 0 || note[pos][j] > 20);

                s += note[pos][j] * coef[j];
                sc += coef[j];
            }

            moyenne[pos] = (sc != 0) ? (s / sc) : 0;
            printf("OK: etudiant mis a jour (ecrase).\n");
        }

        /* ======================= 4) Supprimer un etudiant  ======================= */
        else if (choix == 4) {
            pos = -1;

            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }

            printf("ID a supprimer: ");
            if (scanf("%d", &rid) != 1) { printf("Erreur: entier.\n"); while (getchar()!='\n'); continue; }

            for (i = 0; i < nbEtu; i++) if (id[i] == rid) pos = i;
            if (pos == -1) { printf("Introuvable.\n"); continue; }

            for (i = pos; i < nbEtu - 1; i++) {
                id[i] = id[i + 1];
                strcpy(nom[i], nom[i + 1]);
                strcpy(prenom[i], prenom[i + 1]);
                for (j = 0; j < nbMat; j++) note[i][j] = note[i + 1][j];
                moyenne[i] = moyenne[i + 1];
            }
            nbEtu--;
            printf("OK: supprime.\n");
        }

        /* ======================= 5) Recherche un etudiant par nom et ID ======================= */
        else if (choix == 5) {
            found = 0;
            char key[STR];

            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }
            if (nbMat == -1) { printf("Erreur: aucune matiere.\n"); continue; }

            printf("1) Par ID\n2) Par Nom\nChoix: ");
            if (scanf("%d", &mode) != 1) { printf("Erreur.\n"); while (getchar()!='\n'); continue; }

            if (mode == 1) {
                printf("ID: ");
                if (scanf("%d", &rid) != 1) { printf("Erreur.\n"); while (getchar()!='\n'); continue; }

                for (i = 0; i < nbEtu; i++) {
                    if (id[i] == rid) {
                        max = 0, min = 0;
                        printf("Trouve: %d %s %s | Moy %.2f\n", id[i], nom[i], prenom[i], moyenne[i]);

                        found = 1;
                    }
                }
            } else {
                printf("Nom: ");
                scanf("%s", key);

                for (i = 0; i < nbEtu; i++) {
                    if (strcmp(nom[i], key) == 0) {
                        printf("Trouve: %d %s %s | Moy %.2f\n", id[i], nom[i], prenom[i], moyenne[i]);
                        found = 1;
                    }
                }
            }

            if (!found) printf("Aucun resultat.\n");
        }

        /* ======================= 6) Affichage ======================= */
        else if (choix == 6) {

            if (nbMat == -1) { printf("Erreur: aucune matiere.\n"); continue; }

            printf("\n--- Matieres ---\n");
            for (j = 0; j < nbMat; j++) {printf("- %s (coef %d)\n", matNom[j], coef[j]);}

            printf("\n--- Etudiants ---\n");
            if (nbEtu == 0) { printf("(aucun)\n"); continue; }
            for (i = 0; i < nbEtu; i++)
                printf("%d %s %s | Moy %.2f\n", id[i], nom[i], prenom[i], moyenne[i]);
        }

        /* ======================= 7) Classement par moyyenne ponderée  ======================= */
        else if (choix == 7) {


            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }
            if (nbMat == -1) { printf("Erreur: aucune matiere.\n"); continue; }

            for (i = 0; i < nbEtu - 1; i++) {
                for (j = i + 1; j < nbEtu; j++) {
                    if (moyenne[i] < moyenne[j]) {
                        float tm = moyenne[i]; moyenne[i] = moyenne[j]; moyenne[j] = tm;
                        int tid = id[i]; id[i] = id[j]; id[j] = tid;

                        char t[STR];
                        strcpy(t, nom[i]); strcpy(nom[i], nom[j]); strcpy(nom[j], t);
                        strcpy(t, prenom[i]); strcpy(prenom[i], prenom[j]); strcpy(prenom[j], t);

                        for (k = 0; k < nbMat; k++) {
                            float tn = note[i][k];
                            note[i][k] = note[j][k];
                            note[j][k] = tn;
                        }
                    }
                }
            }
            printf("OK: classement termine.\n");
        }

        /* ======================= 8) Trier par l ordre alphabitique  ======================= */
        else if (choix == 8) {


            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }
            if (nbMat == -1) { printf("Erreur: aucune matiere.\n"); continue; }

            for (i = 0; i < nbEtu - 1; i++) {
                for (j = i + 1; j < nbEtu; j++) {
                    int cond = 0;

/*---------------------- Calculs 2) trier alphabitique  -------------------------*/

                    if (strcmp(nom[i], nom[j]) > 0) cond = 1;
                    else if (strcmp(nom[i], nom[j]) == 0 && strcmp(prenom[i], prenom[j]) > 0) cond = 1;

                    if (cond) {
                        float tm = moyenne[i]; moyenne[i] = moyenne[j]; moyenne[j] = tm;
                        int tid = id[i]; id[i] = id[j]; id[j] = tid;

                        char t[STR];
                        strcpy(t, nom[i]); strcpy(nom[i], nom[j]); strcpy(nom[j], t);
                        strcpy(t, prenom[i]); strcpy(prenom[i], prenom[j]); strcpy(prenom[j], t);

                        for (k = 0; k < nbMat; k++) {
                            float tn = note[i][k];
                            note[i][k] = note[j][k];
                            note[j][k] = tn;

/*--------------------------------------------------------------------------------*/

                        }
                    }
                }
            }
            printf("OK: tri alphabetique termine.\n");
        }

        /* ======================= 9) Moyenne generale par matiére ======================= */
        else if (choix == 9) {


            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }
            if (nbMat == -1) { printf("Erreur: aucune matiere.\n"); continue; }

//----------------------Calculs 3) Moyenne par matiere ------------------------- //

            for (j = 0; j < nbMat; j++) {
                s = 0;
                for (i = 0; i < nbEtu; i++) s += note[i][j];
                printf("%s : %.2f\n", matNom[j], s / nbEtu);

//----------------------------------------------------------------------------------//
            }
        }

        /* ======================= 10) Moyenne génerale globale  ======================= */
        else if (choix == 10) {

            s = 0;

            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }

//---------------------- Calculs 4) Moyenne globale ------------------------- //

            for (i = 0; i < nbEtu; i++) s += moyenne[i];
            printf("Moyenne globale: %.2f\n", s / nbEtu);

//----------------------------------------------------------------------------------//

        }

        /* ======================= 11) Meilleure et pire note par etudiant  ======================= */
        else if (choix == 11) {
            pos = -1;

            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }
            if (nbMat == -1) { printf("Erreur: aucune matiere.\n"); continue; }

            printf("ID: ");
            if (scanf("%d", &rid) != 1) { printf("Erreur.\n"); while (getchar()!='\n'); continue; }

            for (i = 0; i < nbEtu; i++) if (id[i] == rid) pos = i;
            if (pos == -1) { printf("Introuvable.\n"); continue; }

            if (nbMat > 0) {
                max = 0, min = 0;

/*---------------------- Calculs 5) Meilleure et pire note par etudiant ------------------------- */

                for (j = 1; j < nbMat; j++) {
                    if (note[pos][j] > note[pos][max]) max = j;
                    if (note[pos][j] < note[pos][min]) min = j;

//------------------------------------------------------------------------------------------------//

                }
                printf("%s %s | Moy %.2f\n", nom[pos], prenom[pos], moyenne[pos]);
                printf("Best: %s %.2f\n", matNom[max], note[pos][max]);
                printf("Worst: %s %.2f\n", matNom[min], note[pos][min]);
            }
        }

        /* ======================= 12) Meilleure et pire note par matiere  ======================= */
        else if (choix == 12) {


            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }
            if (nbMat == -1) { printf("Erreur: aucune matiere.\n"); continue; }

            for (j = 0; j < nbMat; j++) {
                int ib = 0, iw = 0;

/*---------------------- Calculs 6) Meilleure et pire note par matiere ------------------------- */

                for (i = 1; i < nbEtu; i++) {
                    if (note[i][j] > note[ib][j]) ib = i;
                    if (note[i][j] < note[iw][j]) iw = i;

//------------------------------------------------------------------------------------------------//

                }
                printf("%s -> Best %.2f (%s %s) | Worst %.2f (%s %s)\n",
                       matNom[j],
                       note[ib][j], nom[ib], prenom[ib],
                       note[iw][j], nom[iw], prenom[iw]);
            }
        }

        /* ======================= 13) Etudiants n'ayant pas la moyenne ======================= */
        else if (choix == 13) {
            found = 0;

            if (nbEtu == 0) { printf("Erreur: aucun etudiant.\n"); continue; }

/*---------------------- Calculs 7) Etudiants n'ayant pas la moyenne ------------------------- */

            for (i = 0; i < nbEtu; i++) {
                if (moyenne[i] < 10) {
                    printf("%d %s %s | %.2f\n", id[i], nom[i], prenom[i], moyenne[i]);

//--------------------------------------------------------------------------------------------//

                    found = 1;
                }
            }
            if (!found) printf("Tous ont la moyenne.\n");
        }

    } while (choix != 0);

    return 0;
}
