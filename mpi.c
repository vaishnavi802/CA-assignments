#include<mpi.h>
#include<stdio.h>

			
int main(int argc, char** argv)
{
	int office,n;
	office= 10;
	n=30;
	 
	int arr[office];
	int procs, myid;
	int data = 0;
	int *buff = NULL;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	
		
	
	data =n;
	 
	MPI_Gather(&data,1,MPI_INT,arr,1,MPI_INT,0,MPI_COMM_WORLD);
	
	if(myid==0){
		 
		for(int i = 0;i<office;i++)
		{
			arr[i]*=i;
		}	
		buff = arr;		
	}	
	
	printf("\nData previous paying early tax in process %d is %d",myid,data);
	
	 
	MPI_Scatter(buff,1,MPI_INT,&data,1,MPI_INT,0,MPI_COMM_WORLD);
	if(myid!=0){
	printf("\nCost for paying early taxes in process %d is %d",myid,data);
	}
MPI_Finalize();
printf("\n");
return 0;		

}
