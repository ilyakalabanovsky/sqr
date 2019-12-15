/*
 * Copyright (c) 2019 Ilya Kalabanovsky
 *
 * sqrlib (STACK, QUEUE, RING)
 * A set of structures and functions for working with stack, queue and ring buffer.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <stdlib.h>
// #include <stdio.h>
#include "sqrlib.h"

/**
    Adds an element with a new value to the stack.
*/
void sqr_s_push(DATA_handle val, STACK_handle _buf) {
    STACK **buf = (STACK**) _buf;
    
    STACK *new_buf = (STACK *) calloc(1, sizeof(STACK));
    new_buf -> data = val;
    new_buf -> next = (*buf);
    (*buf) = new_buf;
}

/**
    Get the value and delete element from the stack.
*/
DATA_handle sqr_s_pop(STACK_handle _buf) {
    STACK **buf = (STACK**) _buf;
    
    if ((*buf) == NULL) return NULL;
	STACK *old_buf = (*buf);
	DATA_handle *val = (*buf) -> data;
	(*buf) = (*buf) -> next;
	free(old_buf);
	return val;
}

/**
    Adds the element with a new value to the queue.
 */
void sqr_q_push_back(DATA_handle val,  QUEUE_handle _buf, QUEUE_handle _head) {
    QUEUE **buf = (QUEUE**) _buf;
    QUEUE **head = (QUEUE**) _head;

    QUEUE *new_buf = (QUEUE*) calloc(1, sizeof(QUEUE));
    new_buf -> data = val;
    new_buf -> next = NULL;
    if((*buf) != NULL) {
        (*buf) -> next = new_buf;
        (*buf) = new_buf;
    } else {
        (*buf) = new_buf;
        (*head) = (*buf);
    }
}

/** 
    Get the value and delete element from the queue.
 */
DATA_handle sqr_q_pop_front(QUEUE_handle _buf) {
    QUEUE **buf = (QUEUE**) _buf;
    
    if ((*buf) == NULL)  return NULL;
    DATA_handle data = (*buf) -> data;
    QUEUE *old_buf = (*buf);
    (*buf) = (*buf) -> next;
    free(old_buf);
    return data;
}

/**
    Creates a new ring buffer instance.
 */
RING_handle sqr_rdyn_create(const int buf_size) {
    RING_Buffer *buf = (RING_Buffer*) calloc(1, sizeof(RING_Buffer));
    buf -> head = NULL;
    buf -> tail = NULL;
    buf -> size = (buf_size < 1) ? 1 : buf_size;
    buf -> real_size = 0;
    return buf;
}

/**
    Clears the ring buffer, delete all elements and frees memory. 
 */
void sqr_rdyn_destroy(RING_handle _buf) {
    RING_Buffer *buf = (RING_Buffer*) _buf;
    DATA_Buffer *data_buf;
    
    while(buf -> head != NULL) {
        data_buf = buf -> head;
        if(buf -> head == buf -> tail) {
            buf -> head = NULL;
            buf -> tail = NULL;
        } else {
            buf -> head = buf -> head -> next;
            buf -> head -> prev = buf -> tail;
        }
        free(data_buf);
    }
    free(buf);
}

/**
    Adds a new element to the ring buffer. Expands the buffer until the number of elements reaches the maximum size.
 */
int sqr_rdyn_set(RING_handle _buf, DATA_handle value) {
    RING_Buffer *ring_buf = (RING_Buffer*) _buf;    
    DATA_Buffer* data_buf = (DATA_Buffer*) calloc(1, sizeof(DATA_Buffer));
    
    if(data_buf == NULL) return 0;
    data_buf -> data = value;
    if(ring_buf -> head == NULL) {
        ring_buf -> head = data_buf;
        ring_buf -> tail = data_buf;
        data_buf -> next = ring_buf -> head;
        data_buf -> prev = ring_buf -> tail;
        ring_buf -> real_size++;
    } else {
        if(ring_buf -> real_size < ring_buf -> size) {
            ring_buf -> tail -> next = data_buf;
            data_buf -> prev = ring_buf -> tail;
            data_buf -> next = ring_buf -> head;
            ring_buf -> tail = data_buf;
            ring_buf -> head -> prev = ring_buf -> tail;
            ring_buf -> real_size++;
        } else {
            ring_buf -> head -> data = value;
            ring_buf -> head = ring_buf -> head -> next;
            ring_buf -> tail = ring_buf -> tail -> next;
            free(data_buf);
        }
    }
    return 1;
}

/**
    Get the value and delete the element from the ring buffer.
 */
DATA_handle sqr_rdyn_get(RING_handle _buf) {
    RING_Buffer *ring_buf = (RING_Buffer*) _buf;    
    DATA_Buffer* data_buf;
    DATA_handle result;
    
    if(ring_buf -> head == NULL) return NULL;
    result = ring_buf -> head -> data;
    data_buf = ring_buf -> head;
    if(ring_buf -> head == ring_buf -> tail) {
        ring_buf -> head = NULL;
        ring_buf -> tail = NULL;
    } else {
        ring_buf -> tail -> next = ring_buf -> head -> next;
        ring_buf -> head = ring_buf -> head -> next;
        ring_buf -> head -> prev = ring_buf -> tail;
    }
    ring_buf -> real_size--;
    free(data_buf);
    return result;
}

/**
    Get the value and leave the element in the ring buffer.
 */
DATA_handle sqr_rdyn_peek(RING_handle _buf) {
    RING_Buffer *ring_buf = (RING_Buffer*) _buf;    

    if(ring_buf -> head == NULL) return NULL;
    return ring_buf -> head -> data;
}

/**
    Clears the ring buffer and delete all elements. 
 */
void sqr_rdyn_clear(RING_handle _buf) {
    RING_Buffer *ring_buf = (RING_Buffer*) _buf;
    DATA_Buffer *data_buf;
    
    while(ring_buf -> head != NULL) {
        data_buf = ring_buf -> head;
        if(ring_buf -> head == ring_buf -> tail) {
            ring_buf -> head = NULL;
            ring_buf -> tail = NULL;
        } else {
            ring_buf -> head = ring_buf -> head -> next;
            ring_buf -> head -> prev = ring_buf -> tail;
        }
        free(data_buf);
    }
}

/**
    Return a maximum size of the buffer. 
 */
int sqr_rdyn_get_size(RING_handle _buf) {
    RING_Buffer *ring_buf = (RING_Buffer*) _buf;
    
    return ring_buf -> size;
}

/**
    Return a current size of the buffer. 
 */
int sqr_rdyn_get_real_size(RING_handle _buf) {
    RING_Buffer *ring_buf = (RING_Buffer*) _buf;
    
    return ring_buf -> real_size;
}

