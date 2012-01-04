#ifndef NX_UTIL_H_
#define NX_UTIL_H_

namespace nx
{
namespace util
{

// ********** WMessage **********

class WMessageArgs
{
public:
    WMessageArgs() :
        hwnd(0), message(0), wParam(0), lParam(0) {}
    WMessageArgs(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam) :
        hwnd(_hwnd), message(_message), wParam(_wParam), lParam(_lParam)
    {}
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
};

extern void _WMessage(std::ios_base& os, nx::util::WMessageArgs message);

inline std::_Smanip<WMessageArgs> __cdecl WMessage(nx::util::WMessageArgs message)
{
    return (std::_Smanip<nx::util::WMessageArgs>(&_WMessage, message));
}

// ********** LastError **********
class LastErrorArgs
{
public:
    LastErrorArgs() : functionName(), lastError(0) {}
    LastErrorArgs(const std::wstring &_functionName, DWORD _lastError) :
        functionName(_functionName), lastError(_lastError) {}
    std::wstring functionName;
    DWORD lastError;
};

extern void _LastError(std::ios_base& os, LastErrorArgs args);

inline std::_Smanip<LastErrorArgs> __cdecl LastError(LastErrorArgs args)
{
    return (std::_Smanip<LastErrorArgs>(&_LastError, args));
}

inline size_t ToBlockSize(size_t original, size_t blockSize)
{
    size_t result = blockSize;
    if ( 0 != original) {
        size_t remainder = original % blockSize;
        result = original + (0 != remainder ?
                             blockSize - remainder : 0);
    }
    return result;
}

/**
 * �p�X���t�H���_�ƃt�@�C�����ɕ���.
 * �t�H���_�ƃt�@�C�����̗������ɐ擪��"\"���t�������B
 * @param[in] path ���̓p�X
 * @param[out] folder �t�H���_(�擪��"\"���Ȃ���Εt�������)
 * @param[out] filename �t�@�C����
 * @return true�Ȃ�ΐ���
 */
extern bool SplitToFolderAndFilename(
    const std::wstring &path,
    std::wstring &folder,
    std::wstring &filename);

}
}

#endif // NX_UTIL_H_
