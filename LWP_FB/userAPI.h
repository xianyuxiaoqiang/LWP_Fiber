/* The APIs for user */

/* To start LWPs */
int LWP_EnvInit(int cpu_num);
/* To end LWPs */
int LWP_EnvEnd();
/* To start FiberTest */
int my_test(int fb_num);
/* To start normal thread test */
int normal_test(int thread_num);
