#include "StdAfx.h"
#include "nx/mui/MUI.h"
#include "nx/logging/Logging.h"

nx::mui::MUI::MUI(void)
{
}

nx::mui::MUI::~MUI(void)
{
}

HMODULE nx::mui::MUI::s_hModule = nullptr;

HRESULT nx::mui::MUI::Initialize(const std::wstring &dllName)
{
    if (s_hModule != nullptr) {
        // already loaded
        return S_OK;
    }
    s_hModule = LoadLibraryExW(dllName.c_str(), 0,
                               LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
    if (s_hModule == nullptr) {
        LOG(SEVERITY_LEVEL_ERROR) << L"Could not load " << dllName;
        return E_FAIL;
    }
    return S_OK;
}

wchar_t buf[4096];
const wchar_t* nx::mui::MUI::GetString(UINT uID)
{
    if (LoadStringW(s_hModule, uID, buf, 4096) != 0) {
        return buf;
    }
    LOG(SEVERITY_LEVEL_WARN) << L"Could not load the string '" << uID << L"'";
    buf[0] = '\0';
    return buf;
}

