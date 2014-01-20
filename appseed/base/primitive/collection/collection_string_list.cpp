#include "framework.h"


string_list::string_list(int_ptr nBlockSize)
{
   ASSERT(nBlockSize > 0);

   m_nCount = 0;
   m_pnodeHead = m_pnodeTail = m_pnodeFree = NULL;
   m_pplex = NULL;
   m_nBlockSize = nBlockSize;
}

void string_list::remove_all()
{
   ASSERT_VALID(this);

   // destroy elements

   node* pNode;
   for (pNode = m_pnodeHead; pNode != NULL; pNode = pNode->m_pnodeNext)
      DestructElement(&pNode->data);


   m_nCount = 0;
   m_pnodeHead = m_pnodeTail = m_pnodeFree = NULL;
   m_pplex->FreeDataChain();
   m_pplex = NULL;
}

string_list::~string_list()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Node helpers
/*
 * Implementation note: node's are stored in plex blocks and
 *  chained together. Free blocks are maintained in a singly linked list
 *  using the 'm_pnodeNext' member of node with 'm_pnodeFree' as the head.
 *  Used blocks are maintained in a doubly linked list using both 'm_pnodeNext'
 *  and 'm_pnodePrevious' as links and 'm_pnodeHead' and 'm_pnodeTail'
 *   as the head/tail.
 *
 * We never free a plex block unless the List is destroyed or remove_all()
 *  is used - so the total number of plex blocks may grow large depending
 *  on the maximum past size of the list.
 */

string_list::node*
string_list::NewNode(string_list::node* m_pnodePrevious, string_list::node* m_pnodeNext)
{
   if (m_pnodeFree == NULL)
   {
      // add another block
      plex* pNewBlock = plex::create(m_pplex, m_nBlockSize,
             sizeof(node));

      // chain them into free list
      node* pNode = (node*) pNewBlock->data();
      // free in reverse order to make it easier to debug
      pNode += m_nBlockSize - 1;
      for (int_ptr i = m_nBlockSize-1; i >= 0; i--, pNode--)
      {
         pNode->m_pnodeNext = m_pnodeFree;
         m_pnodeFree = pNode;
      }
   }
   ASSERT(m_pnodeFree != NULL);  // we must have something

   string_list::node* pNode = m_pnodeFree;
   m_pnodeFree = m_pnodeFree->m_pnodeNext;
   pNode->m_pnodePrevious = m_pnodePrevious;
   pNode->m_pnodeNext = m_pnodeNext;
   m_nCount++;
   ASSERT(m_nCount > 0);  // make sure we don't overflow


   ConstructElement(&pNode->data);



   return pNode;
}

void string_list::FreeNode(string_list::node* pNode)
{
   if (pNode == NULL)
   {
      throw invalid_argument_exception(get_app());
   }

   DestructElement(&pNode->data);

   pNode->m_pnodeNext = m_pnodeFree;
   m_pnodeFree = pNode;
   m_nCount--;
   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();
}

/////////////////////////////////////////////////////////////////////////////

POSITION string_list::add_head(const char * newElement)
{

   return add_head(string(newElement));

}


POSITION string_list::add_head(const string & newElement)
{
   ASSERT_VALID(this);

   node* pNewNode = NewNode(NULL, m_pnodeHead);
   pNewNode->data = newElement;
   if (m_pnodeHead != NULL)
      m_pnodeHead->m_pnodePrevious = pNewNode;
   else
      m_pnodeTail = pNewNode;
   m_pnodeHead = pNewNode;
   return (POSITION) pNewNode;
}


POSITION string_list::add_tail(const char * newElement)
{

   return add_tail(string(newElement));

}


POSITION string_list::add_tail(const string & newElement)
{
   ASSERT_VALID(this);

   node* pNewNode = NewNode(m_pnodeTail, NULL);
   pNewNode->data = newElement;
   if (m_pnodeTail != NULL)
      m_pnodeTail->m_pnodeNext = pNewNode;
   else
      m_pnodeHead = pNewNode;
   m_pnodeTail = pNewNode;
   return (POSITION) pNewNode;
}


void string_list::add_head(string_list* pNewList)
{
   ASSERT_VALID(this);
   ASSERT_VALID(pNewList);
   if (pNewList == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   ASSERT_KINDOF(string_list, pNewList);

   // add a list of same elements to head (maintain order)
   POSITION pos = pNewList->get_tail_position();
   while (pos != NULL)
      add_head(pNewList->get_previous(pos));
}

void string_list::add_tail(string_list* pNewList)
{
   ASSERT_VALID(this);
   ASSERT_VALID(pNewList);
   if (pNewList == NULL)
   {
      throw invalid_argument_exception(get_app());
   }
   ASSERT_KINDOF(string_list, pNewList);

   // add a list of same elements
   POSITION pos = pNewList->get_head_position();
   while (pos != NULL)
      add_tail(pNewList->get_next(pos));
}

string string_list::remove_head()
{
   ENSURE_VALID(this);
   ENSURE(m_pnodeHead != NULL);  // throws if called on is_empty list
   ASSERT(__is_valid_address(m_pnodeHead, sizeof(node)));

   node* pOldNode = m_pnodeHead;
   string returnValue = pOldNode->data;

   m_pnodeHead = pOldNode->m_pnodeNext;
   if (m_pnodeHead != NULL)
      m_pnodeHead->m_pnodePrevious = NULL;
   else
      m_pnodeTail = NULL;
   FreeNode(pOldNode);
   return returnValue;
}

string string_list::remove_tail()
{
   ASSERT_VALID(this);
   ASSERT(m_pnodeTail != NULL);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(m_pnodeTail, sizeof(node)));

   node* pOldNode = m_pnodeTail;
   string returnValue = pOldNode->data;

   m_pnodeTail = pOldNode->m_pnodePrevious;
   if (m_pnodeTail != NULL)
      m_pnodeTail->m_pnodeNext = NULL;
   else
      m_pnodeHead = NULL;
   FreeNode(pOldNode);
   return returnValue;
}

