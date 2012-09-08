#ifndef _Sockets_Exception_H
#define _Sockets_Exception_H


#ifdef sockets
namespace sockets {
#endif



class CLASS_DECL_ca Exception
{
public:
   Exception(const string & description);
   virtual ~Exception() {}

   virtual const string ToString() const;

   Exception(const Exception& ) {} // copy constructor

   Exception& operator=(const Exception& ) { return *this; } // assignment operator

private:
   string m_description;

};



#ifdef sockets
} // namespace sockets {
#endif

#endif // _Sockets_Exception_H

