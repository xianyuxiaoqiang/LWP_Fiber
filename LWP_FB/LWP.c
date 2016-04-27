
/* 
 * Copy Right of xianyuxiaoqiang Under MIT Lisence
 */
#include <stdio.h>
#include <stdlib.h>
#include "myCommon.h"
#include "userAPI.h"

void main()
{
    clock_t start,end;
    if( LWP_EnvInit(4) == -1 )
    {
        printf("LWP_EnvInit Fail\n");
        return -1;
    }
    start = clock();
    if( my_test(2000) == -1 )
    {
        printf("my_test Fail\n");
        return -1;
    }
    end = clock();
    printf("[FiberTest]start time: %d (ms)\tend time: %d (ms)\n", start, end);
    printf("[FiberTest]Total time cost: %d (ms)\n", end-start);
    LWP_EnvEnd();
    
    start = clock();
    if( normal_test(2000) == -1 )
    {
        printf("normal_test Fail\n");
        return -1;
    }
    end = clock();
    printf("[normal_test]start time: %d (ms)\tend time: %d (ms)\n", start, end);
    printf("[normal_test]Total time cost: %d (ms)\n", end-start);
}
int LWP( LWP_inf* LWP_INF )
{
    int tmp_id=0;
    int i;
    int FB_num=0;
    LWP_INF->context = ConvertThreadToFiber(NULL);
    /* Start finish */
    ReleaseSemaphore(LWP_INF->init_sem,1,NULL);
    while(1)
    {
        /* Wait For request */
        WaitForSingleObject(LWP_INF->exe_sem, INFINITE);
        if( LWP_INF->stop_flag == 1 )
        {
            /* Stop FBs */
            break;
        }
        if( LWP_INF->FB_num != 0 )
        {
            tmp_id = LWP_INF->First_FB_id;
            FB_num = LWP_INF->FB_num;
        }
        /* Initilize FBs */
        for( i=0; i<FB_num; i++,tmp_id++ )
        {
            /* LWP_FB_ENV.FBs[tmp_id].fin_sem = CreateSemaphore(NULL, 0, 1, NULL);
            if( LWP_FB_ENV.FBs[tmp_id].fin_sem == NULL )return -1; need not?*/
            LWP_FB_ENV.FBs[tmp_id].FB_id = tmp_id;
            if( i < FB_num-1 )
            {
                LWP_FB_ENV.FBs[tmp_id].Next_FB_id = tmp_id+1;
            }
            else
            {
                LWP_FB_ENV.FBs[tmp_id].Next_FB_id = 0;
            }
            LWP_FB_ENV.FBs[tmp_id].LWP = LWP_INF;
            LWP_FB_ENV.FBs[tmp_id].context = 
                CreateFiber(0, (LPFIBER_START_ROUTINE)FB, (LPVOID)&LWP_FB_ENV.FBs[tmp_id]);
            if( LWP_FB_ENV.FBs[tmp_id].context == NULL )
            {
                MY_CHECK_ERR( "CreateFiber", -1 )
                printf("Fail to create Fiber No.%d\n", tmp_id);
                ReleaseSemaphore( LWP_INF->res_sem,1,NULL );
                ReleaseSemaphore(LWP_INF->end_sem,1,NULL);
                return -1;
            }
            LWP_FB_ENV.FBs[tmp_id].stat = 1; /* running */
            /* FBs[tmp_id].func is from User */
        }
        /* execute fibers */
        if( LWP_INF->FB_num != 0 )
        {
            SwitchToFiber(LWP_FB_ENV.FBs[LWP_INF->First_FB_id].context);
        }
        /* All finished */
        ReleaseSemaphore( LWP_INF->res_sem,1,NULL );
        /* Now this version do nothing */
    }
    tmp_id = LWP_INF->First_FB_id;
    for( i=0; i<FB_num; i++,tmp_id++ )
    {
        if( LWP_FB_ENV.FBs[tmp_id].context != NULL )
        {
            DeleteFiber(LWP_FB_ENV.FBs[tmp_id].context);
            LWP_FB_ENV.FBs[tmp_id].context = NULL;
        }
    }
    /* End finish */
    ReleaseSemaphore(LWP_INF->end_sem,1,NULL);
    return 1;
}

