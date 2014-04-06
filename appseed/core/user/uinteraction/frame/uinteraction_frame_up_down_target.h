#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class CLASS_DECL_CORE UpDownTarget :
            virtual public ::object
         {
         public:


            enum e_type
            {
               type_normal_frame,
               type_none,
               type_up,
               type_down,
            };


            e_type         m_eupdowntargettype;

            UpDownTarget();


            virtual void UpDownTargetAttach(CWorkSetDownUpInterface * pupdown);
            virtual void UpDownTargetDetach(CWorkSetDownUpInterface * pupdown);

            virtual bool OnUpDownTargetAttach(CWorkSetDownUpInterface * pupdown) = 0;
            virtual bool OnUpDownTargetDetach(CWorkSetDownUpInterface * pupdown) = 0;

            virtual bool up_down_target_is_up();
            virtual bool up_down_target_is_down();
            virtual bool is_up_down_target();


         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user








