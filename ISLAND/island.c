#include <stdio.h>

  
int right = 1;
int left = 0;

int search(int a[], int n, int mobile)
{
    for (int i = 0; i < n; i++)
        if (a[i] == mobile)
           return i + 1; 
}
  


int getMobileElement(int a[], int dir[], int n)
{
    int mobile_prev = 0, mobile = 0;
    for (int i = 0; i < n; i++)
    {
        
        if (dir[a[i]-1] == left && i!=0)
        {
            if (a[i] > a[i-1] && a[i] > mobile_prev)
            {
                mobile = a[i];
                mobile_prev = mobile;
            }
        }
  
        
        if (dir[a[i]-1] == right && i!=n-1)
        {
            if (a[i] > a[i+1] && a[i] > mobile_prev)
            {
                mobile = a[i];
                mobile_prev = mobile;
            }
        }
    }
  
    if (mobile == 0 && mobile_prev == 0)
        return 0;
    else
        return mobile;
}
  
void swap(int* a, int* b) {
    int t = *a;
    *a=*b;
    *b=t;
}
int printOnePermutation(int a[], int dir[], int n)
{
    int mobile = getMobileElement(a, dir, n);
    int pos = search(a, n, mobile);
  
    if (dir[a[pos - 1] - 1] ==  left)
       swap(&a[pos-1], &a[pos-2]);
  
    else if (dir[a[pos - 1] - 1] == right)
       swap(&a[pos], &a[pos-1]);
    for (int i = 0; i < n; i++)
    {
        if (a[i] > mobile)
        {
            if (dir[a[i] - 1] == right)
                dir[a[i] - 1] = left;
            else if (dir[a[i] - 1] == left)
                dir[a[i] - 1] = right;
        }
    }
    for (int i = 0; i < n; i++)
        printf("%c", (a[i]+64)); //modified
    printf("\n");
}
  

int fact(int n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
    return res;
}
  
void onebyonePermutation(int n)
{
    
    int a[n];
    int dir[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
        printf("%c", (a[i]+64)); //modified
    }
    printf("\n");
  
    for (int i = 0; i < n; i++)
        dir[i] =  left;

    for (int i = 1; i < fact(n); i++)
        printOnePermutation(a, dir, n);
}

int main()
{
    int n;
    printf("Enter n : ");
    scanf("%d", &n);
    printf("\nThe permutations are ;\n\n");
    onebyonePermutation(n);
    return 0;
}