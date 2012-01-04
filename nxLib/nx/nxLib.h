#ifndef NX_NXLIB_H_
#define NX_NXLIB_H_

#include "nxLib_forwarddecl.h"

#define CHK_FATAL_HRESULT(expression)\
{\
    HRESULT __hr__ = expression;\
    if(FAILED(__hr__)) {\
    LOG(SEVERITY_LEVEL_FATAL) << #expression << L", hr = " << std::hex << __hr__ << std::dec;\
    throw std::runtime_error(#expression);\
    }\
}

#define CHK_FATAL_BOOL(expression)\
{\
    BOOL __b__ = expression;\
    if(__b__ == 0) {\
    LOG(SEVERITY_LEVEL_FATAL) << #expression << L", last error = " << std::hex << GetLastError() << std::dec;\
    throw std::runtime_error(#expression);\
    }\
}

#define CHK_ERROR_HRESULT(retValue, expression)\
    retValue = expression;\
    if(FAILED(retValue)) {\
    LOG(SEVERITY_LEVEL_FATAL) << #expression << L", hr = " << std::hex << retValue << std::dec;\
    }

#define CHK_ERROR_BOOL(retValue, expression)\
    retValue = expression;\
    if(retValue == 0) {\
    LOG(SEVERITY_LEVEL_FATAL) << #expression << L", last error = " << std::hex << GetLastError() << std::dec;\
    throw std::runtime_error(#expression);\
    }

#define CHK_WARN_HRESULT(expression)\
{\
    HRESULT __hr__ = expression;\
    if(FAILED(__hr__)) {\
    LOG(SEVERITY_LEVEL_WARN) << #expression << L", hr = " << std::hex << __hr__ << std::dec;\
    }\
}

#define CHK_WARN_BOOL(expression)\
{\
    BOOL __b__ = expression;\
    if(__b__ == 0) {\
    LOG(SEVERITY_LEVEL_WARN) << #expression << L", last error = " << std::hex << GetLastError() << std::dec;\
    }\
}

#define WM_RIBBON_RESIZED WM_USER+1
#define WM_D2DERR_RECREATE_TARGET WM_USER+2

#include "../App/Resource.h"

namespace nx
{
typedef std::string::size_type SIZE_TYPE;
extern const SIZE_TYPE SIZE_NPOS;
}


#endif // NX_NXLIB_H_