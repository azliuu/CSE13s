#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack_calculator.h"

// Allocate a new Stack struct and return a pointer to it.
Stack *stack_create(void) {
  // this one is complete, no need to change it!
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {
  // your code here
  Node *newtop = (Node *)calloc(1, sizeof(Node));
  if (newtop == NULL) {
    return false;
  }
  newtop->item = item;
  newtop->next = s->top;
  s->top = newtop;
  //free(newtop);
  return true;
}

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {
  // your code here
  if (s->top == NULL || s->top == 0) {
    return false;
  }


  float result = s->top->item.value;
  output->value = result;

  Node *delete_this = s->top;
  s->top = s->top->next;

  free(delete_this);


  return true;
}

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
  // your code here
    if (s == NULL || s->top == NULL) {
    return true;
  }
  return false;
}

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {
  // your code here
  Node *child = (*s)->top;
  while (child != NULL) {
      free(&child);
  }
  free(*s);
  s = NULL;
 // if (*s && (*s)->top->item) {
 //     free ((*s)->top->item);
 //     free (*s);
 //     *s = NULL;
 // }
  return;
}

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {
  // your code here
  CalculatorItem x;
  CalculatorItem y;
  CalculatorItem z;
  CalculatorItem result;
  bool success;
  int values = 0;
  if (item.type == NUMBER) {
      stack_push(s, item);
  }
  if (item.type == ADD) {
      stack_pop(s, &z);
          x.value = z.value;
          stack_pop(s, &z);
              y.value = z.value;
              result.value = x.value + y.value;
      //stack_pop(s, &z);
      //x.value = z.value;

      //stack_pop(s, &z);
      //y.value = z.value;
      //result.value = x.value + y.value;

      //}
      stack_push(s, result);
  }
  if (item.type == SUBTRACT) {
      stack_pop(s, &z);
      x.value = z.value;
      stack_pop(s, &z);
      y.value = z.value;
      result.value = y.value - x.value;
      //if (y.type != NUMBER) {
      //    return false;
     // }
      stack_push(s, result);
  }
  if (item.type == MULTIPLY) {
      stack_pop(s, &z);
      x.value = z.value;
      stack_pop(s, &z);
      y.value = z.value;
      result.value = x.value * y.value;
      //if (y.type != NUMBER) {
      //    return false;
      //}
      stack_push(s, result);
  }
  if (item.type == DIVIDE) {
      stack_pop(s, &z);
      x.value = z.value;
      stack_pop(s, &z);
      y.value = z.value;
      result.value = y.value / x.value;
      if (x.value == 0 || y.type != NUMBER)
      //{
      //    return false;
      //}
      stack_push(s, result);
  }
  return true;
}
