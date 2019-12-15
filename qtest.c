// qtest.c
// gcc -o qtest qtest.c sqrlib.c -std=c11
// sudo ./qtest
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "sqrlib.h"

#define MAX_SIZE 8
// #define MAX_SIZE 0

typedef struct _My_DATA {
    int data;
    int value;
} My_DATA;

typedef struct _My_STACK {
    int *data;
//     My_DATA *data;
} My_STACK;

My_STACK *top = NULL;
QUEUE *head = NULL, *tail = NULL;

int main() {
    int *res;
//     My_DATA *res;
    
    for (int i = 0; i < 8; ++i) {
        int *stack_val = (int*) calloc(1, sizeof(int));
        int *queue_val = (int*) calloc(1, sizeof(int));
//         My_DATA *stack_val = (My_DATA*) calloc(1, sizeof(My_DATA));
        *stack_val = i;
        *queue_val = i;
//         stack_val -> value = i;
        sqr_s_push((int*) stack_val, (My_STACK**) &top);
//         sqr_s_push((My_DATA*) stack_val, (My_STACK**) &top);
            printf("%d ", i);
//             printf("[%lu]", top);
//             printf("[%d] ", *top -> data);

//            head = sqr_q_push_back(i, &tail, &head);
//            head = (QUEUE*) sqr_q_push_back(queue_val, (QUEUE**) &tail, (QUEUE**) &head);
        sqr_q_push_back(queue_val, (QUEUE**) &tail, (QUEUE**) &head);
    }
    
    printf("\n---------------\n");
            res = (int*) head -> data;
//             res = (My_DATA*) top -> data;
            printf("[%d]", *res);
//             printf("[%d]", res -> value);
    printf("\n---------------\n");
    if(top == NULL) printf("top == NULL\n");
    
    while(top != NULL) {
        res = (int*) sqr_s_pop((My_STACK**) &top);
//         res = (My_DATA*) sqr_s_pop((My_STACK**) &top);
        printf("%d ", *res);
//         printf("%d ", res -> value);
        free(res);
    }
    printf(" [stack]\n");
    
    int *q_res;
    while(head != NULL) {
        q_res = (int*) sqr_q_pop_front((QUEUE**) &head);
        printf("%d ", *q_res);
//         printf("%d ", sqr_q_pop_front(&head));
        free(q_res);
    }
    printf(" [queue]\n");
    
    int *ring_data = (int*) calloc(1, sizeof(int));
    int *ring_res;
    
    RING_Buffer *r_buf = (RING_Buffer *) sqr_rdyn_create(MAX_SIZE);
    printf("ring buffer size = %d\n", r_buf -> size);
    printf("ring buffer size = %d\n", sqr_rdyn_get_size(r_buf));
    printf("ring buffer real_size = %d\n", sqr_rdyn_get_real_size(r_buf));
    *ring_data = 10;
    sqr_rdyn_set(r_buf, ring_data);
    printf("ring head data = %d\n", *(int*) r_buf -> head -> data);
    printf("ring buffer real_size = %d\n", sqr_rdyn_get_real_size(r_buf));
    
    ring_res = sqr_rdyn_peek(r_buf);
    printf("ring peek result = ");
    if(ring_res == NULL) printf("NULL\n");
    else printf("%d\n", *ring_res);

    ring_res = sqr_rdyn_get(r_buf);
    printf("ring get result  = ");
    if(ring_res == NULL) printf("NULL\n");
    else printf("%d\n", *ring_res);

    sqr_rdyn_clear(r_buf);
    sqr_rdyn_destroy(r_buf);
//     free(ring_data);
    free(ring_res);
//     printf("ring buffer size = %d\n", r_buf -> size);

    return 0;
}

