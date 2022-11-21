#include <iostream>
using namespace std;
 
int main()
{
   
  int n, m, i, j, k;
  n = 5; // Number of processes
  m = 3; // Number of resources

  //int pzero[3];
  //int pone[3];
  //int ptwo[3];
  //int pthree[3];
  //int pfour[3];

  //int pzeromax[3];
  //int ponemax[3];
  //int ptwomax[3];
  //int pthreemax[3];
  //int pfourmax[3];

  //just going to hardcode values from table to make process faster

  //this is the allocation matrix
  int allocation[5][3] = { { 0, 1, 0 }, { 2, 0, 0 }, { 3, 0, 2 },  { 2, 1, 1 }, { 0, 0, 2 } }; 
 
 //max matrix
  int max[5][3] = { { 7, 5, 3 },  { 3, 2, 2 }, { 9, 0, 2 }, { 2, 2, 2 }, { 4, 3, 3 } }; 
 
  //available matrix
  int available[3] = { 3, 3, 2 }; 
 
  int f[n], answer[n], index = 0;
 
  //fill the array with 0s
  for (k = 0; k < n; k++) {
    f[k] = 0;
    }

  // need array determines what resource each process needs
  int need[n][m];
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      need[i][j] = max[i][j] - allocation[i][j];
  }

  int y = 0;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < n; j++) {
      if (f[j] == 0) {
 
        int flag = 0;
        //breaks out of the loop if theres not enough recources available for the process
        for (k = 0; k < m; k++) {
          if (need[j][k] > available[k]){
            flag = 1;
            break;
          }
        }
        
        //else go through and allocate the available resources
        if (flag == 0) {
          answer[index++] = j;
          for (y = 0; y < m; y++)
            available[y] += allocation[j][y];
          f[i] = 1;
        }
      }
    }
  }
   
  int flag = 1;
   
  //these will check if the sequence is safe or not
  for(int i = 0;i<n;i++)
  {
        if(f[i]==0)
      {
        flag = 0;
        cout << "The sequence is not safe";
        break;
      }
  }
 
  if(flag==1)
  {
    cout << "Following sequence is safe" << endl;
      for (i = 0; i < n - 1; i++)
        cout << " P" << answer[i] << " ->";
      cout << " P" << answer[n - 1] <<endl;
  }
 
    return (0);
}
