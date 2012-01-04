#include "stdafx.h"
#include "nx/nxLib.h"
#include "nx/util/StringUtil.h"

namespace nx
{
namespace util
{

TEST( nx_util_StringUtil, ToUpper_001 )
{
    std::wstring inStr(L"abcdefghijklmnopqrstuvwxyz");
    std::wstring expect(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    std::wstring result;
    nx::util::StringUtil::ToUpper(inStr, result);

    ASSERT_EQ(expect, result);
}

TEST( nx_util_StringUtil, ToUpper_002 )
{
    std::wstring inStr(L"abcdefghijklmnopqrstuvwxyz");
    std::wstring expect(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    nx::util::StringUtil::ToUpper(inStr, inStr);

    ASSERT_EQ(expect, inStr);
}

TEST( nx_util_StringUtil, ToLower_001 )
{
    std::wstring inStr(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::wstring expect(L"abcdefghijklmnopqrstuvwxyz");

    std::wstring result;
    nx::util::StringUtil::ToLower(inStr, result);

    ASSERT_EQ(expect, result);
}

TEST( nx_util_StringUtil, ToLower_002 )
{
    std::wstring inStr(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::wstring expect(L"abcdefghijklmnopqrstuvwxyz");

    nx::util::StringUtil::ToLower(inStr, inStr);

    ASSERT_EQ(expect, inStr);
}

}
}