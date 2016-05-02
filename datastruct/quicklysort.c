//
//  main.c
//  sort
//
//  Created by kywoo on 16/4/29.
//  Copyright © 2016年 jerry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define VALUE_TYPE int
#define  MAX_VALUE_LENGTH 50

int  QuickSort(VALUE_TYPE *SorrtArry, int left, int right)
{
    VALUE_TYPE DivideValue = SorrtArry[left];
    VALUE_TYPE Divide_left = left;
    VALUE_TYPE Divide_right = right;
    if (left > right) {
        
        return 0;
    }
    
    
    while (Divide_left != Divide_right)
    {
        while (SorrtArry[Divide_right] <= DivideValue && Divide_left < Divide_right)
        {
            Divide_right --;
        }
        
        while (SorrtArry[Divide_left] >= DivideValue && Divide_left < Divide_right)
        {
            Divide_left ++;
        }
        
        if (Divide_left < Divide_right)
        {
            VALUE_TYPE temp = SorrtArry[Divide_right];
            SorrtArry[Divide_right] = SorrtArry[Divide_left];
            SorrtArry[Divide_left] = temp;
            
        }
   
        
    }
 
    SorrtArry[left] = SorrtArry[Divide_left];
    SorrtArry[Divide_left] = DivideValue;
    printf("over%d   ",SorrtArry[Divide_right]);
    
    QuickSort(SorrtArry, left, Divide_left - 1);
    QuickSort(SorrtArry, Divide_right + 1, right);
    return 0;
    
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    VALUE_TYPE arry[10]={6,1,2,7,9,3,4,5,10,8};
    QuickSort(arry, 0, 9);
    for (int i = 0; i < 10; i++)
        printf("%d \n",arry[i]);
    
    return 0;
}
