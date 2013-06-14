

namespace ca2
{


   class create_context;


} // namespace ca2


namespace ca2
{


   class CLASS_DECL_ca2 command_thread :
      virtual public ::ca2::object
   {
   public:


      mutex                            m_mutex; // all this command_thread data is a kind of global
      spa(command)                     m_ptraHistory; // accumulatted as command_thread history passes
      spa(command)                     m_ptra; // pending commands to be run - command_thread does not "run" forks, let it's own thread/process run it
      stringa                          m_straHistory;


      var                              m_varTopicFile;  // accumulatted, reset, set, or clear as command_thread history passes
      var                              m_varTopicQuery; // accumulatted, reset, set, or clear as command_thread history passes


      command_thread(sp(::ca2::application) papp);
      virtual ~command_thread();

      virtual var run();

      virtual void request_create(sp(::ca2::create_context) pcreationcontext);

      virtual void on_request(sp(::ca2::create_context) pcreationcontext);


      // should transform the following command in a "command_line", a command line can/should/must/shall/ought to be virtually anything
      // virtual void add_audio_command(wave_stream * pstream);
      // virtual void add_wave_command(waving_stroke * pstroke);
      // virtual void add_mbutton_stroke(waving_stroke * pstroke);

      virtual bool is_thread();

      virtual void consolidate(sp(::ca2::create_context) pcreatecontext);
      virtual void consolidate(sp(::ca2::command_thread) pthread);

      virtual var & property(const char * pszKey);
      virtual bool has_property(const char * pszKey);


   };



} // namespace command


