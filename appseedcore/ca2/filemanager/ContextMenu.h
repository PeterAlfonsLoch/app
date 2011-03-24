#pragma once

namespace filemanager
{

   class ContextMenu  : 
      virtual public ::radix::object
   {
   public:
      ContextMenu();
      virtual ~ContextMenu();
   public:
      void OnCommand(UINT uiId);
      void GetMessageString(UINT nID, string & rstrMessage);
      void GetVerb(UINT nID, string & rwstrMessage);

      IContextMenu *    m_pcontextmenu;
      IContextMenu2 *   m_pcontextmenu2;
      UINT              m_uiMinId;            

   };

} // namespace filemanager
