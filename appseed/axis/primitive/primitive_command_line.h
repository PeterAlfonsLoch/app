#pragma once


namespace fs
{


   class item_array;


} // namespace fs


class command_thread;


class CLASS_DECL_AXIS command_line :
   virtual public ::object
{
public:


   enum e_command
   {
      command_file_new,
      command_file_open, 
      command_file_print,
      command_file_print_to,
      command_file_dde, 
      command_app_unregister,
      command_file_nothing = -1
   };


   e_command                     m_ecommand;
   bool                          m_bShowSplash;
   bool                          m_bRunEmbedded;
   bool                          m_bRunAutomated;
   int32_t                           m_nCmdShow;

   // not valid for file_new
   var                           m_varFile;

   // valid only for file_print_to
   string                        m_strPrinterName;
   string                        m_strDriverName;
   string                        m_strPortName;

   var                           m_varQuery;
   ::fs::item_array *            m_pitema;

   sp(::axis::application)             m_pappFork;
   string                        m_strApp;
   string                        m_strAppType;
   sp(::user::interaction)  m_puiParent;
   index                         m_iEdge;
   manual_reset_event            m_eventReady;
   application_bias *            m_pbiasCreate;



   command_line(sp(::axis::application) papp);
   ~command_line();

   void common_construct();

   command_line & operator = (const command_line & info);

   virtual void ParseParam(const char* pszParam, bool bFlag, bool bLast);
   virtual void ParseParamFlag(const char* pszParam);
   virtual void ParseParamNotFlag(const char* pszParam);
   virtual void ParseLast(bool bLast);


   virtual void _001ParseCommandLine(const char * pszCommandLine);
   virtual void _001ParseCommandLineUri(const char * pszCommandLine);

   virtual void _001ParseCommandFork(const char * pszCommandFork);
   virtual void _001ParseCommandForkUri(const char * pszCommandFork);


};



