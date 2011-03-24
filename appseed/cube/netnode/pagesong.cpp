#include "StdAfx.h"

namespace netnode
{
   namespace karaoke		
   {
      page_song::page_song()
		{
			m_params["limitcount"] 	= gprop("gtable")["limitcount"];
			
			m_strQueryStyle = get("slsttyp");
			if(strlen(get("funuid")) > 0)
			{
				m_strQueryStyle = "fun";
			}
			
			initializePerPerTop($params);
			
		//	print_r($params);
			
			m_plist = new MusicIn2ListSong(
				&$musicdb, 
				$request_params_ex, 
				$param_query,
				$param_songid,
				$param_lyrics, 
				$param_querystyle, 
				$_GET['order'], 
				$_GET['page'], 
				$limitcount,
				$_GET['cid'],
				$_GET['aid'],
				$_GET['target'],
				$_GET['funuid'],
				$params);
				
			if($_GET['slsttyp'] == SQS_PER_YEAR_TOP
				|| $_GET['slsttyp'] == SQS_PER_MONTH_TOP
			  	|| $_GET['slsttyp'] == SQS_PER_WEEK_TOP
				|| $_GET['slsttyp'] == SQS_24HOUR_TOP
				|| $_GET['slsttyp'] == SQS_WEEK_TOP
				|| $_GET['slsttyp'] == SQS_LAST_MONTH_TOP
				|| $_GET['slsttyp'] == SQS_LAST_3_MONTH_TOP
				|| $_GET['slsttyp'] == SQS_LAST_6_MONTH_TOP
				|| $_GET['slsttyp'] == SQS_LAST_YEAR_TOP)
			{
				$this->list->bAsc = true;
			}
				
				
			$title1 		= &$this->title1;
			$pagetitle1 	= &$this->pagetitle1;
			
/*			if($param_root == 'letras')
			{
				$title1 = $langstr['SongList:Letras'];
			}
			else if($param_root == 'cifras')
			{
				$title1 = $langstr['SongList:Cifras'];
			}
			else
			{
				$title1 = $langstr['SongList:Songs'];
			}*/
			
//			$title1 = music_getRootShortTitle();
			$title1 = '';
			
			if(strlen($this->list->styletitle) > 0)
			{
				$title1 = str_not_empty($title1, '', ': ').$this->list->styletitle;
			}
			if($this->hasParam('aid'))
			{
				$title1 = str_not_empty($title1, '', ': ').$this->list->performer->name;
			}
			if($this->hasParam('cid'))
			{
				$title1 = str_not_empty($title1, '', ': ').$this->list->classname;
			}
			if($this->perpertop)
			{
				if($_GET['slsttyp'] == SQS_PER_YEAR_TOP)
				{
					$title1 = str_not_empty($title1, '', ': ').$this->ppt_year;
				}
				else if($_GET['slsttyp'] == SQS_PER_MONTH_TOP)
				{
					$title1 = str_not_empty($title1, '', ': ').$this->ppt_year.'-'.datetime_get_month_str($this->ppt_month);
				}
				else if($_GET['slsttyp'] == SQS_PER_WEEK_TOP)
				{
					$title1 = str_not_empty($title1, '', ': ').$this->ppt_year.'-'.datetime_get_month_str($this->ppt_month).'-'.$this->curNav->title;
				}
		  	}
			
			$pagetitle1 .= $title1." - ".music_getRootShortTitle();
			
			$g_html_meta_description = $pagetitle1;
				
			$this->asp = NULL;
			
			$this->lm 					= new AlphaSelectPerformerLinkMaker3();
			$this->lm->lang 			= $param_locale;
			$this->lm->style 			= $param_style;
			
			
			$this->lm->lang 			= $param_locale;
			$this->lm->style 			= $param_style;
			 
			$this->asp 					= new AlphaSelectPerformer($_GET['target']);
			$this->asp->linkMaker 	= &$this->lm;
			$this->asp->db 			= &$db;
			$this->asp->js 			= "_as";
			$this->asp->classid 		= $_GET['cid'];
			
			
/*			if($this->hasParam('aid'))
			{
				if($this->hasParam('cid'))
				{
					$templ = langstr('html:description:pagesong:aid-cid');
				}
				else
				{
					$templ = langstr('html:description:pagesong:aid');
				}
			}
			else
			{
				$templ = langstr('html:description:pagesong:aid');
			}
			$g_html_meta_description = eval("return \"$templ\";");;
			if($this->perpertop)
			{
				if($_GET['slsttyp'] == SQS_PER_YEAR_TOP)
				{
					$templ = langstr('html:description:pagesong:add_per_year_top');
				}
				else if($_GET['slsttyp'] == SQS_PER_MONTH_TOP)
				{
					$templ = langstr('html:description:pagesong:add_per_month_top');
				}
				else if($_GET['slsttyp'] == SQS_PER_WEEK_TOP)
				{
					$templ = langstr('html:description:pagesong:add_per_week_top');
				}
				$g_html_meta_description .= eval("return \"$templ\";");;
		  	}*/
		}


