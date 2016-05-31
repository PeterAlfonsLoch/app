#pragma once

template < typename SIZE >
SIZE typed_unit_size()
{
   SIZE s ={1, 1};
   return s;
}

template < >
inline ::SIZE typed_unit_size < ::SIZE >()
{
   ::SIZE s ={1, 1};
   return s;
}


template < typename POINT2D >
class point2d_array_base:
   public comparable_array < POINT2D >,
   virtual public ::xml::exportable,
   virtual public ::xml::importable
{
public:
   inline point2d_array_base(): comparable_array < POINT2D >() {}
   inline point2d_array_base(const point2d_array_base & pointset) { operator=(pointset); }
   virtual ~point2d_array_base() { }


   operator typename POINT2D::BASE * () { return this->get_data(); }

   void offset(typename POINT2D::TYPE x,typename POINT2D::TYPE y);
   void offset(POINT2D point) { offset(point.x,point.y); }

   void rotate(double dAngle);

   void get_bounding_rect(typename POINT2D::LPRECT lprect) const;

   static void get_bounding_rect(typename POINT2D::LPRECT lprect,const typename POINT2D::BASE * lppoint,::count count);

   bool bounding_rect_contains_pt(typename POINT2D::BASE pt);

   bool polygon_contains(typename POINT2D::BASE pt);

   inline index add(typename POINT2D::TYPE x,typename POINT2D::TYPE y) { return comparable_array < POINT2D >::add(POINT2D(x,y)); }
   inline index add(typename POINT2D::BASE point) { return comparable_array < POINT2D >::add(POINT2D(point)); }
   inline point2d_array_base & operator =(const point2d_array_base & pointset) { this->copy(pointset); return *this; }

   virtual void xml_import(::xml::input_tree & xmlif);
   virtual void xml_export(::xml::output_tree & xmlof);


   ::count add_unique_range(typename POINT2D::BASE ptBeg,typename POINT2D::BASE ptEnd,typename POINT2D::SIZE s = POINT2D::SIZE::unit_size());


};




class CLASS_DECL_AURA point_array :
   public point2d_array_base < point >,
   virtual public ::xml::exportable,
   virtual public ::xml::importable
{
public:
   inline point_array() : point2d_array_base < point >() {}
   inline point_array(const point_array & pointset) { operator=(pointset); }
   point_array(const POINTD * lppt,::count c);
   virtual ~point_array();


   //operator POINT * () { return get_data();  }

   //void offset(int32_t x, int32_t y);
   //void offset(class point point) { offset(point.x,point.y); }

   //void rotate(double dAngle);

   //void get_bounding_rect(LPRECT lprect) const;

   //static void get_bounding_rect(LPRECT lprect, const POINT * lppoint, ::count count);

   //bool bounding_rect_contains_pt(point pt);

   //bool polygon_contains(point pt);

   //__inline index add(int32_t x, int32_t y) {return comparable_array < point >::add(point(x, y)); }
   //__inline index add(POINT point) {return add(point.x, point.y); }
   //__inline point_array & operator =(const point_array & pointset) { copy(pointset); return *this; }

   //virtual void xml_import(::xml::input_tree & xmlif);
   //virtual void xml_export(::xml::output_tree & xmlof);


   //bool add_uniquerange()
   //int x1 = m_ptileset->m_ptBeg.x;

   //int x2 = m_ptileset->m_ptEnd.x;

   //int y1 = m_ptileset->m_ptBeg.y;

   //int y2 = m_ptileset->m_ptEnd.y;

   //::sort::sort(x1,x2);

   //::sort::sort(y1,y2);

   //for(index x = x1; x <= MIN(x2,m_ptileset->xcount() - 1); x++)
   //{
   //   for(index y = y1; y <= MIN(y2,m_ptileset->ycount() - 1); y++)
   //   {
   //      m_ptileset->m_ptaSel.add_unique(point(x,y));
   //   }
   //}


};

class CLASS_DECL_AURA point64_array :
   public point2d_array_base < point64 >
{
public:
   virtual ~point64_array();

   //void offset(int64_t x, int64_t y);
   //void offset(class point64 point);
};


class CLASS_DECL_AURA pointd_array :
   //public comparable_array < pointd >
   public point2d_array_base < pointd >
{
public:
   //__inline pointd_array() : comparable_array < pointd >() {}
   //__inline pointd_array(const pointd_array & pointset) { operator=(pointset); }
   virtual ~pointd_array();

   //void offset(double x, double y);
   //void offset(class point point);

   //void get_bounding_rect(LPRECTD lprect) const;

   //static void get_bounding_rect(LPRECTD lprect, const POINTD * lppoint, ::count count);

   //bool bounding_rect_contains_pt(pointd pt);


   //__inline index add(double x, double y) {return comparable_array < pointd >::add(pointd(x, y)); }
   //__inline index add(pointd point) {return add(point.x, point.y); }
   //__inline pointd_array & operator =(const pointd_array & pointset) { copy(pointset); return *this; }
   //void rotate(double dAngle);


};



