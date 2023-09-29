#include "revert_string.h"

void RevertString(char *str)
{
    char m;
	int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    for (int i=len-1; i>=0; i--){
        m +=str[i];

    }

}

