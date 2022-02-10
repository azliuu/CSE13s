# CSE 13s, Winter 2022 -- Midterm Exam

  * name: Alex Liu
  * email: alzhliu@ucsc.edu

*I understand that getting help from a classmate or an external source would
be a violation of academic integrity. So I did all of this work myself.*
signed: Alex Liu


**HOWTO do this midterm** -- this is a take-home exam, to be done by just you,
with your notes, with the reading materials, and with your ability to read man
pages and search the web. Do not consult with other students, and do not ask
people other than the course staff for help!

The midterm is due in 24 hours (+ accommodations), and turned in the same way
that we turn in homeworks. You must check in your materials into your
course git repository *and* upload the relevant commit ID on Canvas by then.
For most students, this is due at *1:20pm on Thursday 10 February 2022*.

So make sure you check in *at least* these files into a directory called
`midterm` in your git repository:
  * your completed `MIDTERM.md` (ie, this file, filled out)
  * your completed `midterm.c`
  * your `Makefile` for compiling the code -- make sure to turn on the strict
    compiler flags before turning in.

For short answer questions, write your response in this file. For the
programming problems, write a short explanation of what your code does (and *why
it does it!*) in this file, and complete the program in `midterm.c`.

## problem 1

Write a function that returns the first *n* Fibonacci numbers, in a dynamically
allocated array of type `long long`. Recall that the sequence goes 1, 1, 2, 3,
5, 8...

Should this be done iteratively or recursively?

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)
```
dynamically allocate an array of long long * type and n size
create an output variable of long long * type

loop until the value of n
if it is the first or second value in the fibonacci sequence
        set output to 1
otherwise, set output equal to recursive fibonacci sequence with the previous value and the value before the previous.

set the array at value i to the output

end of for loop

return the array
```

The pseudocode here is based upon the given fibonacci sequence file in the class demos repository. There is some complexity in handling how to handle the 0th and 1st values of n given the recursive calls. If n is 0 or 1, the value of output is set equal to one in order to stay within our bounds.


## problem 2

[Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) is a simple (but
relatively inefficient) sorting algorithm that works by comparing elements in an
array and swapping them if they are in the incorrect order.

The pseudocode looks like:

* keep doing this...
  * for every element x of my input array
    * for every *other* element y of my input array
      * if x should go before y but does not, swap x and y's position in the
        array
* stop if I did not perform any swaps

Imagine that we are working at an online shoe retailer, and we want to sort our
customers by their shoe size.

Implement a function for bubble sorting procedure that sorts customers by shoe
size, ascending. Smallest shoe sizes should go first, larger shoe sizes later.

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)
```
create a ShoeCustomer *temp variable
create a swapped bool
use a do/while loop while swapped boolean is false
loop from 1 to greater than or equal to number of customers minus 1
if the previous customers shoe size is greater than the current customers shoe size
        set the temp variables shoe size, customer id, and num purchases equal to the previous customers corresponding shoe size, customer id, and num purchases.
        set the previous customers shoe sie, customer id, and num purchases each equal to the current customers shoe size, customer id, and num purchases.
        set the current customers shoe size, customer id, and num purchases equal to the temps shoe size, customer id, and num purchases.
        set swapped equal to true

        outside the if and for loop, decrement the number of customers
        end of do/while loop
```
I based my solution on the given pseudocode under the "Optimized Bubble Sort" section of the bubble sort wikipedia page. I then applied a swap by creating a temp ShoeCustomer to store all the data while swapping the previous and current customers. And then I followed the do-while structure to successfully complete the task.

## problem 3

Recall in homework 2, we wrote a function `reduce`, which took a collection of
numbers and reduced it down to a single number, essentially a summary of that
collection.

Here we will write a version of the companion function to *reduce*, which is
called [*map*](https://en.wikipedia.org/wiki/Map_(higher-order_function)). Map
takes a function and applies that function to each element in the collection,
and returns a collection of the same shape.

In this version, we will take in a linked list of floating point numbers (see
`LLfloat` in the code) and return a *new* linked list of floating point numbers,
of the same length, where each element of the new list is the result of calling
the specified function on the corresponding number in the input list.

For example, if your input list consisted of:
`[0, 1, 2, 3]`

And your specified function computed the square of the input number, then your
function would return a new linked list (you'll have to allocate it with
`malloc` or `calloc` !) containing:
`[0, 1, 4, 9]`

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)
```
create a count variable to keep track of the length of the given linked list `*numbers`
create a new `LLfloat *variable` named current
while current not at the end of the list
        increment count by 1
        set current equal to the next item
create a new `LLfloat *variable` named output
dynamically allocate the output array of count size
loop from zero to count
    set the value of the ith output to the output of function(value of the ith numbers)
free output
```
The issue is to first understand the length of the given linked list in order to find out how to allocate a new linked list, and what the stop condition for the for loop should be. So in order to achieve that, we create a count variable and an LLfloat that is equal to the given numbers LLfloat. While it is not at the end of the linked list it continues incrementing a count. Afterwards we can create an LLfloat output variable linked list that is dynamically allocated with the count size. Lastly we loop from zeror to the count and set the ith value of output equal to the output after a function is called on the ith value of numbers. Then we return the new linked list
```

## problem 4

Imagine that we are building a calendar system, and we want to find out when a
group of different users are available for a meeting. Here we will represent a
user's availability with a bit vector in the form of an `unsigned long` -- we
get 64 different appointment slots during a week, and a user can be either
*available* (the bit is set to 1) or *unavailable* (the bit is set to 0) for
that appointment slot.

Write a function that takes an array (ie, a pointer to an array) of these
bit-vector calendars, a number of users (ie, the size of the array) and returns
a single `unsigned long` where each bit in the unsigned long is set to 1 if *all
users* are available at that time.

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)
```

```
## problem 5 (short answer)

Consider the following code snippet:
```
float f[10];
float *p;
p = f;
p++;
```

Say that you found out that the array `f` was at memory address `0xC0FF33`. In
your own words, what did we do on the line `p++`, and what is the value of `p`
after this code runs? What is the value of `p + 5`? (give these as hexidecimal
numbers)

In the line p++ we incremented the hex value of p by the size of a float which is 8 bits. By converting 8 bits hex value we get 0x8. Then by adding 0x8 + 0x0C0FF33 you get `p = 0xC0FF3B`. p + 5 is adding 5 bytes, or 40 bits. If we convert 40 bits to hex we get 0x28. Adding 0xC0FF3B + 0x28 we get `p + 5 = 0xC0FF63`.


## problem 6 (short answer)
In math, how many real numbers are there? Comparatively, in a computer, how many
floating point numbers (C type `float`) are there? How could you find out how
many floating point numbers there are, for sure?

YOUR ANSWER HERE
I formulated my answer based on [this article by James Howard](https://jameshoward.us/2015/09/09/how-many-floating-point-numbers-are-there/).
From a mathematical perspective there are infinitely many real numbers. Comparatively in a computer, there are about 3.402 * 10^(38) floating point numbers. In order to find out how many floating point numbers there are for sure, you can break down each part of a 32 bit float. 23/32 bits is the mantissa which equates the significant digits in the base number. The first bit is a signed bit in a float. Lastly the final part of a float is the exponent that consists of 8 bits. Excluding the signed bit for the exponent portion values range from (-126, 127). From (-126, 0) there are 2130706432 possible bit combinations. From (1, 127) there are 2130706432 possible bit combinations. With some exceptions for special floating point numbers (infinity, non-number, and others we arrive at 3.402 * 10^(38) floating point numbers.
