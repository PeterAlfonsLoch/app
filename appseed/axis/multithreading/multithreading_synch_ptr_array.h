template < class T >
class synch_ptr_array:
   virtual public ptr_array < T >
{
public:

   mutex m_mutex;
   synch_index_ptr_array m_indexptra;

   synch_ptr_array(sp(::axis::application) papp): element(papp),m_mutex(papp),m_indexptra(&m_mutex){}
   virtual ~synch_ptr_array() {}

   bool add(T * p)
   {

      synch_lock sl(&m_mutex);

      return this->add_unique(p);

   }

   ::count remove(T * p)
   {

      synch_lock sl(&m_mutex);

      index  iRemove;

      ::count c = 0;

      while((iRemove = this->remove_first(p)) >= 0)
      {

         m_indexptra.on_removed(iRemove);

         c++;

      }

      return c;

   }

   void preg(index * pi)
   {

      m_indexptra.reg(pi);

   }

   void punreg(index * pi)
   {

      m_indexptra.unreg(pi);

   }


   ptr_array < T > base_ptra()
   {
      synch_lock sl(&m_mutex);
      return *dynamic_cast < ptr_array < T > * > (this);

   }



#undef new
   DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION
#define new AXIS_NEW


};
