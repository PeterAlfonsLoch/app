#include "StdAfx.h"

// BEGIN_MESSAGE_MAP(file_manager_operation_thread, thread)
//   ON_THREAD_MESSAGE(WM_USER, &file_manager_operation_thread::On1)
// END_MESSAGE_MAP()

file_manager_operation_thread::file_manager_operation_thread(::ax::application * papp) :
   ax(papp),
   thread(papp),
   simple_thread(papp)
{
   set_auto_delete(false);
   m_bStep = false;
}


bool file_manager_operation_thread::step()
{
   single_lock sl(&m_mutexStep);
   if(!sl.lock(duration::zero()))
      return true;
   if(m_bStep)
      return true;
   keeper < bool >  keepStep(&m_bStep, true, false, true);
         if(m_iOperation >= m_fileoperationa.get_size())
         {
            m_estate = filemanager::state_initial;
            return false;
         }
         switch(m_estate)
         {
         case filemanager::state_start:
            {
               if(m_fileoperationa[m_iOperation].start())
               {
                  m_estate = filemanager::state_step;
               }
               else
               {
                  m_estate = filemanager::state_start;
                  m_iOperation++;
               }
            }
            break;
         case filemanager::state_step:
            {
               if(m_fileoperationa[m_iOperation].step())
               {
                  m_estate = filemanager::state_step;
               }
               else
               {
                  m_estate = filemanager::state_finish;
               }
            }
            break;
         case filemanager::state_finish:
            {
               m_fileoperationa[m_iOperation].finish();
               m_estate = filemanager::state_start;
               m_iOperation++;
            }
            break;
         case filemanager::state_initial:
            {
               return false;
            }
         default:
            ASSERT(FALSE);
         }
         return true;
}




double file_manager_operation_thread::get_item_progress(int iItem)
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   int iLBound = 0;
   int iUBound;
   for(int i = 0; i < m_fileoperationa.get_size(); i++)
   {
      iUBound = iLBound + m_fileoperationa[i].get_item_count() - 1;
      if(iItem >= iLBound && iItem <= iUBound)
         return m_fileoperationa[i].get_item_progress(iItem - iLBound);
      iLBound = iUBound + 1;
   }
   return 0.0;
}


string file_manager_operation_thread::get_item_message(int iItem)
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   int iLBound = 0;
   int iUBound;
   for(int i = 0; i < m_fileoperationa.get_size(); i++)
   {
      iUBound = iLBound + m_fileoperationa[i].get_item_count() - 1;
      if(iItem >= iLBound && iItem <= iUBound)

         return m_fileoperationa[i].get_item_message(iItem - iLBound);
      iLBound = iUBound + 1;
   }
   return "";
}



int file_manager_operation_thread::get_item_count()
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   int iCount = 0;
   for(int i = 0; i < m_fileoperationa.get_size(); i++)
   {
      iCount += m_fileoperationa[i].get_item_count();
   }
   return iCount;
}


void file_manager_operation_thread::kick()
{
   m_estate = filemanager::state_start;
   m_bStop = false;
   m_iOperation = 0;
   Begin();
}

void file_manager_operation_thread::queue_copy(stringa & stra, const char * pszDstBase, const char * pszSrcBase, bool bExpand,
   ::user::interaction * hwndCallback, UINT uiCallbackMessage, WPARAM wparamCallback)
{
   file_operation * poperation = new file_operation(get_app());
   poperation->m_hwndCallback = hwndCallback;
   poperation->m_uiCallbackMessage = uiCallbackMessage;
   poperation->m_wparamCallback = wparamCallback;
   poperation->set_app(get_app());
   poperation->set_copy(stra, pszDstBase, pszSrcBase, bExpand);

   single_lock sl(&m_mutexFileOperationA, TRUE);
   m_fileoperationa.add(poperation);
}

int file_manager_operation_thread::run()
{
   int iStepSetCount = 77;
   int iStepSetSleep = 84;
   while(true)
   {
      int i = iStepSetCount;
      while(i > 0)
      {
         if(!step())
            goto exit;
         i--;
      }
      m_pview->PostMessage(
         file_manager_operation_view::MessageMainPost,
         file_manager_operation_view::MessageMainPostFileOperation,
         0);
      Sleep(iStepSetSleep);
   }
   m_pview->PostMessage(
      file_manager_operation_view::MessageMainPost,
      file_manager_operation_view::MessageMainPostFileOperationFinal,
      0);
exit:
   return 1;
}

double file_manager_operation_thread::get_progress_rate()
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   double dTotal = 0.0;
   for(int i = 0; i < m_fileoperationa.get_size(); i++)
   {
      dTotal += m_fileoperationa[i].m_dSize;
   }
   double dRead = 0.0;
   for(int i = 0; i < m_fileoperationa.get_size(); i++)
   {
      dRead += m_fileoperationa[i].m_dRead;
   }
   if(dTotal == 0.0)
      return 0.0;
   else
      return dRead / dTotal;
}
