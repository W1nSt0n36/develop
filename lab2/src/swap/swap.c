#include "swap.h"

void Swap(char *left, char *right)
{
	char t;
	t=*left;
	*left=*right;
	*right=t;
}
