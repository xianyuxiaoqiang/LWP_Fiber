/* 
 * Copy Right of xianyuxiaoqiang Under MIT Lisence
 */
#include "myCommon.h"

int FB(FB_inf *FB_INF)
{
    int next_id = FB_INF->Next_FB_id;
    if( FB_INF->stat == 1 )
    {
        FB_INF->func(); /* Do what user want */
    }
    /* ReleaseSemaphore(FB_INF->fin_sem,1,NULL); need not? */
    /* To next fiber */
    FB_INF->stat = 0;/* finish */
    while( next_id != 0 )
    {
        if( LWP_FB_ENV.FBs[next_id].stat == 0 )
        {
            /* remove it */
            if( LWP_FB_ENV.FBs[next_id].context != NULL )
            {
                DeleteFiber(LWP_FB_ENV.FBs[next_id].context);
                LWP_FB_ENV.FBs[next_id].context = NULL;
            }
            FB_INF->Next_FB_id = LWP_FB_ENV.FBs[next_id].Next_FB_id;
            next_id = FB_INF->Next_FB_id;
        }
        else
        {
            /* run next fiber */
            SwitchToFiber(LWP_FB_ENV.FBs[next_id].context);
            break;
        }
    }
    /* return to LWP */
    SwitchToFiber( FB_INF->LWP->context );

    return 1;
}
