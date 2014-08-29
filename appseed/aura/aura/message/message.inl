#pragma once


namespace message
{



#define VMSGEN_WINDOW_ON_NOTIFY_REFLECT(wNotifyCode, pinterface, phandler, pfunction) \
   pinterface->AddMessageHandler(\
   phandler,\
   WM_NOTIFY + WM_REFLECT_AXIS,\
   wNotifyCode,\
   0,\
   ::iguimessage::PrototypeConditional_PNMHDR_PLRESULT,\
   static_cast<const ::sigc::slot_base&>(\
   (const ::sigc::slot<bool,NMHDR *,LRESULT *> &) \
   ::sigc::mem_fun(phandler,pfunction)))

#define VMSGEN_WINDOW_ON_COMMAND(id, pinterface, phandler, pfunction) \
   pinterface->AddMessageHandler(\
   phandler,\
   WM_COMMAND,\
   CN_COMMAND,\
   id,\
   ::iguimessage::PrototypeConditional_void,\
   static_cast<const ::sigc::slot_base&>(\
   (const ::sigc::slot<bool> &) \
   ::sigc::mem_fun(phandler,pfunction)))

#define VMSGEN_WINDOW_ON_CLOSE_CONDITIONAL( pinterface, phandler, pfunction ) \
   pinterface->AddMessageHandler(\
   phandler,\
   WM_CLOSE,\
   ::iguimessage::PrototypeConditionalOnClose,\
   static_cast<const ::sigc::slot_base&>(\
   (const ::sigc::slot<bool> &) \
   ::sigc::mem_fun(phandler,pfunction)))

#define VMSGEN_WINDOW_ON_DESTROY_CONDITIONAL( pinterface, phandler, pfunction ) \
   pinterface->AddMessageHandler(\
   phandler,\
   WM_DESTROY,\
   ::iguimessage::PrototypeConditionalOnDestroy,\
   static_cast<const ::sigc::slot_base&>(\
   (const ::sigc::slot<bool> &) \
   ::sigc::mem_fun(phandler,pfunction)))

#define VMSGEN_WINDOW_ON_NCDESTROY_CONDITIONAL( pinterface, phandler, pfunction ) \
   pinterface->AddMessageHandler(\
   phandler,\
   WM_DESTROY,\
   ::iguimessage::PrototypeConditionalOnDestroy,\
   static_cast<const ::sigc::slot_base&>(\
   (const ::sigc::slot<bool> &) \
   ::sigc::mem_fun(phandler,pfunction)))


#define VMSGEN_WINDOW_ON_MEASUREITEM_CONDITIONAL( pinterface, phandler, pfunction ) \
   pinterface->AddMessageHandler(\
   phandler,\
   WM_TIMER,\
   ::iguimessage::PrototypeConditionalOnMeasureItem,\
   static_cast<const ::sigc::slot_base&>(\
   (const ::sigc::slot<bool,int32_t,LPMEASUREITEMSTRUCT> &) \
   ::sigc::mem_fun(phandler,pfunction)))


#define VMSGEN_WINDOW_ON_DRAWITEM_CONDITIONAL( pinterface, phandler, pfunction ) \
   pinterface->AddMessageHandler(\
   phandler,\
   WM_DRAWITEM,\
   ::iguimessage::PrototypeConditionalOnDrawItem,\
   static_cast<const ::sigc::slot_base&>(::sigc::mem_fun(phandler,pfunction)))

   template < class T1,class T2>
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

   template < class T1,class T2>
   void _connect(
      UINT                              message,
      dispatch *   pdispatch,
      T1 *                              psignalizable,
      void (T2::*                      pfn)(signal_details *))
   {

      UINT uiOsMessage = translate_to_os_message(message);

      os_connect(uiOsMessage,pdispatch,psignalizable,pfn);

   }


   template < class T1,class T2>
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



   inline void dispatch::SignalArray::GetSignalsByMessage(dispatch::SignalPtrArray & signalptra,UINT uiMessage,UINT uiCode,UINT uiId)
   {
         for(int32_t i = 0; i < this->get_size(); i++)
         {
            Signal & signal = *this->element_at(i);
            if(uiMessage == signal.m_uiMessage
               && uiCode == signal.m_uiCode
               && uiId >= signal.m_uiIdStart
               && uiId <= signal.m_uiIdEnd)
            {
               signalptra.add(&signal);
            }
         }
      }

