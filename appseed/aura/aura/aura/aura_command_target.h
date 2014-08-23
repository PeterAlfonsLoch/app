#pragma once





class CLASS_DECL_AURA command_target_interface :
   virtual public signalizable,
   virtual public ::message::dispatch
{
public:

   class CLASS_DECL_AURA command_signalid : public signalid
   {
   public:

      command_signalid()
      {
      };
      virtual ~command_signalid();


      id m_id;

      virtual bool is_equal(signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if (pid == NULL)
            return false;
         return pid->m_id == m_id;
      };

      virtual bool matches(signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if (pid == NULL)
            return false;
         return pid->m_id == m_id;
      };

      virtual signalid * copy()
      {
         command_signalid * pid = new command_signalid();
         pid->m_id = m_id;
         return pid;
      }
   };

   class CLASS_DECL_AURA command_signalrange : public signalid
   {
   public:

      command_signalrange()
      {
      };
      virtual ~command_signalrange();


      index m_iStart;
      index m_iEnd;

      virtual bool is_equal(signalid * pidParam)
      {
         command_signalrange * prange = dynamic_cast < command_signalrange * > (pidParam);
         if (prange == NULL)
            return false;
         return prange->m_iStart == m_iStart && prange->m_iEnd == m_iEnd;
      };

      virtual bool matches(signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if (pid == NULL)
            return false;
         return
            pid->m_id >= m_iStart
            && pid->m_id <= m_iEnd;
      };

      virtual signalid * copy()
      {
         command_signalrange * pid = new command_signalrange();
         pid->m_iStart = m_iStart;
         pid->m_iEnd = m_iEnd;
         return pid;
      }
   };

   ::signalid_array m_signalidaCommand;

   ::dispatch  m_dispatchUpdateCmdUi;
   ::dispatch  m_dispatchCommand;

   command_target_interface();
   command_target_interface(sp(::aura::application) papp);


   template < class T >
   bool connect_update_cmd_ui(const char * pszId, void (T::*pfn)(signal_details *))
   {
      return connect_update_cmd_ui(id(pszId), pfn);
   }
   template < class T >
   bool connect_command(const char * pszId, void (T::*pfn)(signal_details *))
   {
      return connect_command(id(pszId), pfn);
   }
   template < class T >
   bool connect_update_cmd_ui(id id, void (T::*pfn)(signal_details *))
   {
      command_signalid signalid;
      ::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      return m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }
   template < class T >
   bool connect_command(id id, void (T::*pfn)(signal_details *))
   {
      command_signalid signalid;
      ::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      return m_dispatchCommand.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }
   template < class T >
   bool connect_update_cmd_range_ui(int32_t iStart, int32_t iEnd, void (T::*pfn)(signal_details *))
   {
      command_signalrange signalrange;
      ::signalid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      return m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }
   template < class T >
   bool connect_command_range(int32_t iStart, int32_t iEnd, void (T::*pfn)(signal_details *))
   {
      command_signalrange signalrange;
      ::signalid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      return m_dispatchCommand.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }

   virtual bool _001SendCommand(id id);
   virtual bool _001SendUpdateCmdUi(cmd_ui * pcmdUI);

   virtual bool on_simple_action(id id);
   virtual bool _001HasCommandHandler(id id);
   virtual bool on_simple_update(cmd_ui * pcmdui);

   //virtual bool on_simple_update(cmd_ui * pcmdui);
   virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);
   //virtual bool _001HasCommandHandler(const char * pszId);

   void get_command_signal_array(::aura::cmd_msg::e_type etype, ::dispatch::signal_item_ptr_array & signalptra, id id);


   virtual void install_message_handling(::message::dispatch * pdispatch);


};



class CLASS_DECL_AURA command_target :
   virtual public command_target_interface
{
public:
   command_target();
   command_target(sp(::aura::application) papp);

   void CommonConstruct();

   void BeginWaitCursor();
   void EndWaitCursor();
   void RestoreWaitCursor();       // call after messagebox


   virtual bool handle(::aura::cmd_msg * pcmdmsg);


   // Overridables
   // route and dispatch standard command message types
   //   (more sophisticated than OnCommand)
   //   virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);


   // Implementation
public:
   virtual ~command_target() = 0;


};




namespace user
{


   class menu;


}


class CLASS_DECL_AURA cmd_ui
{
public:


   id                      m_id;
   id                      m_idControl;     // menu item or other index

   index                   m_iIndex;
   ::count m_iCount;        // last + 1 for iterating m_iIndex

   // if a menu item
   ::user::menu *      m_pMenu;         // NULL if not a menu
   ::user::menu *      m_pSubMenu;      // sub containing menu item
   // if a popup sub menu - ID is for first in popup

   // if from some other interaction_impl
   ::user::interaction *   m_pOther;         // NULL if a menu or not a interaction_impl

   bool                    m_bEnableChanged;
   bool                    m_bContinueRouting;
   bool                    m_bEnableIfHasCommandHandler;

   ::user::menu* m_pParentMenu;   // NULL if parent menu not easily determined
   //  (probably a secondary popup menu)


