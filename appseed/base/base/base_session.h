#pragma once




class CLASS_DECL_BASE base_session :
   virtual public base_application
{
public:


   ::plane::session *      m_pplanesession;

   string_map < sp(base_application) >                    m_mapApplication;

};