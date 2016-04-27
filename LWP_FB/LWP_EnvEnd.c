
/* 
 * Copy Right of xianyuxiaoqiang Under MIT Lisence
 */
/* To stop LWPs */
#include "myCommon.h"

int LWP_EnvEnd()
{
    int i = 0;
    LWP_inf *LWPs = LWP_FB_ENV.LWPs;
    int ret;
    LPVOID lpMsgBuf;
    /* Stop LWPs */
    /*for( i=0; i<LWP_FB_ENV.LWP_num; i++ )*/
    for( i=LWP_FB_ENV.LWP_num-1; i>=0; i-- )
    {
        LWPs[i].stop_flag = 1;
        ReleaseSemaphore( LWPs[i].exe_sem,1,NULL );
        /* Wait for FBs ending */
        ret = WaitForSingleObject( LWPs[i].end_sem, INFINITE );
        MY_CHECK_ERR( "WaitForSingleObject",ret )
        /* CloseHandle( LWPs[i].end_sem );
        CloseHandle( LWPs[i].exe_sem );
        CloseHandle( LWPs[i].res_sem );
        LWPs[i].end_sem = 0;
        LWPs[i].exe_sem = 0;
        LWPs[i].res_sem = 0; */
    }
    /* Free tables */
    if( LWP_FB_ENV.LWPs != NULL )
    {
        free( LWP_FB_ENV.LWPs );
        LWP_FB_ENV.LWPs = NULL;
        LWP_FB_ENV.LWP_num = 0;
    }
    if( LWP_FB_ENV.FBs != NULL )
    {
        free( LWP_FB_ENV.FBs );
        LWP_FB_ENV.FBs = NULL;
        LWP_FB_ENV.FB_num = 0;
    }
    return 1;
}
