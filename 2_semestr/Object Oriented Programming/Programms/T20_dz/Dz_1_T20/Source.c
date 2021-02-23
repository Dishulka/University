#pragma warning(disable:4996)
#pragma warning(disable:6385)
#pragma warning(disable:6001)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int isNatural(char* str)//return 1 if Natural
{
	if (strcmp("1", str) == 1)
		return 0;
	for (int j = 0; j < (int)strlen(str); j++)
		if (!(str[j] >= '0' && str[j] <= '9'))
			return 0;
	return 1;
}
_Bool Compare(char* first, char* second)//return 1: f>s; return 0 f<=s
{
	if (strlen(first) == strlen(second))
	{
		for (int i = 0; i < (int)strlen(first); i++)
			if (first[i] > second[i])
				return 1;
	}
	else if (strlen(first) > strlen(second))
		return 1;
	return 0;
}
int main() {

	//Start Initializations
	int n = 0;//Amount of Naturals numbers
	int len = 0;//Amount of symbols

				//Initialization temp input
	int j = 0;
	char ch = 'a';
	char* word;
	int wordlen = 32;
	if ((word = (char*)malloc(sizeof(char) * (wordlen + 1))) == NULL)
		return 1;
	//Initialize max
	char* max;
	if ((max = (char*)malloc(sizeof(char))) == NULL)
		return 1;
	max[0] = '\0';
	//End Initializations

	//Main Algorithm
	do 
	{
		ch = getchar();
		len++;
		if ((ch == ' ' || ch == '\n' || ch == '\t' || ch == '~') && (j != 0))
		{
			word[j] = '\0';
			j = 0;
			if (isNatural(word))
			{
				n++;//Count Naturals
				if (Compare(word, max))//if(argv[i]>max)
				{
					//start max=argv[i]
					free(max);
					if ((max = (char*)malloc(strlen(word) * sizeof(char) + 1)) == NULL)
						return 1;
					strcpy(max, word);
					//end
				}
			}
		}
		else if (!(ch == ' ' || ch == '\n' || ch == '\t' || ch == '~'))
		{
			if (j == wordlen)
			{
				wordlen += 32;
				char* temp;
				if ((temp = (char*)malloc(sizeof(char) * (wordlen + 1))) == NULL)
					return 1;
				strcpy(temp, word);
				free(word);
				word = temp;

			}
			word[j] = ch;
			j++;
		}
	} while (ch != EOF && ch != '~');
	len--;
	//stderr
	fprintf(stderr, "All length: %d.\nNaturals: %d.\nMax: %s.\n", len, n, max);
	free(word);
	return 0;
}