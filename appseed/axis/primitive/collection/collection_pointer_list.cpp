#include "framework.h"

pointer_list::pointer_list(int_ptr nBlockSize)
{
   ASSERT(nBlockSize > 0);

   m_nCount = 0;
   m_pnodeHead = m_pnodeTail = m_pnodeFree = NULL;
   m_pBlocks = NULL;
   m_nBlockSize = nBlockSize;
}

void pointer_list::remove_all()
{
   ASSERT_VALID(this);

   // destroy elements


   m_nCount = 0;
   m_pnodeHead = m_pnodeTail = m_pnodeFree = NULL;
   m_pBlocks->FreeDataChain();
   m_pBlocks = NULL;
}

pointer_list::~pointer_list()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Node helpers
/*
 * Implementation note: node's are stored in plex blocks and
 *  chained together. Free blocks are maintained in a singly linked list
 *  using the 'pNext' member of node with 'm_pnodeFree' as the head.
 *  Used blocks are maintained in a doubly linked list using both 'pNext'
 *  and 'pPrev' as links and 'm_pnodeHead' and 'm_pnodeTail'
 *   as the head/tail.
 *
 * We never free a plex block unless the List is destroyed or remove_all()
 *  is used - so the total number of plex blocks may grow large depending
 *  on the maximum past size of the list.
 */

pointer_list::node*
pointer_list::NewNode(pointer_list::node* pPrev, pointer_list::node* pNext)
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
         pNode->pNext = m_pnodeFree;
         m_pnodeFree = pNode;
      }
   }
   ASSERT(m_pnodeFree != NULL);  // we must have something

   pointer_list::node* pNode = m_pnodeFree;
   m_pnodeFree = m_pnodeFree->pNext;
   pNode->pPrev = pPrev;
   pNode->pNext = pNext;
   m_nCount++;
   ASSERT(m_nCount > 0);  // make sure we don't overflow




   pNode->data = 0; // start with zero

   return pNode;
}

void pointer_list::FreeNode(pointer_list::node* pNode)
{
   if (pNode == NULL)
   {
      throw invalid_argument_exception(get_app());
   }

   pNode->pNext = m_pnodeFree;
   m_pnodeFree = pNode;
   m_nCount--;
   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();
}

/////////////////////////////////////////////////////////////////////////////

POSITION pointer_list::add_head(void * newElement)
{

   ASSERT_VALID(this);

   node* pNewNode = NewNode(NULL, m_pnodeHead);
   pNewNode->data = newElement;
   if (m_pnodeHead != NULL)
      m_pnodeHead->pPrev = pNewNode;
   else
      m_pnodeTail = pNewNode;
   m_pnodeHead = pNewNode;
   return (POSITION) pNewNode;

}



POSITION pointer_list::add_tail(void * newElement)
{

   ASSERT_VALID(this);

   node* pNewNode = NewNode(m_pnodeTail, NULL);
   pNewNode->data = newElement;
   if (m_pnodeTail != NULL)
      m_pnodeTail->pNext = pNewNode;
   else
      m_pnodeHead = pNewNode;
   m_pnodeTail = pNewNode;
   return (POSITION) pNewNode;

}



