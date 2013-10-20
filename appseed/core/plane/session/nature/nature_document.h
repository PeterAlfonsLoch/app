#pragma once


namespace nature
{


   class view;
   class frame;


   class CLASS_DECL_CORE document :
      public ::user::document
   {
   public:


      document(sp(base_application) papp);
      virtual ~document();

      sp(::user::view)     get_nature_view();
      sp(frame)    get_nature_frame();
      

      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      bool _001OnCommand(id id);


      virtual bool on_new_document();

      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(var varFile);


      DECL_GEN_VSIGNAL(data_on_after_change)


   };


} // namespace nature



