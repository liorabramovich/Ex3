#include <stdio.h>
#include <string.h>
#define TXT 1024
#define WORD 30


void printResult(int ex, char* res)
{
    switch (ex)
        {
        case 1: {
            printf("Gematria Sequences: %s\n", res);
            break;
        }
        case 2: {
            printf("Atbash Sequences: %s\n", res);
            break;
        }
        case 3: {
            printf("Anagram Sequences: %s", res);
            break;
        }
    }
}

int isLowLetter(char ch)
{
    return ch >= 'a' && ch <= 'z' ? 1 : 0;
}

int isBigLetter(char ch)
{
    return ch >= 'A' && ch <= 'Z' ? 1 : 0;
}

int getGimetricOfChar(char ch)
{
    if (isLowLetter(ch) == 1) {
        return ch - 'a' + 1;
    }
    else if (isBigLetter(ch)) {
        return ch - 'A' + 1;
    }
    else {
        return 0;
    }
}

int getGimerticOfWord(char* word)
{
    int res = 0;
    char* ptr = word;
    while (*ptr != '\0')
    {
        res += getGimetricOfChar(*ptr);
        ptr++;
    }

    return res;
}

int isChar(char ch)
{
    return  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ? 1 : 0;
}


void mAkeAbtashFromName(char* name, char* target)
{
    char* ptrName = name;
    char* ptrTarget = target;
    while (*ptrName != '\0')
    {
        if (isBigLetter(*ptrName) == 1) {
            *ptrTarget++ = 'Z' -( *ptrName - 'A');
           
        }
        else if (isLowLetter(*ptrName) == 1)
        {
            *ptrTarget++ = 'z' -( *ptrName - 'a');
        }    
        ptrName++;
    }
}

void reverseWord(char* src, char* target) {
    int size = strlen(src);
    for (int i = 0; i < size; i++) {
        target[size - i - 1] = src[i];
    }
}



int isSameWordExistsInSentence(char* sentence, int from,int size , char* word )
{
    int numberOfSpace = 0;
    for (int i = 0; i < size; i++) {
        if (sentence[from + i + numberOfSpace] != word[i]) {
            if (sentence[from + i + numberOfSpace] == ' ' || sentence[from + i + numberOfSpace] == '\n' || sentence[from + i + numberOfSpace] == '\t') {
                numberOfSpace++;
                i--;
            }
            else {
                return -1;
            }
        }
    }
    return numberOfSpace;
}



void fillCountersArray(char* name, int* arr)
{
    for (int i = 0; i < strlen(name); i++) {
        arr[(int)name[i]]++;
    }
}



int isCountersArrayEquals(int* arr1, int* arr2)
{
    for (int i = 0; i < 256; i++) {
        if (arr1[i] != arr2[i] && i != ' ') {
            return 0;
        }
    }
    return 1;
}

int isSpace(char ch)
{
    return ch == ' ' ? 1 : 0;
}

void exA(char* word, char* text) {
    char result[TXT] = { 0 };
    char* resultPtr = result;
    int gimetraicWord = getGimerticOfWord(word);
    int tempGim = 0;
    for (int i = 0; i < strlen(text); i++) {
        tempGim = 0;
        for (int j = i; j < strlen(text); j++) {
            tempGim += getGimetricOfChar(text[j]);
            if (tempGim > gimetraicWord)
            {
                break;
            }
            if (tempGim == gimetraicWord && isChar(text[i]) == 1) {
                for (int t = i; t <= j; t++) {
                    *resultPtr = text[t];
                    resultPtr++;
                }
                *resultPtr = '~';
                resultPtr++;
                break;
            }

        }
    }

    *--resultPtr = '\0';
   
    printResult(1, result);
}

void exB(char* name, char* sentence) {
    char result[TXT] = { 0 };
    char* resultPtr = result;
    char abtachNormal[WORD] = { 0 };
    char abtachReversed[WORD] = { 0 };
    mAkeAbtashFromName(name, abtachNormal);
    reverseWord(abtachNormal, abtachReversed);
    int size = strlen(sentence);
    for (int i = 0; i < size; i++) {
        int numberOfSpaces = isSameWordExistsInSentence(sentence, i, strlen(abtachNormal), abtachNormal);
        if (numberOfSpaces >= 0)
        {
            for (int j = 0; j < strlen(abtachNormal) + numberOfSpaces; j++) {
                *resultPtr++ = sentence[i + j];
            }
            *resultPtr++ = '~';
        }

        numberOfSpaces = isSameWordExistsInSentence(sentence, i, strlen(abtachReversed), abtachReversed);
        if (numberOfSpaces >= 0)
        {
            for (int j = 0; j < strlen(abtachReversed) + numberOfSpaces; j++) {
                *resultPtr++ = sentence[i + j];
            }
            *resultPtr++ = '~';
        }
    }
    if (strlen(result) > 0)
    {
        *--resultPtr = '\0';
    }

    printResult(2, result);
}

void exC(char* name, char* sentence) {

    char result[TXT] = { 0 };
    int countersNameArray[256] = { 0 };
    fillCountersArray(name, countersNameArray);
    char* resultPtr = result;
    int sizeOfSentence = strlen(sentence);
    for (int i = 0; i < sizeOfSentence; i++) {
        for (int j = i; j < sizeOfSentence; j++) {
            int currentArray[256] = { 0 };
            for (int k = i; k <= j; k++) {
                currentArray[(int)sentence[k]]++;
            }
            if (isSpace(sentence[i]) == 0 && isSpace(sentence[j]) == 0 && isCountersArrayEquals(currentArray, countersNameArray) == 1) {
                for (int x = i; x <= j; x++) {
                    *resultPtr++ = sentence[x];
                }
                *resultPtr++ = '~';
            }
        }
    }
    *--resultPtr = '\0';
   
    printResult(3, result);
}





int main() {

 /* 
 * OUTPUT
   char word[WORD] = "abcd";
   char sentence[TXT] = "a-bc,dbca-zwxyzabzyxw0dcba~";
 
   OUTPUT1
   char word[WORD] = "fish";
   char sentence[TXT] = "One, two, three, four, five,\nOnce I caught a fish alive,\nSix, seven, eight, nine, ten,\nThen I let go again.~";  

    OUTPUT2
   char word[WORD] = "sea";
   char sentence[TXT] = "A sailor went to sea, sea, sea\nTo see what he could see, see, see\nBut all that he could see, see, see\nWas the bottom of the deep blue sea, sea, sea!~";

   OUTPUT3
    //char word[WORD] = "sheep";
    //char sentence[TXT] = "Baa, baa black sheep\nHave you any wool\nYes sir, yes sir\nThree bags full.\n~";
    */

    char word[WORD] = { 0 };
    char sentence[TXT] = { 0 };

    scanf("%s", word);
    scanf("%[^~]s", sentence);
      
   exA(word,sentence);
   exB(word, sentence);
   exC(word, sentence);
   return 0;
}