
// This is core API library.
// 
// 
//
// 
// 
// 
// 
// 

/////////////////////////////////////////////////////////////////////////////
//
// Implementation of parameterized List
//
/////////////////////////////////////////////////////////////////////////////

#include "framework.h"

object_list::object_list(int_ptr nBlockSize)
{
   ASSERT(nBlockSize > 0);

   m_nCount = 0;
   m_pnodeHead = m_pnodeTail = m_pnodeFree = NULL;
   m_pBlocks = NULL;
   m_nBlockSize = nBlockSize;
}

void object_list::remove_all()
{
   ASSERT_VALID(this);

   // destroy elements


   m_nCount = 0;
   m_pnodeHead = m_pnodeTail = m_pnodeFree = NULL;
   m_pBlocks->FreeDataChain();
   m_pBlocks = NULL;
}

object_list::~object_list()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Node helpers
/*
 * Implementation note: node's are stored in plex blocks and
 *  chained together. Free blocks are maintained in a singly linked list
 *  using the 'm_pnext' member of node with 'm_pnodeFree' as the head.
 *  Used blocks are maintained in a doubly linked list using both 'm_pnext'
 *  and 'm_pprevious' as links and 'm_pnodeHead' and 'm_pnodeTail'
 *   as the head/tail.
 *
 * We never free a plex block unless the List is destroyed or remove_all()
 *  is used - so the total number of plex blocks may grow large depending
 *  on the maximum past size of the list.
 */

object_list::node*
object_list::NewNode(object_list::node* m_pprevious, object_list::node* m_pnext)
{
   if (m_pnodeFree == NULL)
   {
      // add another block
      plex* pNewBlock = plex::create(m_pBlocks, m_nBlockSize,
             sizeof(node));

      // chain them into free list
      node* pNode = (node*) pNewBlock->data();
      // free in reverse order to make it easier to debug
      pNode += m_nBlockSize - 1;
      for (int_ptr i = m_nBlockSize-1; i >= 0; i--, pNode--)
      {
         pNode->m_pnext = m_pnodeFree;
         m_pnodeFree = pNode;
      }
   }
   ASSERT(m_pnodeFree != NULL);  // we must have something

   object_list::node* pNode = m_pnodeFree;
   m_pnodeFree = m_pnodeFree->m_pnext;
   pNode->m_pprevious = m_pprevious;
   pNode->m_pnext = m_pnext;
   m_nCount++;
   ASSERT(m_nCount > 0);  // make sure we don't overflow




   pNode->m_pdata = 0; // start with zero

   return pNode;
}

