#pragma once


#include "ca/ca_message.h"
#include "user/user_create_context.h"


class CLASS_DECL_ca2 command_target_interface :
   virtual public ::ca::signalizable,
   virtual public ::ca::message::dispatch
{
public:

   class CLASS_DECL_ca2 command_signalid : public ::ca::signalid
   {
   public:

      command_signalid()
      {
      };
      virtual ~command_signalid();


      id m_id;

      virtual bool is_equal(::ca::signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if(pid == ::null())
            return false;
         return pid->m_id == m_id;
      };

      virtual bool matches(::ca::signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if(pid == ::null())
            return false;
         return pid->m_id == m_id;
      };

      virtual ::ca::signalid * copy()
      {
         command_signalid * pid = new command_signalid();
         pid->m_id = m_id;
         return pid;
      }
   };

   class CLASS_DECL_ca2 command_signalrange : public ::ca::signalid
   {
   public:

      command_signalrange()
      {
      };
      virtual ~command_signalrange();


      index m_iStart;
      index m_iEnd;

      virtual bool is_equal(::ca::signalid * pidParam)
      {
         command_signalrange * prange = dynamic_cast < command_signalrange * > (pidParam);
         if(prange == ::null())
            return false;
         return prange->m_iStart == m_iStart && prange->m_iEnd == m_iEnd;
      };

      virtual bool matches(::ca::signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if(pid == ::null())
            return false;
         return pid->m_id.is_number()
             && pid->m_id >= m_iStart
             && pid->m_id <= m_iEnd;
      };

      virtual ::ca::signalid * copy()
      {
         command_signalrange * pid = new command_signalrange();
         pid->m_iStart = m_iStart;
         pid->m_iEnd = m_iEnd;
         return pid;
      }
   };

   ::ca::signalid_array m_signalidaCommand;

   ::ca::dispatch  m_dispatchUpdateCmdUi;
   ::ca::dispatch  m_dispatchCommand;

   command_target_interface();
   command_target_interface(sp(::ca::application) papp);


   template < class T >
   bool connect_update_cmd_ui(const char * pszId, void (T::*pfn)(::ca::signal_object *))
   {
      return connect_update_cmd_ui(id(pszId), pfn);
   }
   template < class T >
   bool connect_command(const char * pszId, void (T::*pfn)(::ca::signal_object *))
   {
      return connect_command(id(pszId), pfn);
   }
   template < class T >
   bool connect_update_cmd_ui(id id, void (T::*pfn)(::ca::signal_object *))
   {
      command_signalid signalid;
      ::ca::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      return m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }
   template < class T >
   bool connect_command(id id, void (T::*pfn)(::ca::signal_object *))
   {
      command_signalid signalid;
      ::ca::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      return m_dispatchCommand.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }
   template < class T >
   bool connect_update_cmd_range_ui(int32_t iStart, int32_t iEnd, void (T::*pfn)(::ca::signal_object *))
   {
      command_signalrange signalrange;
      ::ca::signalid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      return m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }
   template < class T >
   bool connect_command_range(int32_t iStart, int32_t iEnd, void (T::*pfn)(::ca::signal_object *))
   {
      command_signalrange signalrange;
      ::ca::signalid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      return m_dispatchCommand.AddMessageHandler(pid, dynamic_cast < T *> (this), pfn, true);
   }

   virtual bool _001SendCommand(id id);
   virtual bool _001SendUpdateCmdUi(cmd_ui * pcmdUI);

   virtual bool _001OnCommand(id id);
   virtual bool _001HasCommandHandler(id id);
   virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

   //virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   //virtual bool _001HasCommandHandler(const char * pszId);

   void get_command_signal_array(BaseCmdMsg::e_type etype, ::ca::dispatch::signal_ptr_array & signalptra, id id);
};



class CLASS_DECL_ca2 command_target :
   virtual public ::ca::signalizable,
   virtual public command_target_interface
{
public:
   command_target();
   command_target(sp(::ca::application) papp);

   void CommonConstruct();

   void BeginWaitCursor();
   void EndWaitCursor();
   void RestoreWaitCursor();       // call after messagebox


   virtual bool handle(BaseCmdMsg * pcmdmsg);


// Overridables
   // route and dispatch standard command message types
   //   (more sophisticated than OnCommand)
//   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


// Implementation
public:
   virtual ~command_target() = 0;

protected:
   friend class view;

};


