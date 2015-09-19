

point3d box::center()
{
   point3d p;


   p = m_p + point3d(m_s.x / 2.0,m_s.y / 2.0,m_s.z / 2.0).rotate(m_d);

   //p.x = m_s.x *cos(m_d.z) / 2.0 - m_s.y * sin(m_d.z) / 2.0;
   //p.y = m_s.x *sin(m_d.z) / 2.0 + m_s.y * cos(m_d.z) / 2.0;
   //p.y = m_s.y *cos(m_d.x) / 2.0 - m_s.z * sin(m_d.x) / 2.0;
   //p.z = m_s.y *sin(m_d.x) / 2.0 + m_s.z * cos(m_d.x) / 2.0;
   //p.z = m_s.z *cos(m_d.y) / 2.0 - m_s.x * sin(m_d.y) / 2.0;
   //p.x = m_s.z *sin(m_d.y) / 2.0 + m_s.x * cos(m_d.y) / 2.0;

   //p += m_p;

   return p;


}

void box::rotate(point3d p,point3d r)
{

   operator -=(p);


   //point3d OriginDirection(0, acos(m_p.z / (sqrt(m_p.x * m_p.x + m_p.y * m_p.y + m_p.z * m_p.z))), atan2(m_p.y,m_p.x));

   m_d += r;
   m_p = m_p.rotate(r);

   operator +=(p);


}





array < int_array > box::faces()
{

   array < int_array > a2;

   // front
   {

      int_array a;

      a.add(0);
      a.add(1);
      a.add(3);

      a2.add(a);

   }

   // right
   {

      int_array a;

      a.add(1);
      a.add(5);
      a.add(2);

      a2.add(a);

   }

   // back
   {

      int_array a;

      a.add(5);
      a.add(4);
      a.add(6);

      a2.add(a);

   }

   // left
   {

      int_array a;

      a.add(4);
      a.add(0);
      a.add(7);

      a2.add(a);

   }

   // down
   {

      int_array a;

      a.add(2);
      a.add(3);
      a.add(6);

      a2.add(a);

   }

   // up
   {

      int_array a;

      a.add(4);
      a.add(5);
      a.add(0);

      a2.add(a);

   }


   return a2;
}



array < array < point3d > > box::faces_vertices()
{

   array < point3d > v = vertices();
   array < int_array > f = faces();

   array < array < point3d > > fv;
   array < point3d > vertices;

   for(index i = 0; i < f.get_count(); i++)
   {
      int_array & ia = f[i];
      vertices.remove_all();
      for(index j = 0; j < ia.get_count(); j++)
      {
         vertices.add(v[ia[j]]);
      }
      fv.add(vertices);
   }
   return fv;


}

array < point3d > box::vertices()
{

   array < point3d >  p;

   p.set_size(8);


   p[0] = m_p;
   p[1] = p[0] + point3d(m_s.x,0,0).rotate(m_d);
   p[2] = p[0] + point3d(m_s.x,m_s.y,0).rotate(m_d);
   p[3] = p[0] + point3d(0,m_s.y,0).rotate(m_d);

   p[4] = m_p + point3d(0,0,m_s.z).rotate(m_d);
   p[5] = p[4] + point3d(m_s.x,0,0).rotate(m_d);
   p[6] = p[4] + point3d(m_s.x,m_s.y,0).rotate(m_d);
   p[7] = p[4] + point3d(0,m_s.y,0).rotate(m_d);

   return p;
}
