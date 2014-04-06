#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class CLASS_DECL_CORE CWorkSetDownUpInterface :
            virtual public ::object
         {
         public:


            sp(UpDownTarget)       m_pupdowntarget;
            int32_t                  m_iType;
            int32_t                  m_iIndex;


            CWorkSetDownUpInterface();


            virtual bool WndFrameworkDownUpGetUpEnable() = 0;
            virtual bool WndFrameworkDownUpGetDownEnable() = 0;

            virtual void frame_Attach();
            virtual void frame_Detach();


         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user