#include "user/user_check_interface.h"


namespace user
{


   class menu;


}


class CLASS_DECL_ca2 cmd_ui :
   public ::user::check_interface
{
public:


   id                      m_id;
   id                      m_idControl;     // menu item or other index

   index                   m_iIndex;
   ::count m_iCount;        // last + 1 for iterating m_iIndex

   // if a menu item
   ::user::menu *      m_pMenu;         // ::null() if not a menu
   ::user::menu *      m_pSubMenu;      // sub containing menu item
                     // if a popup sub menu - ID is for first in popup

   // if from some other ::ca::window
   sp(::user::interaction)   m_pOther;         // ::null() if a menu or not a ::ca::window

   bool                    m_bEnableChanged;
   bool                    m_bContinueRouting;
   bool                    m_bEnableIfHasCommandHandler;

   

   ::user::menu* m_pParentMenu;   // ::null() if parent menu not easily determined
                     //  (probably a secondary popup menu)


   cmd_ui(sp(::ca::application) papp);


// Operations to do in ON_UPDATE_COMMAND_UI
   virtual void Enable(bool bOn = TRUE);
   using ::user::check_interface::_001SetCheck;
   virtual void _001SetCheck(check::e_check echeck);   // 0, 1 or 2 (indeterminate)
   virtual void SetRadio(bool bOn = TRUE);
   virtual void SetText(const char * lpszText);

// Advanced operation
   void ContinueRouting();


   bool DoUpdate(command_target* pTarget, bool bDisableIfNoHndler);
};

// cmd_ui
inline void cmd_ui::ContinueRouting()
   { m_bContinueRouting = TRUE; }

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTestCmdUI - used to test for disabled commands before dispatching

class CTestCmdUI : public cmd_ui
{
public:
   CTestCmdUI(sp(::ca::application) papp);

public: // re-implementations only
   virtual void Enable(bool bOn);
   virtual void SetCheck(int32_t nCheck);
   virtual void SetRadio(bool bOn);
   virtual void SetText(const char *);

   bool m_bEnabled;
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
struct CLASS_DECL_ca2 __DISPMAP_ENTRY
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

struct CLASS_DECL_ca2 __EVENTSINKMAP_ENTRY
{
   __DISPMAP_ENTRY dispEntry;
   UINT nCtrlIDFirst;
   UINT nCtrlIDLast;
};

// DSC Sink state/reason codes passed to ca API ::fontopus::user event handlers
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
// ::ca::window implementation
namespace user
{
   class create_context;      // context for creating user interface things
}
namespace ca
{
   class create_context;      // context for creating things
}
struct CPrintInfo;          // print preview customization info

/////////////////////////////////////////////////////////////////////////////
// ::ca::window - a Microsoft Windows application ::ca::window


// ::ca::window::m_nFlags (generic to ::ca::window)
#define WF_TOOLTIPS         0x0001  // ::ca::window is enabled for tooltips
#define WF_TEMPHIDE         0x0002  // ::ca::window is temporarily hidden
#define WF_STAYDISABLED     0x0004  // ::ca::window should stay disabled
#define WF_OLECTLCONTAINER  0x0100  // some descendant is an OLE control
#define WF_TRACKINGTOOLTIPS 0x0400  // ::ca::window is enabled for tracking tooltips

// ::ca::window::m_nFlags (specific to frame_window)
#define WF_STAYACTIVE       0x0020  // look active even though not active
#define WF_NOPOPMSG         0x0040  // ignore WM_POPMESSAGESTRING calls
#define WF_MODALDISABLE     0x0080  // ::ca::window is disabled
#define WF_KEEPMINIACTIVE   0x0200  // stay activate even though you are deactivated


#define WF_NOWIN32ISDIALOGMSG   0x0800
#define WF_ISWINFORMSVIEWWND    0x1000

// flags for ::ca::window::RunModalLoop
#define MLF_NOIDLEMSG       0x0001  // don't send WM_ENTERIDLE messages
#define MLF_NOKICKIDLE      0x0002  // don't send WM_KICKIDLE messages
#define MLF_SHOWONIDLE      0x0004  // show ::ca::window if not visible at idle time

// extra ca API defined TTF_ flags for TOOLINFO::uFlags
#define TTF_NOTBUTTON       0x80000000L // no status help on buttondown
#define TTF_ALWAYSTIP       0x40000000L // always show the tip even if not active
