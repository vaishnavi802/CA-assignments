#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

void Send_from_branch(int a[], int size){
    for(int i = 1; i<size; i++){
        MPI_Send(a, 10, MPI_INT, 0, 8, MPI_COMM_WORLD);
    }
}
void Receive_by_head(int my_rank, int size){
    int arr[11];
    MPI_Status status;
    for(int i = 1; i<size; i++){
        int data = 0;
        MPI_Recv(arr, 10, MPI_INT, i, 8, MPI_COMM_WORLD, &status);
        for(int i=0; i<10; i++){
             printf("%d ", arr[i]);
             //calculate the total cost by adding cost of individual item
            data+= arr[i]*(i+10);
        }
        printf("received from %d branch\n", i);
        arr[10] = data;
        MPI_Send(arr, 11, MPI_INT, i, 8, MPI_COMM_WORLD);
        printf("%d data send to %d branch\n", arr[10], i);
    }
}
void Receive_by_branch(int my_rank){
    int data[11];
    MPI_Status status;
    MPI_Recv(data, 11, MPI_INT, 0, 8, MPI_COMM_WORLD, &status);
    printf("%d data received by %d\n", data[10], my_rank);
}

int main(int argc, char **argv){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        Receive_by_head(rank, size);
    }
    else{
        int arr[10];
        for(int i=0; i<10; i++){
        //random quantity of items is stored in array
            arr[i]=rand()%100+1 + rank;
        }
        Send_from_branch(arr, size);
        Receive_by_branch(rank);
    }
    MPI_Finalize();
    return 0;
}