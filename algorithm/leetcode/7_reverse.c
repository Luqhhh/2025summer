//给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
//如果反转后整数超过 32 位的有符号整数的范围 [−2^31,  2^31 − 1] ，就返回 0。
#include <limits.h>
int reverse(int x) {
    int res=0;
    int num=0;
    while(x) {
        num=x%10;
        x=x/10;
        //注意检查的方式 若检查(res*10+num)则计算过程会产生溢出
        if(res>INT_MAX/10||(res==INT_MAX/10&&num>=7)) return 0; 
        if(res<INT_MIN/10||(res==INT_MIN/10&&num<=-8)) return 0;
        res=res*10+num;
    }
    return res;
}