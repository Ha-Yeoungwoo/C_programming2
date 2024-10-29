#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct { 
    int data[MAX]; 
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1; 
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}                            

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (isFull(s)) {            
        printf("Stack is full!\n");
        return;
    }
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->data[(s->top)--];
}

int main() {
    Stack s;  
    init(&s);  
    push(&s, 10);  
    push(&s, 20);
    push(&s, 30);
    printf("Popped: %d\n", pop(&s));  
    printf("Popped: %d\n", pop(&s));
    return 0;
}