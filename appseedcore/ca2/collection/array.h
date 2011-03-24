#pragma once


namespace gen
{

   template < class A, class T >
   A array(T t1)
   {
      A a;
      a.add(t1);
      return a;
   }

   namespace lemon
   {
      class CLASS_DECL_ca array  : virtual public ::radix::object
      {
      public:
         array(::ca::application * papp);

         template < class A >
         void randomize(A & a)
         {
            A b;
            while(a.get_count() > 0)
            {
               index i = System.math().RandRange(0, a.get_upper_bound());
               b.add(a.element_at(i));
               a.remove_at(i);
            }
            a = b;
         }


         template < class A, class TYPE >
         count populate(A & a, TYPE start, TYPE end, TYPE step, bool bIncludeStart = true, bool bIncludeEnd = true, bool bIncludeEndOnStep = true)
         {
            count count = 0;
            TYPE cur = start;
            if(bIncludeStart)
            {
               if(start == end)
               {
                  if(bIncludeEnd)
                  {
                     a.add(cur);
                     return 1;
                  }
                  else
                     return 0;
               }
               else
               {
                  a.add(cur);
                  count++;
               }
            }
            if(end > start)
            {
               if(step == 0)
                  return count;
               if(step < 0)
                  step = -step;
               while(true)
               {
                  cur = cur + step;
                  if(cur >= end)
                     break;
                  a.add(cur);
                  count++;
               }
            }
            else
            {
               if(step == 0)
                  return count;
               if(step < 0)
                  step = -step;
               while(true)
               {
                  cur = cur - step;
                  if(cur <= end)
                     break;
                  a.add(cur);
                  count++;
               }
            }
            if(bIncludeEnd)
            {
               if(bIncludeEndOnStep)
               {
                  if(cur == end)
                  {
                     a.add(cur);
                     return count + 1;
                  }
                  else
                  {
                     return count;
                  }
               }
               else
               {
                  a.add(cur);
                  return count + 1;
               }
            }
            else
            {
               return count;
            }
         }

      };



      template < class A >
	   void array_merge(A & a, const A & a1, const A & a2)
	   {
         a = a1 + a2;
	   }

      template < class A >
	   void array_makecombination(array_ptr_alloc < A > & comb, const A & a, A blindprefixa = A(), index idx = 0)
	   {
		   comb.add(blindprefixa);
		   for(int i = idx; i < a.get_count(); i++)
		   {
			   array_makecombination(comb, a, blindprefixa + ::gen::array < A > (a[i]), i + 1);
		   }
	   }

/*	function array_arrange($a)
	{
		$comb = array_makecombination($a);
		$ret = array();
		$count = count($comb);
		foreach($comb as $ai)
		{
			if(count($ai) > 0)
				$ret = array_merge($ret, array_permute($ai));
		}
		return $ret;
	}

	function array_permute($a)
	{
		$count = count($a);
		if($count == 1)
			return array($a);
		$ret = array();
		for($i = 0; $i < $count; $i++)
		{
			$elem = $a[$i];
			$elema = array($a[$i]);
			$topermut = array_merge(array_slice($a, 0, $i), array_slice($a, $i + 1, $count - $i - 1));
//			print "implode topermut".implode(",", $topermut);
			$permut = array_permute($topermut);
			foreach($permut as $permi)
			{
				$newelem = array_merge($elema, $permi);
		//		print "implode newelem=$newelem".implode(",", $newelem);
				$ret[] = $newelem;
			}
		}
		return $ret;
	}

	function x1_decode_ida($str)
	{
		if(empty($str))
			return array();
		$str = str_replace("><", ",", $str);
		$str = substr($str, 1, strlen($str) - 2);
		$ida = explode(",", $str);;
		return $ida;
	}
	function x1_encode_ida($ida)
	{
		$ret = "";
		foreach($ida as $id)
		{
			$ret .= "<$id>";
		}
		return $ret;
	}
	
	function array_remove_by_keys($a, $keys, $bStrict = false)
	{
		$newa = array();
		foreach($a as $key=>$value)
		{
			if(!in_array($key, $keys, $bStrict))
			{
				$newa[$key] = $value;
			}
		}
		return $newa;
	}
	
	function array_is_equal(&$a1, &$a2)
	{
		if(!is_array($a1) || !is_array($a2))
			return false;	
		return array_contains_array($a1, $a2) && array_contains_array($a2, $a1);
	}

	function array_contains_array(&$a1, &$a2)
	{
		foreach($a2 as $key=>$value)
		{
			if(!array_key_exists($key, $a1))
				return false;
			if(!gen_is_equal($a1[$key], $value))
				return false;
		}
		return true;
	}
	
	function array_randomize($a)
	{
		$count = count($a);
		$newa = array();
		while($count > 0)
		{
			$i = mt_rand(0, $count - 1);
			$item = array_splice($a, $i, 1);
			$newa[] = $item[0];
			$count--;
		}
		return $newa;		
	}
	
	function array_pick_random_item($a)
	{
		return $a[mt_rand(0, count($a) - 1)];
	}
	
	function array_remove($item, $a)
	{
		$reta = array();
		foreach($a as $key=>$value)
		{
			if($value != $item)
			{
				$reta[$key] = $value;
			}
		}
		return $reta;
	}
*/
   } // namespace lemon
} // namespace gen