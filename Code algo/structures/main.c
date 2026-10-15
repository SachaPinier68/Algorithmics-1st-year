#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define TABLE_SIZE 10

/* =========================================================
   1. TABLEAU (Array) : Insertion avec décalage
   ========================================================= */
void insertArray(int a[], int *n, int i, int x) {
    for (int j = *n - 1; j >= i; j--) {
        a[j + 1] = a[j];
    }
    a[i] = x;
    (*n)++;
}

/* =========================================================
   2. LISTE CHAÎNÉE (Linked List) : Insertion en tête
   ========================================================= */
typedef struct Node {
    int value;
    struct Node *next;
} Node;

void pushFront(Node **head, int val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = *head;
    *head = newNode;
}

void printList(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

/* =========================================================
   3. PILE (Stack - LIFO) : Push et Pop
   ========================================================= */
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void push(Stack *s, int x) {
    if (s->top < MAX_SIZE) {
        s->data[s->top] = x;
        s->top++;
    }
}

int pop(Stack *s) {
    if (s->top > 0) {
        s->top--;
        return s->data[s->top];
    }
    return -1;
}

/* =========================================================
   4. FILE (Queue - FIFO) : Enqueue et Dequeue
   ========================================================= */
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void enqueue(Queue *q, int x) {
    if (q->rear < MAX_SIZE) {
        q->data[q->rear] = x;
        q->rear++;
    }
}

int dequeue(Queue *q) {
    if (q->front < q->rear) {
        int val = q->data[q->front];
        q->front++;
        return val;
    }
    return -1;
}

/* =========================================================
   5. TABLE DE HACHAGE (Hash Table)
   ========================================================= */
int hash(const char *key, int size) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (int)key[i];
    }
    return sum % size;
}

void insertHash(char table[TABLE_SIZE][32], const char *key) {
    int idx = hash(key, TABLE_SIZE);
    strcpy(table[idx], key);
}

/* =========================================================
   6. STRUCTURE EN C (struct)
   ========================================================= */
struct Person {
    char name[32];
    int age;
};

void updateAge(struct Person *p, int newAge) {
    p->age = newAge;
}

/* =========================================================
   MAIN DE TEST
   ========================================================= */
int main(void) {
    // --- Test 1 : Tableau ---
    printf("=== 1. TEST TABLEAU ===\n");
    int arr[10] = {10, 20, 30, 40};
    int n = 4;
    printf("Avant insertion : ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    insertArray(arr, &n, 2, 99); // insertion de 99 à l'indice 2

    printf("Après insertion de 99 à l'indice 2 : ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");

    // --- Test 2 : Liste chaînée ---
    printf("=== 2. TEST LISTE CHAÎNÉE ===\n");
    Node *list = NULL;
    pushFront(&list, 3);
    pushFront(&list, 2);
    pushFront(&list, 1);
    printf("Contenu de la liste : ");
    printList(list);
    freeList(list);
    printf("\n");

    // --- Test 3 : Pile (LIFO) ---
    printf("=== 3. TEST PILE (LIFO) ===\n");
    Stack s = {.top = 0};
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    printf("Pop 1 : %d\n", pop(&s)); // 30
    printf("Pop 2 : %d\n", pop(&s)); // 20
    printf("Pop 3 : %d\n\n", pop(&s)); // 10

    // --- Test 4 : File (FIFO) ---
    printf("=== 4. TEST FILE (FIFO) ===\n");
    Queue q = {.front = 0, .rear = 0};
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printf("Dequeue 1 : %d\n", dequeue(&q)); // 10
    printf("Dequeue 2 : %d\n", dequeue(&q)); // 20
    printf("Dequeue 3 : %d\n\n", dequeue(&q)); // 30

    // --- Test 5 : Table de Hachage ---
    printf("=== 5. TEST TABLE DE HACHAGE ===\n");
    char hashTable[TABLE_SIZE][32] = {{0}};
    insertHash(hashTable, "Ali");
    insertHash(hashTable, "Maxime");
    printf("Hachage de 'Ali'    -> indice %d : %s\n", hash("Ali", TABLE_SIZE), hashTable[hash("Ali", TABLE_SIZE)]);
    printf("Hachage de 'Maxime' -> indice %d : %s\n\n", hash("Maxime", TABLE_SIZE), hashTable[hash("Maxime", TABLE_SIZE)]);

    // --- Test 6 : Struct ---
    printf("=== 6. TEST STRUCT ===\n");
    struct Person alice = {"Alice", 30};
    printf("Avant : %s a %d ans\n", alice.name, alice.age);
    updateAge(&alice, 31);
    printf("Après updateAge : %s a %d ans\n", alice.name, alice.age);

    return 0;
}