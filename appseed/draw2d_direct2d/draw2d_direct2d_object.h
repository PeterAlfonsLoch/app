#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D object :
      virtual public ::draw2d::object
   {
   public:


      graphics *     m_pgraphics;

      enum e_data
      {
         data_graphics = 84,
      };

      
      object();
      virtual ~object();

      virtual void * get_os_data() const;
      virtual void * get_os_data_ex(int i) const;

      bool delete_object();

      int get_object(int nCount, LPVOID lpObject) const;
      UINT GetObjectType() const;
      bool CreateStockObject(int nIndex);
      bool UnrealizeObject();
      bool operator==(const object& obj) const;
      bool operator!=(const object& obj) const;

      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;

   };


} // namespace core