#pragma once



class CLASS_DECL_ACE command_thread :
   virtual public ::object
{
public:

   spa(::primitive::command)        m_ptraHistory; // accumulatted as command_thread history passes
   //spa(::primitive::command)        m_ptra; // pending commands to be run - command_thread does not "run" forks, let it's own thread/process run it
   stringa                          m_straHistory;


   var                              m_varTopicFile;  // accumulatted, reset, set, or clear as command_thread history passes
   var                              m_varTopicQuery; // accumulatted, reset, set, or clear as command_thread history passes
   //manual_reset_event               m_ev;
   sp(command_line)                 m_spcommandline;
   ::thread *                       m_pthread;


   command_thread(::thread * pthread);
   virtual ~command_thread();

   virtual int64_t add_ref()
   {

      return ::object::add_ref();

   }
   virtual int64_t dec_ref()
   {

      return ::object::dec_ref();

   }

   //virtual var run();

   virtual void request_create(sp(::create) pcreate);

   virtual void command(::primitive::command * pcommand);

   virtual void command(::primitive::e_command ecommand);

   virtual void on_command(::primitive::command * pcommand);

   //virtual void on_create(::create * pcreate);


   // should transform the following command in a "command_line", a command line can/should/must/shall/ought to be virtually anything
   // virtual void add_audio_command(wave_stream * pstream);
   // virtual void add_wave_command(waving_stroke * pstroke);
   // virtual void add_mbutton_stroke(waving_stroke * pstroke);

   virtual bool is_thread();

   virtual void consolidate(::create * pcreatecontext);
   virtual void consolidate(::command_thread * pthread);

   virtual var & property(const char * pszKey);
   virtual bool has_property(const char * pszKey);



};