   inline dispatch::Signal * dispatch::SignalArray::
      GetSignalByMessage(UINT uiMessage,UINT uiCode,UINT uiIdStart,UINT uiIdEnd)
   {
         for(int32_t i = 0; i < this->get_size(); i++)
         {
            Signal & signal = *this->element_at(i);
            if(uiMessage == signal.m_uiMessage
               && uiCode == signal.m_uiCode
               && uiIdStart == signal.m_uiIdStart
               && uiIdEnd == signal.m_uiIdEnd)
            {
               return &signal;
            }
         }
         return NULL;
      }


} // namespace message



#if defined(WINDOWS) || defined(LINUX) || defined(APPLEOS)
#define IGUI_WIN_MSG_LINK \
   ::message::os_connect
#else
#define IGUI_WIN_MSG_LINK(p1, p2, p3, p4) \
   ;
#endif
#ifdef LINUX
#define IGUI_MAC_MSG_LINK \
   ::message::os_connect
#else
#define IGUI_MAC_MSG_LINK(p1, p2, p3, p4) \
   ;
#endif

#define IGUI_MSG_LINK(param1, param2, param3, param4) \
   ::message::_connect(param1,param2,param3,param4)

#define USER_MESSAGE_LINK(param1, param2, param3, param4) \
   IGUI_MSG_LINK(::message::param1,param2,param3,param4)


#define IGUI_CREATE(class)       IGUI_MSG_LINK(WM_CREATE, pdispatch, this, &class::_001OnCreate)
#define IGUI_KEYDOWN(class)      IGUI_MSG_LINK(WM_KEYDOWN, pdispatch, this, &class::_001OnKeyDown)
#define IGUI_CHAR(class)         IGUI_MSG_LINK(WM_CHAR, pdispatch, this, &class::_001OnChar)
#define IGUI_LBUTTONDOWN(class)  IGUI_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &class::_001OnLButtonDown)
#define IGUI_LBUTTONUP(class)    IGUI_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &class::_001OnLButtonUp)
#define IGUI_MOUSEMOVE(class)    IGUI_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &class::_001OnMouseMove)

#define MSG_CREATE         IGUI_CREATE(this_class);
#define MSG_KEYDOWN        IGUI_KEYDOWN(this_class);
#define MSG_CHAR           IGUI_CHAR(this_class);
#define MSG_LBUTTONDOWN    IGUI_LBUTTONDOWN(this_class);
#define MSG_LBUTTONUP      IGUI_LBUTTONUP(this_class);
#define MSG_MOUSEMOVE      IGUI_MOUSEMOVE(this_class);

// simple declaration of install message handling


#define IMH() \
   virtual void install_message_handling(::message::dispatch * pdispatch)

// simple implementation of install message handling

#define IMPL_IMH(class, base_class) \
   void class::install_message_handling(::message::dispatch * pdispatch) \
{ \
   \
   typedef class this_class; \
   base_class::install_message_handling(pdispatch); \
   \


#define END_IMH \
   \
} \



#define IGUI_WIN_CMD_LINK \
   ::message::cmd_connect

#define IGUI_WIN_NOTIFY_REFLECT(wNotifyCode, pinterface, phandler, pfunction) \
   IGUI_WIN_CMD_LINK(WM_COMMAND,(UINT)wNotifyCode + WM_REFLECT_AXIS,0,0xffffffff,pinterface,phandler,pfunction)

#define IGUI_WIN_ON_CONTROL(id, ca, pdispatch, phandler, poperation) \
   IGUI_WIN_CMD_LINK(WM_COMMAND,ca,id,id,pdispatch,phandler,poperation)

#define IGUI_WIN_ON_NOTIFY(id, n, pdispatch, phandler, poperation) \
   IGUI_WIN_CMD_LINK(WM_NOTIFY,n,id,id,pdispatch,phandler,poperation)

#define IGUI_WIN_CAST(tcast, pcasted) message::tcast * pcasted = (::message::tcast *) pobj;
#define IGUI_WIN_CST(tcast) ::message::tcast * p##tcast = (::message::tcast *) pobj;




