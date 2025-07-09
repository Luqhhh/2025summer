#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>

char* longestParlindrome_dp(char* s);
char* longestParlindrome_ct(char* s);

int main(){
    char s[17]="addsidadiacvdaki";
    char* res=longestParlindrome_dp(s);
    printf("%s\n",res);
    char* res1=longestParlindrome_ct(s);
    printf("%s",res1);
    return 0;
}



//动态分配
char* longestParlindrome_dp(char* s){
    int len=strlen(s);
    int max_len=0;
    int start=0;
    bool** dp=(bool**)malloc(len*sizeof(bool*));
    for(int i=0;i<len;i++){
        dp[i]=(bool*)malloc(len*sizeof(bool));
        memset(dp[i],false,len*sizeof(bool));
    }
    for(int i=0;i<len;i++){
        dp[i][i]=true; //所有单字母都为回文序列
    }
    for(int i=len-1;i>0;i--){ //关键 保证[i+1][j-1]计算在[i][j]前
        for(int j=i+1;j<len;j++){
            if(s[i]==s[j]){ //两端相等
                if(j-i<3){
                    dp[i][j]=true; //中间仅有单字母或中间无字母回文
                }else{
                    dp[i][j]=dp[i+1][j-1]; //前提是[i+1][j-1]已经计算
                }
            }
            if(dp[i][j]==true&&j-i+1>max_len){
                max_len=j-i+1;
                start=i;
            }  
        }
    }
    for(int i=0;i<len;i++){
        free(dp[i]);
    }
    free(dp);
    char* res=(char*)malloc(sizeof(char)*(max_len+1));
    strncpy(res,s+start,max_len);
    res[max_len]='\0';
    return res;
}


//中心扩展
char* longestParlindrome_ct(char* s){
    int len=strlen(s);
    int start=0;
    int max_len=0;
    int left=0;
    int right=0;
    for(int i=0;i<len;i++){
        left=i; //回文序列长度为偶数
        right=i;
        while(s[left]==s[right]&&left>=0&&right<=len){
            if(right-left+1>max_len){
                start=left;
                max_len=right-left+1;
            }
            left--;
            right++;
        }
        left=i;//回文序列长度为奇数
        right=i+1;
        while(s[left]==s[right]&&left>=0&&right<=len){
            if(right-left+1>max_len){
                start=left;
                max_len=right-left+1;
            }
            left--;
            right++;
        }
    }
    char* res=(char*)malloc(max_len*sizeof(char));
    strncpy(res,s+start,max_len);
    res[max_len]='\0';
    return res;
}
