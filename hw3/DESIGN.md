# Assignment 3 - dynamic memory, linked lists and stacks

## Implementing the Stack

This section has pseudocode for the implementing the stack portion of the assignment.

```
bool stack_push(Stack *s, CalculatorItem item) {
        Create a new node "newtop" with dynamic memory allocation
        if memory allocation fails, return false
        set the new nodes's item equal to item
        set the new node's next equal to top
        free the new node's memory
        return true
}
```
Stack push adds an item to the stack. Then it sets the top to the next value in the stack. Returns false if memory allocations fails.
```
bool stack_pop(Stack *s, CalculatorItem *output) {
        if s is NULL or the top of the stack is null, return false
        store the top of the stacks item into an int result
        set pointer output equal to the result
        Create a new node pointer equal to the top of the stack
        set the top of stack to the next value of the top in the stack
        free the new node you created
        return true
}
```
Pops a value off of the stack, and sets output equal to the value in the stack. If the stack is empty or memory allocation fails, the function returns false.
```
bool stack_empty(Stack *s) {
        If the top of the stack is NULL, then return true
        else, return false
        return false
}
```
Checks if the top of the stack is null, then returns true. Else returns false
```
void stack_delete(Stack **s) {
        if there is a pointer s and pointer s items, free items and pointer s
}
```
Frees the stack, and all of its items
```
bool stack_compute_step(Stack *s, CalculatorItem item) {
        If the items type is a number, then push that value to the stack
        If the items type is add, then pop two numbers from the stack, add them together, and push the result to the stack.
        If the items type is subtract, then pop two numbers from the stack, subtract the second number then the first number, and push the result to the stack.
        If the items type is multiply, pop two numbers from the stack, multiply them and push the result to the stack.
        If the items type is divide, pop two numbers from the stack, divide the second popped value by the first one, and push the result to the stack.
}
```
Does computatations following the RPN calculator format using the stack.
