#pragma once


class db_server;
class FileSystemSizeWnd;


class CLASS_DECL_ca2 file_size_table :
   virtual public object
{
public:


   class get_fs_size :
      public ::file::byte_serializable
   {
   public:


      string   m_strPath;
      bool     m_bPending;
      int64_t  m_iSize;
      bool     m_bRet;
      oswindow     m_oswindow;


      get_fs_size();
      get_fs_size(const get_fs_size & getfssize);


      get_fs_size & operator = (const get_fs_size & getfssize);


      virtual void write(::file::byte_output_stream & ostream);
      virtual void read(::file::byte_input_stream & istream);


   };


   class item :
      virtual public element
   {
   public:


      item *      m_pitemParent;
      string      m_strName;
      bool        m_bPending;
      int64_t     m_iSize;
      index       m_iStep;
      bool        m_bDir;
      bool        m_bPendingLs;

      spa(item)   m_itema;


      item();


      void update_size(sp(::application) papp, index & iIteration);
      void update_size_recursive(sp(::application) papp, index & iIteration);

      item * FindItem(sp(::application) papp, const char * pszPath, index & iIteration);
      index FindName(sp(::application) papp, const char * pszName, index & iIteration);

      string path();

      void ls(sp(::application) papp, index & iIteration);
   };



   item                    m_item;
   HANDLE                  m_hmap;
   class get_fs_size *     m_pgetfssize;
   FileSystemSizeWnd *     m_pwnd;
   FileSystemSizeWnd *     m_pwndServer;
   oswindow                    m_oswindowServer;
   ::event *               m_pevExec;
   ::event *               m_pevDone;
   ::mutex *               m_pmutex;





   file_size_table(sp(::application) papp);
   ~file_size_table();

   bool check_map();

};



class CLASS_DECL_ca2 DBFileSystemSizeSet :
   virtual public object
{
public:


   file_size_table            m_table;
   index                     m_iMaxIteration;


   DBFileSystemSizeSet(sp(::application) papp);
   ~DBFileSystemSizeSet();



   bool get_cache_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);
   bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);


   bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending, index & iIteration);


};





class CLASS_DECL_ca2 FileSystemSizeServerThread :
   virtual public ::ca2::thread
{
public:

   FileSystemSizeServerThread(sp(::application) papp);

   bool initialize_instance();

};




class CLASS_DECL_ca2 FileSystemSizeWnd :
   public ::ca2::window_sp,
   public ::ca2::signalizable
{
public:


   class size_map :
      public string_map < file_size_table::get_fs_size, file_size_table::get_fs_size >
   {
   public:
   };


   uint32_t                            m_dwLastStartTime;
   bool                             m_bServer;
   file_size_table::get_fs_size     m_size;
   bool                             m_bRet;
   critical_section                 m_cs;
   array < file_size_table::get_fs_size, file_size_table::get_fs_size & > m_sizea;

   size_map                         m_map;


   FileSystemSizeWnd(sp(::application) papp);

   bool CreateClient();
   bool CreateServer();



   void ClientStartServer();
   bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);

   void install_message_handling(::ca2::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnCopyData)
   DECL_GEN_SIGNAL(_001OnTimer)


};


