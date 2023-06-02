#include <stdio.h>
#include <stdlib.h>

// Structure for each node of the linked list
typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct dList {
    Node* head;
    int size;
} DList;

Node* makeNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

DList* makeDList() {
    DList* newList = (DList*)malloc(sizeof(DList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

void insert(DList* dList, int data, int position) {
    // Create a new node
    Node* newNode = makeNode(data);
    
    // insert the new node at the head
    if (position == 1) {
        if (dList->size == 0) {
            dList->head = newNode;
            dList->head->next = dList->head;
            dList->head->prev = dList->head;
            dList->size++;
            return;
        }
        newNode->next = dList->head;
        newNode->prev = dList->head->prev;
        dList->head->prev = newNode;
        newNode->prev->next = newNode;

        dList->head = newNode;
        dList->size++;
        return;
    }

    Node* pointer = dList->head;

    position--;

    while (--position > 0) {
        if (pointer == NULL) {
            return;
        }
        pointer = pointer->next;
    }

    newNode->next = pointer->next;
    newNode->next->prev = newNode;
    pointer->next = newNode;
    newNode->prev = pointer;
    dList->size++;
}

void insertHead(DList* dList, int data) {
    insert(dList, data, 1);
}

void insertEnd(DList* dList, int data) {
    insert(dList, data, dList->size + 1);
}


void printLinkedList(DList* dList) {
    Node* pointer = dList->head;
    
    for (int i = 0; i < dList->size; i++) {
        if (i == dList->size - 1) {
            printf("%d", pointer->data);
        } else {
            printf("%d, ", pointer->data);
        }
        pointer = pointer->next;
    }

    printf("\n");
}

void delete(DList* dList, int data) {
    if (dList->size == 0) {
        return;
    }

    Node* dummy = makeNode(0);
    dummy->next = dList->head;
    dummy->prev = dList->head->prev;
    dummy->prev->next = NULL;

    Node* pointer = dummy;

    while (pointer != NULL) {
        while (pointer->next != NULL && pointer->next->data == data) {
            Node* next = pointer->next;
            pointer->next = pointer->next->next;
            pointer->next->prev = pointer;
            free(next);
            dList->size--;
        }
        pointer = pointer->next;
    }

    dList->head = dummy->next;
    dList->head->prev = dummy->prev;
    dummy->prev->next = dList->head;
    free(dummy);
}

void deleteHead(DList* dList) {
    if (dList->size == 0) {
        return;
    }

    if (dList->size == 1) {
        Node* head = dList->head;
        dList->head = NULL;
        free(head);
        dList->size--;
        return;
    }

    Node* head = dList->head;
    dList->head->prev->next = dList->head->next;
    dList->head->next->prev = dList->head->prev;
    dList->head = dList->head->next;
    free(head);
    dList->size--;
}

void deleteTail(DList* dList) {
    if (dList->size == 0) {
        return;
    }

    if (dList->size == 1) {
        Node* head = dList->head;
        dList->head = NULL;
        free(head);
        dList->size--;
        return;
    }
    
    Node* tail = dList->head->prev;
    dList->head->prev->prev->next = dList->head;
    dList->head->prev = dList->head->prev->prev;

    free(tail);
    dList->size--;
}

int search(DList* dList, int data) {
    if (dList->size == 0) {
        return -1;
    }

    int position = 1;

    Node* pointer = dList->head;
    dList->head->prev->next = NULL;

    while (pointer != NULL) {
        if (pointer->data == data) {
            dList->head->prev->next = dList->head;
            return position;
        }
        pointer = pointer->next;
        position++;
    }

    dList->head->prev->next = dList->head;
    return -1;
}

void freeLinkedList(DList* dList) {
    if (dList == NULL) {
        return;
    }

    if (dList->head == NULL) {
        free(dList);
        return;
    }

    dList->head->prev->next = NULL;
    Node* curr = dList->head;
    Node* next = curr->next;

    while (curr != NULL) {
        free(curr);
        curr = next;
        if (next != NULL) {
            next = next->next;
        }
    }
}

int main() {
    DList* dList = makeDList();
    insertEnd(dList, 23);
    insertEnd(dList, 52);
    insertEnd(dList, 19);
    insertEnd(dList, 9);
    insertEnd(dList, 100);

    printf("Original linked list: ");
    printLinkedList(dList);
    printf("\n");

    printf("Search 19. Found at position %d\n", search(dList, 19));
    printf("\n");

    printf("Insert 7 at position 3\n");
    insert(dList, 7, 3);
    printf("Current list: ");
    printLinkedList(dList);
    printf("\n");

    printf("Insert 7 at head\n");
    insertHead(dList, 7);
    printf("List after insertion: ");
    printLinkedList(dList);
    printf("\n");

    printf("Insert 7 at end\n");
    insertEnd(dList, 7);
    printf("List after insertion: ");
    printLinkedList(dList);
    printf("\n");

    printf("Delete 19\n");
    delete(dList, 19);
    printf("List after deletion: ");
    printLinkedList(dList);
    printf("\n");

    printf("Delete head\n");
    deleteHead(dList);
    printf("List after deletion: ");
    printLinkedList(dList);
    printf("\n");

    printf("Delete end\n");
    deleteTail(dList);
    printf("List after deletion: ");
    printLinkedList(dList);
    printf("\n");
    
    freeLinkedList(dList);
    
    return 0;
}