void object_list::FreeNode(object_list::node* pNode)
{
   if (pNode == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   pNode->m_pnext = m_pnodeFree;
   m_pnodeFree = pNode;
   m_nCount--;
   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();
}

/////////////////////////////////////////////////////////////////////////////

POSITION object_list::add_head(object* newElement)
{

   ASSERT_VALID(this);

   node* pNewNode = NewNode(NULL, m_pnodeHead);
   pNewNode->m_pdata = newElement;
   if (m_pnodeHead != NULL)
      m_pnodeHead->m_pprevious = pNewNode;
   else
      m_pnodeTail = pNewNode;
   m_pnodeHead = pNewNode;
   return (POSITION) pNewNode;

}



POSITION object_list::add_tail(object* newElement)
{

   ASSERT_VALID(this);

   node* pNewNode = NewNode(m_pnodeTail, NULL);
   pNewNode->m_pdata = newElement;
   if (m_pnodeTail != NULL)
      m_pnodeTail->m_pnext = pNewNode;
   else
      m_pnodeHead = pNewNode;
   m_pnodeTail = pNewNode;
   return (POSITION) pNewNode;

}



void object_list::add_head(object_list* pNewList)
{
   ASSERT_VALID(this);
   ASSERT_VALID(pNewList);
   if (pNewList == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   ASSERT_KINDOF(object_list, pNewList);

   // add a list of same elements to head (maintain order)
   POSITION pos = pNewList->get_tail_position();
   while (pos != NULL)
      add_head(pNewList->get_previous(pos));
}

void object_list::add_tail(object_list* pNewList)
{
   ASSERT_VALID(this);
   ASSERT_VALID(pNewList);
   if (pNewList == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   ASSERT_KINDOF(object_list, pNewList);

   // add a list of same elements
   POSITION pos = pNewList->get_head_position();
   while (pos != NULL)
      add_tail(pNewList->get_next(pos));
}

object* object_list::remove_head()
{
   ENSURE_VALID(this);
   ENSURE(m_pnodeHead != NULL);  // throws if called on is_empty list

   ASSERT(__is_valid_address(m_pnodeHead, sizeof(node)));

   node* pOldNode = m_pnodeHead;
   object* returnValue = pOldNode->m_pdata;

   m_pnodeHead = pOldNode->m_pnext;
   if (m_pnodeHead != NULL)
      m_pnodeHead->m_pprevious = NULL;
   else
      m_pnodeTail = NULL;
   FreeNode(pOldNode);
   return returnValue;
}

object* object_list::remove_tail()
{
   ASSERT_VALID(this);
   ASSERT(m_pnodeTail != NULL);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(m_pnodeTail, sizeof(node)));

   node* pOldNode = m_pnodeTail;
   object* returnValue = pOldNode->m_pdata;

   m_pnodeTail = pOldNode->m_pprevious;
   if (m_pnodeTail != NULL)
      m_pnodeTail->m_pnext = NULL;
   else
      m_pnodeHead = NULL;
   FreeNode(pOldNode);
   return returnValue;
}

POSITION object_list::insert_before(POSITION position, object* newElement)
{

   ASSERT_VALID(this);

   if (position == NULL)
      return add_head(newElement); // insert before nothing -> head of the list

   // Insert it before position
   node* pOldNode = (node*) position;
   node* pNewNode = NewNode(pOldNode->m_pprevious, pOldNode);
   pNewNode->m_pdata = newElement;

   if (pOldNode->m_pprevious != NULL)
   {
      ASSERT(__is_valid_address(pOldNode->m_pprevious, sizeof(node)));
      pOldNode->m_pprevious->m_pnext = pNewNode;
   }
   else
   {
      ASSERT(pOldNode == m_pnodeHead);
      m_pnodeHead = pNewNode;
   }
   pOldNode->m_pprevious = pNewNode;
   return (POSITION) pNewNode;

}



POSITION object_list::insert_after(POSITION position, object* newElement)
{

   ASSERT_VALID(this);

   if (position == NULL)
      return add_tail(newElement); // insert after nothing -> tail of the list

   // Insert it before position
   node* pOldNode = (node*) position;
   ASSERT(__is_valid_address(pOldNode, sizeof(node)));
   node* pNewNode = NewNode(pOldNode, pOldNode->m_pnext);
   pNewNode->m_pdata = newElement;

   if (pOldNode->m_pnext != NULL)
   {
      ASSERT(__is_valid_address(pOldNode->m_pnext, sizeof(node)));
      pOldNode->m_pnext->m_pprevious = pNewNode;
   }
   else
   {
      ASSERT(pOldNode == m_pnodeTail);
      m_pnodeTail = pNewNode;
   }
   pOldNode->m_pnext = pNewNode;
   return (POSITION) pNewNode;

}



void object_list::remove_at(POSITION position)
{
   ASSERT_VALID(this);

   node* pOldNode = (node*) position;
   ASSERT(__is_valid_address(pOldNode, sizeof(node)));

   if (pOldNode == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   
   // remove pOldNode from list
   if (pOldNode == m_pnodeHead)
   {
      m_pnodeHead = pOldNode->m_pnext;
   }
   else
   {
      ASSERT(__is_valid_address(pOldNode->m_pprevious, sizeof(node)));
      pOldNode->m_pprevious->m_pnext = pOldNode->m_pnext;
   }
   if (pOldNode == m_pnodeTail)
   {
      m_pnodeTail = pOldNode->m_pprevious;
   }
   else
   {
      ASSERT(__is_valid_address(pOldNode->m_pnext, sizeof(node)));
      pOldNode->m_pnext->m_pprevious = pOldNode->m_pprevious;
   }
   FreeNode(pOldNode);
}


/////////////////////////////////////////////////////////////////////////////
// slow operations

POSITION object_list::find_index(int_ptr nIndex) const
{
   ASSERT_VALID(this);

   if (nIndex >= m_nCount || nIndex < 0)
      return NULL;  // went too far

   node* pNode = m_pnodeHead;
   while (nIndex--)
   {
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      pNode = pNode->m_pnext;
   }
   return (POSITION) pNode;
}

POSITION object_list::find(object* searchValue, POSITION startAfter) const
{
   ASSERT_VALID(this);

   node* pNode = (node*) startAfter;
   if (pNode == NULL)
   {
      pNode = m_pnodeHead;  // start at head
   }
   else
   {
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      pNode = pNode->m_pnext;  // start after the one specified
   }

   for (; pNode != NULL; pNode = pNode->m_pnext)
      if (pNode->m_pdata == searchValue)
         return (POSITION) pNode;
   return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Serialization
/*
void object_list::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   object::Serialize(ar);

   if (ar.IsStoring())
   {
      ar.WriteCount(m_nCount);
      for (node* pNode = m_pnodeHead; pNode != NULL; pNode = pNode->m_pnext)
      {
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         ar << pNode->m_pdata;
      }
   }
   else
   {
      uint_ptr nNewCount = ar.ReadCount();
      object* newData;
      while (nNewCount--)
      {
         ar >> newData;
         add_tail(newData);
      }
   }
}
*/



