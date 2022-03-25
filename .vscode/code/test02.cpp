#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREAD 3

void *PrintHello(void* threadid)
{
    int tid = *((int*)threadid);
    cout << "hello runoob! THREAD ID, "<< tid <<endl;
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[NUM_THREAD];
    int indexes[NUM_THREAD];
    int rc ;
    int i;
    for ( i = 0; i < NUM_THREAD; i++)
    {
        /* code */
        cout << "main():CREATE_Thread,"<< i <<endl;
        indexes[i] = i;
        rc = pthread_create(&threads[i],NULL,PrintHello, (void*)&(indexes));
        if(rc){
            cout<< "Error: Can not Create Thread,"<< rc <<endl;
            exit(-1); 
        }
    }
    pthread_exit(NULL);
    
}