void pointer_list::add_head(pointer_list* pNewList)
{
   ASSERT_VALID(this);
   ASSERT_VALID(pNewList);
   if (pNewList == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   ASSERT_KINDOF(pointer_list, pNewList);

   // add a list of same elements to head (maintain order)
   POSITION pos = pNewList->get_tail_position();
   while (pos != NULL)
      add_head(pNewList->get_previous(pos));
}

void pointer_list::add_tail(pointer_list* pNewList)
{
   ASSERT_VALID(this);
   ASSERT_VALID(pNewList);
   if (pNewList == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   ASSERT_KINDOF(pointer_list, pNewList);
   
   // add a list of same elements
   POSITION pos = pNewList->get_head_position();
   while (pos != NULL)
      add_tail(pNewList->get_next(pos));
}

void * pointer_list::remove_head()
{
   ENSURE_VALID(this);
   ENSURE(m_pnodeHead != NULL);  // throws if called on is_empty list
   ASSERT(__is_valid_address(m_pnodeHead, sizeof(node)));

   node* pOldNode = m_pnodeHead;
   void * returnValue = pOldNode->data;

   m_pnodeHead = pOldNode->pNext;
   if (m_pnodeHead != NULL)
      m_pnodeHead->pPrev = NULL;
   else
      m_pnodeTail = NULL;
   FreeNode(pOldNode);
   return returnValue;
}

void * pointer_list::remove_tail()
{
   ASSERT_VALID(this);
   ASSERT(m_pnodeTail != NULL);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(m_pnodeTail, sizeof(node)));

   node* pOldNode = m_pnodeTail;
   void * returnValue = pOldNode->data;

   m_pnodeTail = pOldNode->pPrev;
   if (m_pnodeTail != NULL)
      m_pnodeTail->pNext = NULL;
   else
      m_pnodeHead = NULL;
   FreeNode(pOldNode);
   return returnValue;
}

POSITION pointer_list::insert_before(POSITION position, void * newElement)
{

   ASSERT_VALID(this);

   if (position == NULL)
      return add_head(newElement); // insert before nothing -> head of the list

   // Insert it before position
   node* pOldNode = (node*) position;
   node* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
   pNewNode->data = newElement;

   if (pOldNode->pPrev != NULL)
   {
      ASSERT(__is_valid_address(pOldNode->pPrev, sizeof(node)));
      pOldNode->pPrev->pNext = pNewNode;
   }
   else
   {
      ASSERT(pOldNode == m_pnodeHead);
      m_pnodeHead = pNewNode;
   }
   pOldNode->pPrev = pNewNode;
   return (POSITION) pNewNode;

}



POSITION pointer_list::insert_after(POSITION position, void * newElement)
{

   ASSERT_VALID(this);

   if (position == NULL)
      return add_tail(newElement); // insert after nothing -> tail of the list

   // Insert it before position
   node* pOldNode = (node*) position;
   ASSERT(__is_valid_address(pOldNode, sizeof(node)));
   node* pNewNode = NewNode(pOldNode, pOldNode->pNext);
   pNewNode->data = newElement;

   if (pOldNode->pNext != NULL)
   {
      ASSERT(__is_valid_address(pOldNode->pNext, sizeof(node)));
      pOldNode->pNext->pPrev = pNewNode;
   }
   else
   {
      ASSERT(pOldNode == m_pnodeTail);
      m_pnodeTail = pNewNode;
   }
   pOldNode->pNext = pNewNode;
   return (POSITION) pNewNode;

}



void pointer_list::remove_at(POSITION position)
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
      m_pnodeHead = pOldNode->pNext;
   }
   else
   {
      ASSERT(__is_valid_address(pOldNode->pPrev, sizeof(node)));
      pOldNode->pPrev->pNext = pOldNode->pNext;
   }
   if (pOldNode == m_pnodeTail)
   {
      m_pnodeTail = pOldNode->pPrev;
   }
   else
   {
      ASSERT(__is_valid_address(pOldNode->pNext, sizeof(node)));
      pOldNode->pNext->pPrev = pOldNode->pPrev;
   }
   FreeNode(pOldNode);
}


/////////////////////////////////////////////////////////////////////////////
// slow operations

POSITION pointer_list::find_index(int_ptr nIndex) const
{
   ASSERT_VALID(this);

   if (nIndex >= m_nCount || nIndex < 0)
      return NULL;  // went too far

   node* pNode = m_pnodeHead;
   while (nIndex--)
   {
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      pNode = pNode->pNext;
   }
   return (POSITION) pNode;
}

POSITION pointer_list::find(void * searchValue, POSITION startAfter) const
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
      pNode = pNode->pNext;  // start after the one specified
   }

   for (; pNode != NULL; pNode = pNode->pNext)
      if (pNode->data == searchValue)
         return (POSITION) pNode;
   return NULL;
}


void pointer_list::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << m_nCount << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      POSITION pos = get_head_position();
      while (pos != NULL)
         dumpcontext << "\n\t" << get_next(pos);
   }

   dumpcontext << "\n";
}

void pointer_list::assert_valid() const
{
   object::assert_valid();

   if (m_nCount == 0)
   {
      // is_empty list
      ASSERT(m_pnodeHead == NULL);
      ASSERT(m_pnodeTail == NULL);
   }
   else
   {
      // non-is_empty list
      ASSERT(__is_valid_address(m_pnodeHead, sizeof(node)));
      ASSERT(__is_valid_address(m_pnodeTail, sizeof(node)));
   }
}
