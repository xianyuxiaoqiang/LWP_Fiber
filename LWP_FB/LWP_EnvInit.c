
/* 
 * Copy Right of xianyuxiaoqiang Under MIT Lisence
 */
/* To initialize LWPs */
#include "myCommon.h"

int LWP_EnvInit(int cpu_num)
{
    int i = 0;
    LWP_inf *LWPs;
    int stack = LWP_STACK_SIZE * 1024;
    HANDLE thread_p;
    if( cpu_num <= 0 )return -1;
    /* Initialize LWP tables */
    LWP_FB_ENV.LWPs = malloc( cpu_num * sizeof(LWP_inf) );
    if( LWP_FB_ENV.LWPs == NULL )return -1;
    LWP_FB_ENV.LWP_num = cpu_num;
    memset( LWP_FB_ENV.LWPs, 0, cpu_num * sizeof(LWP_inf) );
    LWPs = LWP_FB_ENV.LWPs;
    /* Start LWPs */
    for( i=0; i<cpu_num; i++ )
    {
        LWPs[i].init_sem = CreateSemaphore(NULL, 0, 1, NULL);
        if( LWPs[i].init_sem == NULL )return -1;
        LWPs[i].end_sem = CreateSemaphore(NULL, 0, 1, NULL);
        if( LWPs[i].end_sem == NULL )return -1;
        LWPs[i].exe_sem = CreateSemaphore(NULL, 0, 1, NULL);
        if( LWPs[i].exe_sem == NULL )return -1;
        LWPs[i].res_sem = CreateSemaphore(NULL, 0, 1, NULL);
        if( LWPs[i].res_sem == NULL )return -1;
        LWPs[i].LWP_id = i;
        thread_p = _beginthread( (int (*)(void *))LWP, stack, (void *)&LWPs[i] );
        if( thread_p == NULL )return -1;
        WaitForSingleObject( LWPs[i].init_sem, INFINITE );
        CloseHandle( LWPs[i].init_sem );
        //CloseHandle( thread_p );
        LWPs[i].init_sem = NULL;
    }
    return 1;
}
