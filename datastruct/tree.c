/*
Study BinTree 
Jerry 20150808
*/

#inlcue<stdio.h>

typedef struct BinTree_t
{
	ElementType data;
	BinTree* Left;
	BinTree* Right;
} BinTree


void PreOrderTravelsal(BinTree pBT)
{
	if (pBT)
	{
		printf("%d", pBT->Data);
		PreOrderTravelsal(pBT->Left);
		PreOrderTravelsal(pBT->Right);
		
	}
}


void InOrderTravelsal(BinTree pBT)
{
	if (pBT)
	{
		printf("%d", pBT->Data);
		PreOrderTravelsal(pBT->Left);
		PreOrderTravelsal(pBT->Right);
		
	}
}




void PostOrderTravelsal(BinTree pBT)
{
	if (pBT)
	{
		PreOrderTravelsal(pBT->Left);
		printf("%d", pBT->Data);
		PreOrderTravelsal(pBT->Right);
		
	}
}

Position Find(ElementType FindValue, BinTree pBT)
{
	if (!pBT)
	{
		return NULL;
	}
	
	while (pBT)
	{
		if (FindValue == pBT->Data)
		{
			return pBT;
		}
		else if (FindValue > pBT->Data)
		{
			pBT = pBT->Right;
		}
		else
		{
			pBT = pBT->Left;
		}
	}
}

Position FindMin(BinTree pBT)
{
	if (!pBT)
	{
		return NULL;
	}
	
	while (pBT->Left != NULL)
	{
		pBT = pBT->Left;
	}
	return pBT;
}


Position FindMax(BinTree pBT)
{
	if (!pBT)
	{
		return NULL;
	}
	
	while (pBT->Right != NULL)
	{
		pBT = pBT->Right;
	}
	
	return pBT;

}
