#include "StdAfx.h"



db_long_set::db_long_set(db_server * pserver) :
   ca(pserver->get_app()),
   db_set(pserver, "integertable")
{
}

db_long_set::~db_long_set()
{
}


// Adiciona na matriz System nomes dos diretórios de imagens.
bool db_long_set::load(const char * lpKey, long *plValue)
{
   single_lock slDatabase(db()->GetImplCriticalSection());

   string strKey;
   strKey = lpKey;
   strKey.replace("'", "''");
   
   string strSql;
   strSql.Format(
      "select value FROM integertable WHERE id = '%s';",
      strKey);

   
   slDatabase.lock();
   //try
   {
      m_pdataset->query(strSql);
   }
   //catch(...)
   {
     // return false;
   }

   if(m_pdataset->num_rows() <= 0)
      return false;

   *plValue = m_pdataset->fv("value");

   return true;
}

bool db_long_set::load(const char * lpKey, int & iValue)
{
   long lValue;
   if(load(lpKey, &lValue))
   {
      iValue = (int) lValue;
      return true;
   }
   else
      return false;
}

bool db_long_set::save(const char * lpKey, long lValue)
{
   single_lock slDatabase(db()->GetImplCriticalSection());
   string strKey;
   strKey = lpKey;
   strKey.replace("'", "''");

   
   ::sqlite::base * pdb   = db()->GetImplDatabase();
   string strSql;
   long l;
   slDatabase.lock();
   if(load(lpKey, &l))
   {
      strSql.Format(
         "UPDATE integertable SET value = '%d' WHERE id = '%s';",
         lValue,
         strKey);

      try
      {
         pdb->start_transaction();
         m_pdataset->exec(strSql);
         pdb->commit_transaction();
      }
      catch(...)
      {
         pdb->rollback_transaction();
         return false;
      }
   }
   else
   {
   
      strSql.Format(
         "INSERT INTO integertable (id, value) values ('%s', '%d');",
         strKey,
         lValue);

      
      
      try
      {
         pdb->start_transaction();
         m_pdataset->exec(strSql);
         pdb->commit_transaction();
      }
      catch(...)
      {
         pdb->rollback_transaction();
         return false;
      }
   }

   return true;
}

bool db_long_set::save(const char * lpKey, int iValue)
{
   return save(lpKey, (long) iValue);
}

bool db_long_set::find(const char * lpKey)
{
   UNREFERENCED_PARAMETER(lpKey);
/*    single_lock sl(&m_CriticalSection, TRUE);
   HRESULT hr;
    if(m_bIndexed)
    {
//         TRACE("CSongsSet::FindKey Seeking\n");
       string strSection(lpSection);
       string strKey(lpKey);
           if(FAILED(hr = MoveFirst()))
           {
              AddOLEDBException(m_spCommand, IID_IRowsetChange);
           }
           if(hr == DB_S_ENDOFROWSET)
           {
              return FALSE;
           }
          if(FAILED(get_data(0)))
          {
             AddOLEDBException(m_spCommand, IID_IRowsetChange);
          }
          if(strSection.CompareNoCase(m_Section) == 0 &&
             strKey.CompareNoCase(m_Key) == 0)
          {
             return TRUE;
          }
         CDBLongRow l;
            _tcscpy(l.m_Section , lpSection);
         _tcscpy(l.m_Key , lpKey);
         ReleaseRows();
         hr = m_spRowsetIndex->seek(
            m_pAccessor->GetHAccessor(0),
            2,
            &l,
            DBSEEK_FIRSTEQ);
         if(FAILED(hr))
            return FALSE;
         HROW* phRow = &m_hRow;
         ULONG ulRowsFetched = 0;
         hr = m_spRowset->GetNextRows(NULL, 0, 1, &ulRowsFetched, &phRow);
         if (hr != S_OK)
            return FALSE;
         hr = get_data();
         if(FAILED(hr))
            return FALSE;
         return TRUE;
    }
    else
    {
       string strSection(lpSection);
       string strKey(lpKey);
       if(FAILED(hr = MoveFirst()))
       {
          AddOLEDBException(m_spCommand, IID_IRowsetChange);
       }
       if(hr == DB_S_ENDOFROWSET)
       {
          return FALSE;
       }
       while(TRUE)
       {
          if(FAILED(get_data(0)))
          {
             AddOLEDBException(m_spCommand, IID_IRowsetChange);
          }
          if(strSection.CompareNoCase(m_Section) == 0 &&
             strKey.CompareNoCase(m_Key) == 0)
          {
             return TRUE;
          }
          if(FAILED(hr = MoveNext()))
          {
             AddOLEDBException(m_spCommand, IID_IRowsetChange);
          }
          if(hr == DB_S_ENDOFROWSET)
          {
             return FALSE;
          }
       }
    }*/
   return false;
}


