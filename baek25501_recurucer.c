// recursion함수는 끝과 끝에서부터 서로 정반대에 있는 문자들이 같은지 비교하는 함수인 것으로 추정

#include <stdio.h>
#include <string.h>

int recur_count = 0;

int recursion(char *s, int l, int r){   //l과 r은 인덱스
    recur_count += 1;
    if(l >= r) return 1;
    else if(s[l] != s[r]) return 0;
    else return recursion(s, l+1, r-1);
}

int isPalindrome(char *s){
    return recursion(s, 0, strlen(s)-1);
}  

int main(){
    int T = 0;
    char ca[1001][1001]; // ***함정 조심 & 2차원 배열에서 앞에 괄호는 행(문자열 개수), 뒤애 괄호는 열(문자열 최대 크기)
    
    scanf("%d", &T);
    for (int i=0; i<T; i++){
        scanf("%s", ca[i]); // 2차원 배열 사용시 앞에 괄호만 적어서 사용하면 문자열을 하나씩 불러낼 수 있음
    }

    for (int i=0; i<T; i++){
        int isPal = 0;
        recur_count = 0;
        isPal = isPalindrome(ca[i]);
        printf("%d %d\n", isPal, recur_count);
    }

}

