#include "framework.h"

// BEGIN_MESSAGE_MAP(file_manager_operation_thread, thread)
//   ON_THREAD_MESSAGE(WM_USER, &file_manager_operation_thread::On1)
// END_MESSAGE_MAP()

file_manager_operation_thread::file_manager_operation_thread(sp(::base::application) papp) :
   element(papp),
   thread(papp),
   simple_thread(papp),
   m_mutexFileOperationA(papp),
   m_mutexStep(papp)
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
   keep < bool >  keepStep(&m_bStep, true, false, true);
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




double file_manager_operation_thread::get_item_progress(int32_t iItem)
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   int32_t iLowerBound = 0;
   int32_t iUpperBound;
   for(int32_t i = 0; i < m_fileoperationa.get_size(); i++)
   {
      iUpperBound = iLowerBound + m_fileoperationa[i].get_item_count() - 1;
      if(iItem >= iLowerBound && iItem <= iUpperBound)
         return m_fileoperationa[i].get_item_progress(iItem - iLowerBound);
      iLowerBound = iUpperBound + 1;
   }
   return 0.0;
}


string file_manager_operation_thread::get_item_message(int32_t iItem)
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   int32_t iLowerBound = 0;
   int32_t iUpperBound;
   for(int32_t i = 0; i < m_fileoperationa.get_size(); i++)
   {
      iUpperBound = iLowerBound + m_fileoperationa[i].get_item_count() - 1;
      if(iItem >= iLowerBound && iItem <= iUpperBound)

         return m_fileoperationa[i].get_item_message(iItem - iLowerBound);
      iLowerBound = iUpperBound + 1;
   }
   return "";
}



int32_t file_manager_operation_thread::get_item_count()
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   int32_t iCount = 0;
   for(int32_t i = 0; i < m_fileoperationa.get_size(); i++)
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
   begin();
}

void file_manager_operation_thread::queue_copy(stringa & stra, const char * pszDstBase, const char * pszSrcBase, bool bExpand,
   sp(::user::interaction) oswindowCallback, UINT uiCallbackMessage, WPARAM wparamCallback)
{
   file_operation * poperation = new file_operation(get_app());
   poperation->m_oswindowCallback = oswindowCallback;
   poperation->m_uiCallbackMessage = uiCallbackMessage;
   poperation->m_wparamCallback = wparamCallback;
   poperation->set_app(get_app());
   poperation->set_copy(stra, pszDstBase, pszSrcBase, bExpand);

   single_lock sl(&m_mutexFileOperationA, TRUE);
   m_fileoperationa.add(poperation);
}

int32_t file_manager_operation_thread::run()
{
   int32_t iStepSetCount = 84;
   int32_t iStepSetSleep = 23;
   while(get_run())
   {
      int32_t i = iStepSetCount;
      while(i > 0)
      {
         if(!step())
            goto exit;
         i--;
      }
      m_pview->post_message(
         file_manager_operation_view::MessageMainPost,
         file_manager_operation_view::MessageMainPostFileOperation);
      Sleep(iStepSetSleep);
   }
   m_pview->post_message(
      file_manager_operation_view::MessageMainPost,
      file_manager_operation_view::MessageMainPostFileOperationFinal);
exit:
   return 1;
}

double file_manager_operation_thread::get_progress_rate()
{
   single_lock sl(&m_mutexFileOperationA, TRUE);
   double dTotal = 0.0;
   for(int32_t i = 0; i < m_fileoperationa.get_size(); i++)
   {
      dTotal += m_fileoperationa[i].m_dSize;
   }
   double dRead = 0.0;
   for(int32_t i = 0; i < m_fileoperationa.get_size(); i++)
   {
      dRead += m_fileoperationa[i].m_dRead;
   }
   if(dTotal == 0.0)
      return 0.0;
   else
      return dRead / dTotal;
}
