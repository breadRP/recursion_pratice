#include <stdio.h>

int fibo();

int main(){
    int num = 0;
    scanf("%d", &num);
    printf("%d", fibo(num));
}

int fibo(int n){
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }

    return fibo(n-1) + fibo(n-2);
}