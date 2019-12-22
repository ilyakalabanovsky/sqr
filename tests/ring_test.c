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

int main() {
    My_DATA *res = NULL;
    int res_data[MAX_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7};
    bool test_res = true;
    int iter = 0;
    RING_Buffer *r_buf = NULL;
    
// Ffilling test
    r_buf = (RING_Buffer *) sqr_rdyn_create(MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++) {
        My_DATA *rb_val = (My_DATA*) calloc(1, sizeof(My_DATA));
        rb_val -> value = i;
        sqr_rdyn_set(r_buf, rb_val);
    }
    
    printf("ring buffer maximum size test ...%s\n", (sqr_rdyn_get_size(r_buf) == MAX_SIZE) ? "passed" : "failed");
    printf("ring buffer real size test ......%s\n", (sqr_rdyn_get_real_size(r_buf) == MAX_SIZE) ? "passed" : "failed");
    
    res = sqr_rdyn_peek(r_buf);
    printf("ring buffer peek test ...........%s\n", (res != NULL && res -> value == 0) ? "passed" : "failed");

    do {
        res = sqr_rdyn_get(r_buf);
        if(res != NULL && res -> value != res_data[iter++]) test_res = false;
        free(res);
    } while(res != NULL);
    printf("ring buffer filling test ........%s\n", (test_res) ? "passed" : "failed");

    sqr_rdyn_destroy(&r_buf);
    printf("ring buffer destroy test ........%s\n", (r_buf) ? "failed" : "passed");
    
// Clear test
    test_res = true;
    r_buf = (RING_Buffer *) sqr_rdyn_create(MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++) {
        My_DATA *rb_val = (My_DATA*) calloc(1, sizeof(My_DATA));
        rb_val -> value = i;
        sqr_rdyn_set(r_buf, rb_val);
    }
    sqr_rdyn_clear(r_buf);
    res = sqr_rdyn_peek(r_buf);
    printf("ring buffer clear test ..........%s\n", (res == NULL) ? "passed" : "failed");
    sqr_rdyn_destroy(&r_buf);

// Overload filling test

    test_res = true;
    r_buf = (RING_Buffer *) sqr_rdyn_create(MAX_SIZE);
    for (int i = 0; i < MAX_SIZE + 1; i++) {
        My_DATA *rb_val = (My_DATA*) calloc(1, sizeof(My_DATA));
        rb_val -> value = i;
        sqr_rdyn_set(r_buf, rb_val);
    }
    res = sqr_rdyn_peek(r_buf);
    printf("ring buffer overload test .......%s\n", (res != NULL && res -> value == 1) ? "passed" : "failed");
    sqr_rdyn_destroy(&r_buf);

    return 0;
}

