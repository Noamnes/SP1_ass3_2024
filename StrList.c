
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"


// Node & List Data Structures
typedef struct _node {
	char* data;
	struct _node* next;
} Node;


struct _StrList {
	Node* head;
	size_t size;
};

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc()
{
	StrList* strList = malloc(sizeof(Node));
	strList->head = NULL;
	strList->size = 0;
	return strList;
}
/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* pStrList)
{
	StrList_free2(pStrList, 1);
}

void StrList_free2(StrList* pStrList, int freeListItself)
{
	if (pStrList == NULL)
		return;

	Node* curNode = pStrList->head;
	Node* nextNode;
	while (curNode != NULL)
	{
		nextNode = curNode->next;
		free(curNode->data);
		free(curNode);
		curNode = nextNode;
	}

	if (freeListItself == 1)
		free(pStrList);
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* pStrList)
{
	return pStrList->size;
}

/*
  Inserts an element in the end of the StrList.
 [str="abc"] -> null, LL size=1

 [str="abc"] -> [str="def"] -> [str="noam"]->null, LL size=3
 */

void StrList_insertLast(StrList* pStrList,
	const char* data)
{
	Node* pNewStrNode = (Node*)malloc(sizeof(Node));
	pNewStrNode->next = NULL;
	pNewStrNode->data = malloc(strlen(data) + 1);
	strcpy(pNewStrNode->data, data);

	if (pStrList->head == NULL)
	{
		pStrList->head = pNewStrNode;
	}
	else
	{
		// find last node 
		Node* pCurNode = pStrList->head;
		while (pCurNode->next != NULL)
		{
			pCurNode = pCurNode->next;
		}
		pCurNode->next = pNewStrNode;
	}
	pStrList->size++;
}

/*
* Inserts an element at given index
"ab"->"b"->"a"->"c", data="d", index=5
"ab"->"b"->"d"->"a"->"c",

"ab"->"b"->"c", data="d", index=0
new node "ab"
head "d"
insert new node after head , before 2nd node
"d"->"ab"->"b"->"c"

"null", data="d", index=0
"d"
*/
void StrList_insertAt(StrList* pStrList, const char* data, int index)
{
	if (index < 0 || index > (int)(pStrList->size))
		return;

	Node* pNewStrNode = (Node*)malloc(sizeof(Node));
	pNewStrNode->next = NULL;
	pNewStrNode->data = malloc(strlen(data) + 1);
	strcpy(pNewStrNode->data, data);

	Node* prevNode = NULL;
	Node* curNode = pStrList->head;
	int curNodeInd = 0;

	// "ab"->"b"->"a"->"c", data="d", index=2
	// "ab"->"b"->"d"->"a"->"c"

	// "ab"->"b"->"a"->"c", data="d", index=0
	// "d"->"ab"->"b"->"a"->"c"
	while (curNode != NULL && curNodeInd != index)
	{
		prevNode = curNode;
		curNode = curNode->next;
		curNodeInd++;
	}

	if (prevNode == NULL)
	{
		pNewStrNode->next = pStrList->head;
		pStrList->head = pNewStrNode;
	}
	else
	{
		prevNode->next = pNewStrNode;
		pNewStrNode->next = curNode;
	}

	pStrList->size++;

}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* pStrlist)
{
	return pStrlist->head->data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* pStrList)
{
	if (pStrList == NULL){
		printf("\n");
		return;
	}
	
	Node* curNode = pStrList->head;
	
	while (curNode != NULL)
	{
		if(curNode==pStrList->head){
			printf("%s",curNode->data);
		}else{
			printf(" %s", curNode->data);
		}
		curNode = curNode->next;
	}
	printf("\n");
}

/*
 Prints the word at the given index to the standard output.
 "ab"->"b"->"a"->"c", index=2
*/
void StrList_printAt(const StrList* pStrlist, int index)
{
	if (index < 0 || index >= (int)(pStrlist->size))
		return;

	Node* curNode = pStrlist->head;
	int curNodeInd = 0;
	while (curNode != NULL && curNodeInd != index)
	{
		curNode = curNode->next;
		curNodeInd++;
	}
	printf("%s\n", curNode->data);
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* pStrlist)
{
	Node* curNode = pStrlist->head;
	int listTotalChars = 0;
	while (curNode != NULL)
	{
		listTotalChars += strlen(curNode->data);
		curNode = curNode->next;
	}
	return listTotalChars;
}

