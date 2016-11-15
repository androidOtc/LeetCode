/*
*Title: 410. Split Array Largest Sum
*Given an array which consists of non-negative integers and an integer m, 
*you can split the array into m non-empty continuous subarrays. 
*Write an algorithm to minimize the largest sum among these m subarrays.
*Note:
*Given m satisfies the following constraint: 1 ≤ m ≤ length(nums) ≤ 14,000.
*
*Examples:
*
*Input:
*nums = [7,2,5,10,8]
*m = 2
*
*Output:
*18
*
*Explanation:
*There are four ways to split nums into two subarrays.
*The best way is to split it into [7,2,5] and [10,8],
*where the largest sum among the two subarrays is only 18.
*
*Submission Result: Time Limit Exceeded!
*Last executed input:
*[4999,4998,4997,4996,4995,4994,4993,4992,4991,4990,4989,4988,4987,4986,4985,4984,4983,4982,4981,4980,4979,
*4978,4977,4976,......,0]
*m = 500
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_split(int *nums, int numsSize, int m, int expect, int *maxSum)
{
    int index = 0, sum = 0;
    if(numsSize == m)
    {
        for(index = 0; index < numsSize; index++)
        {
            if(*(nums + index) > *maxSum)
                *maxSum = *(nums + index);
        }
        return;
    }
    if(1 == m)
    {
        for(index = 0; index < numsSize; index++)
            sum += *(nums + index);
        if(sum > *maxSum)
            *maxSum = sum;
        return;
    }
    for(index = 0; index < numsSize-m+1; index++)
    {
        sum += *(nums + index);
        if(sum >= expect)
            break;
    }
    int tempMax = *maxSum;
    if(index < numsSize-m+1)
    {
        if(sum > tempMax)
            tempMax = sum;
        do_split(nums + index + 1, numsSize - index - 1, m - 1, expect, &tempMax);
        if(index > 0)
        {
            int tempMax2 = *maxSum;
            sum -= *(nums + index);
            if(sum > tempMax2)
                tempMax2 = sum;
            do_split(nums + index , numsSize - index, m - 1, expect, &tempMax2);
            tempMax = (tempMax2 > tempMax) ? tempMax : tempMax2;
        }
        *maxSum = tempMax;
    }
    else
        do_split(nums + index, numsSize - index, m -1, expect, maxSum);
}

int splitArray(int* nums, int numsSize, int m) {
    if(NULL == nums || numsSize <= 0 || m <= 0 || numsSize < m)
        return -1;
    int index = 0, totalSum = 0;
    int expect = 0, maxSum = 0;
    for(index = 0; index < numsSize; index++)
        totalSum += nums[index];
    expect = totalSum/m;
    do_split(nums, numsSize, m, expect, &maxSum);
    return maxSum;
}
