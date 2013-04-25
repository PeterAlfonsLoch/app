#pragma once


class CLASS_DECL_ca2 simple_combo_box :
   virtual public ::user::combo_box
{
public:


   stringa           m_straList;
   


   simple_combo_box(sp(::ca::application) papp);
   virtual ~simple_combo_box();

   

   
   


   virtual void _001OnDraw(::ca::graphics * pdc);

   virtual void _001GetListText(index iSel, string & str) const;
   virtual index _001FindListText(const string & str) const;
   virtual count _001GetListCount() const;



};

