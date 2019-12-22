# SQRlib - C library for stack, queue, and ring buffers

The library provides some functions and structures for working with the most popular buffers, such as the stack, queue, and ring buffer.

# Stack
The classic self referential structure Stack buffer includes a data pointer and the "next" pointer.
Functions:

   sqr_s_push - Adds an element with a new value to the stack.
   sqr_s_pop - Get the value and delete element from the stack.

# Queue
The classic self referential structure Queue buffer includes the data, "prev" and the "next" pointer.
Functions:

   sqr_q_push_back - Adds the element with a new value to the queue.
   sqr_q_pop_front - Get the value and delete element from the queue.

# Ring buffer
The dynamically expandable unordered ring buffer with adjustable size.
Functions:

   sqr_rdyn_create - Creates a new ring buffer instance.
   sqr_rdyn_destroy - Clears the ring buffer, delete all elements and frees memory. 
   sqr_rdyn_set - Adds a new element to the ring buffer. Expands the buffer until the number of elements reaches the maximum size.
   sqr_rdyn_get - Get the value and delete the element from the ring buffer.
   sqr_rdyn_peek - Get the value and leave the element in the ring buffer.
   sqr_rdyn_clear - Clears the ring buffer and delete all elements.
   sqr_rdyn_get_size - Return a maximum size of the buffer.
   sqr_rdyn_get_real_size - Return a current size of the buffer.

# Author
Ilya Kalabanovsky
