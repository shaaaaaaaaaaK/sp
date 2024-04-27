#include <stdio.h>
#include <pthread.h>

#define LOOPS 1000000
int money = 1000;

void *inc()
{
  for (int i=0; i<LOOPS; i++) {
    money = money + 100;
  }
  return NULL;
}

void *dec()
{
  for (int i=0; i<LOOPS; i++) {
    money = money - 100;
  }
  return NULL;
}


int main() 
{
    int counter=0;
    while (1)
    {
        pthread_t thread1, thread2;

        pthread_create(&thread1, NULL, inc, NULL);
        pthread_create(&thread2, NULL, dec, NULL);

        pthread_join( thread1, NULL);
        pthread_join( thread2, NULL);
        if(money<0){
            printf("Error");
            break;
        }
        else
        {
            printf("money=%d\n", money);
        }
        
    }
    
 
}
