#include "myCommon.h"

int normal_thread(HANDLE fin_sem)
{
    int ret;
    testFunc2();
    ret = ReleaseSemaphore( fin_sem,1,NULL );
    MY_CHECK_ERR( "ReleaseSemaphore",!ret )
    return 1;
}
int normal_test(int thread_num)
{
    HANDLE *fin_sems = NULL;
    HANDLE thread_p;
    int stack = LWP_STACK_SIZE * 1024;
    int i;
    int ret;
    if( thread_num <= 0 )return -1;
    fin_sems = malloc( thread_num * sizeof(HANDLE) );
    if( fin_sems == NULL )return -1;
    for( i=0; i<thread_num; i++)
    {
        fin_sems[i] = CreateSemaphore(NULL, 0, 1, NULL);
        if( fin_sems[i] == NULL )
        {
            MY_CHECK_ERR( "CreateSemaphore",-1 )
            printf("Too many threads: %d of %d\n", i+1, thread_num);
            return -1;
        }
        //thread_p = _beginthread( (int (*)(void *))normal_thread, stack, (void *)fin_sems[i] );
        thread_p = CreateThread(NULL, stack,(LPTHREAD_START_ROUTINE)normal_thread,
                                (void *)fin_sems[i], STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
        if( thread_p == NULL )
        {
            MY_CHECK_ERR( "CreateThread",-1 )
            printf("Too many threads: %d of %d\n", i+1, thread_num);
            return -1;
        }
        //CloseHandle( thread_p );
    }
    //for( i=0; i<thread_num; i++)
    for( i=thread_num-1; i>=0; i--)
    {
        ret = WaitForSingleObject( fin_sems[i], INFINITE );
        MY_CHECK_ERR( "WaitForSingleObject",ret )
        CloseHandle( fin_sems[i] );
    }
    if( fin_sems != NULL )free(fin_sems);
    return 1;
}
