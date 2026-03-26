#include<bits/stdc++.h>
using namespace std;
 
string orders;
int x=1;
int y=1;
int counter=0;
 
void PrintMatrix(int matrix[9][9])
{
	for (int i = 0; i < 9; i++)
	{
	   for (int j = 0; j < 9; j++)
	   {
	      cout << matrix[i][j] << " ";
	   }
	   cout << endl;
	}
	return;
}
 
void Path(int grid[9][9],int n){
	if(n==48){
		if(x==1 && y==7) counter++;
        return;
    } 
    
    if(x==1 && y==7) return;
    if(grid[x][y+1]==1 && grid[x][y-1]==1 && grid[x+1][y]==0 && grid[x-1][y]==0) return;
    if(grid[x][y+1]==0 && grid[x][y-1]==0 && grid[x+1][y]==1 && grid[x-1][y]==1) return;
    
    if((orders[n]=='?' || orders[n]=='D') && grid[x][y+1]==0){
        y++;			
        grid[x][y]=1;
        Path(grid,n+1);		
        grid[x][y]=0;
        y--;
    }
    if((orders[n]=='?' || orders[n]=='R') && grid[x+1][y]==0){
        x++;			
        grid[x][y]=1;
        Path(grid,n+1);		
        grid[x][y]=0;
        x--;
    }
    if((orders[n]=='?' || orders[n]=='U') && grid[x][y-1]==0){
        y--;			
        grid[x][y]=1;
        Path(grid,n+1);		
        grid[x][y]=0;
        y++;
    }
    if((orders[n]=='?' || orders[n]=='L') && grid[x-1][y]==0){
        x--;
        grid[x][y]=1;
        Path(grid,n+1);		
        grid[x][y]=0;
        x++;
    }
}
 
int main(){
	int grid[9][9]={};
	for(int i=0; i<9;i++){
		grid[i][0]=1;
		grid[i][8]=1;
		if(i==0 || i==8){
			for(int j=0; j<8; j++) grid[i][j]=1;
		}
	}
	grid[1][1]=1;
	getline(cin, orders);
	Path(grid,0);
	cout << counter;
	
}