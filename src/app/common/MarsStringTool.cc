////
//// Created by zhanglei on 2021/4/26.
////
#include "common/MarsStringTool.h"
//
//std::string LeftTrimString(const std::string& strSource, const std::string& strDrop)
//{
//    std::string strDstString(strSource);
//    return strDstString.erase(0, strDstString.find_first_not_of(strDrop));
//}
//
//std::string RightTrimString(const std::string& strSource, const std::string& strDrop)
//{
//    std::string strDstString(strSource);
//    return strDstString.erase(strDstString.find_last_not_of(strDrop) + 1);
//}
//
//std::string TrimString(const std::string& strSource, const std::string& strDrop)
//{
//    return LeftTrimString(RightTrimString(strSource, strDrop), strDrop);
//}
using namespace common;

//把字符串切割成数组
std::vector<std::string> MarsStringTool::split(const std::string &str, const std::string &delim) {
    std::vector<std::string> res;
    if ("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char *strs = new char[str.length() + 1]; //不要忘了
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        std::string s = p; //分割得到的字符串转换为string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }

    return res;
}


std::string MarsStringTool::UrlEncode(const std::string &str) {
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++) {
        if (isalnum((unsigned char) str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else {
            strTemp += '%';
            strTemp += ToHex((unsigned char) str[i] >> 4);
            strTemp += ToHex((unsigned char) str[i] % 16);
        }
    }
    return strTemp;
}

std::string MarsStringTool::UrlDecode(const std::string &str) {
    std::string strTemp;
    size_t length = str.length();
    for (size_t i = 0; i < length; i++) {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%') {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char) str[++i]);
            unsigned char low = FromHex((unsigned char) str[++i]);
            strTemp += high * 16 + low;
        } else strTemp += str[i];
    }
    return strTemp;
}