#include <stdio.h>
#include <stdlib.h>
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
	hash = ((hash << 5) + hash) + c;

    return hash;
}
size_t hash2(unsigned char *str)
{
	size_t hash = 0;

	for(hash = 0; *str != '\0'; str++)
		hash = *str + 31*hash;

	return hash;
}

int main()
{
	printf("%li\n", hash2("lambda") % 3);
}