		//////////////////////////////////////////////////////////////////////////
		//
		//  initializePerPerTop
		//
		//////////////////////////////////////////////////////////////////////////
		function initializePerPerTop(&$params)
		{
			global $musicdb;
			global $langstr;
			
			if($_GET['slsttyp'] == SQS_PER_YEAR_TOP
				|| $_GET['slsttyp'] == SQS_PER_MONTH_TOP
			  	|| $_GET['slsttyp'] == SQS_PER_WEEK_TOP)
		  	{
				$this->perpertop = TRUE;
		  	}
		  	else
		  	{
				$this->perpertop = FALSE;
		  	}
  
			if($this->perpertop)
			{
				if(isset($_GET['year']))
				{
					$this->ppt_year = $_GET['year'];
					if(isset($_GET['month']))
					{
						$this->ppt_month = $_GET['month'];
						if(isset($_GET['week']))
						{
							$this->ppt_week = $_GET['week'];
						}
						else
						{
							if($this->ppt_month == 1)
							{
								$this->ppt_week = 1;
							}
							else
							{
								$this->ppt_week = strftime("%V", mktime(0, 0, 0, $this->ppt_month, 1, $this->ppt_year));
							}
						}
					}
					else
					{
						$this->ppt_month = 1;
						if(isset($_GET['week']))
						{
							$this->ppt_week = $_GET['week'];
						}
						else
						{
							$this->ppt_week = strftime("%V", strtotime("last monday", mktime(0, 0, 0, 1, 2, $this->ppt_year)));
						}
					}
				}
				else
			{
				$this->ppt_year = strftime("%Y");
				if(isset($_GET['month']))
				{
					$this->ppt_month = $_GET['month'];
					if(isset($_GET['week']))
					{
						$this->ppt_week = $_GET['week'];
					}
					else
					{
						$this->ppt_week = strftime("%V", strtotime("last monday, + {$this->ppt_month} month", mktime(0, 0, 0, 1, 2, $this->ppt_year)));
					}
				}
				else
				{
					$this->ppt_month = strftime("%m");
					if(isset($_GET['week']))
					{
						$this->ppt_week = $_GET['week'];
					}
					else
					{
						$this->ppt_week = strftime("%V");
					}
				}
			}
			$ts_newyearsday = mktime(0, 0, 0, 1, 2, $this->ppt_year);
			dprint("ts_newyearsday=$ts_newyearsday");
			$ts_firstmonday = strtotime("last monday", $ts_newyearsday);
			dprint("ts_firstmonday=$ts_firstmonday");
			dprint("ppt_week=$ppt_week");
			$montha = $musicdb->db_read->perpertop_getMonths($this->ppt_year);
	//																			print_r($weeka);
			if(!in_array($this->ppt_month, $montha))
			{
				if($this->ppt_month >= 7)
				{
					dprint("$this->ppt_month >= 7");
					$this->ppt_month = $montha[0];
					foreach($montha as $month)
					{
						if($month >= 7)
						{
							$this->ppt_month = $month;
							break;
						}
					}
				}
				else
				{
					$this->ppt_month = $montha[0];
				}
			}
			
			switch($_GET['slsttyp'])
			{
				case SQS_PER_WEEK_TOP:
				{
					$this->navWeek = array();
					
					dprint("year=$ppt_year");
					dprint("month=$ppt_month");
					$weeka = $musicdb->db_read->perpertop_getWeeks($this->ppt_year, $this->ppt_month);
	//																			print_r($weeka);
					$navcount = count($weeka);
					if(!in_array($this->ppt_week, $weeka))
					{
						$this->ppt_week = $weeka[0];
					}
					
	
					for($inav = 0; $inav < $navcount; $inav++)
					{
						$week = $weeka[$inav];
						dprint("week=$week");
						$link = "/songs?slsttyp={$_GET['slsttyp']}&year={$this->ppt_year}&month={$this->ppt_month}&week={$week}";
						$ts_monday = strtotime("+ $week weeks", $ts_firstmonday);
						$ts_sunday = strtotime("this sunday", $ts_monday);
						if($ts_sunday > time())
						{
							$ts_sunday = time();
						}
						$monday = strftime("%d/%m", $ts_monday); 
						$sunday = strftime("%d/%m", $ts_sunday); 
						$title = "$monday - $sunday";
						
						$navitem = new NavItem();
						$navitem->bCurrent = $week == $this->ppt_week;
						$navitem->bEnable = true;
						$navitem->link = $link;
						$navitem->title = $title;
						$this->navWeek[] = $navitem;
						if($navitem->bCurrent)
						{
							$this->curNav = $navitem;
						}
					}
					
	
				}
				case SQS_PER_MONTH_TOP:
				{
					$semestre1 = false;
					$semestre2 = false;
	
					$this->navMonth = array();
					
					dprint("PER_MONTH year={$this->ppt_year}<br>");
					dprint("PER_MONTH month={$this->ppt_month}<br>");
	//																			print_r($weeka);
					$navcount = count($montha);
					
	
					for($inav = 0; $inav < $navcount; $inav++)
					{
						$month = $montha[$inav];
						if($month <= 6)
						{
							$semestre1 = true;
						}
						else
						{
							$semestre2 = true;
						}
						if($this->ppt_month <= 6)
						{
							if($month > 6)
							{
								continue;
							}
						}
						else
						{
							if($month <= 6)
							{
								continue;
							}
						}
						dprint("month=$month");
						$link = "/songs?slsttyp={$_GET['slsttyp']}&year={$this->ppt_year}&month={$month}";
						$title = langstr("Month:$month");
						
						$navitem = new NavItem();
						$navitem->bCurrent = $month == $this->ppt_month;
						$navitem->bEnable = true;
						$navitem->link = $link;
						$navitem->title = $title;
						$this->navMonth[] = $navitem;
					}
					
					$this->navSemestre = array();
					if($semestre1)
					{
						$navitem = new NavItem();
						$link = "/songs?slsttyp={$_GET['slsttyp']}&year={$this->ppt_year}&month=1";
						$navitem->bCurrent = $this->ppt_month <= 6;
						$navitem->bEnable = true;
						$navitem->link = $link;
						$navitem->title = langstr('TopSongs:Semester:1');
						$this->navSemestre[] = $navitem;
					}
					if($semestre2)
					{
						$navitem = new NavItem();
						$link = "/songs?slsttyp={$_GET['slsttyp']}&year={$this->ppt_year}&month=7";
						$navitem->bCurrent = $this->ppt_month >= 7;
						$navitem->bEnable = true;
						$navitem->link = $link;
						$navitem->title = langstr('TopSongs:Semester:2');
						$this->navSemestre[] = $navitem;
					}
	
				}
				case SQS_PER_YEAR_TOP:
				{
					$this->navYear = array();
					
					dprint("year=$ppt_year");
					dprint("month=$ppt_month");
					$yeara = $musicdb->db_read->perpertop_getYears();
	//																			print_r($weeka);
					$navcount = count($yeara);
	
					for($inav = 0; $inav < $navcount; $inav++)
					{
						$year = $yeara[$inav];
						dprint("year=$year");
						$link = "/songs?slsttyp={$_GET['slsttyp']}&year={$year}";
						$title = $year;
						
						$navitem = new NavItem();
						$navitem->bCurrent = $year == $this->ppt_year;
						$navitem->bEnable = true;
						$navitem->link = $link;
						$navitem->title = $title;
						$this->navYear[] = $navitem;
					}
				}
			}
		}
		$params['year'] 	= $this->ppt_year;
		$params['month'] 	= $this->ppt_month;
		$params['week'] 	= $this->ppt_week;
		
	
	}
	
