#include "framework.h"



id_space::id_space()
{
   m_pmutex = new mutex(NULL);
}

// id_space is static, it goes aways only and with the application
// so avoid freeing errors when even crash translators does not exist.

id_space::~id_space()
{

   /*try
   {
      if(m_pmutex != NULL)
      {
         delete m_pmutex;
      }
   }
   catch(...)
   {
   }

   try
   {
      for(index i = 0; i < this->get_count(); i++)
      {
         try
         {
            if(this->element_at(i).is_text())
            {
               free((void *) this->element_at(i).m_psz);
            }
         }
         catch(...)
         {
         }
      }
   }
   catch(...)
   {
   }*/
}

id id_space::operator()(const string & str)
{
   
   single_lock sl(m_pmutex, TRUE);
   
   id idSearch;
   idSearch.raw_set(&str);
   index iIndex = 0;
   
   if(find(idSearch, iIndex))
      return m_ida.element_at(m_iaStr.m_pData[iIndex]);

   id id;
   string * pstr = new string(str);
   if(pstr == NULL)
      throw memory_exception(::get_thread_app());
   id.raw_set(pstr);
   m_ida.add(id);
   m_iaStr.insert_at(iIndex, m_ida.get_upper_bound());
   //sort();
   return id;
   
}

id id_space::operator()(int64_t i)
{

   return id_space::operator()(::str::from(i));


   
}


void id_space::sort()
{

   if(m_ida.m_nSize <= 1)
      return;

   stackLowerBound.allocate(0, 1024);
   stackUpperBound.allocate(0, 1024);

   id * pid1 = NULL;
    id * pid2 = NULL;

   id * pida = m_ida.m_pData;
   index * pia = m_iaStr.m_pData;

    index iU;
    index iM = 0;
    index iL;

   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
//   index i;
   stackLowerBound.push(0);
   stackUpperBound.push(m_ida.m_nSize - 1);
   while(true)
   {
      iLowerBound = stackLowerBound.pop();
      iUpperBound = stackUpperBound.pop();
      iLPos = iLowerBound;
      iMPos = iLowerBound;
      iUPos = iUpperBound;
      while(true)
      {
         if(iMPos != iUPos)
         {
            iM = pia[iMPos];
            pid1 = &pida[iM];
         }
         while(true)
         {
            if(iMPos == iUPos)
               break;
            // REFERENCE
            //if(id_strcmp(&m_ida.m_pData[m_iaStr.m_pData[iMPos]], &m_ida.m_pData[m_iaStr.m_pData[iUPos]]) <= 0)
            // iUPos--;
            iU = pia[iUPos];
            pid2 = pida + iU;
            if(strcmp(pid1->m_pstr->m_pszData, pid2->m_pstr->m_pszData) > 0)
               iUPos--;
            else
            {
                pia[iMPos] = iU;
                pia[iUPos] = iM;
                break;
            }
         }
         if(iMPos == iUPos)
            break;
         iMPos = iUPos;
         if(iMPos != iLPos)
         {
            iM = pia[iMPos];
            pid2 = &pida[iM];
         }
         while(true)
         {
            if(iMPos == iLPos)
               break;
            iL = pia[iLPos];
            pid1 = pida + iL;
            if(strcmp(pid1->m_pstr->m_pszData, pid2->m_pstr->m_pszData) > 0)
               iLPos++;
            else
            {
                pia[iLPos] = iM;
                pia[iMPos] = iL;
               break;
            }
         }
         if(iMPos == iLPos)
            break;
         iMPos = iLPos;
      }
      if(iLowerBound < iMPos - 1)
      {
         stackLowerBound.push(iLowerBound);
         stackUpperBound.push(iMPos - 1);
      }
      if(iMPos + 1 < iUpperBound)
      {
         stackLowerBound.push(iMPos + 1);
         stackUpperBound.push(iUpperBound);
      }
      if(stackLowerBound.get_size() == 0)
         break;
   }

}


bool id_space::find(const id & t, index & iIndex)
{
   single_lock sl(m_pmutex, TRUE);
   if(m_ida.m_nSize == 0)
   {
      return false;
   }
   index iLowerBound = 0;
   index iMaxBound = m_ida.m_nSize - 1;
   index iUpperBound = iMaxBound;
   int64_t iCompare;
   // do binary search
   iIndex = (iUpperBound + iLowerBound) / 2;
   while(iUpperBound - iLowerBound >= 8)
   {
      iCompare = id_strcmp(&m_ida.m_pData[m_iaStr.m_pData[iIndex]], &t);
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
      }
      else
      {
         iLowerBound = iIndex + 1;
         if(iLowerBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
      }
      iIndex = (iUpperBound + iLowerBound) / 2;
   }
   // do sequential search
   while(iIndex < m_ida.m_nSize)
   {
      iCompare = id_strcmp(&m_ida.m_pData[m_iaStr.m_pData[iIndex]], &t);
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= m_ida.m_nSize)
      return false;
   while(iIndex >= 0)
   {
      iCompare = id_strcmp(&m_ida.m_pData[m_iaStr.m_pData[iIndex]], &t);
      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         iIndex--;
      else
         break;
   }
   iIndex++;
   return false;

}




