#include "myCommon.h"
/* The function to test performance */
#define LOOPTIME 1000
int first1=1;
int first2=1;
int testFunc()
{
    int i = 0;
    int j = 1;
    for( i=1; i<LOOPTIME; i++ )
    {
        j *= i;
    }
    for( i=1; i<LOOPTIME; i++ )
    {
        j /= i;
    }
    return j;
}
int testFunc2()
{
    int i = 0;
    int j = 1;
    for( i=1; i<LOOPTIME; i++ )
    {
        j *= i;
    }
    for( i=1; i<LOOPTIME; i++ )
    {
        j /= i;
    }
    return j;
}
int testFunc4()
{
    clock_t start,end;
    int i = 0;
    int j = 1;
    FILE *fp = NULL;
    if(first2)
    {
        start = clock();
    }
    for( i=1; i<LOOPTIME; i++ )
    {
        j *= i;
    }
    for( i=1; i<LOOPTIME; i++ )
    {
        j /= i;
    }
    if(first2)
    {
        end = clock();
        printf("[testFunc2]start time: %d (ms)\tend time: %d (ms)\n", start, end);
        printf("[testFunc2]Total time cost: %d (ms)\n", end-start);
        first2 = 0;
    }
    return j;
}
int testFunc3()
{
    Sleep(1000);
}
int testFunc5()
{
    clock_t start,end;
    int i = 0;
    int j = 1;
    FILE *fp = NULL;
    if(first1)
    {
        start = clock();
    }
    for( i=1; i<LOOPTIME; i++ )
    {
        j *= i;
    }
    for( i=1; i<LOOPTIME; i++ )
    {
        j /= i;
    }
    if(first1)
    {
        end = clock();
        printf("[testFunc]start time: %d (ms)\tend time: %d (ms)\n", start, end);
        printf("[testFunc]Total time cost: %d (ms)\n", end-start);
        first1 = 0;
    }
    return j;
}
