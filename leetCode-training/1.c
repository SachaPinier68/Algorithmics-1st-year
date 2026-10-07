#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPalindrome(int x) {
    // Cas négatifs et multiples de 10 non nuls
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int revertedNumber = 0;
    // On extrait les chiffres jusqu'à la moitié du nombre
    while (x > revertedNumber) {
        revertedNumber = revertedNumber * 10 + (x % 10);
        x /= 10;
    }

    // Longueur paire : x == revertedNumber
    // Longueur impaire : x == revertedNumber / 10 (on ignore le chiffre du milieu)
    if (x == revertedNumber || x == revertedNumber / 10) {
        return true;
    } else {
        return false;
    }
}



#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // 1. Variable normale (pas un pointeur) pour la sentinelle
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* current = &dummy;

    // 2. Boucle de comparaison
    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            current->next = list1; // On passe le pointeur list1, pas la valeur
            list1 = list1->next;
        } else {
            current->next = list2; // Nom exact de variable : list2
            list2 = list2->next;
        }
        current = current->next;
    }

    // 3. Raccordement du reste de la liste non vide
    if (list1 != NULL) {
        current->next = list1;
    } else {
        current->next = list2;
    }

    // 4. Renvoi du premier vrai élément
    return dummy.next;
}


int main (void) {
    
    int test1 = isPalindrome(121);
    int test2 = isPalindrome(1441);
    int test3 = isPalindrome(1252);

    printf("test1 : %d\n, test2 : %d\n, test3 : %d\n", test1, test2, test3);

    printf("=== 2. TEST LISTE CHAÎNÉE ===\n");

    

    return 0;
}