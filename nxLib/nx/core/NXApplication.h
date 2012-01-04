#ifndef NX_CORE_NXAPPLICATION_H_
#define NX_CORE_NXAPPLICATION_H_

#include "nx/nxLib.h"

namespace nx
{
namespace core
{
/**
 * �A�v���P�[�V����.
 */
class NXApplication
{
private:
    /**
     * �R���e�L�X�g.
     * �����Ŏ��̂����������B
     */
    std::unique_ptr<nx::core::GLContext> m_context;
    /**
     * ���C���E�B���h�E.
     * �����Ŏ��̂����������B
     */
    std::unique_ptr<nx::win::MainWindow> m_mainWindow;
    /**
     * TSF�}�l�[�W��.
     * �����Ŏ��̂����������B
     */
    std::unique_ptr<nx::tsf::TSFManager> m_tsfManager;
    /**
     * ���O�t�@�C���p�X.
     */
    std::wstring m_logFilePath;
    /**
     * MUI DLL��.
     */
    std::wstring m_muiDllName;
public:
    /**
     * �R���X�g���N�^.
     * @param[in] hInstance ���݂̃A�v���P�[�V�����C���X�^���X�̃n���h��
     * @param[in] hPrevInstance �O�̃A�v���P�[�V�����C���X�^���X�̃n���h��(���NULL)
     * @param[in] lpCmdLine �v���O�������������R�}���h���C��
     * @param[in] nCmdShow �ǂ̂悤�ɃA�v���P�[�V������\�����邩�𐧌�(�ŏ������ĕ\���Ȃ�)
     */
    NXApplication(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow);
    /**
     * �f�X�g���N�^.
     */
    virtual ~NXApplication() {}
    /**
     * ���O�t�@�C���p�X.
     * ���[�U�v���t�@�C����"AppData\Local"�t�H���_�ȉ��̎w�肵���p�X�Ƀ��O���o�͂����B
     * �K���t�H���_���܂ރp�X���w�肵�Ȃ���΂Ȃ�Ȃ��B�܂�A"logfile.log"�͕s�ƂȂ�A
     * "folder1\logfile.log"�̂悤�Ƀt�H���_���w�肵�Ȃ���΂Ȃ�Ȃ��B
     * @param[in] logFilePath ���O�t�@�C���p�X
     */
    void SetLogFilePath(const std::wstring &logFilePath) {
        m_logFilePath = logFilePath;
    }
    /**
     * MUI DLL��.
     * @param[in] muiDllName MUI DLL��
     */
    void SetMUIDllName(const std::wstring &muiDllName) {
        m_muiDllName = muiDllName;
    }
    /**
     * ���C���E�B���h�E�̎擾.
     * @return ���C���E�B���h�E
     */
    nx::win::MainWindow* GetMainWindow() const {
        return m_mainWindow.get();
    }
    /**
     * �R���e�L�X�g�̎擾.
     * @return �R���e�L�X�g
     */
    nx::core::GLContext* GetContext() const {
        return m_context.get();
    }
    nx::tsf::TSFManager* GetTSFManager() const {
        return m_tsfManager.get();
    }
    /**
     * ������.
     * @return ���s����
     */
    HRESULT Initialize();
    /**
     * ���b�Z�[�W���[�v�̎��s.
     */
    void RunMessageLoop();
};
}
}

#endif // NX_CORE_NXAPPLICATION_H_