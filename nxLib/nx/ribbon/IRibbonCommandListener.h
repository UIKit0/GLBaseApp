#ifndef NX_RIBBON_IRIBBONEVENTLISTENER_H_
#define NX_RIBBON_IRIBBONEVENTLISTENER_H_

namespace nx
{
namespace ribbon
{
/**
 * ���{���C�x���g���X�i�[.
 */
class IRibbonCommandListener
{
public:
    /**
     * ���{���}�[�N�A�b�v�ɂ����ĊY���R�}���h�����������ꍇ�ɌĂяo����郁�\�b�h.
     * �R�}���h�n���h���ւ̃|�C���^��ݒ肷��΁A���̃R�}���h�n���h���փC�x���g�𑗂邱�Ƃ��ł���B
     * @param[in] typeID �R�}���h�^�C�v
     * @param[out] ppCommandHandler �R�}���h�n���h���ւ̃|�C���^
     * @return ���s����
     */
    virtual HRESULT OnCreateUICommand(
        __in UI_COMMANDTYPE typeID,
        __deref_out IUICommandHandler** commandHandler) = 0;
    /**
     * �R�}���h��Execute�R�}���h�̏���.
     * @param[in] verb ���[�U���J�n�����A�N�V����
     * @param[in] key �l���ς�����v���p�e�B�L�[�ւ̃|�C���^(NULL�ɂȂ�\��������)
     * @param[in] currentValue �v���p�e�B�L�[�̌��ݒl�ւ̃|�C���^(NULL�ɂȂ�\��������)
     * @param[in] commandExecutionProperties �R�}���h�X�e�[�g�v���p�e�B��v���p�e�B�l���܂�IUISimplePropertySet�ւ̃|�C���^
     * @return ���s����
     */
    virtual HRESULT Execute(
        UI_EXECUTIONVERB verb,
        __in_opt const PROPERTYKEY* key,
        __in_opt const PROPVARIANT* currentValue,
        __in_opt IUISimplePropertySet* commandExecutionProperties) = 0;
    /**
     * �v���p�e�B�̍X�V.
     * @param[in] key �X�V���ꂽ�v���p�e�B�L�[
     * @param[in] currentValue �v���p�e�B�L�[�̌��ݒl�ւ̃|�C���^(NULL�ɂȂ�\��������)
     * @param[in] newValue �{���\�b�h�����^�[������ۂɁA�v���p�e�B�L�[�̐V�����l���w���Ă���|�C���^
     * @return ���s����
     */
    virtual HRESULT UpdateProperty(
        __in REFPROPERTYKEY key,
        __in_opt const PROPVARIANT* currentValue,
        __out PROPVARIANT* newValue) = 0;
    /**
     * �A�v���P�[�V�����E�B���h�E���j�������ۂɌĂяo����郁�\�b�h.
     * @param[in] typeID �R�}���h�^�C�v
     * @param[in] commandHandler IUICommandHandler�ւ̃|�C���^(NULL�ɂȂ�\��������)
     */
    virtual HRESULT OnDestroyUICommand(
        __in UI_COMMANDTYPE typeID,
        __in_opt IUICommandHandler* commandHandler) = 0;

};
}
}

#endif // NX_RIBBON_IRIBBONEVENTLISTENER_H_