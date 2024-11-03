#include <stdio.h>

// 노드 구조체 정의
typedef struct node {
    int data;
    struct node* next;
} node;

int main(void) {
    // 노드 생성 및 초기화
    node first = { 10, NULL };
    node second = { 20, NULL };
    node third = { 30, NULL };

    // 노드 연결
    node* head = &first;
    first.next = &second;
    second.next = &third;

    // 링크드 리스트 순회 및 출력
    node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    return 0;
}