strid_array::strid_array(bool bSynch)
{
   
   if(bSynch)
   {
    
      m_pmutex = canew(mutex(get_thread_app()));

   }

}

// id_space is static, it goes aways only and with the application
// so avoid freeing errors when even crash translators does not exist.

strid_array::~strid_array()
{

   /*try
   {
      if(m_pmutex != NULL)
      {
         delete m_pmutex;
      }
   }
   catch(...)
   {
   }

   try
   {
      for(index i = 0; i < this->get_count(); i++)
      {
         try
         {
            if(this->element_at(i).is_text())
            {
               free((void *) this->element_at(i).m_psz);
            }
         }
         catch(...)
         {
         }
      }
   }
   catch(...)
   {
   }*/
}
void strid_array::sort()
{
   single_lock sl(m_pmutex, TRUE);
   if(m_idptra.m_nSize <= 1)
      return;

   stackLowerBound.allocate(0, 1024);
   stackUpperBound.allocate(0, 1024);

   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   index i;
   stackLowerBound.push(0);
   stackUpperBound.push(m_idptra.m_nSize - 1);
   while(true)
   {
      iLowerBound = stackLowerBound.pop();
      iUpperBound = stackUpperBound.pop();
      iLPos = iLowerBound;
      iMPos = iLowerBound;
      iUPos = iUpperBound;
      while(true)
      {
         while(true)
         {
            if(iMPos == iUPos)
               break;
            if(m_idptra.m_pData[m_iaId.m_pData[iMPos]] <= m_idptra.m_pData[m_iaId.m_pData[iUPos]])
               iUPos--;
            else
            {
                i = m_iaId.m_pData[iMPos];
                m_iaId.m_pData[iMPos] = m_iaId.m_pData[iUPos];
                m_iaId.m_pData[iUPos] = i;
                break;
            }
         }
         if(iMPos == iUPos)
            break;
         iMPos = iUPos;
         while(true)
         {
            if(iMPos == iLPos)
               break;
            if(m_idptra.m_pData[m_iaId.m_pData[iLPos]] <= m_idptra.m_pData[m_iaId.m_pData[iMPos]])
               iLPos++;
            else
            {
                i = m_iaId.m_pData[iMPos];
                m_iaId.m_pData[iMPos] = m_iaId.m_pData[iUPos];
                m_iaId.m_pData[iUPos] = i;
               break;
            }
         }
         if(iMPos == iLPos)
            break;
         iMPos = iLPos;
      }
      if(iLowerBound < iMPos - 1)
      {
         stackLowerBound.push(iLowerBound);
         stackUpperBound.push(iMPos - 1);
      }
      if(iMPos + 1 < iUpperBound)
      {
         stackLowerBound.push(iMPos + 1);
         stackUpperBound.push(iUpperBound);
      }
      if(stackLowerBound.get_size() == 0)
         break;
   }


}



bool strid_array::find(const char * psz, index & iIndex) const
{
   single_lock sl(m_pmutex, TRUE);
   if(m_idptra.m_nSize == 0)
   {
      iIndex = 0;
      return false;
   }

   index iLowerBound = 0;
   index iMaxBound = m_idptra.m_nSize - 1;
   index iUpperBound = iMaxBound;
   index iCompare;
   // do binary search
   iIndex = (iUpperBound + iLowerBound) / 2;
   while(iUpperBound - iLowerBound >= 8)
   {
      iCompare = m_idptra.m_pData[m_iaId.m_pData[iIndex]] - psz;
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
      }
      else
      {
         iLowerBound = iIndex + 1;
         if(iLowerBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
      }
      iIndex = (iUpperBound + iLowerBound) / 2;
   }
   // do sequential search
   while(iIndex < m_idptra.m_nSize)
   {
      iCompare = m_idptra.m_pData[m_iaId.m_pData[iIndex]] - psz;
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= m_idptra.m_nSize)
      return false;
   while(iIndex >= 0)
   {
      iCompare = m_idptra.m_pData[m_iaId.m_pData[iIndex]] - psz;
      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         iIndex--;
      else
         break;
   }
   iIndex++;
   return false;

}


void strid_array::add(const id & id)
{
   
   index iIndex;

   if(find(id, iIndex))
      return;

   m_idptra.add(id);
   m_iaId.insert_at(iIndex, m_idptra.get_upper_bound());
   //m_iaId.add(m_idptra.get_upper_bound());
   //sort();

}

bool strid_array::find(const id & id, index & iIndex) const
{
   

   if(!find((const char *) id, iIndex))
      return false;

   iIndex = m_iaId[iIndex];

   return true;


}



