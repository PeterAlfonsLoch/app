#pragma once


class CLASS_DECL_AURA box
{
public:


   point3d m_p; // origin
   point3d m_d; // direction
   point3d m_s; // size


   point3d center();

   void rotate(point3d p,point3d r);

   box & operator -= (const point3d & p)
   {

      m_p -= p;

      return *this;


   }

   box & operator += (const point3d & p)
   {

      m_p += p;

      return *this;


   }

   array < point3d > vertices();
   static array < int_array > faces();
   array < array < point3d > > faces_vertices();
   point3d get_nearest_vertice(point3d p);
   index find_nearest_vertice(point3d p);
   index find_nearest_vertice(LONG x,LONG y);



};

