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


struct ListNode {
    int val;
    struct ListNode *next;
};

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
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

int climbStairs(int n) {
    // Cas de base pour les petites valeurs de n
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    int prev2 = 1; // Représente les chemins pour n-2
    int prev1 = 2; // Représente les chemins pour n-1
    int current = 0;

    // On calcule itérativement de la marche 3 jusqu'à n
    for (int i = 3; i <= n; i++) {
        current = prev1 + prev2; // La marche actuelle est la somme des 2 précédentes
        prev2 = prev1;           // On décale d'un cran pour la prochaine itération
        prev1 = current;
    }
    
    printf("Voici le nombre de chemins pour monter %d marches : %d\n", n, current);
    return current;
}

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode nvListe;
    nvListe.next = NULL;
    struct ListNode* current = &nvListe;
    while (head->next != NULL)
    {
        if (head->val == head->next) {
            current = head->val;
            head = head->next->next;
        }
        else {
            current = head->val;
            head = head->next;
        }
    }
    return current;   
}

int maxDepth(struct TreeNode* root) {
    int depth = 0;
    if (root == NULL) {
        return depth;
    }
    int leftWay = maxDepth(root->left);
    int rightWay = maxDepth(root->right);

    return 1 + (leftWay > rightWay ? leftWay : rightWay);
    
}


bool isMirror(struct TreeNode* t1, struct TreeNode* t2) {
    if ((t1 == NULL) && (t2 == NULL)) {
        return true;
    }
    if (((t1 == NULL) && (t2 != NULL)) || ((t1 != NULL) && (t2 == NULL))) {
        return false;
    }

    if (t1->val != t2->val) {
        return false;
    }

    return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    return isMirror(root->left, root->right);
}

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if ((p == NULL) && (q == NULL)) {
        return true;
    }
    if ((p == NULL) || (q == NULL)){
        return false;
    }
    if (p->val != q->val) {
        return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}


int minDepth(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL) {
        return 1 + minDepth(root->right);
    }
    if (root->right == NULL) {
        return 1 + minDepth(root->left);
    }

    int leftWay = minDepth(root->left);
    int rightWay = minDepth(root->right);

    return 1 + (leftWay < rightWay ? leftWay : rightWay);

    
}

int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    *returnSize = numRows;
    *returnColumnSizes = (int*)malloc(numRows * sizeof(int));
    int** triangle = (int**)malloc(numRows * sizeof(int*));

    for (int i = 0; i < numRows; i++) {
        int rowSize = i + 1;
        (*returnColumnSizes)[i] = rowSize;

        triangle[i] = (int*)malloc(rowSize * sizeof(int));

        triangle[i][0] = 1;
        triangle[i][rowSize - 1] = 1;

        for (int j = 1; j < rowSize - 1; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }

    }
    return triangle;
}



// Longest Common Prefix N°4

int compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str1, str2);
}

char* longestCommonPrefix(char** strs, int strsSize) {

    if (strsSize == 0) {
        char* empty = (char*)malloc(1);
        empty[0] == '\0';
        return empty;
    }

    qsort(strs, strsSize, sizeof(char*), compare);

    char* first = strs[0];
    char* last = strs[strsSize - 1];

    int i = 0;
    while (first[i] && last[i] && first[i] == last[i]) {
        i++;
    }

    char* prefix = (char*)malloc((i + 1) * sizeof(char));
    strncpy(prefix, first, i);
    prefix[i] = '\0';

    return prefix;
}


int main (void) {
    
    int test1 = isPalindrome(121);
    int test2 = isPalindrome(1441);
    int test3 = isPalindrome(1252);

    printf("test1 : %d\n, test2 : %d\n, test3 : %d\n", test1, test2, test3);

    printf("=== 2. TEST LISTE CHAÎNÉE ===\n");


    climbStairs(10);

    

    return 0;
}