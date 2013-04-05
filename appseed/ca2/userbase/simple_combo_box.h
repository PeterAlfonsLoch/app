#pragma once


class CLASS_DECL_ca2 simple_combo_box :
   public ::userbase::combo_box
{
public:


   stringa           m_straList;
   


   simple_combo_box(::ca::applicationsp papp);
   virtual ~simple_combo_box();

   

   
   


   virtual void _001OnDraw(::ca::graphics * pdc);

   virtual void _001GetListText(index iSel, string & str) const;
   virtual index _001FindListText(const string & str) const;
   virtual count _001GetListCount() const;



};

