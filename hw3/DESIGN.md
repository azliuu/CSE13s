# Assignment 3 - dynamic memory, linked lists and stacks

## Implementing the Stack

This section has pseudocode for the implementing the stack portion of the assignment.

```
bool stack_push(Stack *s, CalculatorItem item) {
        Create a new node "newtop" with dynamic memory allocation
        if memory allocation fails, return false
        set the new nodes's item equal to item
        set the new node's next equal to top
        stack push succeeds
}
```
Stack push adds an item to the stack. Then it sets the top to the next value in the stack. Returns false if memory allocations fails.
```
bool stack_pop(Stack *s, CalculatorItem *output) {
        if s is NULL or the top of the stack is null, return false
        store the top of the stacks item into an float variable called result
        set the output's value equal to result
        Create a new node pointer equal to the top of the stack
        set the top of stack to the next value of the top in the stack
        free the new node you created
        return true
}
```
Pops a value off of the stack, and sets output equal to the value in the stack. If the stack is empty or memory allocation fails, the function returns false.
```
bool stack_empty(Stack *s) {
        If the top of the stack is NULL or the stack is NULL, then the stack is empty
        else, the stack is not empty
}
```
Checks if the top of the stack or the stack is null, then returns true. Else returns false
```
void stack_delete(Stack **s) {
        create a new node equal to the top of the stack pointer
        while child does not equal null, free the address of child
        free stack pointer
        set the stack to null
        return
}
```
Frees the stack, and all of its nodes
```
bool stack_compute_step(Stack *s, CalculatorItem item) {
        Create 4 variables of CalculatorItem type that indicate two calculator inputs, the result of the calculations, and the final pushed result to the stack.
        If the items type is a number, then push that value to the stack
        If the items type is add, then pop two numbers from the stack.
            If after popping one value the stack is empty, return false to indicate error.
            Store the popped values into two different variables
            Add two variables together into a result variable
            Push the result to the stack.
        If the items type is subtract, then pop two numbers from the stack
            If after popping one value the stack is empty, return false to indicate error.
            Store the popped values into two different variables
            Subtract the second popped value then the first number
            And store the result into the result variable
            Push the result to the stack.
        If the items type is multiply, pop two numbers from the stack
            If after popping one value the stack is empty, return false to indicate error.
            Store the popped values into two different variables
            Multiply them and store the result into a result variable
            Push the result to the stack.
        If the items type is divide, pop two numbers from the stack
            If after popping one value the stack is empty, return false to indicate error.
            Store the popped vcalues into two different variables (denominator, then numerator)
            If the denominator equals zero, return false
            divide the second popped value by the first one and store the result into a result variable
            Push the result to the stack.
}
```
Does computatations following the RPN calculator format using the stack. Using 4 variables, the function successfully completes mathematical calcalations and pushes the result to the stack. However, it checks for 2 main erorr cases: if the user inputs only only one number the function returns false. If the user tries to divide by zero, the function also will return false.
