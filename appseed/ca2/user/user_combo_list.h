#pragma once


namespace user
{

   
   class combo_box;


   class CLASS_DECL_ca2 combo_list : 
      virtual public ::user::control
   {
   public:


      combo_box *    m_pcombo;


      combo_list();
      virtual ~combo_list();


      virtual void install_message_handling(::gen::message::dispatch * pdispatch);


      virtual void _001OnDraw(::ca::graphics * pdc);


      virtual void query_full_size(LPSIZE lpsize) const;

      virtual int _001GetItemHeight() const;

      const char * GetIconWndClass(DWORD dwDefaultStyle, const char * pszMatter);



   };


} //  namespace user



