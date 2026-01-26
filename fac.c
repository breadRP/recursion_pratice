#include <stdio.h>

long long fact(int n);
    
int main() 
{
	int num = 0;
	scanf("%d", &num);
	printf("%lld", fact(num));
	
	return 0;
}

long long fact(int n)
{
	if(n != 0) {
		if (n == 1) {
			return 1;
		}
		return n * fact(n-1);
	}
	else {
		return 1;
	}
}