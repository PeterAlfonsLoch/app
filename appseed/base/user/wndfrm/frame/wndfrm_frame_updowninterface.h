#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         class CLASS_DECL_BASE WorkSetUpDownInterface :
            virtual public box
         {
         public:


            ::user::interaction *      m_pupdowntarget;
            e_updown                   m_eupdown;


            WorkSetUpDownInterface();
            virtual ~WorkSetUpDownInterface();

            virtual bool wfi_is_up();
            virtual bool wfi_is_down();
            virtual bool wfi_is_up_down();


         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user



