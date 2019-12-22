// queue_test.c
// gcc -std=c11 queue_test.c ../src/sqrlib.c -o queue_test
// sudo ./queue_test 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../src/sqrlib.h"

#define MAX_SIZE 8

typedef struct _My_DATA {
    int value;
} My_DATA;

typedef struct _My_QUEUE {
    My_DATA *data;
} My_QUEUE;

My_QUEUE *head = NULL, *tail = NULL;

int main() {
    My_DATA *res;
    int res_data[MAX_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7};
    bool test_res = true;
    int iter = 0;
    
    for (int i = 0; i < MAX_SIZE; ++i) {
        My_DATA *queue_val = (My_DATA*) calloc(1, sizeof(My_DATA));
        queue_val -> value = i;
        sqr_q_push_back(queue_val, (My_QUEUE**) &tail, (My_QUEUE**) &head);
//         printf("%d ", i);
    }
    
//     printf("\n---------------\n");
    
    while(head != NULL) {
        res = (My_DATA*) sqr_q_pop_front((My_QUEUE**) &head);
        
//         printf("%d ", res -> value);

        if(res -> value != res_data[iter++]) test_res = false;
        free(res);
    }
//     printf(" [queue]\n");
    
    printf("queue test ...%s", (test_res) ? "passed\n" : "failed\n");

//     for(int i = 0; i < MAX_SIZE; i++) {
//         printf("%d ", res_data[i]);
//     }
//     printf(" [res_data]\n");
    
    

    return 0;
}

