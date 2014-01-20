#pragma once


/*
class CLASS_DECL_CORE fixed_string_log_interface
{
public:

   
   virtual void OnAllocateSpill(strsize nActualChars, strsize nFixedChars, const string_data * pData) throw() = 0;
   virtual void OnReallocateSpill(strsize nActualChars, strsize nFixedChars, const string_data * pData) throw() = 0;


};


class CLASS_DECL_CORE fixed_string_manager :
   public string_manager
{
protected:


   string_manager * m_pMgr;
   string_data* m_pData;


public:


   static fixed_string_log_interface * s_pLog;

   fixed_string_manager(string_data * pData,int32_t nChars, string_manager * pMgr = NULL ) throw();
   virtual ~fixed_string_manager() throw();

   string_manager* GetBackupManager() const throw();

   virtual string_data * allocate(strsize nChars, int32_t nCharSize) throw();
   virtual void Free( string_data * pData ) throw();
   virtual string_data * Reallocate(string_data * pData, strsize nChars, int32_t nCharSize ) throw();
   virtual string_data * GetNilString() throw();
   virtual string_manager* Clone() throw();

};


template< int32_t t_nChars >
class fixed_string :
   private fixed_string_manager,
   public string
{
protected:


   string_data m_data;
   char m_achData[t_nChars+1];


public:
   fixed_string() throw();
   explicit fixed_string(string_manager* pstringmanager ) throw();
   fixed_string(const fixed_string< t_nChars >& str );
   fixed_string(string str );
   fixed_string(const char* psz);
   fixed_string(const char* psz,int32_t nLength);
   explicit fixed_string(const wchar_t* psz);
   explicit fixed_string(const uchar* psz);
   ~fixed_string() throw();

   fixed_string< t_nChars >& operator=(const fixed_string< t_nChars >& str );
   fixed_string< t_nChars >& operator=(const char* psz );
   fixed_string< t_nChars >& operator=(const wchar_t* psz );
   fixed_string< t_nChars >& operator=(const uchar* psz);
   fixed_string< t_nChars >& operator=(const string & str );

};

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string() throw() :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( static_cast< string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string(string_manager* pstringmanager ) throw() :
   fixed_string_manager( &m_data, t_nChars, pstringmanager ),
   string( static_cast< string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string(const fixed_string< t_nChars >& str ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( str.GetString(), str.get_length(), static_cast< fixed_string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string(string str ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( str.GetString(), str.get_length(), static_cast< fixed_string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string(const char* psz ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, static_cast< fixed_string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string(const char* psz,int32_t nLength ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, nLength, static_cast< fixed_string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string(const wchar_t* psz ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, static_cast< fixed_string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::fixed_string(const uchar* psz ) :
   fixed_string_manager( &m_data, t_nChars, string_trait::GetDefaultManager() ),
   string( psz, static_cast< fixed_string_manager* >( this ) )
{
}

template < int32_t t_nChars >
fixed_string< t_nChars >::~fixed_string() throw()
{
   Empty();
}

template < int32_t t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const fixed_string< t_nChars >& str )
{
   string::operator=( str );
   return *this;
}

template < int32_t t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const char* psz )
{
   string::operator=( psz );
   return *this;
}

template < int32_t t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const wchar_t* psz )
{
   string::operator=( psz );
   return *this;
}

template < int32_t t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const uchar* psz )
{
   string::operator=( psz );
   return *this;
}

template < int32_t t_nChars >
fixed_string< t_nChars >& fixed_string< t_nChars >::operator=(const string & str )
{
   string::operator=( str );
   return *this;
}


class CLASS_DECL_CORE fixed_string_log :
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
template < int32_t t_nChars> struct const_fixed_string
{


   string_data m_data;
   char m_achData[t_nChars];


};

*/