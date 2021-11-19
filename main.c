#include <stdio.h>
//#include <assert.h>
//#include <ctype.h>
//#include <errno.h>
//#include <float.h>
//#include <limits.h>
//#include <locale.h>
//#include <math.h>
//#include <setjmp.h>
//#include <signal.h>
//#include <stdarg.h>
//#include <stddef.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
#define putd(x) printf(#x ": %d\n", x)

char dict[2000][4];
int dlen = 0;
int inuse[2000];

int from;
int to;

int stack[2000];
int slen = 0;

int adj(char *a, char *b)
{
    if(strlen(a) != strlen(b))
        return 0;
    int c = 0;
    for(int i = 0; i < strlen(a); i++)
    {
        if(a[i] != b[i])
            c++;
    }
    return c == 1;
}

void pstack()
{
    printf("found one of length %d\n", slen);
    if(slen >= 20)
    {
        return;
    }
    for(int i = 0; i < slen; i++)
    {
        printf("%s ", dict[stack[i]]);
    }
    puts("\n");
}

void climb(int f, int t)
{
    putd(slen);
    stack[slen++] = f;
    if(f == t)
    {
        pstack();
        slen--;
        return;
    }

    inuse[f] = 1;

    for(int i = 0; i < dlen; i++)
    {
        if(inuse[i])
            continue;
        if(adj(dict[i], dict[f]))
        {
            climb(i,t);
        }
    }

    inuse[f] = 0;
    slen--;
}

int main(int argc, char **argv)
{
    putd(argc);
    while(scanf("%s", dict[dlen++]) != EOF) ;

    for(int i = 0; i < dlen; i++)
    {
        if(!strcmp(dict[i], argv[1]))
            from = i;
    }

    for(int i = 0; i < dlen; i++)
    {
        if(!strcmp(dict[i], argv[2]))
            to = i;
    }

    climb(from, to);

}
