#pragma once


namespace filemanager
{


   class ContextMenu  :
      virtual public ::radix::object
   {
   public:


#ifdef WINDOWS
      IContextMenu *    m_pcontextmenu;
      IContextMenu2 *   m_pcontextmenu2;
#endif
      UINT              m_uiMinId;


      ContextMenu();
      virtual ~ContextMenu();


      void OnCommand(UINT uiId);
      void GetMessageString(UINT nID, string & rstrMessage);
      void GetVerb(UINT nID, string & rwstrMessage);


   };


} // namespace filemanager


