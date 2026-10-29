#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


bool is_sorted_ascending(const int A[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            return false;
        }
    }
    return true;
}

void copy_array(const int source[], int destination[], int n)
{
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

void print_array(const int A[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}


void selection_sort(int A[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int indice_min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[indice_min]) {
                indice_min = j;
            }
        }
        if (indice_min != i) {
            swap_int(&A[i], &A[indice_min]);
        }
    }
}


void insertion_sort(int A[], int n)
{
    for (int i = 1; i < n; i++) {
        int valeur = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > valeur) {   // ">" et non ">=" : on ne passe pas devant un doublon (tri stable)
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = valeur;
    }
}

// Question 4 : tri à bulles
void bubble_sort(int A[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        bool echange = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                swap_int(&A[j], &A[j + 1]);
                echange = true;
            }
        }
        if (!echange) {
            return;  
        }
    }
}

// Question 5 : tri fusion
void merge(int A[], int tmp[], int debut, int milieu, int fin)
{
    int i = debut;   
    int j = milieu;   
    int k = debut;    

    while (i < milieu && j < fin) {
        if (A[i] <= A[j]) {   
            tmp[k] = A[i];
            i++;
        } else {
            tmp[k] = A[j];
            j++;
        }
        k++;
    }
    
    while (i < milieu) {
        tmp[k] = A[i];
        i++;
        k++;
    }
    while (j < fin) {
        tmp[k] = A[j];
        j++;
        k++;
    }
    copy_array(tmp + debut, A + debut, fin - debut);
}

void merge_sort_rec(int A[], int tmp[], int debut, int fin)
{
    if (fin - debut <= 1) {
        return;  
    }
    int milieu = debut + (fin - debut) / 2;
    merge_sort_rec(A, tmp, debut, milieu);
    merge_sort_rec(A, tmp, milieu, fin);
    merge(A, tmp, debut, milieu, fin);
}

void merge_sort(int A[], int n)
{
    int *tmp = malloc(n * sizeof(int));   
    if (tmp == NULL) {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    merge_sort_rec(A, tmp, 0, n);
    free(tmp);
}

// Question 6 : tri rapide

int partition(int A[], int debut, int fin)
{
    int milieu = debut + (fin - debut) / 2;
    swap_int(&A[milieu], &A[fin]);  
    int pivot = A[fin];

    int i = debut;   
    for (int j = debut; j < fin; j++) {
        if (A[j] < pivot) {
            swap_int(&A[i], &A[j]);
            i++;
        }
    }
    swap_int(&A[i], &A[fin]);   
    return i;
}

void quick_sort_rec(int A[], int debut, int fin)   
{
    if (debut >= fin) {
        return;
    }
    int p = partition(A, debut, fin);
    quick_sort_rec(A, debut, p - 1);
    quick_sort_rec(A, p + 1, fin);
}

void quick_sort(int A[], int n)
{
    quick_sort_rec(A, 0, n - 1);
}

// Question 7 : comparaison des performances
typedef struct {
    const char *nom;
    void (*trier)(int[], int);
} Tri;

void comparaison_performances(void)
{
    Tri tris[] = {
        {"selection", selection_sort},
        {"insertion", insertion_sort},
        {"bulles", bubble_sort},
        {"fusion", merge_sort},
        {"rapide", quick_sort},
    };
    int nb_tris = sizeof(tris) / sizeof(tris[0]);
    int tailles[] = {1000, 5000, 10000, 50000, 100000};
    int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);

    srand(42);   // graine fixe : mêmes tableaux à chaque exécution
    printf("%7s", "n");
    for (int t = 0; t < nb_tris; t++) {
        printf(" | %13s", tris[t].nom);
    }
    printf("\n");

    for (int s = 0; s < nb_tailles; s++) {
        int n = tailles[s];
        int *original = malloc(n * sizeof(int));
        int *copie = malloc(n * sizeof(int));
        if (original == NULL || copie == NULL) {
            fprintf(stderr, "Erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < n; i++) {
            original[i] = ((rand() << 15) | rand()) % 1000001;
        }

        printf("%7d", n);
        for (int t = 0; t < nb_tris; t++) {
            copy_array(original, copie, n);   // chaque tri reçoit une copie identique du tableau non trié
            clock_t debut = clock();
            tris[t].trier(copie, n);
            clock_t fin = clock();
            if (!is_sorted_ascending(copie, n)) {
                printf("\nErreur : le tri %s a échoué !\n", tris[t].nom);
                exit(EXIT_FAILURE);
            }
            printf(" | %11.4f s", (double) (fin - debut) / CLOCKS_PER_SEC);
            fflush(stdout);   // affiche la case tout de suite (les tris en O(n^2) sont longs)
        }
        printf("\n");
        free(original);
        free(copie);
    }
}

int main()
{
    // Question 1
    printf("===== Question 1 =====\n");
    int x = 3, y = 7;
    swap_int(&x, &y);
    printf("x = %d, y = %d\n", x, y);                 
    int trie[] = {1, 2, 2, 5, 9};
    int pas_trie[] = {4, 1, 3};
    printf("%d\n", is_sorted_ascending(trie, 5));     
    printf("%d\n", is_sorted_ascending(pas_trie, 3)); 
    int copie[5];
    copy_array(trie, copie, 5);
    print_array(copie, 5);                           
    printf("===== Finish question 1 =====\n");

    // Questions 2 à 6 : chaque tri sur une copie du même petit tableau (avec doublons)
    int scores[] = {42, 7, 19, 7, 100, 0, 63, 19, 5, 88};
    int n = sizeof(scores) / sizeof(scores[0]);
    int A[10];
    Tri tris[] = {
        {"Question 2 - selection", selection_sort},
        {"Question 3 - insertion", insertion_sort},
        {"Question 4 - bulles   ", bubble_sort},
        {"Question 5 - fusion   ", merge_sort},
        {"Question 6 - rapide   ", quick_sort},
    };
    printf("===== Questions 2 a 6 =====\n");
    printf("Avant tri                : ");
    print_array(scores, n);
    for (int t = 0; t < 5; t++) {
        copy_array(scores, A, n);
        tris[t].trier(A, n);
        printf("%s (trie = %d) : ", tris[t].nom, is_sorted_ascending(A, n));
        print_array(A, n);                           
    }
    printf("===== Finish questions 2 a 6 =====\n");

    // Question 7
    printf("===== Question 7 =====\n");
    comparaison_performances();
    printf("===== Finish question 7 =====\n");

    return 0;
}
