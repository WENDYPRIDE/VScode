#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 9

void *say_GOOD(void *args)
{
    cout << "GOOD runoob!" << endl;
    return 0;
}

void *say_hello(void *args)
{
    cout << "hello runoob!" << endl;
    // pthread_t tid;
    // int ret = pthread_create(&tid, NULL, say_GOOD, NULL);
    // if (ret != 0)
    // {
    //     /* code */
    //     cout << "pthread_create error: error_code=" << ret << endl;
    // }
    return 0;
}



void *thread_1(void *args)
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, say_GOOD, NULL);
    if (ret != 0)
    {
        /* code */
        cout << "pthread_create error: error_code=" << ret << endl;
    }
    return 0;
}

int main()
{
    pthread_t tids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if (ret != 0)
        {
            /* code */
            cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    pthread_exit(NULL);
}