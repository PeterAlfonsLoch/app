#pragma once

namespace netshareservercfg
{

   class CLASS_DECL_CA2_NETSHARESERVERCFG application :
      public ::cube::application
   {
   public:
      application(void);
      virtual ~application(void);

      bool initialize_instance();
      BOOL exit_instance();

      void _001OnFileNew();

	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   		


   };

} // namespace netshareservercfg