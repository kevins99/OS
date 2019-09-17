#include<stdio.h> 
#define n 1000
int a[n][n],b[n][n],c[n][n]; 
int main() 
{ 
int i,j,k; 
for(i=0;i<n;i++)     //data initialization 
for(j-0;j<n;j++) 
{ 
a[i][j]=1; 
b[i][j]=1; 
} 
for(i=0;i<n;i++)   //multiplication 
for(j=0;j<n;j++) 
for(k=0;k<n;k++) 
c[i][j]=c[i][j]+a[i][k]*b[k][j]; 
printf("\n The resultant matrix is \n"); 
for(i=0;i<n;i++) 
{ 
for(j=0;j<n;j++) 
{ 
printf("%d",c[i][j]); 
printf("\n"); 
}}}  
