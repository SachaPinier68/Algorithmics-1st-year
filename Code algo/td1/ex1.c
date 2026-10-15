#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================================================
   TD1 - Exercice 1 : Fibonacci
   F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)
   unsigned long long suffit jusqu'à F(93).
   ========================================================= */

/* =========================================================
   1. Algorithme naïf (récursif)
   Chaque appel en relance deux : on recalcule sans arrêt les
   mêmes termes -> complexité exponentielle, O(phi^n) ~ O(1.618^n).
   ========================================================= */
unsigned long long fiboNaive(int n) {
    if (n <= 1) {
        return n;
    }
    return fiboNaive(n - 1) + fiboNaive(n - 2);
}

/* =========================================================
   2. Programmation dynamique (bottom-up)
   On stocke chaque terme dans un tableau et on le réutilise :
   chaque F(i) est calculé une seule fois -> O(n) en temps,
   O(n) en mémoire.
   ========================================================= */
unsigned long long fiboDP(int n) {
    if (n <= 1) {
        return n;
    }

    unsigned long long *f = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (f == NULL) {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }

    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    unsigned long long result = f[n];
    free(f);
    return result;
}

/* =========================================================
   3. Comparaison des temps d'exécution avec clock()
   clock() renvoie le temps CPU en "ticks" ; on divise par
   CLOCKS_PER_SEC pour obtenir des secondes.
   ========================================================= */
int main(void) {
    int valeurs[] = {10, 20, 30, 35, 40, 42};
    int nbValeurs = sizeof(valeurs) / sizeof(valeurs[0]);

    printf("%4s | %15s | %12s | %12s\n", "n", "F(n)", "naif (s)", "DP (s)");
    printf("-----+-----------------+--------------+-------------\n");

    for (int k = 0; k < nbValeurs; k++) {
        int n = valeurs[k];
        clock_t debut, fin;

        debut = clock();
        unsigned long long resNaive = fiboNaive(n);
        fin = clock();
        double tempsNaive = (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        unsigned long long resDP = fiboDP(n);
        fin = clock();
        double tempsDP = (double)(fin - debut) / CLOCKS_PER_SEC;

        if (resNaive != resDP) {
            printf("Erreur : les deux algorithmes ne donnent pas le même résultat pour n = %d\n", n);
        }

        printf("%4d | %15llu | %12.6f | %12.6f\n", n, resDP, tempsNaive, tempsDP);
    }

    /* Le naïf devient inutilisable bien avant n = 90, la DP reste instantanée */
    clock_t debut = clock();
    unsigned long long grand = fiboDP(90);
    clock_t fin = clock();
    printf("\nDP seule : F(90) = %llu en %.6f s\n", grand, (double)(fin - debut) / CLOCKS_PER_SEC);

    return 0;
}
