#pragma once


class CLASS_DECL_ca fixed_string_log_interface
{
public:

   
   virtual void OnAllocateSpill(strsize nActualChars, strsize nFixedChars, const string_data * pData) throw() = 0;
   virtual void OnReallocateSpill(strsize nActualChars, strsize nFixedChars, const string_data * pData) throw() = 0;


};


class CLASS_DECL_ca fixed_string_manager :
   public string_manager_interface
{
protected:


   string_manager_interface * m_pMgr;
   string_data* m_pData;


public:


   static fixed_string_log_interface * s_pLog;

   fixed_string_manager(string_data * pData,int nChars, string_manager_interface * pMgr = NULL ) throw();
   virtual ~fixed_string_manager() throw();

   string_manager_interface* GetBackupManager() const throw();

   virtual string_data * allocate(strsize nChars, int nCharSize) throw();
   virtual void Free( string_data * pData ) throw();
   virtual string_data * Reallocate(string_data * pData, strsize nChars, int nCharSize ) throw();
   virtual string_data * GetNilString() throw();
   virtual string_manager_interface* Clone() throw();

};


template< int t_nChars >
class fixed_string :
   private fixed_string_manager,
   public string
{
protected:


   string_data m_data;
   string::XCHAR m_achData[t_nChars+1];


public:
   fixed_string() throw();
   explicit fixed_string(string_manager_interface* pstringmanager ) throw();
   fixed_string(const fixed_string< t_nChars >& str );
   fixed_string(string str );
   fixed_string(const string::XCHAR* psz);
   fixed_string(const string::XCHAR* psz,int nLength);
   explicit fixed_string(const string::YCHAR* psz);
   explicit fixed_string(const unsigned char* psz);
   ~fixed_string() throw();

   fixed_string< t_nChars >& operator=(const fixed_string< t_nChars >& str );
   fixed_string< t_nChars >& operator=(const char* psz );
   fixed_string< t_nChars >& operator=(const wchar_t* psz );
   fixed_string< t_nChars >& operator=(const unsigned char* psz);
   fixed_string< t_nChars >& operator=(const string & str );

};

template < int t_nChars >
fixed_string< t_nChars >::fixed_string() throw() :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( static_cast< string_manager_interface* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::fixed_string(string_manager_interface* pstringmanager ) throw() :
   fixed_string_manager( &m_data, t_nChars, pstringmanager ),
   string( static_cast< string_manager_interface* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::fixed_string(const fixed_string< t_nChars >& str ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( str.GetString(), str.get_length(), static_cast< fixed_string_manager* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::fixed_string(string str ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( str.GetString(), str.get_length(), static_cast< fixed_string_manager* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::fixed_string(const string::XCHAR* psz ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, static_cast< fixed_string_manager* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::fixed_string(const string::XCHAR* psz,int nLength ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, nLength, static_cast< fixed_string_manager* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::fixed_string(const string::YCHAR* psz ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, static_cast< fixed_string_manager* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::fixed_string(const unsigned char* psz ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, static_cast< fixed_string_manager* >( this ) )
{
}

template < int t_nChars >
fixed_string< t_nChars >::~fixed_string() throw()
{
   Empty();
}

template < int t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const fixed_string< t_nChars >& str )
{
   string::operator=( str );
   return *this;
}

template < int t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const char* psz )
{
   string::operator=( psz );
   return *this;
}

template < int t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const wchar_t* psz )
{
   string::operator=( psz );
   return *this;
}

template < int t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const unsigned char* psz )
{
   string::operator=( psz );
   return *this;
}

template < int t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const string & str )
{
   string::operator=( str );
   return *this;
}


class CLASS_DECL_ca fixed_string_log :
   public fixed_string_log_interface
{
public:


   fixed_string_log() throw();
   virtual ~fixed_string_log() throw();


   void OnAllocateSpill(strsize nActualChars, strsize nFixedChars, const string_data* pData ) throw();
   void OnReallocateSpill(strsize nActualChars, strsize nFixedChars, const string_data* pData ) throw();


};




// This struct have the same primitive::memory layout as string and is used to enable
// const statically initialized string without making a copy on the heap
template < int t_nChars> struct const_fixed_string
{


   string_data m_data;
   string::XCHAR m_achData[t_nChars];


};

