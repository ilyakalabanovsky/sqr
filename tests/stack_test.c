// stack_test.c
// gcc -o stack_test stack_test.c ../src/sqrlib.c -std=c11
// gcc -std=c11 stack_test.c ../src/sqrlib.c -o stack_test
// sudo ./stack_test 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../src/sqrlib.h"

#define MAX_SIZE 8

typedef struct _My_DATA {
    int value;
} My_DATA;

typedef struct _My_STACK {
    My_DATA *data;
} My_STACK;

My_STACK *top = NULL;

int main() {
    My_DATA *res;
    int res_data[MAX_SIZE] = {7, 6, 5, 4, 3, 2, 1, 0};
    bool test_res = true;
    int iter = 0;
    
    for (int i = 0; i < MAX_SIZE; ++i) {
        My_DATA *stack_val = (My_DATA*) calloc(1, sizeof(My_DATA));
        stack_val -> value = i;
        sqr_s_push((My_DATA*) stack_val, (My_STACK**) &top);
//         printf("%d ", i);
    }
    
//     printf("\n---------------\n");
    
    while(top != NULL) {
        res = (My_DATA*) sqr_s_pop((My_STACK**) &top);
//         printf("%d ", res -> value);
        if(res -> value != res_data[iter++]) test_res = false;
        free(res);
    }
//     printf(" [stack]\n");
    
    printf("stack test ...%s", (test_res) ? "passed\n" : "failed\n");

//     for(int i = 0; i < MAX_SIZE; i++) {
//         printf("%d ", res_data[i]);
//     }
//     printf(" [res_data]\n");
    
    

    return 0;
}

