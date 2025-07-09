#include<stdbool.h>
#include <string.h>

bool isMatch(char* s, char* p) {
    if(p[0]=='\0') return s[0]=='\0'; //递归出口
    bool firstmatch=s[0]!='\0'&&(s[0]==p[0]||p[0]=='.'); //前提s不为空，比较首个字符
    if(p[1]=='*'){
        return isMatch(s,p+2)||firstmatch&&isMatch(s+1,p); //分别为，*前为0，*前>=1的情况
    }else{
        return firstmatch&&isMatch(s+1,p+1); //正常匹配
    }
}


bool isMatch_dp_forward(char* s, char* p) {
    int s_len = strlen(s);
    int p_len = strlen(p);

    bool dp[s_len + 1][p_len + 1];

    // 初始化所有为 false
    for (int i = 0; i <= s_len; i++) {
        for (int j = 0; j <= p_len; j++) {
            dp[i][j] = false;
        }
    }

    dp[0][0] = true;  // 空串匹配空模式

    // 初始化第一行：s 为空串，p 是 "a*b*c*" 这种情况
    for (int j = 2; j <= p_len; j++) {
        if (p[j - 1] == '*' && dp[0][j - 2]) {
            dp[0][j] = true;
        }
    }

    // 正序填表
    for (int i = 1; i <= s_len; i++) {
        for (int j = 1; j <= p_len; j++) {
            if (p[j - 1] == '*') {
                // * 匹配 0 次 或 匹配至少一次
                bool firstMatch = (s[i - 1] == p[j - 2] || p[j - 2] == '.');
                dp[i][j] = dp[i][j - 2] || (firstMatch && dp[i - 1][j]);
            } else {
                // 普通字符或 .
                bool firstMatch = (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                dp[i][j] = firstMatch && dp[i - 1][j - 1];
            }
        }
    }

    return dp[s_len][p_len];
}


bool isMatch_dp_backward(char* s, char* p) {
    int slen = strlen(s);
    int plen = strlen(p);

    // 创建 DP 表：dp[i][j] 表示 s[i:] 是否能匹配 p[j:]
    bool dp[slen + 1][plen + 1];

    // 初始化所有为 false
    for (int i = 0; i <= slen; i++)
        for (int j = 0; j <= plen; j++)
            dp[i][j] = false;

    // 空字符串和空模式是匹配的
    dp[slen][plen] = true;

    // 逆序填表，从后往前
    for (int i = slen; i >= 0; i--) {
        for (int j = plen - 1; j >= 0; j--) {

            // 判断当前位置是否匹配
            bool first_match = (i < slen) && (s[i] == p[j] || p[j] == '.');

            if (j + 1 < plen && p[j + 1] == '*') {
                // * 匹配0次 或 匹配1次以上
                dp[i][j] = dp[i][j + 2] || (first_match && dp[i + 1][j]);
            } else {
                // 正常字符匹配
                dp[i][j] = first_match && dp[i + 1][j + 1];
            }
        }
    }

    return dp[0][0];
}
