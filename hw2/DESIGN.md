# Assignment 2 - Functions, arrays, and pointers

## finding the maximum elements of an array

Python Psueudocode of the function `int maximum(int *nums, int len)` which given an array of ints and the length of the array, returns the maximum element of the array.
```
int maximum(int nums, int len)
{
        int max = nums[0]
        for (int i = 0; i<len-1; i++)
        {
                if (nums[i] > max)
                {
                        max = nums[i]
                }
        }
        return max
}
```
Here is a for loop that goes through the nums array, checking if the element in the array is bigger than the current "max" value. The first element is set to the max in order to begin comparing values. The array goes from 0, to len-1 because i starts at 0 instead of 1.

If the value at i in the nums array is bigger than the max value, max is set to the bigger value. Lastly, it returns the maximum value.

## summing all of the positive elements of an array

Python Pseudocode of the function `sum_positive(int *nums, int len)` which given an array returns the sum of all elements in the array that are positive.
```
int sum_positive(int nums, int len)
{
        int sum = 0
        for (int i = 0; i < len-1; i++)
        {
                if (nums[i] > 0)
                {
                        sum += nums[i]
                }
        }
        return sum
}
```
Here is the same for loop above, but the if statement is different. Instead of checking for a maximum, it simply checks if the value at i in the nums array is greater than 0. If so, then the value gets added to the total sum. Then the sum is returned.


## reduce

Python pseudocode for `int reduce(int *nums, int len, int (*f)(int,int), int initial)` which seeks to mimic the behavior of `functools.reduce`.
```
int reduce(*nums, len, f, initial)
{
        for (int i = 0; i < len - 1; i++)
        {
                intial = f(initial, nums[i])
        }
        return initial;
}
```
Again we have the same for loop, but different behavior. Instead the value that is returned by function `f` with the intial and num array value is stored in the intial. After the entire array is looped through, initial is returned in order to complete the reduce function.

## finding the maximum element of an array with `reduce`

Python Pseudocode for `int maximum_with_reduce(int *nums, int size)` function. This mimics `maximum` behavior with only a call to the reduce function with a helper function.
```
int maximum_helper(int x, int y)
{
        if (x > y)
        {
                return x;
        }
        else {
                return y;
        }
}

int maximum_with_reduce(*nums, size)
{
        reduce(nums, len, maximum_helper, initial)
}
```
Here, the helper function `maximum_helper` simply takes two ints and returns the bigger value. Because reduce does a comparison between the previous value stored in `initial` and the next element in the nums array, the maximum value is returned.

## summing all of the positive elements of an array with `reduce`

Python pseudocode for `sum_positive_with_reduce(int *nums, int size)` which mimics the behavior of `sum_positive` in one line using `reduce` and a helper function.

```
int sum_helper(int x, int y)
{
        int sum = 0;
        if (x > 0 and y > 0) {
                sum = x + y
        }
        return sum;
}

int sum_positive_with_reduce(*nums, int size)
{
        reduce(nums, len, sum_helper, initial)
}
```
This is very similar to the `maximum` task, but the helper function sums the two values if they are both positive.

## counting the negative numbers in an array with `reduce`

`int count_negative_with_reduce(int *nums, int size` Python Pseudocode which uses `reduce` to count the negative numbers in an array.

```
int count_helper(int count, int y)
{
        int count = 0;
        if (y < 0)
        {
                count++;
        }
        return count;
}

int count_negative_with_reduce(*nums, int size)
{
        reduce(nums, size, count_helper, initial)
}
```
