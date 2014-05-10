#pragma once


class file_manager_operation_thread;
class file_manager_operation_view;


class CLASS_DECL_CORE file_manager_operation_thread :
   public simple_thread
{
public:


   filemanager::estate              m_estate;
   file_manager_operation_view *    m_pview;
   spa(file_operation)              m_fileoperationa;
   int32_t                          m_iOperation;
   bool                             m_bStep;
   mutex                            m_mutexFileOperationA;
   mutex                            m_mutexStep;
   bool                             m_bStop;

   file_manager_operation_thread(sp(::base::application) papp);

   void queue_copy(stringa & stra, const char * pszDest, const char * pszSrcBase, bool bExpand, sp(::user::interaction) oswindowCallback = NULL, UINT uiMessage = WM_USER, WPARAM wparam = 0x1000);
   void kick();

   int32_t get_item_count();
   string get_item_message(int32_t iItem);
   double get_item_progress(int32_t iItem);

   double get_progress_rate();

   bool step();

   int32_t run();

};
