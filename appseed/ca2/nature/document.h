#pragma once

namespace nature
{

   class view;
   class frame;

   class CLASS_DECL_ca document :
      public ::userbase::document
   {
   public:
      document(::ax::application * papp);

      ::view *     get_nature_view();
      frame *    get_nature_frame();
      
      DECL_GEN_VSIGNAL(data_on_after_change)

      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      bool _001OnCommand(id id);



      virtual BOOL on_new_document();
      virtual ~document();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(var varFile);

   };


} // namespace nature