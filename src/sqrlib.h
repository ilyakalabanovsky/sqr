/*
 * Copyright (c) 2019 Ilya Kalabanovsky
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
 
 /** \mainpage C library for stack, queue, and ring buffers
 The library provides some functions and structures for working with the most popular buffers, such as the stack, queue, and ring buffer.
 
 \par Stack
 The classic self referential structure Stack buffer includes a data pointer and the "next" pointer. 
 
 Functions: 
 <pre>
    \ref sqr_s_push - Adds an element with a new value to the stack.
    \ref sqr_s_pop - Get the value and delete element from the stack.
 </pre>
  
 \par Queue
 The classic self referential structure Queue buffer includes the data, "prev" and the "next" pointer.
 
 Functions: 
 <pre>
    \ref sqr_q_push_back - Adds the element with a new value to the queue.
    \ref sqr_q_pop_front - Get the value and delete element from the queue.
 </pre>
 
 \par Ring buffer
 The dynamically expandable unordered ring buffer with adjustable size.
 
 Functions: 
 <pre>
    \ref sqr_rdyn_create - Creates a new ring buffer instance.
    \ref sqr_rdyn_destroy - Clears the ring buffer, delete all elements and frees memory. 
    \ref sqr_rdyn_set - Adds a new element to the ring buffer. Expands the buffer until the number of elements reaches the maximum size.
    \ref sqr_rdyn_get - Get the value and delete the element from the ring buffer.
    \ref sqr_rdyn_peek - Get the value and leave the element in the ring buffer.
    \ref sqr_rdyn_clear - Clears the ring buffer and delete all elements.
    \ref sqr_rdyn_get_size - Return a maximum size of the buffer.
    \ref sqr_rdyn_get_real_size - Return a current size of the buffer.
 </pre>

  \author Ilya Kalabanovsky
*/

typedef void *STACK_handle;
typedef void *QUEUE_handle;
typedef void *RING_handle;
typedef void *DATA_handle;

/**
 * The stack structure. Includes one data pointer and pointer to the next element.
 */
typedef struct _STACK {
    /** Data pointer. */
    DATA_handle data;
    /** Pointer to the next element. */
    struct _STACK *next;
} STACK;

/**
 * The queue structure. Includes one data pointer and pointer to the next element.
 */
typedef struct _QUEUE {
    /** Data pointer. */
    DATA_handle data;
    /** Pointer to the next element. */
    struct _QUEUE *next;
} QUEUE;

/**
 *  A doubly linked list structure used to store data in a ring buffer. 
 *  Includes one data pointer and pointers to the previous and next elements.
 */
typedef struct _DATA_Buffer {
    /** Data pointer. */
    DATA_handle data;
    /** Pointer to the previous element. */
    struct _DATA_Buffer *prev;
    /** Pointer to the next element. */
    struct _DATA_Buffer *next;
} DATA_Buffer;

/**
 * The ring buffer structure. 
 * Includes pointers to the head and tail of the buffer and sizes of buffer.
 */
typedef struct {
    /** Head pointer. */
    DATA_Buffer *head;
    /** Tail pointer. */
    DATA_Buffer *tail;
    /** The maximum buffer size. */
    int size;
    /** Real (current) buffer size. */
    int real_size;
} RING_Buffer;

#ifndef SQRLIB_H
#define SQRLIB_H

    /** \defgroup stack Stack functions
    
    These functions provide methods for working with a stack. 
       
    @{ */
    /** Push an element to the stack.
    \param[in] val Pointer to data pushed onto the stack.
    \param[in] _buf Pointer to the stack.
    */
    void sqr_s_push(DATA_handle val, STACK_handle _buf);
    
    /** Pop an element from the stack.
    \param[in] _buf Pointer to the stack.
    \return The data pointer.
    */
    DATA_handle sqr_s_pop(STACK_handle _buf);
    
    /** @}    end of stack */
    
    /** \defgroup queue Queue functions
    These functions provide methods for working with a queue. 
    @{ */
    
    /** Pushes a new element to the end of queue
    \param[in] val Pointer to data pushed onto the queue.
    \param[in] _buf Pointer to the queue.
    \param[in] _head Pointer to the head of the queue.
    */
    void sqr_q_push_back(DATA_handle val,  QUEUE_handle _buf, QUEUE_handle _head);
    
    /** Pop the element from the top of the queue
    \param[in] _buf Pointer to the queue.
    \return The data pointer.
    */
    DATA_handle sqr_q_pop_front(QUEUE_handle _buf);
    
    /** @}    end of queue */
        
    /** \defgroup ring Ring buffer functions
    These functions provide methods for working with a ring buffer.
    @{ */
    
    /** Create a new ring buffer
    \param[in] buf_size Number of the buffer elements.
    \return Pointer to the ring buffer.
    */
    RING_handle sqr_rdyn_create(const int buf_size);

    /** Destroy the ring buffer
    \param[in] _buf Pointer to the rinng buffer.
    */
    void sqr_rdyn_destroy(RING_handle _buf);

    /** Adds new data to the ring buffer
    \param[in] _buf Pointer to the rinng buffer.
    \param[in] value The new value of data.
    \return 1 if adding is successful and 0 is not.
    */
    int sqr_rdyn_set(RING_handle _buf, DATA_handle value);

    /** Get the value from the ring buffer
    \param[in] _buf Pointer to the rinng buffer.
    \return The data pointer.
    */
    DATA_handle sqr_rdyn_get(RING_handle _buf);

    /** Get the value from the ring buffer
    \param[in] _buf Pointer to the rinng buffer.
    \return The data pointer.
    */
    DATA_handle sqr_rdyn_peek(RING_handle _buf);

    /** Clear the ring buffer
    \param[in] _buf Pointer to the rinng buffer.
    */
    void sqr_rdyn_clear(RING_handle _buf);
    
    /** Get the size of the buffer
    \param[in] _buf Pointer to the rinng buffer.
    \return The buffer size.
    */
    int sqr_rdyn_get_size(RING_handle _buf);
    
    /** Get the current size of the buffer
    \param[in] _buf Pointer to the rinng buffer.
    \return The current buffer size.
    */
    int sqr_rdyn_get_real_size(RING_handle _buf);
    /** @}    end of ring */
#endif

