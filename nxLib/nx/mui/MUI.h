#ifndef NX_MUI_MUI_H_
#define NX_MUI_MUI_H_

namespace nx
{
namespace mui
{
/**
 * MUI(�}���`�����K�����[�U�C���^�[�t�F�C�X).
 */
class MUI
{
private:
    MUI(void);
    ~MUI(void);
    static HMODULE s_hModule;

public:
    /**
     * MUI�̏�����.
     * @param[in] dllName �����ꃊ�\�[�X���܂�DLL��
     * @return ���s����
     */
    static HRESULT Initialize(const std::wstring &dllName);
    /**
     * MUI�̃��\�[�X���܂�DLL�̃��W���[���n���h���̎擾.
     * @return ���W���[���n���h��
     */
    static HMODULE GetHModule() {
        return s_hModule;
    }
    /**
     * �����񃊃\�[�X�̎擾.
     * @param[in] uID ���\�[�XID
     */
    static const wchar_t * GetString(UINT uID);
};

}
}

#endif // NX_MUI_MUI_H_