#pragma once


namespace user
{


   class document_interface;


    class CLASS_DECL_BASE base_document :
        virtual public object
   {
   public:


      ::user::document_interface *   m_pdoc;


   };


} // namespace user




