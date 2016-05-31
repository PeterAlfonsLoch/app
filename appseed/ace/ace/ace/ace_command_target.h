#pragma once


class CLASS_DECL_AURA command_target_interface:
   virtual public signalizable,
   virtual public ::message::dispatch
{
public:

   class CLASS_DECL_AURA command_signalid: public signalid
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
         if(pid == NULL)
            return false;
         return pid->m_id == m_id;
      };

      virtual bool matches(signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if(pid == NULL)
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

   class CLASS_DECL_AURA command_signalrange: public signalid
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
         if(prange == NULL)
            return false;
         return prange->m_iStart == m_iStart && prange->m_iEnd == m_iEnd;
      };

      virtual bool matches(signalid * pidParam)
      {
         command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
         if(pid == NULL)
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
   command_target_interface(::ace::application * papp);


   template < class T >
   bool connect_update_cmd_ui(const char * pszId,void (T::*pfn)(signal_details *))
   {
      return connect_update_cmd_ui(id(pszId),pfn);
   }
   template < class T >
   bool connect_command(const char * pszId,void (T::*pfn)(signal_details *))
   {
      return connect_command(id(pszId),pfn);
   }
   template < class T >
   bool connect_update_cmd_ui(id id,void (T::*pfn)(signal_details *))
   {
      command_signalid signalid;
      ::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      if (!m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {
         return false;
      }
      return true;
   }
   template < class T >
   bool connect_command(id id,void (T::*pfn)(signal_details *))
   {
      command_signalid signalid;
      ::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      if (!m_dispatchCommand.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {
         return false;
      }
      return true;
   }
   template < class T >
   bool connect_update_cmd_ui(id id,T * psignalizable, void (T::*pfn)(signal_details *))
   {
      command_signalid signalid;
      ::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      if (!m_dispatchUpdateCmdUi.AddMessageHandler(pid, psignalizable, pfn, true))
      {
         return false;
      }
      return true;
   }
   template < class T >
   bool connect_command(id id,T * psignalizable,void (T::*pfn)(signal_details *))
   {
      command_signalid signalid;
      ::signalid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      if (!m_dispatchCommand.AddMessageHandler(pid, psignalizable, pfn, true))
      {
         return false;
      }
      return true;
   }
   template < class T >
   bool connect_update_cmd_range_ui(int32_t iStart,int32_t iEnd,void (T::*pfn)(signal_details *))
   {
      command_signalrange signalrange;
      ::signalid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      if (!m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {
         return false;
      }
      return true;
   }
   template < class T >
   bool connect_command_range(int32_t iStart,int32_t iEnd,void (T::*pfn)(signal_details *))
   {
      command_signalrange signalrange;
      ::signalid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      if (!m_dispatchCommand.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {
         return false;
      }
      return true;
   }

   virtual bool _001SendCommand(id id);
   virtual bool _001SendUpdateCmdUi(cmd_ui * pcmdUI);

   virtual bool on_simple_action(id id);
   virtual bool _001HasCommandHandler(id id);
   virtual bool on_simple_update(cmd_ui * pcmdui);

   //virtual bool on_simple_update(cmd_ui * pcmdui);
   virtual bool _001OnCmdMsg(::ace::cmd_msg * pcmdmsg);
   //virtual bool _001HasCommandHandler(const char * pszId);

   void get_command_signal_array(::ace::cmd_msg::e_type etype,::dispatch::signal_item_ptr_array & signalptra,id id);


   virtual void install_message_handling(::message::dispatch * pdispatch);


};



class CLASS_DECL_AURA command_target:
   virtual public command_target_interface
{
public:
   command_target();
   command_target(::ace::application * papp);

   void CommonConstruct();

   void BeginWaitCursor();
   void EndWaitCursor();
   void RestoreWaitCursor();       // call after messagebox


   virtual bool handle(::ace::cmd_msg * pcmdmsg);


   // Overridables
   // route and dispatch standard command message types
   //   (more sophisticated than OnCommand)
   //   virtual bool _001OnCmdMsg(::ace::cmd_msg * pcmdmsg);


   // Implementation
public:
   virtual ~command_target() = 0;


};









// cmd_ui
inline void cmd_ui::ContinueRouting()
{
   m_bContinueRouting = TRUE;
}