   cmd_ui(sp(::aura::application) papp);


   // Operations to do in ON_UPDATE_COMMAND_UI
   virtual void Enable(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
   virtual void _001SetCheck(bool bCheck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(check::e_check echeck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void SetRadio(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
   virtual void SetText(const char * lpszText, ::action::context actioncontext = ::action::source_system);

   // Advanced operation
   void ContinueRouting();


   bool DoUpdate(command_target* pTarget, bool bDisableIfNoHndler);
};

// cmd_ui
inline void cmd_ui::ContinueRouting()
{
   m_bContinueRouting = TRUE;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTestCmdUI - used to test for disabled commands before dispatching

class CTestCmdUI : public cmd_ui
{
public:


   bool                    m_bEnabled;
   check::e_check          m_echeck;
   string                  m_strText;
   bool                    m_bRadio;
   bool                    m_bRadioChanged;


   CTestCmdUI(sp(::aura::application) papp);


   virtual void Enable(bool bOn, ::action::context actioncontext = ::action::source_system);
   virtual void _001SetCheck(bool bCheck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(check::e_check echeck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void SetRadio(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
   virtual void SetText(const char * lpszText, ::action::context actioncontext = ::action::source_system);


};


// special cmd_ui derived classes are used for other UI paradigms
//  like toolbar buttons and status indicators

// pointer to member function
#ifndef __MSG_CALL
#define __MSG_CALL
#endif
typedef void (__MSG_CALL command_target::*__PMSG)();

enum __DISPMAP_FLAGS
{
   afxDispCustom = 0,
   afxDispStock = 1
};

//IA64: __DISPMAP_ENTRY could be ordered more efficiently to reduce size
// bloat from alignment
#pragma warning( disable: 4121 )
struct CLASS_DECL_AURA __DISPMAP_ENTRY
{
   const char * lpszName;       // member/property name
   long lDispID;           // DISPID (may be DISPID_UNKNOWN)
   const char * lpszParams;      // member parameter description
   WORD vt;                // return value type / or type of property
   __PMSG pfn;           // normal member On<membercall> or, OnGet<property>
   __PMSG pfnSet;        // special member for OnSet<property>
   size_t nPropOffset;     // property offset
   __DISPMAP_FLAGS flags;// flags (e.g. stock/custom)
};
#pragma warning( default: 4121 )

struct CLASS_DECL_AURA __EVENTSINKMAP_ENTRY
{
   __DISPMAP_ENTRY dispEntry;
   UINT nCtrlIDFirst;
   UINT nCtrlIDLast;
};

// DSC Sink state/reason codes passed to core API ::fontopus::user event handlers
enum DSCSTATE
{
   dscNoState = 0,
   dscOKToDo,
   dscCancelled,
   dscSyncBefore,
   dscAboutToDo,
   dscFailedToDo,
   dscSyncAfter,
   dscDidEvent
};

enum DSCREASON
{
   dscNoReason = 0,
   dscClose,
   dscCommit,
   dscDelete,
   dscEdit,
   dscInsert,
   dscModify,
   dscMove
};

/////////////////////////////////////////////////////////////////////////////
// interaction_impl implementation
namespace user
{
   class create_context;      // context for creating user interface things
}
namespace core
{
   class create_context;      // context for creating things
}
struct CPrintInfo;          // print preview customization info

/////////////////////////////////////////////////////////////////////////////
// interaction_impl - a Microsoft Windows application interaction_impl


// interaction_impl::m_nFlags (generic to interaction_impl)
#define WF_TOOLTIPS         0x0001  // interaction_impl is enabled for tooltips
#define WF_TEMPHIDE         0x0002  // interaction_impl is temporarily hidden
#define WF_STAYDISABLED     0x0004  // interaction_impl should stay disabled
#define WF_OLECTLCONTAINER  0x0100  // some descendant is an OLE control
#define WF_TRACKINGTOOLTIPS 0x0400  // interaction_impl is enabled for tracking tooltips

// interaction_impl::m_nFlags (specific to frame_window)
#define WF_STAYACTIVE       0x0020  // look active even though not active
#define WF_NOPOPMSG         0x0040  // ignore WM_POPMESSAGESTRING calls
#define WF_MODALDISABLE     0x0080  // interaction_impl is disabled
#define WF_KEEPMINIACTIVE   0x0200  // stay activate even though you are deactivated


#define WF_NOWIN32ISDIALOGMSG   0x0800
#define WF_ISWINFORMSVIEWWND    0x1000

// flags for interaction_impl::RunModalLoop
#define MLF_NOIDLEMSG       0x0001  // don't send WM_ENTERIDLE messages
#define MLF_NOKICKIDLE      0x0002  // don't send WM_KICKIDLE messages
#define MLF_SHOWONIDLE      0x0004  // show interaction_impl if not visible at idle time

// extra core API defined TTF_ flags for TOOLINFO::uFlags
#define TTF_NOTBUTTON       0x80000000L // no status help on buttondown
#define TTF_ALWAYSTIP       0x40000000L // always show the tip even if not active
