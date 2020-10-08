#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_cross(int A[], int mid, int high)
{
    int left_sum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= low; i--)
    {
        sum = sum + A[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            int max_left = i;
        }
    }
    int right_sum = INT_MIN;
    sum = 0;
    for (int j = mid + 1; i <= high; j++)
    {
        sum = sum + A[j];
        if (sum > right_sum)
        {
            right_sum = sum;
            int max_right = j;
        }
    }
    return (max_left, max_right, left_sum + right_sum);
}