/*
Given a string, return the number of times it exists in the list.
"ab"->"b"->"a"->"a", data="a"
*/
int StrList_count(StrList* pStrList, const char* data)
{
	Node* curNode = pStrList->head;
	int numStringsEqData = 0;
	while (curNode != NULL)
	{
		if (strcmp(curNode->data, data) == 0)
			numStringsEqData++;
		curNode = curNode->next;
	}
	return numStringsEqData;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
		"a", "b", "a", "c", data="a"
		"b", "c"

		"a", "b", "a", "a", data="a"
		"b",
		*/
void StrList_remove(StrList* pStrList, const char* data)
{
	if (pStrList->head == NULL)
		return;

	Node* prevNode = pStrList->head;
	while (prevNode != NULL)
	{
		if (strcmp(prevNode->data, data) == 0 && prevNode == pStrList->head)
		{
			Node* secondNode = pStrList->head->next;
			free(pStrList->head->data);
			free(pStrList->head);
			pStrList->head = secondNode;
			prevNode = secondNode;
			pStrList->size--;
		}
		else if (prevNode->next != NULL && strcmp(prevNode->next->data, data) == 0)
		{
			Node* delNext = prevNode->next->next;
			free(prevNode->next->data);
			free(prevNode->next);
			prevNode->next = delNext;
			prevNode = prevNode->next;
			pStrList->size--;
		}
		else
			prevNode = prevNode->next;
	}
}

/*
	Given an index and a list, remove the string at that index.
	"a", "b", "c", "d", index=2
	"a", "b", "d",

	"a", "b", "c", "d", index=0
	"b", "c", "d",
*/
void StrList_removeAt(StrList* pStrList, int index)
{
	if (index < 0 || index >= (int)(pStrList->size))
		return;

	Node* prevNode = NULL;
	Node* curNode = pStrList->head;
	int curNodeInd = 0;
	while (curNode != NULL && curNodeInd != index)
	{
		prevNode = curNode;
		curNode = curNode->next;
		curNodeInd++;
	}

	if (prevNode == NULL)
	{
		/*
			"a", "b", "c", "d", index=0
			 "b", "c", "d",
		*/
		Node* secondNode = pStrList->head->next;
		free(pStrList->head->data);
		free(pStrList->head);
		pStrList->head = secondNode;
	}
	else
	{
		/*
		"a", "b", "c", "d", index=2
		"a", "b", "d",
		*/
		prevNode->next = curNode->next;
		free(curNode->data);
		free(curNode);
	}
	pStrList->size--;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 "a", "b", "c", "d"
 "a", "b", "c",
 */
int StrList_isEqual(const StrList* pStrlist1, const StrList* pStrlist2)
{
	Node* curNode1 = pStrlist1->head;
	Node* curNode2 = pStrlist2->head;
	while (curNode1 != NULL && curNode2 != NULL)
	{
		if (strcmp(curNode1->data, curNode2->data) != 0)
			return 0;

		curNode1 = curNode1->next;
		curNode2 = curNode2->next;
	}
	return (curNode1 == NULL && curNode2 == NULL) ? 1 : 0;
}

/*
 * Clones the given StrList.
 * It's the user responsibility to free it with StrList_free.
 *  "a", "b", "c", "d"
 */
StrList* StrList_clone(const StrList* pStrlist)
{
	StrList* retList = StrList_alloc();
	retList->size = pStrlist->size;
	Node* curNode = pStrlist->head;
	while (curNode != NULL)
	{
		StrList_insertLast(retList, curNode->data);
		curNode = curNode->next;
	}

	return retList;
}

StrList* StrList_clone2(const StrList* pStrlist)
{
	StrList* retList = StrList_alloc();
	retList->size = pStrlist->size;
	Node* retListLastNode = NULL;
	Node* curNode = pStrlist->head;

	while (curNode != NULL)
	{
		Node* pNewStrNode = (Node*)malloc(sizeof(Node));
		pNewStrNode->next = NULL;
		pNewStrNode->data = malloc(strlen(curNode->data) + 1);
		strcpy(pNewStrNode->data, curNode->data);
		if (retList->head == NULL)
		{
			retList->head = pNewStrNode;
			retListLastNode = pNewStrNode;
		}
		else
		{
			retListLastNode->next = pNewStrNode;
			retListLastNode = pNewStrNode;
		}

		curNode = curNode->next;
	}

	return retList;
}

StrList* StrList_clone3(const StrList* pStrlist)
{
	StrList* retList = StrList_alloc();
	retList->size = pStrlist->size;
	Node* curNode = pStrlist->head;
	Node** ppRetListCurNode = &(retList->head);

	while (curNode != NULL)
	{
		Node* pNewStrNode = (Node*)malloc(sizeof(Node));
		pNewStrNode->next = NULL;
		pNewStrNode->data = malloc(strlen(curNode->data) + 1);
		strcpy(pNewStrNode->data, curNode->data);

		*ppRetListCurNode = pNewStrNode;
		ppRetListCurNode = &((*ppRetListCurNode)->next);

		curNode = curNode->next;
	}

	return retList;
}

/*
 * Reverces the given StrList.
 *  "a", "b", "c", "d"
 *  "d", "c", "b", "a"
 */
void StrList_reverse(StrList* pStrList)
{
	if (pStrList->size <= 1)
		return;

	Node* prevNode = NULL;
	Node* curNode = pStrList->head;
	Node* nextNode = NULL;

	while (curNode != NULL)
	{
		nextNode = curNode->next;

		// cur node now points to prev node
		curNode->next = prevNode;

		// prev becomes cur, cur becomes cur's next
		prevNode = curNode;
		curNode = nextNode;
	}
	// list's head is now prev (which at this point is orig list last node).
	pStrList->head = prevNode;
}

/*
 * Sort the given list in lexicographical order
 "6", "3", "1", "0", "2", "7"
 "3", "6", "1", "0", "2", "7"
 "1" "3", "6" "0", "2", "7"
 "0" "1" "3", "6", "2", "7", "6"
 "0" "1" "2" "3", "6", "7", "8"
 */
void StrList_sort(StrList* pStrList)
{
	StrList* retList = StrList_alloc();
	Node* curNode = pStrList->head;

	while (curNode != NULL)
	{
		Node* pNewStrNode = (Node*)malloc(sizeof(Node));
		pNewStrNode->next = NULL;
		pNewStrNode->data = malloc(strlen(curNode->data) + 1);
		strcpy(pNewStrNode->data, curNode->data);

		if (retList->head == NULL)
		{
			retList->head = pNewStrNode;
		}
		else
		{

			// 1, 2, 4, 6, 8   insert=7
			// 1, 2, 4, 6, 8   insert=10
			// 1, 2, 4, 6, 8   insert=0
			Node* retListPrevNode = NULL;
			Node* retListCurNode = retList->head;
			while (retListCurNode != NULL &&
				strcmp(retListCurNode->data, pNewStrNode->data) < 0)
			{
				retListPrevNode = retListCurNode;
				retListCurNode = retListCurNode->next;
			}

			if (retListPrevNode == NULL)
			{
				pNewStrNode->next = retList->head;
				retList->head = pNewStrNode;
			}
			else
			{
				retListPrevNode->next = pNewStrNode;
				pNewStrNode->next = retListCurNode;
			}
		}

		curNode = curNode->next;
	}

	StrList_free2(pStrList, 0);
	pStrList->head = retList->head;
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 * "a", "bb", "bd", "be"
 */
int StrList_isSorted(StrList* pStrList)
{
	if (pStrList->size <= 1)
		return 1;

	Node* curNode = pStrList->head;
	while (curNode->next != NULL)
	{
		if (strcmp(curNode->data, curNode->next->data) > 0)
			return 0;

		curNode = curNode->next;
	}

	return 1;
}

