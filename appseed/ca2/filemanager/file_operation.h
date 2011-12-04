#pragma once


namespace filemanager
{
   enum eoperation
   {
      operation_none,
      operation_copy,
      operation_delete,
      operation_move,
   };

   enum estate
   {
      state_initial,
      state_start,
      state_step,
      state_finish,
   };

} // namespace filemanager

class file_operation :
   virtual public ::radix::object
{
public:
   file_operation(::ca::application * papp);
   virtual filemanager::eoperation operation();
   
   virtual bool set_copy(stringa & stra, const char * pszDestBase, const char * pszSrcBase, bool bExpand);
   virtual bool set_move(stringa & stra, const char * psz);
   virtual bool set_delete(stringa & stra);
   
//   virtual double size();
//   virtual double progress();

   int get_item_count();
   string get_item_message(int iItem);
   double get_item_progress(int iItem);
   double get_item_read(int iItem);
   double get_item_size(int iItem);

   void expand(stringa & straExpanded, stringa & straExpand);

   virtual bool start();
   virtual bool step();
//   virtual bool mark();
   virtual bool finish();
   virtual void make_duplicate_name(string & str, const char * psz);

public:
   virtual void set_operation(filemanager::eoperation eoperation);
   virtual bool initialize();
   virtual bool open_src_dst(const char * pszSrc, const char * pszDst);

   filemanager::eoperation  m_eoperation;

   stringa         m_stra;
   double_array   m_daRead;
   double_array   m_daSize;
   string            m_str;
   string            m_strBase;
   double            m_dSize;
   double            m_dRead;
   ex1::filesp           m_fileSrc;
   ex1::filesp           m_fileDst;
   int               m_iFile;
   bool              m_bReplaceAll;
   char *            m_pchBuffer;
   int         m_iBufferSize;
   ::user::interaction *  m_hwndCallback;
   UINT              m_uiCallbackMessage;
   WPARAM            m_wparamCallback;
};

