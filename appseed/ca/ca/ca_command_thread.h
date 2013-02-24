

namespace ca
{


   class create_context;


} // namespace ca


namespace ca
{


   class CLASS_DECL_ca command_thread :
      virtual public ::ca::object
   {
   public:


      mutex                            m_mutex; // all this command_thread data is a kind of global
      spa(command)                     m_ptraHistory; // accumulatted as command_thread history passes
      spa(command)                     m_ptra; // pending commands to be run - command_thread does not "run" forks, let it's own thread/process run it
      stringa                          m_straHistory;


      var                              m_varTopicFile;  // accumulatted, reset, set, or clear as command_thread history passes
      var                              m_varTopicQuery; // accumulatted, reset, set, or clear as command_thread history passes


      command_thread(::ca::application * papp);
      virtual ~command_thread();

      virtual var run();

      virtual void request(::ca::create_context * pcreationcontext);

      virtual void on_request(::ca::create_context * pcreationcontext);


      // should transform the following command in a "command_line", a command line can/should/must/shall/ought to be virtually anything
      // virtual void add_audio_command(wave_stream * pstream);
      // virtual void add_wave_command(waving_stroke * pstroke);
      // virtual void add_mbutton_stroke(waving_stroke * pstroke);

      virtual bool is_thread();

      virtual void consolidate(const ::ca::create_context * pcreatecontext);
      virtual void consolidate(ca::command_thread * pthread);

      virtual var & property(const char * pszKey);
      virtual bool has_property(const char * pszKey);


   };



} // namespace command


