#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// PROBLEM 1

long long *fibonacci_numbers(int n) {
  // You're going to have to allocate an array, fill it in, and return it.
  // The array should be of length n.
  // Recall the first few entries should be 1, 1, 2, 3, 5, 8, ...
  // Based on the fibonacci_recursive file in the given class examples
  // repository.
  long long *output = NULL;
  long long *fib_array;
  fib_array = (long long *)malloc((sizeof(long long) * n));


  for (int i = 0; i < n; i++) {
    if (n == 0 || n == 1) {
      *output = 1;
    } else {
     *output = *fibonacci_numbers(n - 1) + *fibonacci_numbers(n - 2);
    }

    fib_array[i] = *output;
  }

  return output;
}

// PROBLEM 2

typedef struct {
  int shoe_size;
  int customer_id;
  int num_purchases;
} ShoeCustomer;

void bubble_sort_customers(ShoeCustomer *customers, int n_customers) {
  // Your code here! Make them sorted!
  // Bubble sort algorithm heavily based upon "Optimized Bubble Sort"
  // generalized pseudo under the Bubble Sort wikipedia page
  ShoeCustomer *temp;
  bool swapped;
  do {
    bool swapped = false;
    for (int i = 1; i <= n_customers - 1; i++) {
      if (customers[i - 1].shoe_size > customers[i].shoe_size) {
        temp->shoe_size = customers[i - 1].shoe_size;
        temp->customer_id = customers[i - 1].customer_id;
        temp->num_purchases = customers[i - 1].num_purchases;

        customers[i - 1].shoe_size = customers[i].shoe_size;
        customers[i - 1].customer_id = customers[i].customer_id;
        customers[i - 1].num_purchases = customers[i].num_purchases;

        customers[i].shoe_size = temp->shoe_size;
        customers[i].customer_id = temp->customer_id;
        customers[i].num_purchases = temp->num_purchases;

        swapped = true;
      }
    }
    n_customers -= 1;
  } while (swapped == false);
}

// PROBLEM 3

// A linked list of floating point numbers.
typedef struct LLfloat {
  float val;
  struct LLfloat *next;
} LLfloat;

LLfloat *map_floats(float (*f)(float), LLfloat *numbers) {
  // finish this function.
  // Should it be recursive? It's up to you, but it could be recursive!
  // given inspiration from the "map.c" file in the class demos repository
  int count = 0;
  LLfloat *current = numbers;
  while (current != NULL) {
    count++;
    current = current->next;
  }

  LLfloat *output;
  output = (LLfloat *)malloc((sizeof(LLfloat) * count));
  for (int i = 0; i < count; i++) {
    output[i].val = f(numbers[i].val);
  }

  return output;
}

// PROBLEM 4

unsigned long compute_availability(unsigned long *calendars, int num_users) {
  unsigned long availability = 0;
  int testing_bit = 0;
  while (testing_bit < sizeof(unsigned long)) {
    for (int i = 0; i < num_users; i++) {
      if (calendars[i] & 0x1) {
        availability = (availability | (1 << (testing_bit - 1)));
      } else {
        availability = (availability & (~(1 << (testing_bit - 1))));
      }
      testing_bit++;
      calendars[i] = calendars[i] >> 1;
    }
  }
  return availability;
}
// put examples for testing your functions in the main! You're going to have to
// figure out how to test these.
int main(void) {
  printf("%llu\n", *fibonacci_numbers(6));
  return 0;
}
