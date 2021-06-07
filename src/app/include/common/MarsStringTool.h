//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSSTRINGTOOL_H
#define MARS_AGENT_MARSSTRINGTOOL_H

#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <cassert>

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

        static unsigned char ToHex(unsigned char x)
        {
            return  x > 9 ? x + 55 : x + 48;
        }

        static unsigned char FromHex(unsigned char x)
        {
            unsigned char y;
            if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
            else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
            else if (x >= '0' && x <= '9') y = x - '0';
            else assert(0);
            return y;
        }

        static std::string UrlEncode(const std::string& str);

        static std::string UrlDecode(const std::string& str);

        //把字符串切割成数组
        static std::vector<std::string> split(const std::string& str, const std::string& delim);
    };
}

#endif //MARS_AGENT_MARSSTRINGTOOL_H
