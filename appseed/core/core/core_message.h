#pragma once

#ifdef METROWIN

#include <agile.h>

typedef struct tagCREATESTRUCTA {
    LPVOID      lpCreateParams;
    HINSTANCE   hInstance;
    HMENU       hMenu;
    oswindow        oswindowParent;
    int32_t         cy;
    int32_t         cx;
    int32_t         y;
    int32_t         x;
    LONG        style;
    LPCSTR      lpszName;
    LPCSTR      lpszClass;
    uint32_t       dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;
typedef struct tagCREATESTRUCTW {
    LPVOID      lpCreateParams;
    HINSTANCE   hInstance;
    HMENU       hMenu;
    oswindow    hwndParent;
    int32_t         cy;
    int32_t         cx;
    int32_t         y;
    int32_t         x;
    LONG        style;
    LPCWSTR     lpszName;
    LPCWSTR     lpszClass;
    uint32_t       dwExStyle;
} CREATESTRUCTW, *LPCREATESTRUCTW;
#ifdef UNICODE
typedef CREATESTRUCTW CREATESTRUCT;
typedef LPCREATESTRUCTW LPCREATESTRUCT;
#else
typedef CREATESTRUCTA CREATESTRUCT;
typedef LPCREATESTRUCTA LPCREATESTRUCT;
#endif // UNICODE

#endif

class cmd_ui;


namespace draw2d
{


   class graphics;


} // namespace draw2d


namespace user
{


   class window;


} // namespace user


#include "user/user_key_enum.h"

#define CN_UPDATE_COMMAND_UI 23
#define WM_REFLECT_BASE 2048
#define MPARAM uint32_t
#define NPARAM uint32_t
#define OPARAM uint32_t

// message
#define MX_APPLANGUAGE 1000

class BaseCommand;

#define USER_MESSAGE 1024

#if defined(LINUX) || defined(MACOS)
#define WM_APP 0x8000
#define WM_USER                         0x0400
#endif

enum e_message
{

   message_create = USER_MESSAGE,
   message_event = WM_APP + 1000,
   message_property = WM_APP + 1001,
   message_pos_create = WM_USER + 193,
   message_frame_initial_update,

};

namespace message
{


   CLASS_DECL_ca2 UINT translate_to_os_message(UINT uiMessage);

   class base;


   enum e_prototype
   {
      PrototypeNone,
      PrototypeMouse,
      PrototypeScroll,
      PrototypeSize,
      PrototypeMove,
      PrototypeMeasureItem,
      PrototypeCreate,
      PrototypeActivate,
      PrototypeNcActivate,
      PrototypeEraseBkgnd,
      PrototypeShowWindow,
      PrototypeSetCursor,
      PrototypeTimer,
      PrototypeMouseWheel,
      PrototypeInitMenuPopup,
      PrototypeNcHitTest,
      PrototypeKey,
      PrototypeNotify,
      PrototypeUpdateCommandUserInterface,
      PrototypeCtlColor,
      PrototypeCtlColorReflect,
      PrototypeSetFocus,
      PrototypeCommand,
      PrototypeWindowPos,
      PrototypeNcCalcSize,

      PrototypeOnDraw,
   };

   ::signal * CreateSignal();

/*   class CLASS_DECL_ca2 Handler
   {
   public:
      Handler();
      virtual ~Handler();
      virtual int32_t OnMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam);
   };
   */

   class CLASS_DECL_ca2 dispatch :
      virtual public object
   {
   public:

      class CLASS_DECL_ca2 HandlerItemBase :
         virtual public root
      {
      public:
         virtual ~HandlerItemBase();
         virtual signalizable* get_signalizable() = 0;
      };

      template < class T >
      class HandlerItem : public HandlerItemBase
      {
      public:
         T *                     m_psignalizable;
         // Pointer to signal object directly associate with the
         // prototype.
         // This is a cached value and not the
         // storage holder of the object.
         virtual signalizable* get_signalizable() { return m_psignalizable; }
      };

      class CLASS_DECL_ca2 HandlerItemArray :
         public array < HandlerItemBase *, HandlerItemBase *>
      {
      public:
         virtual ~HandlerItemArray();
         bool HasSignalizable(signalizable* psignalizable);
      };

      class CLASS_DECL_ca2 Signal :
         virtual public element
      {
      public:
         e_prototype          m_eprototype;
         UINT                 m_uiMessage;
         UINT                 m_uiCode;
         UINT                 m_uiIdStart;
         UINT                 m_uiIdEnd;
         sp(::signal)     m_psignal;

         HandlerItemArray     m_handlera;

         Signal();
         ~Signal();
      };

      class CLASS_DECL_ca2 SignalPtrArray :
         public array < Signal * , Signal * >
      {
      };

      class CLASS_DECL_ca2 SignalArray :
         public spa(Signal)
      {
      public:
         virtual ~SignalArray();
         void GetSignalsByMessage(SignalPtrArray & signalptra, UINT uiMessage, UINT uiCode, UINT uiId);
         Signal * GetSignalByMessage(UINT uiMessage, UINT uiCode, UINT uiIdStart, UINT uiIdEnd);
      };

         
      dispatch();
      virtual ~dispatch();


      virtual void _on_start_user_message_handler();

      virtual sp(base_application) calc_app();

      virtual sp(base) peek_message(LPMESSAGE lpmsg, sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
      virtual sp(base) get_message(LPMESSAGE lpmsg, sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
      virtual sp(base) peek_message(sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
      virtual sp(base) get_message(sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

      virtual sp(base) get_base(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam);
      virtual sp(base) get_base(LPMESSAGE lpmsg, sp(::user::interaction) pwnd = NULL);

#ifdef LINUX

      virtual sp(base) get_base(XEvent * pevent, sp(::user::interaction) pwnd = NULL);

#endif

      void RemoveMessageHandler(signalizable* psignalizable);
      sp(::user::window) _GetWnd();
      // Prototype_bool_WPARAM_LPARAM;

      template < class T >
      bool AddMessageHandler(
         UINT message,
         UINT uiCode,
         UINT uiIdStart,
         UINT uiIdEnd,
         T * psignalizable,
         void (T::*pfn)(signal_details *),
         bool bAddUnique = true)
      {
         Signal * psignal = m_signala.GetSignalByMessage(message, uiCode, uiIdStart, uiIdEnd);
         // If not found a existing Signal, create one
         if(psignal == NULL)
         {
            psignal                    = canew(Signal);
            psignal->m_uiMessage       = message;
            psignal->m_uiCode          = uiCode;
            psignal->m_uiIdStart       = uiIdStart;
            psignal->m_uiIdEnd         = uiIdEnd;
            psignal->m_eprototype      = GetMessagePrototype(message, 0);
            psignal->m_psignal         = canew(::signal());
            psignal->m_psignal->connect(psignalizable, pfn);
            HandlerItem <T> * pitem    = canew(HandlerItem < T >);
            pitem->m_psignalizable     = psignalizable;
            psignal->m_handlera.add(pitem);
            m_signala.add(psignal);
         }
         else
         {
            if(bAddUnique && psignal->m_psignal->is_connected(psignalizable, pfn))
               return true;
            // If a matching Signal is found, connect to
            // this signal.
            psignal->m_psignal->connect(psignalizable, pfn);
            HandlerItem <T> * pitem    = canew(HandlerItem<T>);
            pitem->m_psignalizable     = psignalizable;
            psignal->m_handlera.add(pitem);
         }
         m_iHandling++;
         return true;
      }


      virtual e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001ClearMessageHandling();

      int32_t                    m_iHandling;
      SignalArray                m_signala;
      ::signal               m_signalInstallMessageHandling;
//         sp(manual_reset_event)     m_pevOk;
//         sp(mutex)                  m_pmutex;

      virtual void _start_user_message_handler(signal_details * pobj);

      void (dispatch::*m_pfnDispatchWindowProc)(signal_details * pobj);

      virtual void _user_message_handler(signal_details * pobj);
      //bool _iguimessageDispatchCommandMessage(BaseCommand * pcommand, bool & b);
      // return TRUE to stop routing
#ifdef WINDOWS
      virtual bool igui_RelayEvent(LPMESSAGE lpmsg);
#endif
      virtual bool OnWndMsgPosCreate();


//         inline manual_reset_event * dispatch_event_ok() { if(m_pevOk != NULL) return m_pevOk; m_pevOk = canew(manual_reset_event(NULL)); return m_pevOk; }
//         inline mutex * dispatch_mutex() { if(m_pmutex != NULL) return m_pmutex; m_pmutex = canew(::mutex(NULL)); return m_pmutex; }
   };

#undef new

   class CLASS_DECL_ca2 base :
         public signal_details
      {
      public:


         sp(::user::interaction)   m_pwnd;
         UINT                    m_uiMessage;
         WPARAM                  m_wparam;
         lparam                  m_lparam;
         bool                    m_bConditional;

         base(sp(base_application) papp, ::signal * psignal = NULL);
         base(sp(base_application) papp, sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);



         virtual void set_lresult(LRESULT lresult);
         virtual LRESULT & get_lresult();
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam);
      protected:
         LRESULT * m_plresult;
         LRESULT  m_lresult;
      };

      class CLASS_DECL_ca2 create : public base
      {
      public:

         create(sp(base_application) papp) : element(papp), message::base(papp) {}
         LPCREATESTRUCT m_lpcreatestruct;

         virtual void set_lresult(LRESULT lresult);
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
         virtual void error(const char * lpcszErrorMessage);
         virtual void failed(const char * lpcszErrorMessage);
      };

      class CLASS_DECL_ca2 timer : public base
      {
      public:


         timer(sp(base_application) papp) : element(papp), message::base(papp) {}
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
         UINT m_nIDEvent;
      };

      class CLASS_DECL_ca2 activate : public base
      {
      public:


         UINT  m_nState;
         sp(::user::interaction) m_pWndOther;
         bool  m_bMinimized;


         activate(sp(base_application) papp);

         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };

      class CLASS_DECL_ca2 move : public base
      {
      public:


         move(sp(base_application) papp) : element(papp), message::base(papp) {}
         point m_pt;
      };

      class CLASS_DECL_ca2 size : public base
      {
      public:


         size(sp(base_application) papp) : element(papp), message::base(papp) {}
         UINT     m_nType;
         ::size   m_size;
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };


      class CLASS_DECL_ca2 scroll : public base
      {
      public:


         scroll(sp(base_application) papp) : element(papp), message::base(papp) {}
         UINT              m_nSBCode;
         int32_t           m_nPos;
         sp(::user::interaction)  m_pScrollBar;
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };


      class CLASS_DECL_ca2 mouse : public base
      {
      public:


         uint_ptr                m_nFlags;
         point                   m_pt;
         ::visual::e_cursor      m_ecursor;
         bool                    m_bTranslated;

         mouse(sp(base_application) papp);
         virtual ~mouse();

         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
         static mouse * cast(signal_details * pobj) { return (mouse *) pobj; }
      };

      class CLASS_DECL_ca2 mouse_wheel : public mouse
      {
      public:


         mouse_wheel(sp(base_application) papp) : element(papp), mouse(papp) {}
         UINT     GetFlags();
         int16_t    GetDelta();
         point    GetPoint();

         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };


      class CLASS_DECL_ca2 mouse_activate : public base
      {
      public:


         mouse_activate(sp(base_application) papp) : element(papp), message::base(papp) {}
         sp(::user::interaction) GetDesktopWindow();
         UINT GetHitTest();
         UINT GetMessage();
      };

      class CLASS_DECL_ca2 context_menu : public base
      {
      public:


         context_menu(sp(base_application) papp) : element(papp), message::base(papp) {}
         sp(::user::window) GetWindow();
         point GetPoint();
      };


      class CLASS_DECL_ca2 set_cursor : public base
      {
      public:


         set_cursor(sp(base_application) papp) : element(papp), message::base(papp) {}
         sp(::user::window) m_pWnd;
         UINT m_nHitTest;
         UINT m_message;
      };

      class CLASS_DECL_ca2 show_window : public base
      {
      public:


         show_window(sp(base_application) papp) : element(papp), message::base(papp) {}
         bool m_bShow;
         UINT  m_nStatus;
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };

      class CLASS_DECL_ca2 on_draw : public base
      {
      public:


         on_draw(sp(base_application) papp) : element(papp), message::base(papp) {}
         ::draw2d::graphics * m_pdc;
      };

      class CLASS_DECL_ca2 erase_bkgnd : public base
      {
      public:


         ::draw2d::graphics * m_pdc;


         erase_bkgnd(sp(base_application) papp);

         void set_result(bool bResult);

      };

      // WM_PAINT -> base
      // WM_MOUSELEAVE -> base

      class CLASS_DECL_ca2 nchittest : public base
      {
      public:


         nchittest(sp(base_application) papp) : element(papp), message::base(papp) {}
         point m_pt;
      };

      class CLASS_DECL_ca2 key : public base
      {
      public:


         uint_ptr m_nChar;
         UINT m_nRepCnt;
         UINT m_nFlags;

         ::user::e_key     m_ekey;

/*#ifdef METROWIN

         Platform::Agile < ::Windows::UI::Core::CharacterReceivedEventArgs ^  > m_charrecv;
         Platform::Agile < ::Windows::UI::Core::CharacterReceivedEventArgs ^  > m_key;

#endif*/


         key(sp(base_application) papp);

         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };

      class CLASS_DECL_ca2 nc_activate : public base
      {
      public:


         bool m_bActive;


         nc_activate(sp(base_application) papp);

         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };

#ifdef WINDOWSEX

      class CLASS_DECL_ca2 notify : public base
      {
      public:


         notify(sp(base_application) papp) : element(papp), message::base(papp) {}
         LPNMHDR get_lpnmhdr();
         int32_t get_ctrl_id();
      };

#endif

      class CLASS_DECL_ca2 update_cmd_ui : public base
      {
      public:


         update_cmd_ui(sp(base_application) papp) : element(papp), message::base(papp) {}
         cmd_ui *    m_pcmdui;
      };

      class CLASS_DECL_ca2 command : public base
      {
      public:


         command(sp(base_application) papp) : element(papp), message::base(papp) {}
         UINT GetNotifyCode();
         UINT GetId();
         oswindow get_oswindow();
      };

      class CLASS_DECL_ca2 ctl_color : public base
      {
      public:


         ctl_color(sp(base_application) papp) : element(papp), message::base(papp) {}
         HBRUSH      m_hbrush;
         ::draw2d::graphics *       m_pdc;
         sp(::user::window)      m_pwnd;
         UINT        m_nCtlType;
      };

      class CLASS_DECL_ca2 set_focus : public base
      {
      public:


         set_focus(sp(base_application) papp) : element(papp), message::base(papp) {}
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };



      class CLASS_DECL_ca2 window_pos : public base
      {
      public:

         window_pos(sp(base_application) papp) : element(papp), message::base(papp) {}
         WINDOWPOS * m_pwindowpos;
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      };



#ifdef WINDOWSEX


      class CLASS_DECL_ca2 measure_item : public base
      {
      public:


         measure_item(sp(base_application) papp) : element(papp), message::base(papp) {}
         int32_t m_i;
         LPMEASUREITEMSTRUCT m_lpmis;
      };

#endif

      class CLASS_DECL_ca2 nc_calc_size : public base
      {
      public:


         nc_calc_size(sp(base_application) papp) : element(papp), message::base(papp) {}
         NCCALCSIZE_PARAMS * m_pparams;
         bool GetCalcValidRects();
         virtual void set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult);

      };


      class CLASS_DECL_ca2 enable : public base
      {
      public:


         enable(sp(base_application) papp) : element(papp), message::base(papp) {}
         bool get_enable();
      };


#define new DEBUG_NEW

   #define VMSGEN_WINDOW_ON_NOTIFY_REFLECT(wNotifyCode, pinterface, phandler, pfunction) \
      pinterface->AddMessageHandler( \
         phandler, \
         WM_NOTIFY + WM_REFLECT_BASE, \
         wNotifyCode, \
         0, \
         ::iguimessage::PrototypeConditional_PNMHDR_PLRESULT, \
         static_cast<const ::sigc::slot_base&>( \
         (const ::sigc::slot<bool, NMHDR *, LRESULT *> &) \
         ::sigc::mem_fun(phandler, pfunction)))

   #define VMSGEN_WINDOW_ON_COMMAND(id, pinterface, phandler, pfunction) \
      pinterface->AddMessageHandler( \
         phandler, \
         WM_COMMAND, \
         CN_COMMAND, \
         id, \
         ::iguimessage::PrototypeConditional_void, \
         static_cast<const ::sigc::slot_base&>( \
         (const ::sigc::slot<bool> &) \
         ::sigc::mem_fun(phandler, pfunction)))

   #define VMSGEN_WINDOW_ON_CLOSE_CONDITIONAL( pinterface, phandler, pfunction ) \
      pinterface->AddMessageHandler( \
         phandler, \
         WM_CLOSE, \
         ::iguimessage::PrototypeConditionalOnClose, \
         static_cast<const ::sigc::slot_base&>( \
         (const ::sigc::slot<bool> &) \
         ::sigc::mem_fun(phandler, pfunction)))

   #define VMSGEN_WINDOW_ON_DESTROY_CONDITIONAL( pinterface, phandler, pfunction ) \
      pinterface->AddMessageHandler( \
         phandler, \
         WM_DESTROY, \
         ::iguimessage::PrototypeConditionalOnDestroy, \
         static_cast<const ::sigc::slot_base&>( \
         (const ::sigc::slot<bool> &) \
         ::sigc::mem_fun(phandler, pfunction)))

   #define VMSGEN_WINDOW_ON_NCDESTROY_CONDITIONAL( pinterface, phandler, pfunction ) \
      pinterface->AddMessageHandler( \
         phandler, \
         WM_DESTROY, \
         ::iguimessage::PrototypeConditionalOnDestroy, \
         static_cast<const ::sigc::slot_base&>( \
         (const ::sigc::slot<bool> &) \
         ::sigc::mem_fun(phandler, pfunction)))


   #define VMSGEN_WINDOW_ON_MEASUREITEM_CONDITIONAL( pinterface, phandler, pfunction ) \
      pinterface->AddMessageHandler( \
         phandler, \
         WM_TIMER, \
         ::iguimessage::PrototypeConditionalOnMeasureItem, \
         static_cast<const ::sigc::slot_base&>( \
         (const ::sigc::slot<bool, int32_t, LPMEASUREITEMSTRUCT> &) \
         ::sigc::mem_fun(phandler, pfunction)))


   #define VMSGEN_WINDOW_ON_DRAWITEM_CONDITIONAL( pinterface, phandler, pfunction ) \
      pinterface->AddMessageHandler( \
         phandler, \
         WM_DRAWITEM, \
         ::iguimessage::PrototypeConditionalOnDrawItem, \
         static_cast<const ::sigc::slot_base&>(::sigc::mem_fun(phandler, pfunction)))

   template < class T1, class T2>
   void os_connect(
      UINT                              message,
      dispatch *   pdispatch,
      T1 *                              psignalizable,
      void (T2::*                      pfn)(signal_details *))
   {
      pdispatch->AddMessageHandler(
         message,
         0,
         0,
         0,
         dynamic_cast < T2 * > (psignalizable),
         pfn);
   }

   template < class T1, class T2>
   void _connect(
      UINT                              message,
      dispatch *   pdispatch,
      T1 *                              psignalizable,
      void (T2::*                      pfn)(signal_details *))
   {

      UINT uiOsMessage = translate_to_os_message(message);

      os_connect(uiOsMessage, pdispatch, psignalizable, pfn);

   }

   template < class T1, class T2>
   void cmd_connect(
      UINT                             uiMessage,
      UINT                              uiCode,
      UINT                              uiIdStart,
      UINT                              uiIdEnd,
      dispatch *   pdispatch,
      T1 *                              psignalizable,
      void (T2::*                      pfn)(signal_details *))
   {
      pdispatch->AddMessageHandler(
         uiMessage,
         uiCode,
         uiIdStart,
         uiIdEnd,
         dynamic_cast < T2 * > (psignalizable),
         pfn);
   }

   inline void dispatch::SignalArray::
   GetSignalsByMessage(dispatch::SignalPtrArray & signalptra, UINT uiMessage, UINT uiCode, UINT uiId)
   {
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         Signal & signal = this->element_at(i);
         if(uiMessage      == signal.m_uiMessage
         && uiCode         == signal.m_uiCode
         && uiId           >= signal.m_uiIdStart
         && uiId           <= signal.m_uiIdEnd)
         {
            signalptra.add(&signal);
         }
      }
   }

   inline dispatch::Signal * dispatch::SignalArray::
   GetSignalByMessage(UINT uiMessage, UINT uiCode, UINT uiIdStart, UINT uiIdEnd)
   {
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         Signal & signal = this->element_at(i);
         if(uiMessage      == signal.m_uiMessage
         && uiCode         == signal.m_uiCode
         && uiIdStart      == signal.m_uiIdStart
         && uiIdEnd        == signal.m_uiIdEnd)
         {
            return &signal;
         }
      }
      return NULL;
   }


} // namespace message



#if defined(WINDOWS) || defined(LINUX) || defined(MACOS)
#define IGUI_WIN_MSG_LINK \
   message::os_connect
#else
#define IGUI_WIN_MSG_LINK(p1, p2, p3, p4) \
   ;
#endif
#ifdef LINUX
#define IGUI_MAC_MSG_LINK \
   message::os_connect
#else
#define IGUI_MAC_MSG_LINK(p1, p2, p3, p4) \
   ;
#endif

#define IGUI_MSG_LINK(param1, param2, param3, param4) \
   message::_connect(param1, param2, param3, param4)

#define USER_MESSAGE_LINK(param1, param2, param3, param4) \
   IGUI_MSG_LINK(::core::param1, param2, param3, param4)



#define IGUI_WIN_CMD_LINK \
   message::cmd_connect

#define IGUI_WIN_NOTIFY_REFLECT(wNotifyCode, pinterface, phandler, pfunction) \
   IGUI_WIN_CMD_LINK(WM_COMMAND, (UINT) wNotifyCode + WM_REFLECT_BASE, 0, 0xffffffff, pinterface, phandler, pfunction)

#define IGUI_WIN_ON_CONTROL(id, ca, pdispatch, phandler, poperation) \
   IGUI_WIN_CMD_LINK(WM_COMMAND, ca, id, id, pdispatch, phandler, poperation)

#define IGUI_WIN_ON_NOTIFY(id, n, pdispatch, phandler, poperation) \
   IGUI_WIN_CMD_LINK(WM_NOTIFY, n, id, id, pdispatch, phandler, poperation)

#define IGUI_WIN_CAST(tcast, pcasted) message::tcast * pcasted = (message::tcast *) pobj;
#define IGUI_WIN_CST(tcast) message::tcast * p##tcast = (message::tcast *) pobj;