bool db_long_set::load(const char * lpKey, LPRECT lpRect)
{
   rect rect;
   string strKey = lpKey;
   if(!load(strKey + ".left", &rect.left))
      return FALSE;
   if(!load(strKey + ".top", &rect.top))
      return FALSE;
   if(!load(strKey + ".right", &rect.right))
      return FALSE;
   if(!load(strKey + ".bottom", &rect.bottom))
      return FALSE;
   *lpRect = rect;
   return TRUE;
}

//////////////////////////////
//
// Output:
// 'false' if one or more save operations has failed.
// 'true' otherwise

bool db_long_set::save(const char * lpKey, LPCRECT lpRect)
{
   string strKey = lpKey;
   if(!save(strKey + ".left", lpRect->left))
      return false;
   if(!save(strKey + ".top", lpRect->top))
      return false;
   if(!save(strKey + ".right", lpRect->right))
      return false;
   if(!save(strKey + ".bottom", lpRect->bottom))
      return false;
   return true;

}
bool db_long_set::MoveWindow_(const char * lpKey, ::ca::window *pWnd)
{
   rect rect;
   if(!load(lpKey, &rect))
      return false;
   pWnd->MoveWindow(&rect);
   return true;
}

bool db_long_set::SaveWindowRect_(const char * lpKey, ::ca::window *pWnd)
{
   WINDOWPLACEMENT wp;
   pWnd->GetWindowPlacement(&wp);
   return save(lpKey , &wp.rcNormalPosition);
}

/*HRESULT db_long_set::OpenQuery(CDataSource *pdb, const char * lpcszSql)
{
         CSession   session;
//      HRESULT      hr;
/*       if(m_spRowset != NULL)
         close();
      if(m_spRowsetIndex != NULL)
         m_spRowsetIndex.Release();
        m_bIndexed = false;

      hr = session.open(*pdb);
      if (FAILED(hr))
         return hr;

      CDBPropSet   propset(DBPROPSET_ROWSET);
      propset.add_property(DBPROP_BOOKMARKS, true);
      propset.add_property(DBPROP_CANFETCHBACKWARDS, true);
      propset.add_property(DBPROP_IRowsetScroll, true);
      propset.add_property(DBPROP_IRowsetChange, true);
      propset.add_property(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE );
      m_CriticalSection.lock();
      hr = CCommand<CAccessor<CDBLongRow> >::open(session, lpcszSql, &propset);
      m_CriticalSection.unlock();
      if (FAILED(hr))
      {
         AddOLEDBException(session.m_spOpenRowset, IID_ICommandPrepare);
//         AddOLEDBException(session.m_spOpenRowset, IID_IRowsetChange);
      }

      return MoveNext(); */
  /*    return S_OK;

}*/

/*HRESULT db_long_set::OpenIndexed(CDataSource *pdb)
{
//    HRESULT hr;
    CSession session;
/*       if(m_spRowset != NULL)
         close();
      if(m_spRowsetIndex != NULL)
         m_spRowsetIndex.Release();
   try
   {
        
      hr = session.open(*pdb);
      if (FAILED(hr))
        {
            AddOLEDBException(pdb->m_spInit, IID_IOpenRowset);
        }
   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return hr;
   }
      DBID    dbIdIndex;
      DBID   dbIdTable;

      dbIdTable.eKind = DBKIND_NAME;
      dbIdTable.uName.pwszName = OLESTR("Long");

      dbIdIndex.eKind = DBKIND_NAME;
      dbIdIndex.uName.pwszName = OLESTR("PrimaryKey");
      
      CDBPropSet   propset(DBPROPSET_ROWSET);
      propset.add_property(DBPROP_BOOKMARKS, true);
      propset.add_property(DBPROP_CANFETCHBACKWARDS, true);
      propset.add_property(DBPROP_IRowsetScroll, true);
      propset.add_property(DBPROP_IRowsetChange, true);
      propset.add_property(DBPROP_IRowsetIndex, true);
      propset.add_property(DBPROP_IRowset, true);
//        propset.add_property(DBPROP_OTHERUPDATEDELETE, true);
//        propset.add_property(DBPROP_OTHERINSERT, true);
      propset.add_property(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE );


 // open the Index with default properties and default interfaces. (IRowsetIndex,
 // IAccessor, IRowset, IColumnsInfo, IRowsetInfo).
      //CComPtr<IRowsetIndex> spIndex ;
   try
   {
      
      hr = session.m_spOpenRowset->OpenRowset(
         NULL,
         &dbIdTable,
         &dbIdIndex,
         IID_IRowset,
         1,
         &propset,
             (IUnknown**) &m_spRowset);
      if (FAILED(hr))
        {
            AddOLEDBException(session.m_spOpenRowset, IID_IOpenRowset);
            return hr;
        }
      hr = Bind();
      if(FAILED(hr))
         return hr;
      CComPtr<IRowsetIndex> spRowsetIndex;
      hr = m_spRowset->QueryInterface(&spRowsetIndex);
      if(FAILED(hr))
         return hr;
      // Sets the range to the entire index.
      hr = spRowsetIndex->SetRange(
         m_pAccessor->GetHAccessor(0),
         0,
         NULL,
         0,
         NULL,
         0);
      if(FAILED(hr))
         return hr;
      SetupOptionalRowsetInterfaces();
      hr = m_spRowset->QueryInterface(&m_spRowsetIndex);
      if(FAILED(hr))
         return hr;
        
        m_bIndexed = true;

   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return hr;
   }*/

      //return MoveNext();
  //  return S_OK;

