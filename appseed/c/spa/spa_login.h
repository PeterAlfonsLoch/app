#pragma once


class CLASS_DECL_c spa_login :
   public simple_ui
{

public:


   simple_label         m_labelUser;
   simple_edit          m_editlUser;
   simple_label         m_labelPassword;
   simple_password      m_password;

   
   spa_login(simple_ui * puiParent);
   virtual ~spa_login();


};