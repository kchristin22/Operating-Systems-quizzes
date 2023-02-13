#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef void (*sighandler_t)(int); /* type definition for return handler */
static jmp_buf jbuf;            /* setup as global/static for sigsetjmp and siglongjmp */

/* signal handler */
void handler(int signo)
{
    /* issue siglongjmp */
    siglongjmp(jbuf,1);
    
}


int safeWrite(int* ptr, int val)
{
  int status = 0;

  /* call signal and keep old handler */
  sighandler_t previous_handler = signal(SIGSEGV,handler);

  /* check if ptr is NULL and set sigsetjmp to be able to return */
  /* try to write the value at the specified memory location */
  if (ptr==NULL) return 1;
  int returnCode = sigsetjmp(jbuf,1);
  
  if(returnCode==0) *ptr = val;	  	
  
  /* handle success/error */  
  else status = 1;
  
  /* revert to old handler */
  signal(SIGSEGV,previous_handler);	 

  return status;

}

void main(){
	int *ptr = (int *) calloc( 10,sizeof(int) );
	int pos  = 100000;
	int val  = 5;
	int status = safeWrite( &ptr[pos], val );
	printf("status is %d\n",status);
	return;
}

