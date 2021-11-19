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
#define MAXLEN 2000
#define putd(x) printf(#x ": %d\n", x)

char dict[MAXLEN][4];
int dlen = 0;
// int inuse[MAXLEN];
int back[MAXLEN] = {[0 ... MAXLEN-1] = -1}; // start all with null backrefs

int queue[MAXLEN]; // circular queue
int qbeg, qend;

int from;
int to;

// int stack[MAXLEN];
// int slen = 0;


void enqueue(int e)
{
    queue[qbeg++] = e;
    qbeg %= MAXLEN;
}

int dequeue()
{
    int e = queue[qend++];
    qend %= MAXLEN;
    return e;
}


int findword(char *a)
{
    int lo = 0, hi = dlen;
    int i;

    i = (lo + hi)/2;
    do
    {
        int c = strcmp(a, dict[i]);
        if(c == 0)
        {
            return i;
        }
        else if(c < 0)
        {
            hi = i;
        }
        else
        {
            lo = i+1;
        }
        i = (lo+hi)/2;
    } while(lo != hi);

    return -1;
}

int isadj(char *a, char *b)
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

void putchain(int i) // print a chain of backreferences
{
    do
    {
        printf("%s <- ", dict[i]);
        i = back[i];
    } while(i != -1);
}

void bfsearch()
{

    enqueue(from); // put start in queue
    back[from] = -1; // end the chain of backreferences

    while(qbeg != qend) // while there are still viable nodes to search
    {
        int i = dequeue();
        if(strcmp(dict[i], dict[to]) == 0) // found the target word
        {
            putchain(i);
        }
        else
        {
            for(int j = 0; j < dlen; j++)
            {
                if(back[j] == -1)
                {
                    continue;
                }
                if(isadj(dict[i], dict[j]))
                {
                    enqueue(j);
                    back[j] = i;
                }
            }
        }
    }

}

// void pstack()
// {
//     printf("found one of length %d\n", slen);
//     if(slen >= 20)
//     {
//         return;
//     }
//     for(int i = 0; i < slen; i++)
//     {
//         printf("%s ", dict[stack[i]]);
//     }
//     puts("\n");
// }

// void climb(int f, int t)
// {
//     // putd(slen);
//     stack[slen++] = f;
//     if(f == t)
//     {
//         pstack();
//         slen--;
//         return;
//     }

//     inuse[f] = 1;

//     for(int i = 0; i < dlen; i++)
//     {
//         if(inuse[i])
//             continue;
//         if(adj(dict[i], dict[f]))
//         {
//             climb(i,t);
//         }
//     }

//     inuse[f] = 0;
//     slen--;
// }



int main(int argc, char **argv)
{
    // read in dict
    putd(argc);
    while(scanf("%s", dict[dlen++]) != EOF) ;
    // dict is already sorted

    putd(1);
    // find start and end words
    from = findword(argv[1]);
    to   = findword(argv[2]);

    puts(argv[1]);
    puts(argv[2]);

    putd(from);
    putd(to);



}
