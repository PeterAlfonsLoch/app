//#include "framework.h"


string_list::string_list() 
{

}



string_list::~string_list()
{
}

//POSITION string_list::add_head(const char * newElement)
//{
//
//   return add_head(string(newElement));
//
//}
//
//
//POSITION string_list::add_head(const string & newElement)
//{
//   ASSERT_VALID(this);
//
//   node* pNewNode = NewNode(NULL, m_phead);
//   pNewNode->data = newElement;
//   if (m_phead != NULL)
//      m_phead->m_pprev = pNewNode;
//   else
//      m_ptail = pNewNode;
//   m_phead = pNewNode;
//   return (POSITION) pNewNode;
//}
//
//
//POSITION string_list::add_tail(const char * newElement)
//{
//
//   return add_tail(string(newElement));
//
//}
//
//
//POSITION string_list::add_tail(const string & newElement)
//{
//   ASSERT_VALID(this);
//
//   node* pNewNode = NewNode(m_ptail, NULL);
//   pNewNode->data = newElement;
//   if (m_ptail != NULL)
//      m_ptail->m_pnext = pNewNode;
//   else
//      m_phead = pNewNode;
//   m_ptail = pNewNode;
//   return (POSITION) pNewNode;
//}
//
//
//void string_list::add_head(string_list* pNewList)
//{
//   ASSERT_VALID(this);
//   ASSERT_VALID(pNewList);
//   if (pNewList == NULL)
//   {
//      throw invalid_argument_exception(get_app());
//   }
//   ASSERT_KINDOF(string_list, pNewList);
//
//   // add a list of same elements to head (maintain order)
//   POSITION pos = pNewList->get_tail_position();
//   while (pos != NULL)
//      add_head(pNewList->get_previous(pos));
//}
//
//void string_list::add_tail(string_list* pNewList)
//{
//   ASSERT_VALID(this);
//   ASSERT_VALID(pNewList);
//   if (pNewList == NULL)
//   {
//      throw invalid_argument_exception(get_app());
//   }
//   ASSERT_KINDOF(string_list, pNewList);
//
//   // add a list of same elements
//   POSITION pos = pNewList->get_head_position();
//   while (pos != NULL)
//      add_tail(pNewList->get_next(pos));
//}
//


//POSITION string_list::insert_before(POSITION position, const char * newElement)
//{
//
//   return insert_before(position, string(newElement));
//
//}
//
//
//POSITION string_list::insert_before(POSITION position, const string & newElement)
//{
//   ASSERT_VALID(this);
//
//   if (position == NULL)
//      return add_head(newElement); // insert before nothing -> head of the list
//
//   // Insert it before position
//   node* pOldNode = (node*) position;
//   node* pNewNode = NewNode(pOldNode->m_pprev, pOldNode);
//   pNewNode->data = newElement;
//
//   if (pOldNode->m_pprev != NULL)
//   {
//      ASSERT(__is_valid_address(pOldNode->m_pprev, sizeof(node)));
//      pOldNode->m_pprev->m_pnext = pNewNode;
//   }
//   else
//   {
//      ASSERT(pOldNode == m_phead);
//      m_phead = pNewNode;
//   }
//   pOldNode->m_pprev = pNewNode;
//   return (POSITION) pNewNode;
//}
//
//
//POSITION string_list::insert_after(POSITION position, const char * newElement)
//{
//
//   return insert_after(position, string(newElement));
//
//}
//
//
//POSITION string_list::insert_after(POSITION position, const string & newElement)
//{
//   ASSERT_VALID(this);
//
//   if (position == NULL)
//      return add_tail(newElement); // insert after nothing -> tail of the list
//
//   // Insert it before position
//   node* pOldNode = (node*) position;
//   ASSERT(__is_valid_address(pOldNode, sizeof(node)));
//   node* pNewNode = NewNode(pOldNode, pOldNode->m_pnext);
//   pNewNode->data = newElement;
//
//   if (pOldNode->m_pnext != NULL)
//   {
//      ASSERT(__is_valid_address(pOldNode->m_pnext, sizeof(node)));
//      pOldNode->m_pnext->m_pprev = pNewNode;
//   }
//   else
//   {
//      ASSERT(pOldNode == m_ptail);
//      m_ptail = pNewNode;
//   }
//   pOldNode->m_pnext = pNewNode;
//   return (POSITION) pNewNode;
//}
//
//
//void string_list::remove_at(POSITION position)
//{
//   ASSERT_VALID(this);
//
//   node* pOldNode = (node*) position;
//   ASSERT(__is_valid_address(pOldNode, sizeof(node)));
//
//   if (pOldNode == NULL)
//   {
//      throw invalid_argument_exception(get_app());
//   }
//
//   // remove pOldNode from list
//   if (pOldNode == m_phead)
//   {
//      m_phead = pOldNode->m_pnext;
//   }
//   else
//   {
//      ASSERT(__is_valid_address(pOldNode->m_pprev, sizeof(node)));
//      pOldNode->m_pprev->m_pnext = pOldNode->m_pnext;
//   }
//   if (pOldNode == m_ptail)
//   {
//      m_ptail = pOldNode->m_pprev;
//   }
//   else
//   {
//      ASSERT(__is_valid_address(pOldNode->m_pnext, sizeof(node)));
//      pOldNode->m_pnext->m_pprev = pOldNode->m_pprev;
//   }
//   FreeNode(pOldNode);
//}



POSITION string_list::find(string searchValue, POSITION startAfter) const
{
   ASSERT_VALID(this);

   node* pNode = (node*) startAfter;
   if (pNode == NULL)
   {
      pNode = m_phead;  // start at head
   }
   else
   {
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      pNode = pNode->m_pnext;  // start after the one specified
   }

   for (; pNode != NULL; pNode = pNode->m_pnext)
      if (pNode->m_value == searchValue)
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
      ar.WriteCount(m_count);
      for (node* pNode = m_phead; pNode != NULL; pNode = pNode->m_pnext)
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

   dumpcontext << "with " << m_count << " elements";
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

   if (m_count == 0)
   {
      // is_empty list
      ASSERT(m_phead == NULL);
      ASSERT(m_ptail == NULL);
   }
   else
   {
      // non-is_empty list
      ASSERT(__is_valid_address(m_phead, sizeof(node)));
      ASSERT(__is_valid_address(m_ptail, sizeof(node)));
   }
}




