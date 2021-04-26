//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSSTRINGTOOL_H
#define MARS_AGENT_MARSSTRINGTOOL_H

#include <string>
#include <algorithm>

namespace common {
    class MarsStringTool {
    public:
        std::string leftTrimString(const std::string& strSource, const std::string& strDrop)
        {
            std::string strDstString(strSource);
            return strDstString.erase(0, strDstString.find_first_not_of(strDrop));
        }

        std::string rightTrimString(const std::string& strSource, const std::string& strDrop)
        {
            std::string strDstString(strSource);
            return strDstString.erase(strDstString.find_last_not_of(strDrop) + 1);
        }

        std::string trimString(const std::string& strSource, const std::string& strDrop)
        {
            return leftTrimString(rightTrimString(strSource, strDrop), strDrop);
        }

        void strTolower(std::string& str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        }

        void strToUpper(std::string& str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        }
    };
}

#endif //MARS_AGENT_MARSSTRINGTOOL_H
