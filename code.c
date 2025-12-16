#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ETU 50
#define MAX_MAT 10

typedef struct {
    char nom[20];
    float note;
    int coef;
} Matiere;

typedef struct {
    char nom[20];
    char prenom[20];
    int id;
    Matiere mat[MAX_MAT];
    int nbMat;
    float moyenne;
} Etudiant;

int main() {
    Etudiant tab[MAX_ETU];
    int n = 0;
    int choix;

    do {
        printf("\n----- MENU -----\n");
        printf("1. Ajouter etudiant\n");
        printf("2. Mettre a jour etudiant\n");
        printf("3. Supprimer etudiant\n");
        printf("4. Rechercher etudiant\n");
        printf("5. Apercu des etudiants\n");
        printf("6. Classement par moyenne\n");
        printf("7. Moyenne par matiere\n");
        printf("8. Moyenne globale\n");
        printf("9. Etudiants sans moyenne\n");
        printf("10. Meilleure / pire note par matiere\n");
        printf("0. Quitter\n");
        printf("Choix: ");

        while (scanf("%d", &choix) != 1) {
            printf("Erreur: choix invalide.\nChoix: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        /* ================= AJOUT ================= */
        if (choix == 1) {
            if (n >= MAX_ETU) {
                printf("Erreur: nombre maximum d'etudiants atteint (50).\n");
            } else {
                Etudiant e;
                int i, ok, existe;
                float s = 0;
                int sc = 0;

                /* Nom */
                do {
                    printf("Nom (lettres seulement): ");
                    scanf("%19s", e.nom);
                    while (getchar() != '\n');

                    ok = 1;
                    for (i = 0; e.nom[i]; i++)
                        if (!isalpha(e.nom[i])) ok = 0;

                    if (!ok) printf("Erreur: nom invalide.\n");
                } while (!ok);

                /* Prenom */
                do {
                    printf("Prenom (lettres seulement): ");
                    scanf("%19s", e.prenom);
                    while (getchar() != '\n');

                    ok = 1;
                    for (i = 0; e.prenom[i]; i++)
                        if (!isalpha(e.prenom[i])) ok = 0;

                    if (!ok) printf("Erreur: prenom invalide.\n");
                } while (!ok);

                /* ID */
                do {
                    printf("ID (nombre positif): ");
                    while (scanf("%d", &e.id) != 1) {
                        printf("Erreur: ID doit etre un nombre.\nID: ");
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');

                    existe = 0;
                    if (e.id <= 0) {
                        printf("Erreur: ID invalide.\n");
                        ok = 0;
                    } else {
                        for (i = 0; i < n; i++)
                            if (tab[i].id == e.id) existe = 1;

                        if (existe) {
                            printf("Erreur: ID deja utilise.\n");
                            ok = 0;
                        } else ok = 1;
                    }
                } while (!ok);

                /* Nombre de matieres */
                do {
                    printf("Nombre de matieres (0..10): ");
                    while (scanf("%d", &e.nbMat) != 1) {
                        printf("Erreur: valeur invalide.\n");
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');

                    ok = (e.nbMat >= 0 && e.nbMat <= MAX_MAT);
                    if (!ok) printf("Erreur: doit etre entre 0 et 10.\n");
                } while (!ok);

                for (i = 0; i < e.nbMat; i++) {
                    printf("Matiere %d nom: ", i + 1);
                    scanf("%19s", e.mat[i].nom);
                    while (getchar() != '\n');

                    do {
                        printf("Note (0..20): ");
                        while (scanf("%f", &e.mat[i].note) != 1) {
                            printf("Erreur.\n");
                            while (getchar() != '\n');
                        }
                        while (getchar() != '\n');

                        ok = (e.mat[i].note >= 0 && e.mat[i].note <= 20);
                        if (!ok) printf("Erreur: note invalide.\n");
                    } while (!ok);

                    do {
                        printf("Coefficient (1..5): ");
                        while (scanf("%d", &e.mat[i].coef) != 1) {
                            printf("Erreur.\n");
                            while (getchar() != '\n');
                        }
                        while (getchar() != '\n');

                        ok = (e.mat[i].coef >= 1 && e.mat[i].coef <= 5);
                        if (!ok) printf("Erreur: coefficient invalide.\n");
                    } while (!ok);

                    s += e.mat[i].note * e.mat[i].coef;
                    sc += e.mat[i].coef;
                }

                e.moyenne = (sc != 0) ? s / sc : 0;
                tab[n++] = e;
                printf("OK: etudiant ajoute.\n");
            }
        }

        /* ================= MISE A JOUR ================= */
        else if (choix == 2) {
            if (n == 0) {
                printf("Erreur: aucun etudiant.\n");
            } else {
                Etudiant e;
                int i, pos = -1, ok;
                float s = 0;
                int sc = 0;

                do {
                    printf("ID a modifier: ");
                    while (scanf("%d", &e.id) != 1) {
                        printf("Erreur.\n");
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');

                    for (i = 0; i < n; i++)
                        if (tab[i].id == e.id) pos = i;

                    ok = (pos != -1);
                    if (!ok) printf("Erreur: ID introuvable.\n");
                } while (!ok);

                printf("Nouveau nom: ");
                scanf("%19s", e.nom);
                while (getchar() != '\n');

                printf("Nouveau prenom: ");
                scanf("%19s", e.prenom);
                while (getchar() != '\n');

                do {
                    printf("Nombre de matieres (0..10): ");
                    while (scanf("%d", &e.nbMat) != 1) {
                        printf("Erreur.\n");
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');

                    ok = (e.nbMat >= 0 && e.nbMat <= MAX_MAT);
                    if (!ok) printf("Erreur.\n");
                } while (!ok);

                for (i = 0; i < e.nbMat; i++) {
                    printf("Matiere %d nom: ", i + 1);
                    scanf("%19s", e.mat[i].nom);
                    while (getchar() != '\n');

                    printf("Note: ");
                    scanf("%f", &e.mat[i].note);
                    printf("Coef: ");
                    scanf("%d", &e.mat[i].coef);

                    s += e.mat[i].note * e.mat[i].coef;
                    sc += e.mat[i].coef;
                }

                e.moyenne = (sc != 0) ? s / sc : 0;
                tab[pos] = e;
                printf("OK: etudiant mis a jour.\n");
            }
        }

        /* ================= SUPPRESSION ================= */
        else if (choix == 3) {
            int id, i, pos = -1;
            printf("ID: ");
            scanf("%d", &id);
            while (getchar() != '\n');

            for (i = 0; i < n; i++)
                if (tab[i].id == id) pos = i;

            if (pos == -1) printf("Introuvable.\n");
            else {
                for (i = pos; i < n - 1; i++)
                    tab[i] = tab[i + 1];
                n--;
                printf("OK: supprime.\n");
            }
        }

        /* ================= RECHERCHE ================= */
        else if (choix == 4) {
            int id, i;
            printf("ID: ");
            scanf("%d", &id);
            while (getchar() != '\n');

            for (i = 0; i < n; i++)
                if (tab[i].id == id) {
                    int j, max = 0, min = 0;
                    printf("%s %s | Moyenne %.2f\n",
                           tab[i].nom, tab[i].prenom, tab[i].moyenne);

                    for (j = 1; j < tab[i].nbMat; j++) {
                        if (tab[i].mat[j].note > tab[i].mat[max].note) max = j;
                        if (tab[i].mat[j].note < tab[i].mat[min].note) min = j;
                    }

                    if (tab[i].nbMat > 0) {
                        printf("Meilleure: %s %.2f\n",
                               tab[i].mat[max].nom, tab[i].mat[max].note);
                        printf("Pire: %s %.2f\n",
                               tab[i].mat[min].nom, tab[i].mat[min].note);
                    }
                }
        }

        /* ================= APERCU ================= */
        else if (choix == 5) {
            int i;
            for (i = 0; i < n; i++)
                printf("%d %s %s %.2f\n",
                       tab[i].id, tab[i].nom,
                       tab[i].prenom, tab[i].moyenne);
        }

        /* ================= CLASSEMENT ================= */
        else if (choix == 6) {
            int i, j;
            Etudiant tmp;
            for (i = 0; i < n - 1; i++)
                for (j = i + 1; j < n; j++)
                    if (tab[i].moyenne < tab[j].moyenne) {
                        tmp = tab[i];
                        tab[i] = tab[j];
                        tab[j] = tmp;
                    }
            printf("OK: classement effectue.\n");
        }

        /* ================= MOYENNE PAR MATIERE ================= */
        else if (choix == 7) {
            int i, j;
            for (j = 0; j < tab[0].nbMat; j++) {
                float s = 0;
                for (i = 0; i < n; i++)
                    s += tab[i].mat[j].note;
                printf("%s : %.2f\n", tab[0].mat[j].nom, s / n);
            }
        }

        /* ================= MOYENNE GLOBALE ================= */
        else if (choix == 8) {
            int i;
            float s = 0;
            for (i = 0; i < n; i++)
                s += tab[i].moyenne;
            printf("Moyenne globale: %.2f\n", s / n);
        }

        /* ================= SANS MOYENNE ================= */
        else if (choix == 9) {
            int i;
            for (i = 0; i < n; i++)
                if (tab[i].moyenne < 10)
                    printf("%s %s %.2f\n",
                           tab[i].nom, tab[i].prenom, tab[i].moyenne);
        }

        /* ================= BEST / WORST PAR MATIERE ================= */
        else if (choix == 10) {
            int i, j;
            for (j = 0; j < tab[0].nbMat; j++) {
                float best = tab[0].mat[j].note;
                float worst = tab[0].mat[j].note;
                int ib = 0, iw = 0;

                for (i = 1; i < n; i++) {
                    if (tab[i].mat[j].note > best) {
                        best = tab[i].mat[j].note;
                        ib = i;
                    }
                    if (tab[i].mat[j].note < worst) {
                        worst = tab[i].mat[j].note;
                        iw = i;
                    }
                }

                printf("\nMatiere %s\n", tab[0].mat[j].nom);
                printf("Best: %.2f (%s %s)\n",
                       best, tab[ib].nom, tab[ib].prenom);
                printf("Worst: %.2f (%s %s)\n",
                       worst, tab[iw].nom, tab[iw].prenom);
            }
        }

    } while (choix != 0);

    return 0;
}
