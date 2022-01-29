
/*
 * All of your code goes in here. You need to finish these functions.
 */

#include "num_arrays.h"
#include <limits.h>

int maximum(int *nums, int len) {
  int max = nums[0];
  for (int i = 0; i < len; i++) {
    if (max < nums[i]) {
      max = nums[i];
    }
  }
  return max;
}

int sum_positive(int *nums, int len) {
  int sum = 0;
  for (int i = 0; i < len; i++) {
    if (nums[i] > 0) {
      sum += nums[i];
    }
  }
  return sum;
}

int reduce(int *nums, int len, int (*f)(int, int), int initial) {
  for (int i = 0; i < len; i++) {
    initial = f(initial, nums[i]);
  }
  return initial;
}

int max_helper(int x, int y) {
  if (x > y) {
    return x;
  }
  return y;
}

int maximum_with_reduce(int *nums, int size) {
  return reduce(nums, size, max_helper, INT_MIN);
}

int sum_helper(int x, int y) {
  if (y > 0) {
    x += y;
  }
  return x;
}

int sum_positive_with_reduce(int *nums, int size) {
  return reduce(nums, size, sum_helper, 0);
}

int count_helper(int x, int y) {
  if (y < 0) {
    x += 1;
  }
  return x;
}

int count_negative_with_reduce(int *nums, int size) {
  return reduce(nums, size, count_helper, 0);
}
