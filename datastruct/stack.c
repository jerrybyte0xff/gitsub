//
//  main.c
//  Stack
//
//  Created by kywoo on 16/4/27.
//  Copyright © 2016年 jerry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 50
#define ELEMENT_TYPE int

typedef struct _STACK
{
    ELEMENT_TYPE stack[STACK_MAX_SIZE];
    int top;
    
}STACK;

STACK *StackInit()
{

    STACK *pstack =  (STACK*)malloc(sizeof(STACK));
    pstack->top = -1;
    return pstack;
}


int StackPush(STACK * pstack, ELEMENT_TYPE value)
{
    if (pstack->top == STACK_MAX_SIZE - 1)
    {
        printf("stack full \n ");
        return -1;
        
    }
    
    pstack->stack[++pstack->top] = value;
    return 0;
}

int StackPop(STACK * pstack, ELEMENT_TYPE *value)
{
    if (pstack->top ==  - 1)
    {
        printf("stack null \n ");
        return -1;
        
    }
    
    *value = pstack->stack[(pstack->top)--];
    return 0;

}


int main(int argc, const char * argv[])
{
    // insert code here...
    int temp = 0;
    printf("Hello, World!\n");
    
    STACK *pStack = StackInit();
    
    StackPush(pStack, 1);
    StackPush(pStack, 2);
    StackPush(pStack, 3);
    
    StackPop(pStack, &temp);
    printf("%d \n",temp);
    StackPop(pStack, &temp);
    printf("%d \n",temp);

    
    
    
    
    
    return 0;
}
