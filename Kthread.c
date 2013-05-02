#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h> 
#include <linux/sched.h>
#include <linux/time.h>     
#include <linux/timer.h>
#include <linux/semaphore.h>
#include <linux/bitops.h>
#include <linux/spinlock.h>
/*DEFINE_SPINLOCK(slock);
unsigned long flags;*/
void random(int n);
#define LINESIZE 5 // line size interms of chars or bytes
#define BLOCKSIZE 5 // block size in terms of lines
#define MM_SIZE 7 // main memory size in terms of blocks 
#define HD_SIZE 25
char hddm[HD_SIZE][BLOCKSIZE][LINESIZE] = {'\0'}; // hdd memory 
int indexx[MM_SIZE]={0};
int freq[MM_SIZE]={0}; // frequency of occurance ..use ful for lfu algorithm
int dirty[MM_SIZE]={0};
int count[MM_SIZE]={0}; //indexx will store block no that is current1ly in mainm , count is for lru. dirth bit is for checkiing 
//that that perticuler block is dirty or not.
int t=1; // global time variable used in lru.
int pfault =0;
int current1=0; // fifo pointer for keeping track of indexx of oldest block.....

char mainm[MM_SIZE][BLOCKSIZE][LINESIZE] ={'\0'}; // main memory
#include "Algo.c"
#include "Request.c"


static struct task_t *thread1,*thread2,*thread3,*thread4;
MODULE_LICENSE("GPL");

void call()
{
  int i=0;
	for(i;i<3;i++)
	{
		request_block();
	}
}
void call2()
{
	int i=0;
	request_block2();
	
}
static int __init mainn()
{
	//printk("Dirty bit array is......................................................................................................................\n");
	//print_arr_int(dirty,MM_SIZE);
	int i,j,k;
	char l='L',I='I',n='N',e='E';
		char tt = 'a';
		/*for(i=0;i< HD_SIZE;i++){
			 for(j=0;j< BLOCKSIZE;j++){				
				       		for(k=0;k< LINESIZE; k++){		
						hddm[i][j][k] = tt;
						tt++;
					}
			 }
		}*/
	for(i=0;i< HD_SIZE;i++){
			 for(j=0;j< BLOCKSIZE;j++){				
				       		for(k=0;k< LINESIZE; k++){
						if(k==0)			
							hddm[i][j][k] =l;
						if(k==1)			
							hddm[i][j][k] =I;
						if(k==2)			
							hddm[i][j][k] =n;
						if(k==3)			
							hddm[i][j][k] =e;
						if(k==4 )			
							hddm[i][j][k] =tt;
					}
			tt++;
			 }
		}

	
	int pass=25;
	printk(KERN_ALERT "Hi, This is Kernel Thread\n");
		
	
	

		
		thread1 = kthread_create(call,NULL,"Thread 1");
		thread1 = kthread_run(&call, NULL,"Thread 1");

		thread2 = kthread_create(call,NULL,"Thread 2");
		thread2 = kthread_run(&call, NULL,"Thread 2");

		thread3 = kthread_create(call,NULL,"Thread 3");
		thread3 = kthread_run(&call, NULL,"Thread 3");
		
		thread4 = kthread_create(call2,NULL,"Thread 4");
		thread4 = kthread_run(&call2, NULL,"Thread 4");
		//kt_sem_destroy(&s1);
		//kt_sem_destroy(&s2);
	return 0;
}


static void __exit exit()
{
	printk(KERN_ALERT "Meet you soon\n");
}


module_init(mainn);
module_exit(exit);




