#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

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
// Complexité au pire : O(n). Pire cas = x absent (ou en dernière case) : on regarde les n cases.
int linear_search(int A[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (A[i] == target) {
            return i;   
        }
    }
    return -1;         
}

// Question 3

int jump_search(const int A[], int n, int x) {
    if (!is_sorted_increasing(A, n)) {
        return -1;
    }
    int step = (int) sqrt((double) n);  

    
    int debut = 0;
    int fin = step;

    while (fin < n && A[fin - 1] < x) {
        debut = fin;
        fin = fin + step;
    }
 
    if (fin > n) {
        fin = n;
    }

   
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
            return milieu;                 
        } else if (A[milieu] < x) {
            gauche = milieu + 1;          
        } else {
            droite = milieu - 1;           
        }
    }
    return -1;                          
}


// Question 5

volatile int puits;

double temps_moyen(int (*recherche)(const int[], int, int), const int A[], int n, int x, int repetitions)
{
    clock_t debut = clock();
    for (int r = 0; r < repetitions; r++) {
        puits = recherche(A, n, x);
    }
    clock_t fin = clock();
    return (double) (fin - debut) / CLOCKS_PER_SEC / repetitions;
}

int linear_search_const(const int A[], int n, int x)
{
    return linear_search((int *) A, n, x);
}

int verification_seule(const int A[], int n, int x)
{
    (void) x;
    return is_sorted_increasing(A, n);
}

void comparaison_performances(void)
{
    int tailles[] = {1000, 10000, 100000, 1000000};
    int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);

    printf("%9s | %12s | %12s | %12s | %16s\n", "n", "lineaire (s)", "jump (s)", "binaire (s)", "verif. tri (s)");
    for (int t = 0; t < nb_tailles; t++) {
        int n = tailles[t];
        int *A = malloc(n * sizeof(int));   
        if (A == NULL) {
            fprintf(stderr, "Erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < n; i++) {
            A[i] = 2 * i;                  
        }
        int x = A[n - 1] + 1;              
        int repetitions = 100000000 / n;    
        printf("%9d | %12.3e | %12.3e | %12.3e | %16.3e\n", n,
               temps_moyen(linear_search_const, A, n, x, repetitions),
               temps_moyen(jump_search, A, n, x, repetitions),
               temps_moyen(binary_search, A, n, x, repetitions),
               temps_moyen(verification_seule, A, n, x, repetitions));
        free(A);
    }

    
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
    printf("%i\n", jump_search(D, q, 21)); 
    printf("%i\n", jump_search(D, q, 1));  
    printf("%i\n", jump_search(D, q, 31)); 
    printf("%i\n", jump_search(D, q, 20)); 
    printf("%i\n", jump_search(D, q, 40)); 
    printf("%i\n", jump_search(A, n, 4)); 
    printf("===== Finish question 3 =====\n");

    // Question 4
    printf("===== Question 4 =====\n");
    printf("%i\n", binary_search(D, q, 21)); 
    printf("%i\n", binary_search(D, q, 1));
    printf("%i\n", binary_search(D, q, 31));
    printf("%i\n", binary_search(D, q, 20));
    printf("%i\n", binary_search(D, q, 40)); 
    printf("%i\n", binary_search(C, p, 42)); 
    printf("%i\n", binary_search(A, n, 4));  
    printf("===== Finish question 4 =====\n");

    // Question 5
    printf("===== Question 5 =====\n");
    comparaison_performances();
    printf("===== Finish question 5 =====\n");

    return 0;
}