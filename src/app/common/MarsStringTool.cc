////
//// Created by zhanglei on 2021/4/26.
////
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