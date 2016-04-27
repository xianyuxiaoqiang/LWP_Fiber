/* 
 * Copy Right of xianyuxiaoqiang Under MIT Lisence
 */
#include "myCommon.h"
int my_test(int fb_num)
{
    int every = 0;         /* FB number per LWP    */
    int i,j;
    int First_FB_id = 1;         /* FB's id (0==nothing) */
    int tmp_id = 0;
    int ret;
    FB_inf *FBs = NULL;
    if( fb_num <= 0 )return -1;
    FBs = malloc( (fb_num+1) * sizeof(FB_inf) );  /* No.0==nothing) */
    memset( FBs, 0, (fb_num+1) * sizeof(FB_inf) );
    if( FBs == NULL )return -1;
    LWP_FB_ENV.FBs = FBs;
    LWP_FB_ENV.FB_num = fb_num;
    every = fb_num / LWP_FB_ENV.LWP_num;
    fb_num = fb_num - every * LWP_FB_ENV.LWP_num; /* The left FBs */
    for( i=0; i< LWP_FB_ENV.LWP_num; i++ )
    {
        LWP_FB_ENV.LWPs[i].First_FB_id = First_FB_id;
        if( fb_num > 0 )
        {
            /* more 1 */
            LWP_FB_ENV.LWPs[i].FB_num = every + 1;
            fb_num--;
        }
        else
        {
            LWP_FB_ENV.LWPs[i].FB_num = every;
        }
        First_FB_id += LWP_FB_ENV.LWPs[i].FB_num;
        /* Initilize FBs */
        for( j=0; j<LWP_FB_ENV.LWPs[i].FB_num; j++ )
        {
            tmp_id = LWP_FB_ENV.LWPs[i].First_FB_id + j;
            /* Initilize func */
            LWP_FB_ENV.FBs[tmp_id].func = (void *)testFunc;
        }
        /* Start test */
        ReleaseSemaphore( LWP_FB_ENV.LWPs[i].exe_sem,1,NULL );
    }
    for( i=0; i< LWP_FB_ENV.LWP_num; i++ )
    {
        ret = WaitForSingleObject( LWP_FB_ENV.LWPs[i].res_sem,INFINITE );
        MY_CHECK_ERR( "WaitForSingleObject",ret )
    }
    return 1;
}
