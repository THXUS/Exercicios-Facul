#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max2(int a, int b)
{
    return (a > b) ? a : b; //operador question mark, equivale a um if else
}

int max3(int a, int b, int c)
{
    return max2(max2(a, b), c);
}

int find_max_cross(int A[], int low, int mid, int high)
{
    int left_sum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= low; i--)
    {
        sum = sum + A[i];
        if (sum > left_sum)
            left_sum = sum;
    }
    int right_sum = INT_MIN;
    sum = 0;
    for (int j = mid + 1; j <= high; j++)
    {
        sum = sum + A[j];
        if (sum > right_sum)
            right_sum = sum;
    }
    return max3(left_sum + right_sum, left_sum, right_sum);
}

int find_max_subarray(int A[], int low, int high)
{
    if (high == low)
        return (low, high, A[low]);
    else
    {
        int mid = (low + high) / 2;
        return max3(find_max_subarray(A, low, mid),
                    find_max_subarray(A, mid + 1, high),
                    find_max_cross(A, low, mid, high));
    }
}

int main()
{
    int *A;
    int n;
    printf("Array size: ");
    scanf("%d", &n);
    A = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        printf("Pos %d: ", i);
        scanf("%d", &A[i]);
    }

    int max_sum = find_max_subarray(A, 0, n - 1);
    printf("Maximum subArray sum is %d", max_sum);
    getchar();
}
