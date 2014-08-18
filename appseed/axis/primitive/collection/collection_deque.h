#pragma once


template < class TYPE,class ARG_TYPE = const TYPE &,class BASE_ARRAY = array < TYPE,ARG_TYPE > >
class deque:
   virtual public BASE_ARRAY
{
public:
    
    typedef TYPE BASE_TYPE;
    typedef ARG_TYPE BASE_ARG_TYPE;

    void push_back(ARG_TYPE t)
    {
       BASE_ARRAY::add(t);
    }

    void pop_back()
    {
       BASE_ARRAY::remove_last();
    }
    

};
