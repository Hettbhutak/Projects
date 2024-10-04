#include<stdio.h>
#include<stdlib.h>

struct node {
int data ;
struct node* next ;
} ;

struct node* front = NULL ;
struct node* rear = NULL ;

void enqueue(int num) ;
void display() ;
void dequeue() ;
int main() {
int ch =1 ;
while(ch!=0) {
printf("1.Enqueue\n") ;
printf("2.Dequeue\n") ;
printf("3.Display\n") ;
printf("0.Exit\n") ;
printf("Enter your choice : ") ;
scanf("%d" , &ch) ;
if(ch==1) {
int n ;
printf("Enter the number you want to insert in a queue : ") ;
scanf("%d" , &n) ;
enqueue(n) ;

    }
    else if(ch==2) {
        dequeue() ; 
    }
    else if(ch==3) {
        display() ; 
    }
    else if(ch==0) {
        continue;
    }else {
        printf("Enter the valid choice!!") ;
    }
}
return 0 ; 
}

void enqueue(int num) {
struct node* ptr = malloc(sizeof(struct node)) ;
ptr->data = num ;
ptr->next = NULL ;

if((front==NULL) && (rear==NULL)) {
    front = rear = ptr ; 
    printf("%d inserted !!\n" , num) ; 
}else {
    rear->next = ptr ; 
    rear = ptr ;
    printf("%d inserted !!\n" , num) ; 
}
}

void display() {
if((front==NULL) && (rear==NULL)){
printf("Queue is Empty!!!\n") ;
}else {
struct node* temp = front ;
while(temp != NULL) {
printf("%d\t" , temp->data) ;
temp = temp->next ;
}
printf("\n") ;
}
}

void dequeue() {
struct node* temp = front ;
if((front==NULL) && (rear==NULL)){
printf("Queue is Empty!!!\n") ;
}else {
front = front->next ;
printf("Element dequeued!!\n") ;
free(temp) ;
}

}
