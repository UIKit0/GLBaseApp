#include "stdafx.h"
#include "nx/core/GLContext.h"
#include "nx/core/NXApplication.h"
#include "nx/mui/MUI.h"
#include "nx/tsf/TSFManager.h"
#include "nx/util/OSVersionChecker.h"
#include "nx/util/Utils.h"
#include "nx/win/MainWindow.h"
#include "nx/win/CanvasWindow.h"

nx::core::NXApplication::NXApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) :
    m_context(new nx::core::GLContext()),
    m_mainWindow(new nx::win::MainWindow()),
    m_tsfManager(new nx::tsf::TSFManager()),
    m_logFilePath(),
    m_muiDllName()
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
}

HRESULT nx::core::NXApplication::Initialize()
{
    HRESULT hr = S_OK;

    std::wstring logFolder;
    std::wstring logFileName;
    hr = nx::util::SplitToFolderAndFilename(m_logFilePath, logFolder, logFileName) ? S_OK : E_FAIL;

    PWSTR ppszPath = nullptr;
    if (SUCCEEDED(hr)) {
        hr = ::SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &ppszPath);
        if (SUCCEEDED(hr)) {
            std::wstring path(ppszPath);
            path += logFolder;
            int ret = ::SHCreateDirectory(nullptr, path.c_str());
            hr = (ret == ERROR_SUCCESS || ret == ERROR_FILE_EXISTS || ret == ERROR_ALREADY_EXISTS) ? S_OK : E_FAIL;
            if (SUCCEEDED(hr)) {
                path += logFileName;
                nx::logging::InitLogger(path.c_str());
            }
        }
    }
    if (FAILED(hr)) {
        TCHAR lpTempPathBuffer[MAX_PATH];
        GetTempPath(MAX_PATH, lpTempPathBuffer);
        std::wstring tempPath(lpTempPathBuffer);
        tempPath += logFileName;
        nx::logging::InitLogger(tempPath.c_str());
    }
    if (ppszPath != nullptr) {
        CoTaskMemFree(ppszPath);
    }

    //    ULONG numLangs;
    //    SetProcessPreferredUILanguages(MUI_LANGUAGE_NAME, L"en-US", &numLangs);
    //    SetProcessPreferredUILanguages(MUI_LANGUAGE_NAME, L"de-DE", &numLangs);
    hr = nx::mui::MUI::Initialize(m_muiDllName);

    bool vista = nx::util::OSVersionChecker::IsVista();
    bool win7 = nx::util::OSVersionChecker::IsWin7();
    LOG(SEVERITY_LEVEL_INFO) << L"Vista = " << std::boolalpha << vista;
    LOG(SEVERITY_LEVEL_INFO) << L"Win7 = " << std::boolalpha << win7;
    if (!vista && !win7) {
        MessageBox(nullptr, L"This application only works Vista and Win7", L"OS check error", MB_OK | MB_ICONERROR);
        hr = E_FAIL;
    }

    if (SUCCEEDED(hr)) {
        m_mainWindow->SetContext(m_context.get());
        m_mainWindow->SetTSFManager(m_tsfManager.get());
    }
    return hr;
}

void nx::core::NXApplication::RunMessageLoop()
{
    if (SUCCEEDED(CoInitialize(nullptr))) {
        {
            if (SUCCEEDED(m_mainWindow->Initialize())) {
                m_mainWindow->RunMessageLoop();
                m_mainWindow = nullptr;
                m_context = nullptr;
            }
        }
        CoUninitialize();
    }
}
