#pragma once


//#include "gen/buffered_file.h"


class db_server;
class FileSystemSizeWnd;


class CLASS_DECL_ca file_size_table :
   virtual public ::radix::object
{
public:
   file_size_table(::ca::application * papp);
   ~file_size_table();


   FileSystemSizeWnd * m_pwnd;
   FileSystemSizeWnd * m_pwndServer;
   HWND m_hwndServer;


   class get_fs_size :
      public ex1::byte_serializable
   {
   public:


      string   m_strPath;
      bool     m_bPending;
      __int64  m_iSize;
      bool     m_bRet;
      HWND     m_hwnd;

      get_fs_size();
      get_fs_size(const get_fs_size & getfssize);

      get_fs_size & operator = (const get_fs_size & getfssize);


      virtual void write(ex1::byte_output_stream & ostream);
      virtual void read(ex1::byte_input_stream & istream);


   };


   ::event * m_pevExec;
   ::event * m_pevDone;
   ::mutex * m_pmutex;



   class item
   {
   public:
      item *   m_pitemParent;
      string   m_strName;
      bool     m_bPending;
      __int64  m_iSize;
      int      m_iStep;
      bool     m_bDir;
      bool     m_bPendingLs;
      item();
      void update_size(::ca::application * papp, int & iIteration);
      void update_size_recursive(::ca::application * papp, int & iIteration);

      item * FindItem(::ca::application * papp, const char * pszPath, int & iIteration);
      int FindName(::ca::application * papp, const char * pszName, int & iIteration);
      array_ptr_alloc < class item, class item & > m_itema;
      string path();

      void ls(::ca::application * papp, int & iIteration);
   };

   bool check_map();

   item m_item;
   HANDLE m_hmap;
   class get_fs_size * m_pgetfssize;

};



class CLASS_DECL_ca DBFileSystemSizeSet :
   virtual public ::radix::object
{
public:

   DBFileSystemSizeSet(::ca::application * papp);
   ~DBFileSystemSizeSet();



   file_size_table         m_table;
protected:
   int                     m_iMaxIteration;
public:

   bool get_cache_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending);
   bool get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending);


protected:
   bool get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending, int & iIteration);
};

class CLASS_DECL_ca FileSystemSizeServerThread :
   virtual public ::radix::thread
{
public:
   FileSystemSizeServerThread(::ca::application * papp);

   bool initialize_instance();
};


class CLASS_DECL_ca FileSystemSizeWnd :
   public ::ca::window_sp,
   public gen::signalizable
{
public:
   FileSystemSizeWnd(::ca::application * papp);

   bool CreateClient();
   bool CreateServer();

   void ClientStartServer();

   DWORD m_dwLastStartTime;

   class size_map :
      public ::collection::string_map < file_size_table::get_fs_size, file_size_table::get_fs_size >
   {
   public:
   };



   bool m_bServer;
   file_size_table::get_fs_size m_size;
   bool m_bRet;
   critical_section m_cs;
   base_array < file_size_table::get_fs_size, file_size_table::get_fs_size & > m_sizea;

   size_map m_map;

   bool get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending);

   void install_message_handling(::gen::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnCopyData)
   DECL_GEN_SIGNAL(_001OnTimer)


};


