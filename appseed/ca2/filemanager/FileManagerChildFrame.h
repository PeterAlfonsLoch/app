#pragma once


class FileManagerInterface;


namespace fs
{


   class item;
   class item_array;


} // namespace fs



class CLASS_DECL_ca2 FileManagerChildFrame :
   public simple_child_frame
{
public:
   FileManagerChildFrame(::ca::application * papp);

     simple_toolbar           m_toolbar;

   void install_message_handling(::ca::message::dispatch * pinterface);

   void OnChangeEditSearch();

   inline FileManagerInterface * GetFileManager()
   {
      return dynamic_cast < FileManagerInterface * > (GetActiveDocument());
   }
   void GetSelected(::fs::item_array &itema);

   bool CreateBars();
   bool DestroyBars();
   public:
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   virtual ~FileManagerChildFrame();

   DECL_GEN_SIGNAL(_001OnCreate)

   DECL_GEN_SIGNAL(_001OnAppLanguage)
   DECL_GEN_SIGNAL(_001OnShowWindow)
};

