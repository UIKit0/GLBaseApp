#ifndef NX_WIN_MAINWINDOW_H_
#define NX_WIN_MAINWINDOW_H_

#include "nx/nxLib.h"
#include "nx/touch/ManipulationResult.h"

namespace nx
{
namespace win
{
typedef std::function < nx::touch::ManipulationResult(
    std::shared_ptr<nx::win::MainWindow> mainWindow,
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam) > MainWindowMessageFunctor;

/**
 * ���C���E�B���h�E.
 */
class MainWindow :
    public std::enable_shared_from_this<MainWindow>
{
private:
    /**
     * ���C���E�B���h�E�̃E�B���h�E�n���h��.
     */
    HWND m_hwnd;
    /**
     * �E�B���h�E�̊�]���镝.
     */
    UINT m_preferredWidth;
    /**
     * �E�B���h�E�̊�]���鍂��.
     */
    UINT m_preferredHeight;
    /**
     * �E�B���h�E�^�C�g��.
     */
    std::wstring m_title;
    /**
     * �R���e�L�X�g.
     * ���̂�NXApplication�ɂĐ��������B
     */
    nx::core::GLContext *m_pContext;
    nx::tsf::TSFManager *m_pTSFManager;
    /**
     * ���{���t���[�����[�N.
     * �����Ŏ��̂����������B
     */
    std::unique_ptr<nx::ribbon::RibbonFramework> m_ribbonFramework;
    /**
     * �L�����o�X�E�B���h�E.
     * �����Ŏ��̂����������B
     */
    std::unique_ptr<nx::win::CanvasWindow> m_canvasWindow;

protected:
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam);

public:
    /**
     * �R���X�g���N�^.
     */
    MainWindow(void);
    /**
     * �f�X�g���N�^.
     */
    virtual ~MainWindow(void);
    /**
     * �R���e�L�X�g�̐ݒ�.
     * @param[in] context �R���e�L�X�g
     */
    void SetContext(nx::core::GLContext *pContext) {
        m_pContext = pContext;
    }
    /**
     * �R���e�L�X�g�̎擾.
     * @return �R���e�L�X�g
     */
    nx::core::GLContext* GetContext() const {
        return m_pContext;
    }
    void SetTSFManager(nx::tsf::TSFManager *pTSFManager) {
        m_pTSFManager = pTSFManager;
    }
    nx::tsf::TSFManager* GetTSFManager() const {
        return m_pTSFManager;
    }
    /**
     * ��]����E�B���h�E�T�C�Y.
     * @param[in] preferredWidth ��]����E�B���h�E��
     * @param[in] preferredHeight ��]����E�B���h�E����
     */
    void SetPreferredSize(UINT preferredWidth, UINT preferredHeight) {
        m_preferredWidth = preferredWidth;
        m_preferredHeight = preferredHeight;
    }
    /**
     * �E�B���h�E�^�C�g��.
     * @param[in] title �E�B���h�E�^�C�g��
     */
    void SetTitle(const std::wstring &title) {
        m_title = title;
    }
    /**
     * ������.
     * @return ���s����
     */
    HRESULT Initialize();
    /**
     * WM_CREATE�ŌĂяo����郁�\�b�h.
     * @param[in] hwnd �E�B���h�E�n���h��
     * @param[in] message �E�B���h�E���b�Z�[�W
     * @param[in] wParam WPARAM
     * @param[in] lParam LPARAM
     * @return ���s����
     */
    HRESULT OnCreate(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    /**
     * ���b�Z�[�W���[�v�̎��s.
     */
    void RunMessageLoop();
    /**
     * ���{���t���[�����[�N�̎擾.
     * @return ���{���t���[�����[�N
     */
    nx::ribbon::RibbonFramework* GetRibbonFramework() const {
        return m_ribbonFramework.get();
    }
    /**
     * ���{���̍����̎擾.
     * @return ���{���̍���
     */
    UINT GetRibbonHeight() const;
    /**
     * �L�����o�X�E�B���h�E�̎擾.
     * @return �L�����o�X�E�B���h�E
     */
    nx::win::CanvasWindow* GetCanvasWindow() const {
        return m_canvasWindow.get();
    }
    /**
     * �E�B���h�E�n���h���̎擾.
     */
    HWND GetHWnd() const {
        return m_hwnd;
    }
};

}
}

#endif // NX_WIN_MAINWINDOW_H_