//}

bool db_long_set::SetWindowPlacement(const char * lpKey, ::ca::window *pWnd)
{
   WINDOWPLACEMENT wp;
   if(!load(lpKey , &wp.rcNormalPosition))
        return false;

    string strKey;
    strKey = lpKey;
    strKey += ".ptMinPosition";
    if(!load(strKey, &wp.ptMinPosition))
        return false;
    strKey = lpKey;
    strKey += ".ptMaxPosition";
    if(!load(strKey, &wp.ptMaxPosition))
        return false;
    strKey = lpKey;
    strKey += ".showCmd";
    if(!load(strKey, (int &) wp.showCmd))
        return false;
    strKey = lpKey;
    strKey += ".flags";
    if(!load(strKey, (int &) wp.flags))
        return false;
    pWnd->SetWindowPlacement(&wp);
   return true;
}

bool db_long_set::SaveWindowPlacement(const char * lpKey, ::ca::window *pWnd)
{
   WINDOWPLACEMENT wp;
   pWnd->GetWindowPlacement(&wp);
   if(!save(lpKey , &wp.rcNormalPosition))
      return false;
    string strKey;
    strKey = lpKey;
    strKey += ".ptMinPosition";
    if(!save(strKey, &wp.ptMinPosition))
      return false;
    strKey = lpKey;
    strKey += ".ptMaxPosition";
    if(!save(strKey, &wp.ptMaxPosition))
      return false;
    strKey = lpKey;
    strKey += ".showCmd";
    if(!save(strKey, (int) wp.showCmd))
      return false;
    strKey = lpKey;
    strKey += ".flags";
    if(!save(strKey, (int) wp.flags))
      return false;
   return true;

}

bool db_long_set::save(const char * lpKey, WINDOWPLACEMENT & wp)
{

   if(!save(lpKey , &wp.rcNormalPosition))
      return false;
    string strKey;
    strKey = lpKey;
    strKey += ".ptMinPosition";
    if(!save(strKey, &wp.ptMinPosition))
      return false;
    strKey = lpKey;
    strKey += ".ptMaxPosition";
    if(!save(strKey, &wp.ptMaxPosition))
      return false;
    strKey = lpKey;
    strKey += ".showCmd";
    if(!save(strKey, (int) wp.showCmd))
      return false;
    strKey = lpKey;
    strKey += ".flags";
    if(!save(strKey, (int) wp.flags))
      return false;

   return true;
}

bool db_long_set::load(const char * lpKey, WINDOWPLACEMENT & wp)
{

   load(lpKey , &wp.rcNormalPosition);
    string strKey;
    strKey = lpKey;
    strKey += ".ptMinPosition";
    load(strKey, &wp.ptMinPosition);
    strKey = lpKey;
    strKey += ".ptMaxPosition";
    load(strKey, &wp.ptMaxPosition);
    strKey = lpKey;
    strKey += ".showCmd";
    load(strKey, (int &) wp.showCmd);
    strKey = lpKey;
    strKey += ".flags";
    load(strKey, (int &) wp.flags);

   return true;
}


bool db_long_set::load(const char * lpKey, LPPOINT lpPoint)
{
   point point;
   string strKey = lpKey;
   if(!load(strKey + ".x", &point.x))
      return FALSE;
   if(!load(strKey + ".y", &point.y))
      return FALSE;
   *lpPoint = point;
   return TRUE;

}

bool db_long_set::save(const char * lpKey, LPPOINT lpPoint)
{
   string strKey = lpKey;
   if(!save(strKey + ".x", lpPoint->x))
      return false;
   if(!save(strKey + ".y", lpPoint->y))
      return false;
   return true;
}

