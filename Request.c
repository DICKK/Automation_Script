//#include <linux/init.h>
//#include <linux/module.h>
//#include <linux/kthread.h> 
//#include <linux/sched.h>
//#include <stdio.h>
//#include <stdlib.h>

int i,n,c,temp;
//time_t t;
int MAX_STRING_LENGTH = 100;

int append_length = 20;
int random_func()
{  
	static int k=1;
	int l=(k*3)%HD_SIZE;
	k++;
	
	return l;
}

int callfunc()
{
	temp = random_func();
	printk("requesting blockno %d \n",temp);
	c = lru(temp);
	printk("Returning index is %d",c);
	printk(" Main memory......................................................................................................................\n");
	print_arr_int(indexx,MM_SIZE);
	return c;
}

void request_block()
{
	int j;
	int counter = 5;
	int blockno =callfunc();
	char c = 'a';
	
	//printk("The main memory is......................................................................................................................");	
	
	
	printk("The HardDrive data is......................................................................................................................\n");
	print_arr_block(hddm,HD_SIZE,BLOCKSIZE,LINESIZE);
	//printk("The blocks position in main memory......................................................................................................................");
	
	//printk("\n");
	printk("The main memory data is......................................................................................................................\n");	
	print_arr_block(mainm,MM_SIZE,BLOCKSIZE,LINESIZE);
}
void request_block2()//modifying MM
{
	printk("block2");
	int j;
	int counter = 5;
	int blockno =callfunc();
	//char s[1][5] = {'a','b','c','d','e'};
	//mainm[0][BLOCKSIZE][LINESIZE] = 'c';
	char c = 'a';
	//Modifies MM
	printk("Modifies Main Memory of %d ",blockno);
	while(counter>=0)
	{
		mainm[blockno][BLOCKSIZE-1][counter] = c;
		c++;
		counter--;
	}
	dirty[blockno]=1;
	//printk("The main memory is......................................................................................................................");	
	
	
	printk("The HardDrive data is......................................................................................................................\n");
	print_arr_block(hddm,HD_SIZE,BLOCKSIZE,LINESIZE);
	//printk("The blocks position in main memory......................................................................................................................");
	
	//printk("\n");
	printk("The main memory data is......................................................................................................................\n");	
	print_arr_block(mainm,MM_SIZE,BLOCKSIZE,LINESIZE);
	printk("Dirty bit array is......................................................................................................................\n");
	print_arr_int(dirty,MM_SIZE);

	//if(strlen(s) > MAX_STRING_LENGTH)
	//MAX_STRING_LENGTH = strlen(s);
	//char change[] = "";
	//int chng = strlen(change);
	//char new_string[MAX_STRING_LENGTH + chng];
	//strcpy(new_string , s);
	//for(int j = 0; j < ; j++)
	//{
	//	if(j>10)
	//	{
	//		s
	//}
	//char new_s[1][3][15]={{"iron","man", "contagious"}};
	//for( j = 0 ; j < 128 ; j++)
	/*{
		s[0][0][j] = new_s[0][0][j];
	}
	mainm[c] = s;*/
}
