#include "revert_string.h"

void RevertString(char *str)
{
    char m;
	int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    for (int i=0; i<len/2; i++){
        m=str[i];
        str[i]=str[len-i-1];
        str[len-i -1]=m;
    }

}

