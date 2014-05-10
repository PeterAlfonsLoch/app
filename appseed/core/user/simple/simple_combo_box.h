#pragma once


class CLASS_DECL_CORE simple_combo_box :
   virtual public ::user::combo_box
{
public:


   enum e_data_mode
   {

      data_mode_opaque,
      data_mode_string

   };


   e_data_mode                   m_edatamode;
   stringa                       m_straList;
   numeric_array < uint_ptr >    m_uiptra;



   


   simple_combo_box(sp(::base::application) papp);
   virtual ~simple_combo_box();

   

   
   virtual void _001SetCurSelByStringValue(const string & strValue, ::action::context eaction_source);
   virtual void _001SetCurSelByData(uint_ptr ui, ::action::context eaction_source);

   virtual string _001GetCurSelStringValue();



   virtual void _001OnDraw(::draw2d::graphics * pdc);

   virtual void _001GetListText(index iSel, string & str) const;
   virtual index _001FindListText(const string & str) const;
   virtual count _001GetListCount() const;


   virtual index AddString(const char * lpszString, uint_ptr dwItemData);
   virtual index AddString(const char * lpszString, const string & strValue);


};