	//////////////////////////////////////////////////////////////////////////
	//
	//  printHead
	//
	//////////////////////////////////////////////////////////////////////////
	
	function printHead()
	{
//		veriwell_printcssinclude();
	//	$this->list->printCssInclude();
		//$this->list->print_jsInclude();	
	
	}
	//////////////////////////////////////////////////////////////////////////
	//
	//  printBody
	//
	//////////////////////////////////////////////////////////////////////////
	
	function printBody()
	{
		global $music;
		if($this->perpertop)
		{
			print "<div style=\"display:block; height:0.2em;\"></div>";
			if(isset($this->navYear))
			{
				karaoke_printOutTabNav70($this->navYear);
				print "<div style=\"display:block; height:0.2em;\"></div>";
			}
			if(isset($this->navMonth))
			{
				karaoke_printOutTabNav70($this->navSemestre);
				print "<div style=\"display:block; height:0.2em;\"></div>";
				karaoke_printOutTabNav70($this->navMonth);
				print "<div style=\"display:block; height:0.2em;\"></div>";
			}
			if(isset($this->navWeek))
			{
				karaoke_printOutTabNav70($this->navWeek);
				print "<div style=\"display:block; height:0.2em;\"></div>";
			}
		}
		else
		{
			?>
            <div class="karaoke_asp_box">
	           <span class="karaoke_asp"><?php print langstr("karaoke_asp"); ?>&nbsp;</span>
			<?php
			if(!is_null($this->asp))
				$this->asp->out(3);
			?> </div> 
			<?php
		}

		if(strlen($this->list->cid) > 0)
		{
			$music->printListClassInclude($this->list->cid);
		}

		if(strlen($this->list->aid) > 0)
		{
			$music->printListArtistInclude($this->list->aid);
		}

		$this->list->printSListPreamble();
		$this->list->printList();
		$this->list->printSListClosure();
	}
	
	
	
}
