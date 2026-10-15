#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* =========================================================
   TD1 - Exercice 2 : Nombres premiers
   On compte les nombres premiers STRICTEMENT inférieurs à n.
   ========================================================= */

/* =========================================================
   1. Algorithme naïf en O(n * sqrt(n))
   Pour chaque k < n, on teste les diviseurs d de 2 à sqrt(k)
   (si k = a * b avec a <= b, alors a <= sqrt(k)).
   -> au plus sqrt(n) tests pour chacun des n nombres.
   ========================================================= */
bool estPremier(int k) {
    if (k < 2) {
        return false;
    }
    // d * d <= k évite d'appeler sqrt() et les erreurs d'arrondi
    for (int d = 2; (long long)d * d <= k; d++) {
        if (k % d == 0) {
            return false;
        }
    }
    return true;
}

int compterPremiersNaif(int n) {
    int compteur = 0;
    for (int k = 2; k < n; k++) {
        if (estPremier(k)) {
            compteur++;
        }
    }
    return compteur;
}

/* =========================================================
   2. Algorithme efficace : crible d'Ératosthène
   Les multiples d'un nombre premier ne sont pas premiers :
   pour chaque premier p, on raye 2p, 3p, 4p, ...
   On peut commencer à p * p (les multiples plus petits ont déjà
   été rayés par un premier plus petit) et s'arrêter à p <= sqrt(n).
   ========================================================= */
int compterPremiersCrible(int n) {
    if (n < 3) {
        return 0;
    }

    // estCompose[k] == true  <=>  k a été rayé (k n'est pas premier)
    bool *estCompose = (bool *)calloc(n, sizeof(bool));
    if (estCompose == NULL) {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }

    for (int p = 2; (long long)p * p < n; p++) {
        if (!estCompose[p]) {
            for (long long m = (long long)p * p; m < n; m += p) {
                estCompose[m] = true;
            }
        }
    }

    int compteur = 0;
    for (int k = 2; k < n; k++) {
        if (!estCompose[k]) {
            compteur++;
        }
    }

    free(estCompose);
    return compteur;
}

/* =========================================================
   3. Complexité du crible : O(n log(log(n)))

   - Initialisation (calloc) + comptage final : O(n).
   - Pour chaque premier p, la boucle interne raye au plus n/p cases.
     Le coût total du rayage est donc au plus :

         somme_{p premier, p <= n} n/p  =  n * somme_{p premier, p <= n} 1/p

   - D'après l'indication (Meissel-Mertens) :

         somme_{p premier, p <= n} 1/p  <=  log(log(n + 1)) + M

     donc le rayage coûte au plus n * (log(log(n + 1)) + M).

   - M est une constante et log(log(n + 1)) ~ log(log(n)), d'où :

         T(n) = O(n) + O(n log(log(n)))  =  O(n log(log(n)))

   (Les p non premiers ne coûtent qu'un test O(1) chacun, soit O(sqrt(n))
   au total, négligeable.)
   ========================================================= */

/* =========================================================
   4. Comparaison des temps d'exécution avec clock()
   ========================================================= */
int main(void) {
    int valeurs[] = {1000, 10000, 100000, 1000000, 10000000};
    int nbValeurs = sizeof(valeurs) / sizeof(valeurs[0]);

    printf("%10s | %10s | %12s | %12s\n", "n", "pi(n)", "naif (s)", "crible (s)");
    printf("-----------+------------+--------------+-------------\n");

    for (int i = 0; i < nbValeurs; i++) {
        int n = valeurs[i];
        clock_t debut, fin;

        debut = clock();
        int resNaif = compterPremiersNaif(n);
        fin = clock();
        double tempsNaif = (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        int resCrible = compterPremiersCrible(n);
        fin = clock();
        double tempsCrible = (double)(fin - debut) / CLOCKS_PER_SEC;

        if (resNaif != resCrible) {
            printf("Erreur : résultats différents pour n = %d\n", n);
        }

        printf("%10d | %10d | %12.6f | %12.6f\n", n, resCrible, tempsNaif, tempsCrible);
    }

    return 0;
}
