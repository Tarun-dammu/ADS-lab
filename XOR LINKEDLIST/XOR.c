#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
typedef struct node {
    int data;
    struct node* link;
}node;
node* xor(node* x, node* y) {
    return (node*)((uintptr_t) (x) ^ (uintptr_t) (y));
}
void add(node** head, int data) {

    node* curr = *head;
    node* prev = NULL;
    while(curr!=NULL){
        node* temp = curr;
        curr = xor(curr->link, prev);
        prev = temp;
    }

    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->link = xor(prev, NULL);
    if(*head==NULL) {
        *head = newNode;
        return;
    }
    prev->link = xor(xor(prev->link, NULL), newNode);
}

int delete(node** head, int key) {
    if((*head) == NULL)
        return -1;
    if((*head)->data==key) {
        node* next = xor(NULL, (*head)->link);
        if(next!=NULL) {
            next->link = xor(NULL,xor(next->link, (*head)));
        }
        free(*head);
        *head = next;
        return 0;
    }
    node* curr = *head;
    node* prev = NULL;
    while(curr!=NULL && curr->data!=key){
        node* temp = curr;
        curr = xor(curr->link, prev);
        prev = temp;
    }

    if(curr==NULL) // key not found in list
        return -1;
    node* prevPrev = xor(prev->link, curr);
    node* next = xor(curr->link, prev);
    prev->link = xor(prevPrev, next);
    if(next!=NULL)
        next->link = xor(xor(next->link, curr), prev);
    free(curr);
    return 0; // successful
}

int search(node* head, int key) {
    node* curr = head;
    node* prev = NULL;
    while(curr!=NULL && curr->data!=key){
        node* temp = curr;
        curr = xor(curr->link, prev);
        prev = temp;
    }
    if(curr==NULL) // key not found in list
        return -1;
    return 0; // key found in list
}

void print(node* head) {
    node* curr = head;
    node* prev = NULL;
    while(curr!=NULL){
        printf("%d, ", curr->data);
        node* temp = curr;
        curr = xor(curr->link, prev);
        prev = temp;
    }
    printf("\b\b ");
}

void main() {
    int choice = 0, data = 0, ret = 0;
    node* head = NULL;
    while(choice != -1) {
        printf("\nEnter 1 to add\n");
        printf("Enter 2 to delete from list\n");
        printf("Enter 3 to search the list\n");
        printf("Enter 4 to display the list\n");
        printf("Enter -1 to quit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        if(choice==-1)
            break;
        switch(choice) {
            case 1:
                printf("Enter data to add to the list : ");
                scanf("%d", &data);
                add(&head, data);
                break;
            case 2:
                printf("Enter data to delete from the list : ");
                scanf("%d", &data);
                ret = delete(&head, data);
                if(ret==-1)
                    printf("\n%d not found in list", data);
                else
                    printf("\n%d deleted from the list", data);
                break;
            case 3:
                printf("Enter data to search the list : ");
                scanf("%d", &data);
                ret = search(head, data);
                if(ret==-1)
                    printf("\n%d not found in list", data);
                else
                    printf("\n%d found in the list", data);
                break;
            case 4:
                printf("The list contais : ");
                print(head);
                break;
            default:
                printf("Invalid Choice\n");
        }
    }
}