POSITION string_list::insert_before(POSITION position, const char * newElement)
{

   return insert_before(position, string(newElement));

}


POSITION string_list::insert_before(POSITION position, const string & newElement)
{
   ASSERT_VALID(this);

   if (position == NULL)
      return add_head(newElement); // insert before nothing -> head of the list

   // Insert it before position
   node* pOldNode = (node*) position;
   node* pNewNode = NewNode(pOldNode->m_pnodePrevious, pOldNode);
   pNewNode->data = newElement;

   if (pOldNode->m_pnodePrevious != NULL)
   {
      ASSERT(__is_valid_address(pOldNode->m_pnodePrevious, sizeof(node)));
      pOldNode->m_pnodePrevious->m_pnodeNext = pNewNode;
   }
   else
   {
      ASSERT(pOldNode == m_pnodeHead);
      m_pnodeHead = pNewNode;
   }
   pOldNode->m_pnodePrevious = pNewNode;
   return (POSITION) pNewNode;
}


POSITION string_list::insert_after(POSITION position, const char * newElement)
{

   return insert_after(position, string(newElement));

}


POSITION string_list::insert_after(POSITION position, const string & newElement)
{
   ASSERT_VALID(this);

   if (position == NULL)
      return add_tail(newElement); // insert after nothing -> tail of the list

   // Insert it before position
   node* pOldNode = (node*) position;
   ASSERT(__is_valid_address(pOldNode, sizeof(node)));
   node* pNewNode = NewNode(pOldNode, pOldNode->m_pnodeNext);
   pNewNode->data = newElement;

   if (pOldNode->m_pnodeNext != NULL)
   {
      ASSERT(__is_valid_address(pOldNode->m_pnodeNext, sizeof(node)));
      pOldNode->m_pnodeNext->m_pnodePrevious = pNewNode;
   }
   else
   {
      ASSERT(pOldNode == m_pnodeTail);
      m_pnodeTail = pNewNode;
   }
   pOldNode->m_pnodeNext = pNewNode;
   return (POSITION) pNewNode;
}


void string_list::remove_at(POSITION position)
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
      m_pnodeHead = pOldNode->m_pnodeNext;
   }
   else
   {
      ASSERT(__is_valid_address(pOldNode->m_pnodePrevious, sizeof(node)));
      pOldNode->m_pnodePrevious->m_pnodeNext = pOldNode->m_pnodeNext;
   }
   if (pOldNode == m_pnodeTail)
   {
      m_pnodeTail = pOldNode->m_pnodePrevious;
   }
   else
   {
      ASSERT(__is_valid_address(pOldNode->m_pnodeNext, sizeof(node)));
      pOldNode->m_pnodeNext->m_pnodePrevious = pOldNode->m_pnodePrevious;
   }
   FreeNode(pOldNode);
}


/////////////////////////////////////////////////////////////////////////////
// slow operations

POSITION string_list::find_index(int_ptr nIndex) const
{
   ASSERT_VALID(this);

   if(nIndex == 0 && m_nCount > 0)
      return (POSITION) m_pnodeHead;

   if (nIndex >= m_nCount || nIndex < 0)
      return NULL;  // went too far

   node* pNode = m_pnodeHead;
   while(nIndex-- > 0)
   {
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      pNode = pNode->m_pnodeNext;
   }
   return (POSITION) pNode;
}

POSITION string_list::reverse_find_index(int_ptr nIndex) const
{
   ASSERT_VALID(this);

   nIndex = m_nCount - nIndex - 1;

   if(nIndex == 0 && m_nCount > 0)
      return (POSITION) m_pnodeTail;

   if (nIndex >= m_nCount || nIndex < 0)
      return NULL;  // went too far


   node* pNode = m_pnodeTail;
   while(nIndex-- > 0)
   {
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      pNode = pNode->m_pnodePrevious;
   }
   return (POSITION) pNode;
}

POSITION string_list::find(const char * searchValue, POSITION startAfter) const
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
      pNode = pNode->m_pnodeNext;  // start after the one specified
   }

   for (; pNode != NULL; pNode = pNode->m_pnodeNext)
      if (pNode->data == searchValue)
         return (POSITION) pNode;
   return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Serialization
/*
void string_list::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   object::Serialize(ar);

   if (ar.IsStoring())
   {
      ar.WriteCount(m_nCount);
      for (node* pNode = m_pnodeHead; pNode != NULL; pNode = pNode->m_pnodeNext)
      {
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         ar << pNode->data;
      }
   }
   else
   {
      uint_ptr nNewCount = ar.ReadCount();
      string newData;
      while (nNewCount--)
      {
         ar >> newData;
         add_tail(newData);
      }
   }
}
*/

void string_list::dump(dump_context & dumpcontext) const
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

void string_list::assert_valid() const
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




