#include <pthread.h>
#include <semaphore.h>

int main ()
{
  /*Semaphores*/
  int agentSem = 1, tobacco = 0, paper = 0, match = 0;
  while(1)
  {
    P(agentSem);
    V(tobacco);
    V(paper);
  }
}
