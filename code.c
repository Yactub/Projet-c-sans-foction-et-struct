#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ETU 50
#define MAX_MAT 10
#define STR 30

int main() {

    /* ================= Donnees ================= */
    char nom[MAX_ETU][STR], prenom[MAX_ETU][STR];
    int id[MAX_ETU];

    char matNom[MAX_MAT][STR];
    int coef[MAX_MAT];

    float note[MAX_ETU][MAX_MAT];
    float moyenne[MAX_ETU];

    int nbEtu = 0;
    int nbMat = -1;

    int choix;

    /* ================= MENU ================= */
    do {
        printf("\n========= MENU =========\n");
        printf("1. Ajouter etudiant\n");
        printf("2. Mettre a jour etudiant\n");
        printf("3. Supprimer etudiant\n");
        printf("4. Rechercher etudiant\n");
        printf("5. Affichage simple\n");
        printf("6. Classement par moyenne\n");
        printf("7. Affichage alphabetique\n");
        printf("8. Moyenne par matiere\n");
        printf("9. Moyenne globale\n");
        printf("10. Best/Worst par etudiant\n");
        printf("11. Best/Worst par matiere\n");
        printf("12. Etudiants sans moyenne\n");
        printf("0. Quitter\n");
        printf("Choix: ");

        if (scanf("%d", &choix) != 1) {
            printf("Erreur: choix invalide.\n");
            while (getchar() != '\n');
            continue;
        }

        /* ================= AJOUT ================= */
        if (choix == 1) {
            int i, j, ok, existe;
            float s;
            int sc;

            if (nbEtu >= MAX_ETU) {
                printf("Erreur: maximum 50 etudiants atteint.\n");
                continue;
            }

            /* Initialisation matieres une seule fois */
            if (nbMat == -1) {
                do {
                    printf("Nombre de matieres (0..10): ");
                    scanf("%d", &nbMat);
                } while (nbMat < 0 || nbMat > MAX_MAT);

                for (j = 0; j < nbMat; j++) {
                    printf("Nom matiere %d: ", j + 1);
                    scanf("%s", matNom[j]);
                    do {
                        printf("Coefficient (0..5): ");
                        scanf("%d", &coef[j]);
                    } while (coef[j] < 0 || coef[j] > 5);
                }
            }

            /* Nom */
            do {
                printf("Nom: ");
                scanf("%s", nom[nbEtu]);
                ok = 1;
                for (i = 0; nom[nbEtu][i]; i++)
                    if (!isalpha(nom[nbEtu][i])) ok = 0;
                if (!ok) printf("Erreur: lettres seulement.\n");
            } while (!ok);

            /* Prenom */
            do {
                printf("Prenom: ");
                scanf("%s", prenom[nbEtu]);
                ok = 1;
                for (i = 0; prenom[nbEtu][i]; i++)
                    if (!isalpha(prenom[nbEtu][i])) ok = 0;
                if (!ok) printf("Erreur: lettres seulement.\n");
            } while (!ok);

            /* ID */
            do {
                printf("ID (positif unique): ");
                scanf("%d", &id[nbEtu]);
                ok = id[nbEtu] > 0;
                existe = 0;
                for (i = 0; i < nbEtu; i++)
                    if (id[i] == id[nbEtu]) existe = 1;
                if (!ok || existe)
                    printf("Erreur: ID invalide ou deja existe.\n");
            } while (!ok || existe);

            /* Notes */
            s = 0; sc = 0;
            for (j = 0; j < nbMat; j++) {
                do {
                    printf("Note %s (0..20): ", matNom[j]);
                    scanf("%f", &note[nbEtu][j]);
                } while (note[nbEtu][j] < 0 || note[nbEtu][j] > 20);

                s += note[nbEtu][j] * coef[j];
                sc += coef[j];
            }

            moyenne[nbEtu] = (sc != 0) ? s / sc : 0;
            nbEtu++;

            printf("OK: etudiant ajoute.\n");
        }

        /* ================= UPDATE ================= */
        else if (choix == 2) {
            int rid, pos = -1, i, j;
            float s; int sc;

            printf("ID a modifier: ");
            scanf("%d", &rid);

            for (i = 0; i < nbEtu; i++)
                if (id[i] == rid) pos = i;

            if (pos == -1) {
                printf("Introuvable.\n");
                continue;
            }

            do {
                printf("Nouveau nom: ");
                scanf("%s", nom[pos]);
                ok = 1;
                for (i = 0; nom[pos][i]; i++)
                    if (!isalpha(nom[pos][i])) ok = 0;
            } while (!ok);

            do {
                printf("Nouveau prenom: ");
                scanf("%s", prenom[pos]);
                ok = 1;
                for (i = 0; prenom[pos][i]; i++)
                    if (!isalpha(prenom[pos][i])) ok = 0;
            } while (!ok);

            s = 0; sc = 0;
            for (j = 0; j < nbMat; j++) {
                do {
                    printf("Nouvelle note %s: ", matNom[j]);
                    scanf("%f", &note[pos][j]);
                } while (note[pos][j] < 0 || note[pos][j] > 20);

                s += note[pos][j] * coef[j];
                sc += coef[j];
            }

            moyenne[pos] = (sc != 0) ? s / sc : 0;
            printf("Etudiant mis a jour.\n");
        }

        /* ================= DELETE ================= */
        else if (choix == 3) {
            int rid, pos = -1, i, j;
            printf("ID a supprimer: ");
            scanf("%d", &rid);

            for (i = 0; i < nbEtu; i++)
                if (id[i] == rid) pos = i;

            if (pos == -1) {
                printf("Introuvable.\n");
            } else {
                for (i = pos; i < nbEtu - 1; i++) {
                    id[i] = id[i + 1];
                    strcpy(nom[i], nom[i + 1]);
                    strcpy(prenom[i], prenom[i + 1]);
                    for (j = 0; j < nbMat; j++)
                        note[i][j] = note[i + 1][j];
                    moyenne[i] = moyenne[i + 1];
                }
                nbEtu--;
                printf("Supprime.\n");
            }
        }

        /* ================= RECHERCHE ================= */
        else if (choix == 4) {
            int mode, i, found = 0;
            printf("1) Par ID\n2) Par Nom\nChoix: ");
            scanf("%d", &mode);

            if (mode == 1) {
                int rid;
                printf("ID: ");
                scanf("%d", &rid);
                for (i = 0; i < nbEtu; i++)
                    if (id[i] == rid) {
                        printf("%s %s | Moyenne %.2f\n",
                               nom[i], prenom[i], moyenne[i]);
                        found = 1;
                    }
            } else {
                char key[STR];
                printf("Nom: ");
                scanf("%s", key);
                for (i = 0; i < nbEtu; i++)
                    if (strcmp(nom[i], key) == 0) {
                        printf("%s %s | ID %d | Moy %.2f\n",
                               nom[i], prenom[i], id[i], moyenne[i]);
                        found = 1;
                    }
            }
            if (!found) printf("Aucun resultat.\n");
        }

        /* ================= AFFICHAGE ================= */
        else if (choix == 5) {
            int i;
            for (i = 0; i < nbEtu; i++)
                printf("%d %s %s %.2f\n",
                       id[i], nom[i], prenom[i], moyenne[i]);
        }

        /* ================= CLASSEMENT ================= */
        else if (choix == 6) {
            int i, j;
            for (i = 0; i < nbEtu - 1; i++)
                for (j = i + 1; j < nbEtu; j++)
                    if (moyenne[i] < moyenne[j]) {
                        float tm = moyenne[i];
                        moyenne[i] = moyenne[j];
                        moyenne[j] = tm;

                        int tid = id[i];
                        id[i] = id[j];
                        id[j] = tid;

                        char t[STR];
                        strcpy(t, nom[i]); strcpy(nom[i], nom[j]); strcpy(nom[j], t);
                        strcpy(t, prenom[i]); strcpy(prenom[i], prenom[j]); strcpy(prenom[j], t);
                    }
            printf("Classement termine.\n");
        }

        /* ================= TRI ALPHABETIQUE ================= */
        else if (choix == 7) {
            int i, j;
            for (i = 0; i < nbEtu - 1; i++)
                for (j = i + 1; j < nbEtu; j++)
                    if (strcmp(nom[i], nom[j]) > 0) {
                        char t[STR];
                        strcpy(t, nom[i]); strcpy(nom[i], nom[j]); strcpy(nom[j], t);
                        strcpy(t, prenom[i]); strcpy(prenom[i], prenom[j]); strcpy(prenom[j], t);

                        int tid = id[i]; id[i] = id[j]; id[j] = tid;
                        float tm = moyenne[i]; moyenne[i] = moyenne[j]; moyenne[j] = tm;
                    }
            printf("Tri alphabetique termine.\n");
        }

        /* ================= MOYENNE PAR MATIERE ================= */
        else if (choix == 8) {
            int i, j;
            for (j = 0; j < nbMat; j++) {
                float s = 0;
                for (i = 0; i < nbEtu; i++)
                    s += note[i][j];
                printf("%s : %.2f\n", matNom[j], s / nbEtu);
            }
        }

        /* ================= MOYENNE GLOBALE ================= */
        else if (choix == 9) {
            int i;
            float s = 0;
            for (i = 0; i < nbEtu; i++) s += moyenne[i];
            printf("Moyenne globale: %.2f\n", s / nbEtu);
        }

        /* ================= BEST/WORST ETUDIANT ================= */
        else if (choix == 10) {
            int rid, pos = -1, i, j;
            printf("ID: ");
            scanf("%d", &rid);
            for (i = 0; i < nbEtu; i++)
                if (id[i] == rid) pos = i;

            if (pos != -1) {
                int max = 0, min = 0;
                for (j = 1; j < nbMat; j++) {
                    if (note[pos][j] > note[pos][max]) max = j;
                    if (note[pos][j] < note[pos][min]) min = j;
                }
                printf("Best: %s %.2f\n", matNom[max], note[pos][max]);
                printf("Worst: %s %.2f\n", matNom[min], note[pos][min]);
            } else printf("Introuvable.\n");
        }

        /* ================= BEST/WORST MATIERE ================= */
        else if (choix == 11) {
            int i, j;
            for (j = 0; j < nbMat; j++) {
                int ib = 0, iw = 0;
                for (i = 1; i < nbEtu; i++) {
                    if (note[i][j] > note[ib][j]) ib = i;
                    if (note[i][j] < note[iw][j]) iw = i;
                }
                printf("%s -> Best %.2f (%s %s) | Worst %.2f (%s %s)\n",
                       matNom[j],
                       note[ib][j], nom[ib], prenom[ib],
                       note[iw][j], nom[iw], prenom[iw]);
            }
        }

        /* ================= SANS MOYENNE ================= */
        else if (choix == 12) {
            int i;
            for (i = 0; i < nbEtu; i++)
                if (moyenne[i] < 10)
                    printf("%s %s %.2f\n",
                           nom[i], prenom[i], moyenne[i]);
        }

    } while (choix != 0);

    return 0;
}
