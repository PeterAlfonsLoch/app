#pragma once

class file_manager_operation_thread;
class file_manager_operation_view;

class CLASS_DECL_ca file_manager_operation_thread :
   public simple_thread
{
public:
   filemanager::estate              m_estate;
   file_manager_operation_view *    m_pview;
   array_del_ptr < file_operation, file_operation & > m_fileoperationa;
   int                              m_iOperation;
   bool                             m_bStep;
   mutex                            m_mutexFileOperationA;
   mutex                            m_mutexStep;
   bool                             m_bStop;

   file_manager_operation_thread(::ax::application * papp);

   void queue_copy(stringa & stra, const char * pszDest, const char * pszSrcBase, bool bExpand, ::user::interaction * hwndCallback = NULL, UINT uiMessage = WM_USER, WPARAM wparam = 0x1000);
   void kick();

   int get_item_count();
   string get_item_message(int iItem);
   double get_item_progress(int iItem);

   double get_progress_rate();

   bool step();

   int run();

};
