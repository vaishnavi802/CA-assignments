#include<bits/stdc++.h>
#include<cstring>

using namespace std;

const int MAX = 100;


void luDecomposition(int A[][MAX],int B[], int n)
{
	int lower[n][n], upper[n][n];
	

	// Decomposing matrix into Upper and Lower
	// triangular matrix
	for (int i = 0; i < n; i++)
	{
		// Upper Triangular
		for (int k = i; k < n; k++)
		{
			// Summation of L(i, j) * U(j, k)
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower[i][j] * upper[j][k]);

			// Evaluating U(i, k)
			upper[i][k] = A[i][k] - sum;
		}

		// Lower Triangular
		for (int k = i; k < n; k++)
		{
			if (i == k)
				lower[i][i] = 1; // Diagonal as 1
			else
			{
				// Summation of L(k, j) * U(j, i)
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower[k][j] * upper[j][i]);

				// Evaluating L(k, i)
				lower[k][i]
					= (A[k][i] - sum) / upper[i][i];
			}
		}
	}
	cout<<endl;	

	
	cout<< "Lower Triangular  Matrix "<<endl;
	cout<<endl;	
		

	// Displaying the result :
	for (int i = 0; i < n; i++)
	{
		// Lower
		for (int j = 0; j < n; j++)
			cout  << lower[i][j] << " ";
		cout <<endl;
    }

    cout<<endl;

	cout<< "Upper Triangular  Matrix "<<endl;
	cout<<endl;	

    for (int i = 0; i < n; i++)
	{
		// Upper
		for (int j = 0; j < n; j++)
			cout << upper[i][j] << " ";
		cout <<endl;
	}
    //For calculating y
    int ans1[n];
    for(int i = 0;i<n;i++){
        int sum = 0;
        for(int j = 0;j<i;j++){
            sum += lower[i][j]*ans1[j];
        }
        if(lower[i][i]!=0){
            ans1[i] = (B[i]-sum)/lower[i][i];
        }
        else{
            ans1[i] = 0;
        }
    }
    //For calculating x
    cout<<endl;
    cout<<"Amount to be spent for different policies : \n";
    double ans2[n];
    for(int i = n-1;i>=0;i--){
        int sum = 0;
        for(int j = n-1;j>i;j--){
            sum += upper[i][j]*ans2[j];
        }
        if(upper[i][i]!=0){
            ans2[i] = float((ans1[i]-sum)/upper[i][i]);
        }
        else{
            ans2[i] = 0;
        }
    }
    for(int i = 0;i<n;i++){
        cout<<ans2[i]<<"000 Rs "<<endl;
    }
}


int main()
{
    int urban,suburban,rural,outsider;
    cout<<"Enter the total voters in Urban area: "<<endl;
    cin>>urban;
    cout<<"Enter the total voters in Suburban area: "<<endl;
    cin>>suburban;
    cout<<"Enter the total voters in Rural area: "<<endl;
    cin>>rural;
    cout<<"Enter the total voters in Outsider area: "<<endl;
    cin>>outsider;

    cout<<endl;
    int M[4][4];

    int mat[][MAX]
		= { { -2,5,3,6}, { 8, 2, -5, -2 }, {  1, 3, 10, 4}, {10, 6, -2, 5}};
    int B[4] = {urban,suburban,rural,outsider};
	luDecomposition(mat, B, 4);
    return 0;
}