#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Question 1
bool is_sorted_increasing(const int A[], int n)
{
    int i = 0;
    while (i < n - 1)
    {
        if (A[i] < A[i + 1])
        {
            i = i + 1;
        }
        else
        {
            return false;
        }
    }
    return true;
}

// Question 2
int linear_search(int A[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (A[i] == target) {
            return i;   // on renvoie l'indice, pas "vrai"
        }
    }
    return -1;          // -1 = absent (0 serait un indice valide !)
}

// Question 3
int jump_search(const int A[], int n, int x) {
    if (!is_sorted_increasing(A, n)) {
        return -1;
    }
    int step = (int) sqrt((double) n);   // >= 1 car n >= 1

    // Le bloc courant couvre les indices [debut, fin[
    int debut = 0;
    int fin = step;

    // On saute de bloc en bloc tant que la dernière case du bloc est < x.
    // "fin < n" garantit que A[fin - 1] n'est jamais lu hors du tableau.
    while (fin < n && A[fin - 1] < x) {
        debut = fin;
        fin = fin + step;
    }
    // Le dernier bloc peut être incomplet : on ne dépasse pas n
    if (fin > n) {
        fin = n;
    }

    // Recherche linéaire dans le bloc trouvé
    for (int i = debut; i < fin; i++) {
        if (A[i] == x) {
            return i;
        }
    }
    return -1;
}

// Question 4
int binary_search(const int A[], int n, int x)
{
    if (!is_sorted_increasing(A, n)) {
        return -1;
    }
    int gauche = 0;
    int droite = n - 1;                    
    while (gauche <= droite)
    {
        int milieu = gauche + (droite - gauche) / 2;
        if (A[milieu] == x) {
            return milieu;                 // l'indice où on a trouvé x
        } else if (A[milieu] < x) {
            gauche = milieu + 1;           // x est à droite du milieu (le milieu est déjà testé)
        } else {
            droite = milieu - 1;           // x est à gauche du milieu
        }
    }
    return -1;                             // gauche > droite : intervalle vide, x absent
}



int main()
{
    // Question 1
    printf("===== Question 1 =====\n");
    int A[] = {1, 5, 4, 4, 2};
    int B[] = {1, 2, 4, 5, 6};
    int C[] = {42};
    int n = sizeof(A) / sizeof(A[0]);
    int m = sizeof(B) / sizeof(B[0]);
    int p = sizeof(C) / sizeof(C[0]);
    printf("%i\n", is_sorted_increasing(A, n)); 
    printf("%i\n", is_sorted_increasing(B, m));
    printf("%i\n", is_sorted_increasing(C, p)); 
    printf("===== Finish question 1 =====\n");

    // Question 2 
    printf("===== Question 2 =====\n");
    printf("%i\n", linear_search(A, n, 4 )); 
    printf("%i\n", linear_search(B, m, 8)); 
    printf("%i\n", linear_search(C, p, 42)); 
    printf("===== Finish question 2 =====\n");

    // Question 3
    printf("===== Question 3 =====\n");
    int D[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
    int q = sizeof(D) / sizeof(D[0]);
    printf("%i\n", jump_search(D, q, 21)); // attendu : 10 (l'exemple vu ensemble)
    printf("%i\n", jump_search(D, q, 1));  // attendu : 0  (première case)
    printf("%i\n", jump_search(D, q, 31)); // attendu : 15 (dernière case)
    printf("%i\n", jump_search(D, q, 20)); // attendu : -1 (absent, entre deux valeurs)
    printf("%i\n", jump_search(D, q, 40)); // attendu : -1 (plus grand que tout)
    printf("%i\n", jump_search(A, n, 4));  // attendu : -1 (A n'est pas trié)
    printf("===== Finish question 3 =====\n");

    // Question 4
    printf("===== Question 4 =====\n");
    printf("%i\n", binary_search(D, q, 21)); // attendu : 10 (4 étapes, cf. tableau)
    printf("%i\n", binary_search(D, q, 1));  // attendu : 0
    printf("%i\n", binary_search(D, q, 31)); // attendu : 15
    printf("%i\n", binary_search(D, q, 20)); // attendu : -1
    printf("%i\n", binary_search(D, q, 40)); // attendu : -1
    printf("%i\n", binary_search(C, p, 42)); // attendu : 0  (une seule case)
    printf("%i\n", binary_search(A, n, 4));  // attendu : -1 (A n'est pas trié)
    printf("===== Finish question 4 =====\n");

    return 0;
}