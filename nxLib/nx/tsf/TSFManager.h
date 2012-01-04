#ifndef NX_TSF_TSFMANAGER_H_
#define NX_TSF_TSFMANAGER_H_

#include "nx/nxLib.h"

namespace nx
{
namespace tsf
{
/**
 * TSF(Text Service Framework)�}�l�[�W��.
 */
class TSFManager
{
private:
    /**
     * �A�N�Z�����[�^�n���h��.
     */
    HACCEL m_hAccel;
    /**
     * �E�B���h�E�n���h��.
     */
    HWND m_hWnd;
    /**
     * �X���b�h�}�l�[�W��.
     */
    ITfThreadMgr *m_pThreadMgr;
    /**
     * �L�[�X�g���[�N�}�l�[�W��.
     */
    ITfKeystrokeMgr *m_pKeyMgr;
    /**
     * ���b�Z�[�W�|���v.
     */
    ITfMessagePump *m_pMsgPump;
    /**
     * �J�e�S���[�}�l�[�W��.
     */
    ITfCategoryMgr *m_pCategoryMgr;
    /**
     * �\�������}�l�[�W��.
     */
    ITfDisplayAttributeMgr *m_pDisplayAttrMgr;
    /**
     * �N���C�A���gID.
     */
    TfClientId m_tfClientID;
    /**
     * TSF���A�N�e�B�u���ǂ���.
     */
    bool m_isThreadMgrActivated;

public:
    /**
     * �R���X�g���N�^.
     */
    TSFManager(void);
    /**
     * �f�X�g���N�^.
     */
    ~TSFManager(void);
    /**
     * �A�N�Z�����[�^�̐ݒ�.
     * @param[in] hWnd �w�肳�ꂽ�E�B���h�E�̃C�x���g���A�N�Z�����[�^�Ƃ��ď�������
     * @param[in] hAccel �A�N�Z�����[�^�̃n���h��
     */
    void SetAccelerator(HWND hWnd, HACCEL hAccel) {
        m_hWnd = hWnd;
        m_hAccel = hAccel;
    }
    /**
     * ������.
     */
    void Initialize();
    /**
     * ���b�Z�[�W���[�v�̎��s.
     * TSF��p����A�v���P�[�V�����́A�K���A���̃��b�Z�[�W���[�v���Ăяo���Ȃ���΂Ȃ�Ȃ��B
     */
    int  RunMessageLoop();
    /**
     * �X���b�h�}�l�[�W���̎擾.
     * ITfThreadMgr�́A�e�L�X�g�T�[�r�X���A�N�e�B�u���A�N�e�B�u�ɂ��邽�߂�A
     * �h�L�������g�}�l�[�W�����쐬���邽�߁A�h�L�������g�R���e�L�X�g�t�H�[�J�X��
     * �����e�i���X���邽�߂ɃA�v���P�[�V�����ƃe�L�X�g�T�[�r�X�ɂ��g����B
     * @return �X���b�h�}�l�[�W��
     */
    ITfThreadMgr* GetThreadMgr() const  {
        return m_pThreadMgr;
    }
    /**
     * �L�[�X�g���[�N�}�l�[�W���̎擾.
     * ITfKeystrokeMgr�́ATSF�}�l�[�W���ɂ���������A�L�[�{�[�h�}�l�[�W����
     * ����肷�邽�߂ɁA�A�v���P�[�V�����ƃe�L�X�g�T�[�r�X�ɂ��g����B
     * @return �L�[�X�g���[�N�}�l�[�W��
     */
    ITfKeystrokeMgr* GetKeystrokeMgr() const {
        return m_pKeyMgr;
    }
    /**
     * ���b�Z�[�W�|���v�̎擾.
     * ITfMessagePump��TSF�}�l�[�W���ɂ���������A�A�v���P�[�V�������b�Z�[�W�L���[����
     * ���b�Z�[�W���擾���邽�߂ɃA�v���P�[�V�����ɂ��g����B�{�C���^�[�t�F�C�X�̃��\�b�h�́A
     * GetMessage��PeekMessage�̃��b�p�[�ł���B�{�C���^�[�t�F�C�X�́A�K�v�Ȏ��O�A�����
     * ���b�Z�[�W���������s���邽�߂��Ƃ�TSF�}�l�[�W���ɑ΂��ĉ\�ɂ���B
     * @return ���b�Z�[�W�|���v
     */
    ITfMessagePump* GetMessagePump() const {
        return m_pMsgPump;
    }
    /**
     * TSF�}�l�[�W���ɂ�芄�蓖�Ă�ꂽ�N���C�A���gID�̎擾.
     * @return �N���C�A���gID
     */
    TfClientId GetClientId() const {
        return m_tfClientID;
    }
    /**
     * �J�e�S���[�}�l�[�W���̎擾.
     * ITfCategoryMgr�́A�e�L�X�g�T�[�r�X�̂��߂̃I�u�W�F�N�g��
     * �J�e�S�����Ǘ�����BTSF�}�l�[�W���͂��̃C���^�[�t�F�C�X����������B
     * @return �J�e�S���[�}�l�[�W��
     */
    ITfCategoryMgr* GetCatetoryMgr() const {
        return m_pCategoryMgr;
    }
    /**
     * �\�������}�l�[�W���̏���.
     * ITfDisplayAttributeMgr�́ATSF�}�l�[�W���ɂ���������A
     * �\���������擾�A�񋓂��邽�߂ɃA�v���P�[�V�����ɂ��g����B
     * �X�̕\�������́AITfDisplayAttributeInfo����ăA�N�Z�X�����B
     * @return �\�������}�l�[�W��
     */
    ITfDisplayAttributeMgr* GetDisplayAttributeMgr() const {
        return m_pDisplayAttrMgr;
    }
    /**
     * TSF�̃A�N�e�B�x�[�g.
     * @return ���s����
     */
    HRESULT ActivateTSF();
    /**
     * TSF�̔�A�N�e�B�x�[�g.
     * @return ���s����.
     */
    HRESULT DeactivateTSF();
};

}
}

#endif // NX_TSF_TSFMANAGER_H_