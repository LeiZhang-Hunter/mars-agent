//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSSTRINGTOOL_H
#define MARS_AGENT_MARSSTRINGTOOL_H

#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

namespace common {
    class MarsStringTool {
    public:
        static std::string leftTrimString(const std::string& strSource, const std::string& strDrop)
        {
            std::string strDstString(strSource);
            return strDstString.erase(0, strDstString.find_first_not_of(strDrop));
        }

        static std::string rightTrimString(const std::string& strSource, const std::string& strDrop)
        {
            std::string strDstString(strSource);
            return strDstString.erase(strDstString.find_last_not_of(strDrop) + 1);
        }

        static std::string trimString(const std::string& strSource, const std::string& strDrop)
        {
            return leftTrimString(rightTrimString(strSource, strDrop), strDrop);
        }

        static void strTolower(std::string& str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        }

        static void strToUpper(std::string& str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        }

        //把字符串切割成数组
        static std::vector<std::string> split(const std::string& str, const std::string& delim) {
            std::vector<std::string> res;
            if("" == str) return res;
            //先将要切割的字符串从string类型转换为char*类型
            char * strs = new char[str.length() + 1] ; //不要忘了
            strcpy(strs, str.c_str());

            char * d = new char[delim.length() + 1];
            strcpy(d, delim.c_str());

            char *p = strtok(strs, d);
            while(p) {
                std::string s = p; //分割得到的字符串转换为string类型
                res.push_back(s); //存入结果数组
                p = strtok(NULL, d);
            }

            return res;
        }
    };
}

#endif //MARS_AGENT_MARSSTRINGTOOL_H
