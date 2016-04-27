//
//  list.c
//  List
//
//  Created by jerry on 16/4/18.
//  Copyright c 2016年 jerry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*  element value tpye */
#define ELEMENT_TYPE int

typedef struct _LIST
{
    ELEMENT_TYPE value;
    struct _LIST * Next;
    
}LIST;



/* Get The length Of the List  */
int List_GetLength(LIST *ListHeader)
{
    int i_ListLength = 0;
    LIST *List = ListHeader;
    
    while (NULL != List)
    {
        i_ListLength++;
        List = List->Next;
        
    }
    return i_ListLength;
}

/* Find The Element Of The List From The number (The First element`s number is 0)  */
LIST *List_FindAccordingNumber (LIST *ListHeader, int number)
{
    LIST *list = ListHeader;
    for (int i = 0; i < number; i++)
    {
        if (NULL == list)
        {
            return NULL;
        }
        list = list->Next;
    }
    return list;
}

/* Find The Element Of The List From The Value (The First element`s number is 0)  */
LIST *List_FindAccordingValue (LIST *ListHeader, ELEMENT_TYPE Value)
{
    LIST *list = ListHeader;
    while (list->value != Value && list != NULL)
    {
        list = list->Next;
        
    }
    return list;
    
}

/*
  insert the element  according the number
 */

LIST *List_Insert(LIST *ListHeader, int number, ELEMENT_TYPE Value)
{
    LIST * ListBefore = NULL;
    LIST  *InsertObject = NULL;
	
    if (0 == number)
    {
    	printf("insert number error (0 is not allowed)\n");
    	return NULL;
    }
    else
    {
    	InsertObject = (LIST*)malloc(sizeof(LIST));
    	InsertObject->value = Value;
        ListBefore = List_FindAccordingNumber(ListHeader, number - 1);
    
        if (NULL == ListBefore)
        {
            printf("intsert number error \n");
            return NULL;
        
        }

        ListBefore->Next = InsertObject;
        InsertObject->Next = ListBefore->Next;
    }
 
    
    
    return InsertObject;
    
    
    
}

/*
  delete the element  according the number
 */
LIST *List_Delete(LIST *ListHeader, int number)
{
    LIST * ListBefore = NULL;
    
    if (NULL == ListHeader)
    {
        printf("ListHeader Error \n");
        return NULL;
    }
    
    
    if (0 == number)
    {
        
        free(ListHeader);
    }
    else
    {
        ListBefore = List_FindAccordingNumber(ListHeader, number - 1);
        
        if (NULL == ListBefore ||  NULL == ListBefore->Next)
        {
            printf("intsert number error \n");
            return NULL;
            
        }
        
        ListBefore->Next = ListBefore->Next->Next;
        free(ListBefore->Next);
    }

    
    
    return ListBefore;
    
    
    
}

/* Main test */

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    LIST Listheader ={0,NULL};
    LIST *list = &Listheader;
    
    List_Insert(list, 1, 11);


    List_Insert(list, 2, 22);
 
    List_Insert(list, 3, 33);

    List_Insert(list, 4, 44);
    printf("0:%d",list->value);

    printf("2:%d",List_FindAccordingNumber(list, 2)->value);
    
    
    
    
    
    
    return 0;
}
