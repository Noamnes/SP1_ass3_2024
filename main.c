#include <stdio.h>
#include "StrList.h"

void getStrOfAnyLength(char** pStr);

void AddStr2LLFromUser(StrList* listHead)
{
	int wordsNum2Input = 0;
	scanf("%d", &wordsNum2Input); // adds \n stdin
	getchar(); // read \n from stdin
	for (int i = 0; i < wordsNum2Input; i++)
	{	
		char* dStr;
		getStrOfAnyLength(&dStr);

		StrList_insertLast(listHead, dStr);
	}
}
/* getStrOfAnyLength get an addr of a (char*) and puts there the string the user puts
*/
// assumes the input buffer is empty (without \n!!)
void getStrOfAnyLength(char** pStr){
		// word max len unknown
		char ch;
		scanf("%c",&ch);
		char* dStr = NULL;
		int dStrSize = 0;

		// ch='a', ['a', ' '], dStrSize=1
		// ch='m', ['a', 'm', ' '], dStrSize=2
		// ch='i', ['a', 'm', 'i', ' '], dStrSize=3
		// ch='t', ['a', 'm', 'i', 't', ' '], dStrSize=4
		// ch='t', ['a', 'm', 'i', 't', '\0'], dStrSize=4
		while (ch != ' ' && ch != '\n')
		{
			dStr = realloc(dStr, dStrSize + 2);
			dStr[dStrSize] = ch;
			dStrSize++;
			ch = getchar();
		}

		if (dStrSize != 0)
		{
			dStr[dStrSize] = '\0';
		}
		else
		{
			dStr = realloc(dStr, 1);
			dStr[0] = '\0';
		}

		*pStr = dStr;
}

void writeInputBufferToFile() {
    FILE *file = fopen("input buffer contents.txt", "w"); // Open the file for writing
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        fputc(ch, file); // Write the character to the file
    }
    
	fclose(file); // Close the file
    printf("Input buffer contents have been written to 'input buffer contents.txt'.\n");
}

int main()
{
	
	// int number;
    // printf("Enter a number: ");
    // scanf("%d", &number); // Assume the user enters a number and then presses Enter

    // // Call the function to write remaining input buffer contents to the file
    // writeInputBufferToFile();


	StrList* listHead = StrList_alloc();

	int option;
	int index; // used to put in some index in certian user-options
	char* str; // used to put a Str in certian user-options
	while(scanf("%d",&option) != 0){
		switch (option){
			case 1:
				AddStr2LLFromUser(listHead);
				break;
			
			case 2:
				scanf("%d",&index); // input \n to the stdin
				getchar(); // get the redundent \n
				getStrOfAnyLength(&str);
				StrList_insertAt(listHead, str, index);
				break;
			
			case 3:
				StrList_print(listHead);
				break;
			
			case 4:
				printf("%ld\n",StrList_size(listHead));
				break;
			
			case 5:
				scanf("%d",&index);
				StrList_printAt(listHead, index);
				break;
			
			case 6:
				printf("%d\n",StrList_printLen(listHead));
				break;

			case 7:
				getchar();
				getStrOfAnyLength(&str);
				printf("%d\n",StrList_count(listHead, str));
				break;

			case 8:
				getchar();
				getStrOfAnyLength(&str);
				StrList_remove(listHead, str);
				break;

			case 9:
				scanf("%d",&index);
				StrList_removeAt(listHead, index);
				break;
			
			case 10:
				StrList_reverse(listHead);
				break;
			
			case 11:
				StrList_free(listHead);
				listHead=NULL;
				break;
			
			case 12:
				StrList_sort(listHead);
				break;

			case 13:
				if(StrList_isSorted(listHead) == 1){
					printf("true\n");
				}else{
					printf("false\n");
				}
				break;
			
			case 0:
				exit(0);
			
			case 100:
				writeInputBufferToFile();
				break;

			default:
				break;
		}
	}
	
}
