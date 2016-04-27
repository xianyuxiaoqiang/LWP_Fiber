
/* 
 * Copy Right of xianyuxiaoqiang Under MIT Lisence
 */
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <time.h>
#include <stdio.h>
/* data definition */
typedef int( *MYFUNC )();
typedef struct FB_inf_tag{
    int FB_id;                      /* The ID of each FB          */
    int Next_FB_id;                 /* Next FB in the array       */
    struct LWP_inf_tag *LWP;        /* it's LWP                   */
    /* HANDLE fin_sem; need not?*/                /* For job finish             */
    int stat;                       /* 1:running 0:stop           */
    void *context;                  /* FB's context               */
    MYFUNC func;                     /* FB's main function         */
}FB_inf;
typedef struct LWP_inf_tag{
    int LWP_id;                     /* The ID of each LWP         */
    int First_FB_id;                /* The header of FB SubArray  */
    int FB_num;                     /* Number of FB SubArray      */
    HANDLE init_sem;                /* For Create LWP             */
    HANDLE end_sem;                 /* For Stop LWP               */
    HANDLE exe_sem;                 /* For execute LWP            */
    HANDLE res_sem;                 /* For response job finish    */
    int stop_flag;                  /* 1=stop  0=nothing          */
    void *context;                  /* LWP's context              */
}LWP_inf;
typedef struct LWP_FB_env_tag{
    struct LWP_inf_tag *LWPs;       /* The header of LWP list     */
    int LWP_num;                    /* Number of LWP              */
    struct FB_inf_tag *FBs;         /* The memory of FBs          */
    int FB_num;                     /* The Total Number of FB     */
}LWP_FB_env;
LWP_FB_env LWP_FB_ENV;

/* Number definition */
#define LWP_STACK_SIZE 200          /* KB */

/* functions */
int testFunc();
int LWP(LWP_inf *);
int FB(FB_inf *);
#define MY_CHECK_ERR( FUNC,ret )\
        if( ret != 0 )\
        {\
            LPVOID lpMsgBuf;\
            FormatMessage( \
                FORMAT_MESSAGE_ALLOCATE_BUFFER | \
                FORMAT_MESSAGE_FROM_SYSTEM | \
                FORMAT_MESSAGE_IGNORE_INSERTS,\
                NULL,\
                GetLastError(),\
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), \
                (LPTSTR) &lpMsgBuf,\
                0,\
                NULL \
                );\
            printf("%s: %s\n",FUNC, lpMsgBuf);\
            LocalFree( lpMsgBuf );\
        }
