#Assignment 4 - graphs, queues, and search

## Enqueue
 Pseudocode for the enqueue function based on class lecture given on 2/4/22.
```
create a new node with value equal to the given path
if  the queue is empty, return the new node.

otherwise, create a new LLPath named cur equal to the queue
while not at the end of the queue cur
        set cur equal to the next value of cur
set the next value of cur equal to the new node

return the queue
```
Enqueue adds a new node to the end of a queue. If the queue is empty, the new node is returned as it is the only element of the queue. Otherwise, the queue must be traversed to ensure that the new node is added at the end of the queue. This is done with the while loop until NULL as queues are NULL terminated.

## Dequeue
Pseudocode for the dequeue function based on class lecutre given on 2/4/22.
```
If the queue is empty, return false.
Set the return value equal to the value of the queue.
Create a new queue that equals the current queue.
Set the current queue equal to the next value of the queue
free the new queue
return true
```
Dequeue returns the top value of the queue, deceases the queue by one, and then frees the memory. If the queue is empty the function returns false as there is nothing to take off of the queue.

## BFS
Pseudocode for the BFS search algorithm based on the class lecture given on 2/4/22.
```
keep track of a set of paths that have been visited
keep a queue of the paths that we want to visit
while there are more paths to visit
        get the next place to visit
        see if it is where we want to go
        if not, enqueue all of it's neighbors that have not been visited
return false if there are not more paths to visit.
```
This code mimics BFS behavior where a parent node is first checked, then it's children are checked for if they are the location we want.

## DFS
Pseudocode for the DFS search algorithm
```
Mimic BFS behavior but with a stack instead of a queue.
Instead of using enqueue/dequeue functions implement stack push and stack pop logic
```
Because of the orientation of a stack, DFS uses the same logic as BFS but with a stack instead of queue structure.
