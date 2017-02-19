#pragma once


namespace file_watcher
{


   class CLASS_DECL_AURA listener_thread :
      virtual public ::thread,
      virtual public file_watcher,
      virtual public file_watch_listener
   {
   public:

      enum
      {

         message_add_watch = WM_APP + 54321,

      };

      struct add :
         virtual public object
      {

         string                  m_str;
         bool                    m_bRecursive;
         file_watch_listener *   m_plistener;
         event                   m_event;
         file_watch_id           m_id;
         bool                    m_bOwn;

         add() : m_event(get_thread_app(), false, true) {}

      };

      ref_array < file_watch_listener > m_listenerptra;
      

      listener_thread(::aura::application * papp);
      virtual ~listener_thread();


      virtual int32_t run();



      file_watch_id add_file_watch(const char * directory, bool bRecursive);

      file_watch_id add_file_watch(const char * directory, file_watch_listener * plistener, bool bRecursive, bool bOwn = false);

      template < typename PRED >
      file_watch_id pred_add_watch(const char * directory, PRED pred, bool bRecursive)
      {

         return add_file_watch(directory, new pred_file_watch_listener < PRED >(pred), bRecursive, true);

      }

      virtual void install_message_handling(::message::dispatch * pdispatch) override;

      DECL_GEN_SIGNAL(_001OnAddWatch);

   };


} // namespace file_watcher



