
// .....................................................function definations.......................................................
// this is to print int array
void print_arr_int(int arr[] , int size){
  int i;
	for( i=0;i<size;i++)
	{
		printk("%d ",arr[i]);	
	}

}
// to print any block of strings in our case main mamory data and hdd data......
void print_arr_block (char mainm[][BLOCKSIZE][LINESIZE] , int a,int b,int c){
	int i,j,k;
	for(i=0;i<a;i++){
		printk(KERN_ALERT"indexx %d.........................\n",i);
		for( j=0;j<b;j++)
		{
			for(k=0;k<c;k++)
			{
				printk(KERN_ALERT"%c ",mainm[i][j][k]);
			}
			printk(KERN_ALERT"\t");
		}
	}
}
// to find min in array 
int find_min(int count[], int size)
{
	int pos,i;
	pos=0;
	for(i=1;i<size;i++)
	{
		if(count[i]<count[pos])
		pos=i;
	}
	return pos;
}


// this will replace block at index i with block no which is in hdd  
replace(int index , int blockno) // add this block no at index index.
{
	//indexx[index]=blockno;
  int i,old_block_no,iterator1,iterator2 , j1,j2;
//find is dirty bit of that perticular index is set ?
//if yes
	if(dirty[index]==1){
		     
           old_block_no=indexx[index];
	   
           //block transfer into the hdd at appropriate place
           for(iterator1=0;iterator1<BLOCKSIZE;iterator1++){				
	       //strcpy(ftype[old_block_no].text[iterator1],type[index].text[iterator1]);
		for(j1=0;j1< LINESIZE; j1++){		
			hddm[old_block_no][iterator1][j1] = mainm[index][iterator1][j1]; 
		}
	   }    

           indexx[index]=blockno;//adding block no to the index array
           
           //replacing lines of block no in mainm array
	   for(iterator2=0;iterator2<BLOCKSIZE;iterator2++){
	           //strcpy(type[index].text[iterator2],ftype[blockno].text[iterator2]);
		for(j2=0;j2< LINESIZE; j2++){		
			mainm[index][iterator2][j2] = hddm[blockno][iterator2][j2]; 
		}	   
	    }
	   dirty[index]=0;
	}		
	//retrive block no of old block at that perticular index
	//write it in to the hdd at appropriate place.
	
	//then add block no in indexx ARRAY  
	//replace lines of block no in mainm array
	// make dirty bit of that perticular bit is equal to 0. in dirty array.
	else
	{
           indexx[index]=blockno;
	   for(iterator2=0;iterator2<BLOCKSIZE;iterator2++){
	           //strcpy(type[index].text[iterator2],ftype[blockno].text[iterator2]);
		for(j2=0;j2< LINESIZE; j2++){		
			mainm[index][iterator2][j2] = hddm[blockno][iterator2][j2]; 
		}	   
	    }
	   dirty[index]=0;

	} 

	//then  simply add block no in indexx ARRAY  
	//replace lines of block no in mainm array
	// make dirty bit of that perticular bit is equal to 0. in dirty array.


}
//..........................................>>LRU<<..............................................................//
int lru(/*int indexx[],int dirty[],char mainm[][BLOCKSIZE][LINESIZE],int count[],*/int blockno)
{
	int indx= -1;// indexx of block if it is there.
	int ispresent = 0;
	int min,i; 
	for(i=0;i<MM_SIZE;i++)
	{
		if(indexx[i]==blockno)
		{
			ispresent = 1; 
			indx = i;
		}
	
	}

	if(ispresent==1)
	{
		count[indx] = t;
		t++;
		return indx ;// indexx of requested block if is found in mainm
		
	}
	else
	{
			min=find_min(count,MM_SIZE);	
			count[min]=t++;
			pfault++;
			//replace(min,indexx,dirty,mainm,count);
			replace(min,blockno);
			// needed to be implemented by vishva replacing block at indexx min with new requested block which is blockno. 

			return min; // indexx of requested block if not found in mainm 
	}

}


//temp assign needed to be replaced with vishva's code...





//.............................................................<<FIFO>>.....................................................//

int fifo(int indexx[],int dirty[],char mainm[][BLOCKSIZE][LINESIZE],int count[],int blockno)
{
	int indx= -1;// indexx of block if it is there.
	int ispresent = 0;
	int min,i; 
	for(i=0;i<MM_SIZE;i++)
	{
		if(indexx[i]==blockno)
		{
			ispresent = 1; 
			indx = i;
		}
	
	}

	if(ispresent==1)
	{
		return indx ;// indexx of requested block if is found in mainm
		
	}
	else
	{
			
			pfault++;
			int temp = current1;
			//replace(current1,indexx,dirty,mainm,count,blockno);
			replace(current1,blockno);
			// needed to be implemented by vishva replacing block at indexx min with new requested block which is blockno. 
			current1 = (current1 +1)%MM_SIZE;
			return temp; // indexx of requested block if not found in mainm 
	}

}

//....................................................<<LFU>..................................................

int lfu(/*int indexx[],int dirty[],char mainm[][BLOCKSIZE][LINESIZE],int freq[],*/int blockno)
{
	int indx= -1;// indexx of block if it is there.
	int ispresent = 0;
	int min,i; 
	for(i=0;i<MM_SIZE;i++)
	{
		if(indexx[i]==blockno)
		{
			ispresent = 1; 
			indx = i;
		}
	
	}
/*spin_lock_irqsave(&slock,flags);
spin_unlock_irqrestore(&slock,flags);*/

	if(ispresent==1)
	{	
		freq[indx] = freq[indx] +1;
		return indx ;// indexx of requested block if is found in mainm
		
	}
	else

	{
			
			pfault++;
			min=find_min(freq,MM_SIZE);
			
			//replace(min,indexx,dirty,mainm,count);
			replace(min,blockno);
			freq[min] = 0;
			// needed to be implemented by vishva replacing block at indexx min with new requested block which is blockno. 
			return min; // indexx of requested block if not found in mainm 
	}


}
void main()
{
	
}
