#include <stdio.h>
#include <stdlib.h>
struct arr{
int array[100];
};

 
 

void write(struct arr new, int n){
printf("Solution:\n");
for (int i=0; i<n; i++){
       printf("In row number %d,  queen is in column number %d\n", i+1, new.array[i]+1);     }
}

 
 

int place(int k, int i, int x[]) {
for (int j=0; j<k; j++){
if (x[j]==i){
return 0; }        
if (abs(x[j] - i)==abs(j-k)){
            return 0;

    }     }
return 1;
}

 
 struct arr Nqueens(int k, int  n,int x[]){
    struct arr new;
    for (int j=0; j<k; j++){
        new.array[j] = x[j];
    }
    for (int i=0; i<n; i++){
        if (place(k, i, x) == 1){
            new.array[k] = i;
            if (k==n-1){
                write(new, n);}
                else{
                    Nqueens(k+1, n, new.array);
                }
            }
        }
    }

     

  int main() {
   int n;
    int x[100];
    printf("Enter n\n");
    scanf("%d",&n);
    Nqueens(0, n, x);
    return 0;

} 