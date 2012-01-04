#ifndef NX_UTIL_STRINGUTIL_H_
#define NX_UTIL_STRINGUTIL_H_

namespace nx
{
namespace util
{
class StringUtil
{
private:
    StringUtil(void);
    ~StringUtil(void);
public:
    static void Tokenize(
        IN const std::wstring& str,
        IN const std::wstring& delimiters,
        OUT std::vector<std::wstring> &tokens);
    static void RemoveSpaces(
        IN const std::wstring& inStr,
        OUT std::wstring& outStr);
    static void ToUpper(
        IN const std::wstring& inStr,
        OUT std::wstring& outStr);
    static void ToUpper(
        IN OUT std::wstring& inOutStr) {
        ToUpper(inOutStr, inOutStr);
    }
    static void ToLower(
        IN const std::wstring& inStr,
        OUT std::wstring& outStr);
    static void ToLower(IN OUT std::wstring& inOutStr) {
        ToUpper(inOutStr, inOutStr);
    }
};
}
}

#endif // NX_UTIL_STRINGUTIL_H_
