#include <iostream>
#include <stack>

void Hanoi(int n,char *from,char *work,char *dest)
{
    if(n>=1){
        Hanoi(n-1,from,dest,work);

        printf("%d を %s から %s へ\n",n,from,dest);

        Hanoi(n-1,work,from,dest);
    }
}

int main(void)
{
    Hanoi(4,"A","B","C");

    return 0;
}
