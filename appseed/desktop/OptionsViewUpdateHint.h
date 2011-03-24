// OptionsViewUpdateHint.h: interface for the OptionsViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONSVIEWUPDATEHINT_H__6E718C19_D4E0_454C_B88E_FDEF3A56C509__INCLUDED_)
#define AFX_OPTIONSVIEWUPDATEHINT_H__6E718C19_D4E0_454C_B88E_FDEF3A56C509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EOptionsView
{
   OptionsViewNone,
   OptionsViewFileAssociation,
   OptionsViewAudioDevices,
   OptionsViewKaraoke,
};

class BaseView;

class OptionsViewUpdateHint :
   public base_object  
{
public:
   enum EType
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnShowView,
      TypeSetViewVmsDataKey,
   };
   DECLARE_DYNAMIC(OptionsViewUpdateHint)
public:
	void SetType(EType etype);
	bool IsTypeOf(EType etype);

	OptionsViewUpdateHint();
	virtual ~OptionsViewUpdateHint();

   EOptionsView      m_eview;
   BaseView *        m_pview;
   _vms::DataKey     m_datakey;
protected:
   EType m_etype;

};

#endif // !defined(AFX_OPTIONSVIEWUPDATEHINT_H__6E718C19_D4E0_454C_B88E_FDEF3A56C509__INCLUDED_)
