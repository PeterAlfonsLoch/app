#include "stdafx.h"

namespace webserver
{

   namespace music
   {

#define TIMEOUT_DEFER_USER_UPDATE_VERIFICATION_CODE_CHECK "+10 minute"
	database_cache::database_cache()
	{
	}


	// $onlycheck - it does only check, but does not update the last user update time
	bool database_cache::can_bypass_user_update_verification_code_check(var userid)
	{
//		DWORD time = ::GetTickCount();
/*		string lastupdate = musicdb().get_prop_bigint("last_user_update_verification_code_check(var userid)");
		string strtimeout = TIMEOUT_DEFER_USER_UPDATE_VERIFICATION_CODE_CHECK;
		$timeout = strtotime($strtimeout, $lastupdate);
		dprint("Timeout:".$strtimeout);
		if(!$lastupdate || $time > $timeout)
		{
			return false;
		}*/
		return true;

	}

	// $onlycheck - it does only check, but does not update the last user update time
void database_cache::set_bypass_user_update_verification_code_check(var userid)
	{
/*		DWORD time = ::GetTickCount();
		$lastupdate = db_read->get_prop_bigint("last_user_update_verification_code_check(var userid)");
		$strtimeout = TIMEOUT_DEFER_USER_UPDATE_VERIFICATION_CODE_CHECK;
		$timeout = strtotime($strtimeout, $lastupdate);
		dprint("Timeout:".$strtimeout);
		if(!$lastupdate || $time > $timeout)
		{
			db_read->set_prop_bigint("last_user_update_verification_code_check(var userid)", $time);
		}*/
	}

	void database_cache::defer_updatecycle1()
	{
/*		DWORD time = ::GetTickCount();
		$lastupdate = db_read->get_prop_bigint("last_tmp_song_click_update");
//		$strtimeout = "+1 minute";
		$strtimeout = TIMEOUT_STRTOTIME_REGISTER_SONG_CLICK_FULL_UPDATE;
		$timeout = strtotime($strtimeout, $lastupdate);
		dprint("Timeout:".$strtimeout);
		if(!$lastupdate || $time > $timeout || isset($_GET['forceupdate']))
		{
			db_read->set_prop_bigint("last_tmp_song_click_update", $time);
			karaoke_update_tmp_song_clickdistinct1(isset($_GET['debug']));
			update_tmp_topic_click(isset($_GET['debug']));
		}*/
	}


	void database_cache::create_proc()
	{
/*		strSql = "DROP PROCEDURE update_tmp_song_lang_style_rank";
		strSql =  <<<SQL
CREATE PROCEDURE update_tmp_song_lang_style_rank()
	BEGIN
	DECLARE done INT DEFAULT 0;
	DECLARE old_langid INT;
	DECLARE old_styleid INT;
	DECLARE old_type INT;
	DECLARE old_click INT;
	DECLARE l_rank INT;
	DECLARE cur1 CURSOR FOR SELECT topicid, langid, styleid, type, click FROM tmp_topic_lang_style_click ORDER BY langid, styleid, type, click DESC, topicid DESC;
	DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done = 1;
	OPEN cur1;
	loop1: LOOP
		FETCH cur1 INTO l_topicid, l_langid, l_styleid, l_type, l_click;
		IF NOT done THEN
			LEAVE loop1;
		END IF;
		IF old_langid <> l_langid OR old_styleid <> l_styleid OR old_type <> l_type THEN
			SET l_rank 	= 1;
			SET old_click 	= -1;
		END IF;
		IF old_click > click THEN SET
			l_rank = l_rank + 1;
		END IF;
		UPDATE tmp_topic_lang_style_click SET rank = l_rank WHERE topicid = l_topicid AND langid = l_langid AND styleid = l_styleid AND type = l_type LIMIT 1;
		SET old_langid 		= langid;
		SET old_styleid 	= styleid;
		SET old_type 		= type;
		SET old_click 		= click;
	END LOOP loop1;
	CLOSE cur1;
END;
//

SQL;
	musicdb().query(strSql);*/
	}

	var database_cache::get_useragent_id_ex(var useragent)
	{
		useragent = musicdb().real_escape_string(useragent);
		var item = musicdb().query_item("SELECT id FROM useragent WHERE useragent.useragent = 'var useragent'");
		if(item.is_empty())
		{
			musicdb().query("INSERT INTO useragent(`useragent`) VALUES ('var useragent')");
			return musicdb().get_insert_id();
		}
		else
		{
			return item;
		}
	}


	var database_cache::getClassIdArray2()
	{
		//return db_read->getRowArray('tmp_class_2', 'classid');
//      return var;
      return gen::g_emptyconst;
	}


	void database_cache::pulse_access_stats_1()
	{
		/*var ip = inattr("REMOTE_ADDR");
		hostname = gprop("g_hostname");
		string sql_select = "SELECT EXISTS(SELECT * FROM access_stats_1 WHERE `ip` = 'ip' AND `hostname` = 'hostname')";
		mysql::result * presult = musicdb().query(sql_select);
		$already_exists = false;
		if(presult)
		{
			$row = fonto_fetch_row(presult);
			if($row)
			{
				dprint("exists = ".$row[0]);
				$already_exists = $row[0] > 0;
			}
		}
		$now = datetime_getGMTDateTime();
		if($already_exists)
		{
			$sql_update = "UPDATE access_stats_1 SET `lastvisit` = '$now', `hitcount` = (`hitcount` + 1) WHERE `ip` = 'ip' AND `hostname` = 'hostname'";
			$result_update = musicdb().query($sql_update);
		}
		else
		{
			$sql_insert = "INSERT INTO access_stats_1 (`ip`, `hostname`, `firstvisit`, `lastgethost`, `lastvisit`, `hitcount`) VALUES ('ip', 'hostname', '$now', '$now', '$now', '0')";
			$result_insert = musicdb().query($sql_insert);
		}
			*/
	}

	void database_cache::registerSongClick(var topicid, var address, var http_referer, var lang , var style , var referer ,var type)
	{

		/*bool bVerbose = isset($_GET['debug']);
		$isrobot = 0;
		hostname =	gprop("g_hostname'];
				DWORD time0 = ::GetTickCount();
		time1 = time0;

		////////////////////////////////////////////////////////////////////////////
		//
		// 	song_click_partial update
		//
		//    song_click has data from the minimal detail interval in topic_click_compiled
		//		currnetly one hour
		// 	for security margin, three hours are taken.

		if(net_hostname_is_spider(hostname, inattr("HTTP_USER_AGENT']))
		{
			$isrobot = 1;
		}
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>net_hostname_is_spider</h3>");
			print("<br>");
			print("delta: "+delta+"<br>");

		}
/*		if(inattr("HTTP_HOST'] === "kar2.veriwell.net")
		{
			$flag1 |= 1;
		}*/
//		print("flag1=$flag1";

		/*var useragent = get_useragent_id_ex(inattr("HTTP_USER_AGENT']);

		langid = db_read->forceGetLangId($lang);
		styleid = db_read->forceGetStyleId($style);
		$now = datetime_getGMTDateTime();
		strSql = "INSERT INTO `topic_click` (`topic`, `type`, `datetime`, `address`, `hostname`, `http_referer`, `lang`, `style`, `langid`, `styleid`, `referer`, `isrobot`, `useragent`) VALUES ('topicid', '$type', '$now', '$address', 'hostname', '$http_referer', '$lang', '$style', 'langid', 'styleid', '$referer', '$isrobot', 'var useragent');";
		//	echo strSql;
		presult =musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>insert into topic click</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}
		$song_click_id = musicdb().get_insert_id;

		strSql = "INSERT INTO `tmp_topic_last_access` (`topic`,`type`, `datetime`, `address`, `hostname`, `http_referer`, `lang`, `style`, `langid`, `styleid`, `referer`, `isrobot`) VALUES ('topicid', '$type', '$now', '$address', 'hostname', '$http_referer', '$lang', '$style', 'langid', 'styleid', '$referer', '$isrobot');";
		presult =musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>tmp_topic_last_access</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}

		$dry_datetime = datetime_strtotime("90 day ago", timestamp_getToday());
		strSql = "DELETE FROM tmp_topic_last_access WHERE tmp_song_last_access.datetime < '$dry_datetime'";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>clean tmp_topic_last_access</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}

//		DWORD time = ::GetTickCount();
//		$lastupdate = db_read->get_prop_bigint("last_tmp_song_click_update");
//		$timeout = strtotime(TIMEOUT_STRTOTIME_REGISTER_SONG_CLICK_FULL_UPDATE, $lastupdate);
//		if(!$lastupdate || $time > $timeout)
//		{
//			db_read->set_prop_bigint("last_tmp_song_click_update", $time);
//			karaoke_update_tmp_song_clickdistinct1(isset($_GET['debug']));
//		}
//		else
	//	{
//			if(($flag1 & 1) == 0)
	//		{
		//		update_tmp_song_clickdistinct1_item($song_click_id, $songid, langid, styleid, isset($_GET['debug']));
			//}
		//}
//		if(!$isrobot)
	//	{
		//	update_tmp_song_clickdistinct1_item($song_click_id, topicid, langid, styleid, isset($_GET['debug']));
//		}
	*/
	}


/*	var database_cache::getstring($id)
	{
		return musicdb().get_string($id);
	}

	var database_cache::getlangstring($id, $languageid)
	{
		return db_read->getlangstring($id, $languageid);
	}
   */
	void database_cache::tmp_song_insert(bool bVerbose)
	{


		DWORD time1 = ::GetTickCount();
		if(bVerbose)
		{
			print ("<h3>tmp_song insert</h3>");
		}
		string strSql = "INSERT IGNORE INTO tmp_song (song) SELECT song.id FROM song";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}
	}

	void database_cache::tmp_song_update_classida(bool bVerbose)
	{


		DWORD time1 = ::GetTickCount();
		if(bVerbose)
		{
			print ("<h3>tmp_song_update_classida</h3>");
		}
		string strSql = "UPDATE tmp_song SET classida = (SELECT CAST(GROUP_CONCAT(DISTINCT CONCAT('<',topic_class.class,'>') ORDER BY topic_class.class SEPARATOR '') AS CHAR) FROM topic_class INNER JOIN topic_song ON topic_song.topic = topic_class.topic AND topic_song.topictype = topic_class.topictype WHERE topic_song.song = tmp_song.song GROUP BY tmp_song.song)";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}
	}

	void database_cache::tmp_song_update_performerida(bool bVerbose)
	{

		DWORD time1 = ::GetTickCount();
		if(bVerbose)
		{
			print( "<h3>tmp_song_update_personida</h3>");
		}
		string strSql = "UPDATE tmp_song SET performerida = (SELECT CAST(GROUP_CONCAT(DISTINCT CONCAT('<',topic_person.person,'>') ORDER BY topic_person.person SEPARATOR '') AS CHAR) FROM topic_person INNER JOIN topic_song ON topic_person.topic = topic_song.topic AND topic_person.topictype = topic_song.topictype WHERE topic_person.role = 2 AND topic_song.song = tmp_song.song GROUP BY tmp_song.song)";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}
	}

	var database_cache::gethostbyaddr_ex(var ip)
	{
      /*
		if(access_stats_1_gethostbyaddr(ip, hostname, $lastvisit, $lastgethost))
		{
			$now 					= datetime_getGMTDateTime();
			$now_ts 				= strtotime($now);
			$lastgethost_ts	= strtotime($lastgethost);
			$timeout_ts   		= strtotime('+15 minutes', $lastgethost_ts);
//			print("reverse found last gethost: ".datetime_formatDateTime($lastgethost_ts)."<br>");
			if($now_ts > $timeout_ts)
			{
				hostname = access_stats_1_updatehost(ip);
			}
		}
		else
		{
			hostname = access_stats_1_updatehost(ip);
		}

		return hostname;*/
      return ip;

	}

	bool database_cache::access_stats_1_gethostbyaddr(var ip, string &hostname, string &lastvisit, string &lastgethost)
	{
//      UNREFERENCED_PARAMETER(ip);
      UNREFERENCED_PARAMETER(hostname);
      UNREFERENCED_PARAMETER(lastvisit);
      UNREFERENCED_PARAMETER(lastgethost);
		/*string sql_select = "SELECT `hostname`, `lastvisit`, `lastgethost` FROM access_stats_1 WHERE `ip` = 'ip' ORDER BY `lastvisit` DESC LIMIT 0, 1";
		mysql::result * presult = musicdb().query(sql_select);
		if(presult)
		{
			$row = fonto_fetch_row(presult);
			if($row)
			{
				hostname 		= $row[0];
				$lastvisit 		= $row[1];
				$lastgethost	= $row[2];
/*				print("access_stats_1_gethostbyaddr<br>");
				print("found host: hostname<br>");
				print("found last visit: $lastvisit<br>");
				print("found last gethost: $lastgethost<br>");*/
				/*return true;
			}
		}
		return false;*/
      return false;
	}

	var database_cache::access_stats_1_updatehost(var ip)
	{
		// ATTENTION: gethostbyaddr can take a long time to perform a host name lookup.
		// access_stats_1 make a cache of the hostname
		/*hostname = gethostbyaddr(ip);

		string sql_select = "SELECT COUNT(*) FROM access_stats_1 WHERE `ip` = 'ip' AND `hostname` = 'hostname'";
		mysql::result * presult = musicdb().query(sql_select);
		$already_exists = false;
		if($result)
		{
			$row = fonto_fetch_row($result);
			if($row)
			{
				$already_exists = $row[0] > 0;
			}
		}
		$now = datetime_getGMTDateTime();
		if($already_exists)
		{
			$sql_update = "UPDATE access_stats_1 SET `lastgethost` = '$now', `lastvisit` = '$now'";
			$result_update = musicdb().query($sql_update);
		}
		else
		{
			$sql_insert = "INSERT INTO access_stats_1 (`ip`, `hostname`, `firstvisit`, `lastgethost`, `lastvisit`, `hitcount`) VALUES ('ip', 'hostname', '$now', '$now', '$now', '0')";
			$result_insert = musicdb().query($sql_insert);
		}
		return hostname;*/
      return ip;
	}

	void database_cache::update_tmp_song_clickdistinct1_item(var song_click_id, var topicid, var langid, var styleid, bool bVerbose)
	{
		karaoke_update_tmp_song_clickdistinct1_item(song_click_id, topicid, langid, styleid, bVerbose);
	}

	void database_cache::song_cache_initialize(bool bVerbose)
	{
      UNREFERENCED_PARAMETER(bVerbose);
      string strSql;

      strSql = "UPDATE topic_click, lang SET topic_click.langid = lang.id WHERE lang.lang = topic_click.lang";
		musicdb().query(strSql);

		strSql = "UPDATE topic_click, style SET topic_click.styleid = style.id WHERE style.style = topic_click.style";
		musicdb().query(strSql);

/*		strSql = "DELETE FROM tmp_topic_lang_style";
		musicdb().query(strSql);

		strSql = "INSERT INTO `tmp_topic_lang_style`(`langid`, `styleid`, `topicid`, `topictype`, `songid`) SELECT langstyle.langid, langstyle.styleid, topic_song.topictype, topic_song.id, topic_song.songid FROM langstyle, topic_song";
		musicdb().query(strSql);*/
	}



	var database_cache::update_song_click_stats(bool bVerbose, bool bPartial)
	{
      UNREFERENCED_PARAMETER(bPartial);
		karaoke_update_tmp_song_clickdistinct1(bVerbose);
      return gen::g_emptyconst;
	}












































	void database_cache::karaoke_update_tmp_song_clickdistinct1(bool bVerbose)
	{
		if(bVerbose)
		{
			print("<h2>karaoke_update_tmp_song_clickdistinct1</h2>");

		}

		DWORD time0 = ::GetTickCount();
		DWORD time1 = time0;

//		strSql = "DELETE FROM topic_click_1";
	//	musicdb().query(strSql);
		var now = musicdb().query_item("SELECT DATE_FORMAT(NOW(), '%Y-%m-%d %h:00:00')");
		dprint("SQL time = $now <br>");
		//xxxvar lastdatetime = db_read->get_prop_text("last_partial_update_tmp_song_clickdistinct1");
		//xxxvar time = datetime_formatDateTime(strtotime("-1 day", strtotime(lastdatetime)));
		dprint("time = $time<br>");

		//xxxdb_read->set_prop_text("last_partial_update_tmp_song_clickdistinct1", datetime_formatDateTime(strtotime($now)));


		string min_song_click = get_min_datetime_hour_round_song_click();
		string max_song_click = get_max_datetime_hour_round_song_click();
		string min_topic_click_compiled = get_min_datetime_topic_click_compiled();
		string max_topic_click_compiled = get_max_datetime_topic_click_compiled();

/*		if(bVerbose)
		{
			print("<br>");
			print("min_song_click: $min_song_click<br>");
			print("max_song_click: $max_song_click<br>");
			print("min_topic_click_compiled: $min_topic_click_compiled<br>");
			print("max_topic_click_compiled: $max_topic_click_compiled<br>");
			print("<br>");

		}*/


		// Se não existem registros de clique em música, não existe porque
		// atualizar informações sobre clique em música.
		if(min_song_click.is_empty())
			return;

		// Se existem registros de clique em música, a função prossegue.
		string strWhere;
      string delta_time1;
		if(min_topic_click_compiled.is_empty())
		{
			// Se não existem registros compilados de clique em música,
			// todos os registros de clique em música são usados para
			// gerar os dados compilados.
			strWhere = "";
		}
		else if(min_topic_click_compiled > min_song_click)
		{
			// Se o registro compilado mais antigo é uma compilação de dados
			// mais recente do que o registro original mais antigos, todos
			// os dados compilado precisam ser recompilados.
			strWhere = "";
		}
		else
		{
			// Em qualquer outro caso, ou seja, os registros compilados e os originais
			// mais antigos se equivalem, e os registros compilados são mais recentes
			// (perda dos originais) ou menos recentes que os originais (condição normal),
			// a atualização "delta" é feita a partir dos dados de um dia antes da última
			// atualização dos dados compilados. Não é usada a data exata da última atualização,
			// pois é necessário "conectar" os dados para o cálculo de arredondamento
			// usado na eliminação de contagem de cliques sucessivos do mesmo endereço
			// num espaço curto de tempo.
			delta_time1 = datetime_formatDateTime(strtotime("-2 day", strtotime(max_topic_click_compiled)));
			strWhere = " AND datetime >= '" + delta_time1 + "'";
		}

		string strSql = "TRUNCATE TABLE topic_click_compiled_delta";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: song_click_delta</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}

//		$delta_time2 = datetime_formatDateTime(strtotime("-2 month",time()));

		strSql = "INSERT INTO topic_click_compiled_delta SELECT topic, click_type_group.groupid, langid, styleid, CONCAT(SUBSTRING(datetime, 1, 13), ':00:00') as hour_round, COUNT(DISTINCT SUBSTRING(datetime, 1, 15), (SUBSTRING(datetime, 16, 1) > 5), `address`), SUBSTRING(`datetime`, 1, 4), SUBSTRING(`datetime`, 6, 2), SUBSTRING(`datetime`, 9, 2), SUBSTRING(`datetime`, 12, 2), WEEK(datetime, 7) FROM topic_click INNER JOIN click_type_group ON click_type_group.typeid = topic_click.`type` WHERE isrobot = 0 "+strWhere+" GROUP BY topic, click_type_group.groupid, langid, styleid, hour_round";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: song_click_delta</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}





	//	strSql = "INSERT INTO song_click_delta SELECT *, '0000-00-00 00:00:00', 0, 0, 0, 0, 0, 0, 0 FROM song_click";


		strSql = "REPLACE INTO topic_click_compiled(`topic`, `type`, `langid`, `styleid`, `datetime`, `click`, `year`,`month`,`day`,`hour`, `week` ) SELECT topic, `type`, langid, styleid, datetime, click, year, month, day, hour, week FROM topic_click_compiled_delta";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: topic_click_compiled</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}
		strSql = "LOCK TABLES tmp_topic_lang_style_click2 WRITE, tmp_topic_lang_style_click WRITE, topic_click_compiled WRITE, click_type_topic_type WRITE";
		mysql::result * presult =musicdb().query(strSql);

		///////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Cleaning
		//

		strSql = "TRUNCATE TABLE tmp_topic_lang_style_click2";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>tmp_topic_lang_style_click2 Cleaning</h3>");
			print(strSql);
			print("<br>");
			print("delta: " + delta);
			print("<br>");

		}


		///////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Cleaning
		//

		strSql = "TRUNCATE TABLE tmp_topic_lang_style_click";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>tmp_topic_lang_style_click Cleaning</h3>");
			print(strSql);
			print("<br>");
			print("delta: " + delta);
			print("<br>");

		}


		///////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Global
		//

		tmp_topic_lang_style_update_top("click", NULL, bVerbose);

		///////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 1 Year
		//

		string lastdatetime = datetime_formatDateTime((strtotime("1 year ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top("clickLastYear", lastdatetime, bVerbose);

		///////////////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 6 Month
		//
		lastdatetime = datetime_formatDateTime((strtotime("6 month ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top("clickLast6Month", lastdatetime, bVerbose);

		////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 3 Month
		//
		lastdatetime = datetime_formatDateTime((strtotime("3 month ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top("clickLast3Month", lastdatetime, bVerbose);

		///////////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 1 Month
		//

		lastdatetime = datetime_formatDateTime((strtotime("1 month ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top("clickLastMonth", lastdatetime, bVerbose);

		///////////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 7 days
		//
		lastdatetime = datetime_formatDateTime((strtotime("-7 day", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top("click7days", lastdatetime, bVerbose);


		///////////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 24 Hours
		//
		lastdatetime = datetime_formatDateTime((strtotime("-24 hour", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top("click24hours", lastdatetime, bVerbose);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("karaoke_update_tmp_song_clickdistinct1<br>");
			print("delta: "+delta+"<br>");

		}

		strSql = "UNLOCK TABLES";
		presult =musicdb().query(strSql);


		update_tmp_song_lang_style_rank(bVerbose);


		////////////////////////////////////////////////////////////////////////////
		//
		// 	tmp_performer_lang_style update
		//

		strSql = "REPLACE INTO tmp_person_lang_style(`langid`, `styleid`, `person`) SELECT langstyle.langid, langstyle.styleid, person.id FROM langstyle, person";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("karaoke_update_tmp_song_clickdistinct1<br>");
			print("delta: "+delta+"<br>");

		}

		///////////////////////////////////////////////////////////////////
		// tmp_person_lang_style_click Cleaning
		//

		strSql = "DELETE FROM tmp_person_lang_style_click";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>tmp_person_lang_style_click Cleaning</h3>");
			print(strSql);
			print("<br>");
			print("delta: " +delta);
			print("<br>");

		}


		// tmp_performer_lang_style Global
		strSql = "INSERT INTO tmp_person_lang_style_click SELECT topic_person.person, sclick.topictype, sclick.langid, sclick.styleid, sclick.`type`, SUM(sclick.click), 0, 0 FROM topic_person INNER JOIN tmp_topic_lang_style_click as sclick ON sclick.topic = topic_person.topic AND sclick.topictype = topic_person.topictype GROUP BY topic_person.person, topic_person.topictype, sclick.langid, sclick.styleid, sclick.`type`";
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>tmp_person_lang_style_click Insertion</h3>");
			print(strSql);
			print("<br>");
			print("delta: " +delta);
			print("<br>");

		}
		presult =musicdb().query(strSql);

		strSql = "DROP TABLE temp1";
		musicdb().query(strSql);

		// tmp_song_click_year
		int min_year = musicdb().query_item("SELECT MAX(year) FROM tmp_topic_click_year");
      var year;
		if(min_year <= 0)
		{
			strWhere = "";
		}
		else
		{
			year = min_year - 1;
			strWhere = "WHERE topic_click_compiled.year >= '" + gen::str::itoa(min_year) + "'";
		}


		strSql = "REPLACE INTO tmp_topic_click_year SELECT topic_click_compiled.topic, topic_click_compiled.`type`, topic_click_compiled.langid, topic_click_compiled.styleid, topic_click_compiled.year, SUM(topic_click_compiled.click) as songclick FROM topic_click_compiled "+strWhere+" GROUP BY topic_click_compiled.topic,  topic_click_compiled.`type`, topic_click_compiled.langid, topic_click_compiled.styleid, topic_click_compiled.year ";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: tmp_song_click_year</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");
		}


		string sct = "topic_click_compiled";
		// tmp_topic_click_month


		var row = musicdb().query_row("SELECT year, month FROM tmp_topic_click_month ORDER BY year DESC, month DESC LIMIT 1");
      min_year = row.at(0);
      int min_month = row.at(1);
		if(min_year <= 0)
		{
			strWhere = "";
		}
		else
		{
			min_month = min_month - 1;
			if(min_month <= 0)
			{
				min_month = 12;
				min_year--;
			}
			strWhere = "WHERE topic_click_compiled.year > '"+gen::str::itoa(min_year)+"' OR (topic_click_compiled.year = '"+gen::str::itoa(min_year)+"' AND topic_click_compiled.month >= '"+gen::str::itoa(min_month)+"')";
		}

		strSql = "REPLACE INTO tmp_topic_click_month SELECT topic, `type`, langid, styleid, year, month, SUM(click) as songclick FROM  "+sct+"   "+strWhere+"  GROUP BY topic, `type`, langid, styleid, year, month";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: tmp_topic_click_month</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");
		}
		sct = "topic_click_compiled";
		// tmp_topic_click_week
		row = musicdb().query_row("SELECT year, week FROM tmp_topic_click_week ORDER BY year DESC, month DESC, week DESC LIMIT 1");
      min_year = row.at(0);
      int min_week = row.at(1);

		if(min_year <= 0)
		{
			strWhere = "";
		}
		else
		{
			min_week = min_week- 1;
			if(min_week <= 0)
			{
				min_week = 50;
				min_year--;
			}
			strWhere = "WHERE topic_click_compiled.year >= '"+gen::str::itoa(min_year)+"' OR (topic_click_compiled.year = '"+gen::str::itoa(min_year)+"' AND topic_click_compiled.week >= '"+gen::str::itoa(min_week)+"')";
		}


		strSql = "REPLACE INTO tmp_topic_click_week SELECT topic, `type`, langid, styleid, year, month, week, SUM(click) as songclick FROM "+sct+"  "+strWhere+"  GROUP BY topic, `type`, langid, styleid, year, week";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: tmp_topic_click_week</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");
		}
	}


	void database_cache::karaoke_update_tmp_song_clickdistinct1_item(var song_click_id, var topicid, var langid, var styleid, bool bVerbose)
	{

		DWORD time0 = ::GetTickCount();
		DWORD time1 = time0;

		////////////////////////////////////////////////////////////////////////////
		//
		// 	song_click_partial update
		//
		//    song_click has data from the minimal detail interval in topic_click_compiled
		//		currnetly one hour
		// 	for security margin, three hours are taken.

		string delta_time1 = datetime_formatDateTime(strtotime("-1 day", time::get_current_time().get_time()));
		string strWhere = " AND topic = 'topicid' AND datetime >= '" +delta_time1 + "'";

		string strSql = "REPLACE INTO topic_click_compiled_delta SELECT topic, click_type_group.groupid, langid, styleid, CONCAT(SUBSTRING(datetime, 1, 13), ':00:00') as hour_round, COUNT(DISTINCT SUBSTRING(datetime, 1, 15), (SUBSTRING(datetime, 16, 1) > 5), `address`), SUBSTRING(`datetime`, 1, 4), SUBSTRING(`datetime`, 6, 2), SUBSTRING(`datetime`, 9, 2), SUBSTRING(`datetime`, 12, 2), WEEK(datetime, 7) FROM topic_click  INNER JOIN click_type_group ON click_type_group.typeid = topic_click.`type` WHERE isrobot = 0 strWhere GROUP BY topic, click_type_group.groupid, langid, styleid, hour_round";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>song clickdistinct1 item: topic_click_compiled_delta</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}


		strSql = "REPLACE INTO topic_click_compiled(`topic`, `type`, `langid`, `styleid`, `datetime`, `click`, `year`,`month`,`day`,`hour`, `week` ) SELECT topic, `type`, langid, styleid, datetime, click, year, month, day, hour, week FROM topic_click_compiled_delta";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>song clickdistinct1 item: topic_click_compiled</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}


		strSql = "LOCK TABLES tmp_topic_lang_style_click WRITE, topic_click_compiled WRITE, click_type_topic_type WRITE";
		mysql::result * presult =musicdb().query(strSql);

		///////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 1 Year
		//

		string lastdatetime = datetime_formatDateTime((strtotime("1 year ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top_item(topicid, langid, styleid, "clickLastYear", lastdatetime, bVerbose);

		///////////////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 6 Month
		//
		lastdatetime = datetime_formatDateTime((strtotime("6 month ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top_item(topicid, langid, styleid, "clickLast6Month", lastdatetime, bVerbose);

		////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 3 Month
		//
		lastdatetime = datetime_formatDateTime((strtotime("3 month ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top_item(topicid, langid, styleid, "clickLast3Month", lastdatetime, bVerbose);

		///////////////////////////////////////////////////////////////////////
		// tmp_song_lang_style Last 1 Month
		//

		lastdatetime = datetime_formatDateTime((strtotime("1 month ago", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top_item(topicid, langid, styleid, "clickLastMonth", lastdatetime, bVerbose);

		// tmp_song_lang_style Last 7 days
		lastdatetime = datetime_formatDateTime((strtotime("-7 day", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top_item(topicid, langid, styleid, "click7days", lastdatetime, bVerbose);

		// tmp_song_lang_style Last 24 Hours
		lastdatetime = datetime_formatDateTime((strtotime("-24 hour", datetime_getTimestamp().get_time()) / 3600) * 3600);
		tmp_topic_lang_style_update_top_item(topicid, langid, styleid, "click24hours", lastdatetime, bVerbose);

		strSql = "UNLOCK TABLES";
		presult =musicdb().query(strSql);

		////////////////////////////////////////////////////////////////////////////
		//
		// 	tmp_performer_lang_style update
		//

/*		strSql = "REPLACE INTO tmp_performer_lang_style(`langid`, `styleid`, `performerid`) SELECT langstyle.langid, langstyle.styleid, performer.id FROM langstyle, performer";
		musicdb().query(strSql);


		// tmp_performer_lang_style Global
		strSql = "CREATE TEMPORARY TABLE `temp1` SELECT tmp_performer_lang_style.langid, tmp_performer_lang_style.styleid, tmp_performer_lang_style.performerid, SUM(tmp_song_lang_style.click) as songclick FROM tmp_performer_lang_style INNER JOIN tmp_song_lang_style ON tmp_performer_lang_style.langid = tmp_song_lang_style.langid AND tmp_performer_lang_style.styleid = tmp_song_lang_style.styleid INNER JOIN song_performer ON song_performer.performerid = tmp_performer_lang_style.performerid INNER JOIN song_file ON song_performer.songid = song_file.songid AND song_file.id = tmp_song_lang_style.topicid GROUP BY tmp_performer_lang_style.performerid, tmp_song_lang_style.langid, tmp_song_lang_style.styleid";
		if(bVerbose)
		{
			print("<h3>tmp_performer_lang_style Global</h3>");
			print strSql."<br>");
			print("<br>");
		}
		presult =musicdb().query(strSql);*/

/*		strSql = "UPDATE tmp_performer_lang_style, temp1 SET tmp_performer_lang_style.click = temp1.songclick WHERE tmp_performer_lang_style.performerid = temp1.performerid AND tmp_performer_lang_style.langid = temp1.langid AND tmp_performer_lang_style.styleid = temp1.styleid";
		musicdb().query(strSql);

		strSql = "DROP TABLE temp1";
		musicdb().query(strSql);*/


		// tmp_song_click_year
		int min_year = musicdb().query_item("SELECT MIN(year) FROM tmp_song_click_year");;
      int year = 0;
		if(min_year <= 0)
		{
			strWhere = "WHERE topic = 'topicid'";
		}
		else
		{
			year = min_year - 1;
			strWhere = "WHERE topic = 'topicid' AND topic_click_compiled.year >= '$min_year'";
		}


		strSql = "REPLACE INTO tmp_song_click_year SELECT topic_click_compiled.topic, topic_click_compiled.langid, topic_click_compiled.styleid, topic_click_compiled.year, SUM(topic_click_compiled.click) as songclick FROM topic_click_compiled strWhere GROUP BY topic_click_compiled.topic, topic_click_compiled.langid, topic_click_compiled.styleid, topic_click_compiled.year ";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: tmp_song_click_year</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");
		}


		string sct = "topic_click_compiled";
		// tmp_topic_click_month


		var row = musicdb().query_row("SELECT year, month FROM tmp_topic_click_month ORDER BY year, month LIMIT 1");
      min_year = row.at(0);
      int min_month = row.at(1);
		if(min_year <= 0)
		{
			strWhere = "WHERE topic = 'topicid'";
		}
		else
		{
			min_month = min_month - 1;
			if(min_month <= 0)
			{
				min_month = 12;
				min_year--;
			}
			strWhere = "WHERE topic = 'topicid' AND topic_click_compiled.year >= '$min_year' AND topic_click_compiled.month >= '$min_month'";
		}

		strSql = "REPLACE INTO tmp_topic_click_month SELECT topic, langid, styleid, year, month, SUM(click) as songclick FROM $sct strWhere GROUP BY topic, langid, styleid, year, month";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: tmp_topic_click_month</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");
		}
		sct = "topic_click_compiled";
		// tmp_topic_click_week
		row = musicdb().query_row("SELECT year, week FROM tmp_topic_click_week ORDER BY year, month, week LIMIT 1");
      min_year = row.at(0);
      int min_week = row.at(1);
		if(min_year <= 0)
		{
			strWhere = "WHERE topic = 'topicid'";
		}
		else
		{
			min_week = min_week - 1;
			if(min_week == 0)
			{
				min_week = 50;
				min_year--;
			}
			strWhere = "WHERE topic = 'topicid' AND topic_click_compiled.year >= '$min_year' AND topic_click_compiled.week >= '$min_week'";
		}


		strSql = "REPLACE INTO tmp_topic_click_week SELECT topic, langid, styleid, year, month, week, SUM(click) as songclick FROM $sct strWhere GROUP BY topic, langid, styleid, year, week";
		musicdb().query(strSql);

		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<h3>karaoke_update_tmp_song_clickdistinct1: tmp_topic_click_week</h3>");
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");
		}

}

void database_cache::tmp_performer_update(bool bVerbose)
{
	string strSql = "DELETE FROM work_temp_int_int";
	musicdb().query(strSql);

	strSql = "INSERT IGNORE INTO tmp_person(`person`, `topictype`, `role`) SELECT DISTINCT `person`, `topictype`, `role` FROM topic_person";
	musicdb().query(strSql);

//	// tmp_performer Global
	//strSql = "INSERT INTO work_temp_int_int SELECT song_performer.performerid, COUNT(song_performer.songid) as songcount FROM song_performer GROUP BY song_performer.performerid";
//	presult =musicdb().query(strSql);

	strSql = "UPDATE tmp_person SET tmp_person.songcount = (SELECT COUNT(DISTINCT topic_song.song) FROM topic_song INNER JOIN topic_person ON topic_person.topic = topic_song.topic AND topic_person.topictype = topic_song.topictype WHERE topic_person.person = tmp_person.person)";
	if(bVerbose)
	{
		print("<br>");
		print("<h3>tmp_person.songcount</h3>");
		print(strSql);
		print("<br>");
	}
	musicdb().query(strSql);

//	strSql = "DELETE FROM work_temp_int_int";
	//musicdb().query(strSql);
	strSql = "DROP TABLE temp_table1";
	musicdb().query(strSql);


	strSql = "UPDATE tmp_person SET tmp_person.topiccount = (SELECT COUNT(DISTINCT topic_person.topic) FROM topic_person WHERE topic_person.person = tmp_person.person AND topic_person.topictype = tmp_person.topictype)";
	if(bVerbose)
	{
		print("<br>");
		print("<h3>tmp_person.songcount</h3>");
		print(strSql);
		print("<br>");
	}
	musicdb().query(strSql);

/*	strSql = "DROP TABLE temp_table1";
	musicdb().query(strSql);

	strSql = "DROP TABLE temp1";
	musicdb().query(strSql);

	// tmp_person.classida

	strSql = "DELETE FROM work_temp_pint_mtext";
	musicdb().query(strSql);

	strSql = "INSERT INTO work_temp_pint_mtext SELECT song_performer.performerid,  FROM ";
	presult =musicdb().query(strSql);
	if(bVerbose)
	{
		print("<br>");
		print("<h3>tmp_person.classida</h3>");
		print(strSql);
		print("<br>");
	}*/
	string update_sql = "UPDATE tmp_person SET tmp_person.classida = ( SELECT GROUP_CONCAT(DISTINCT CONCAT('<',class,'>') ORDER BY class SEPARATOR '')  FROM topic_person INNER JOIN topic_class ON topic_class.topic = topic_person.topic AND topic_class.topictype = topic_person.topictype WHERE tmp_person.person = topic_person.person)";
	musicdb().query(update_sql);
	if(bVerbose)
	{
		print("<strong>tmp_person.classida</strong><br>");
		print(strSql);
		print("<br>");
	}





	strSql = "UPDATE tmp_person SET tmp_person.classida = (SELECT CAST(GROUP_CONCAT(CONCAT('<',topic_class.class,'>') ORDER BY topic_class.class SEPARATOR '') AS CHAR) FROM topic_person AND topic_person.role = tmp_person.role ON topic_person.person = tmp_person.person INNER JOIN topic_class ON topic_class.topic = topic_person.topic AND topic_class.topictype = topic_person.topictype";
	if(bVerbose)
	{
		print("<br>");
		print("<h3>tmp_person.classida</h3>");
		print(strSql);
		print("<br>");
	}
	musicdb().query(strSql);
}


	void database_cache::tmp_performer_item_update_classida(var performerid, var classida)
	{
		var classida_text = get_classida_text(classida);
		print (performerid + "  --- " + classida_text + "<br>");
		string update_sql = "UPDATE tmp_person SET classida = '" + classida_text + "' WHERE performerid = '" +performerid + "'";
		musicdb().query(update_sql);
	}

	void database_cache::tmp_performer_item_update_chord_classida(var performerid, var classida)
	{
		var classida_text = get_classida_text(classida);
		print (performerid + " --- " + classida_text + "<br>");
		string update_sql = "UPDATE tmp_person SET chord_classida = '" + classida_text + "' WHERE performerid = '" +performerid + "'";
		musicdb().query(update_sql);
	}


	void database_cache::karaoke_update_tmp_class(bool bVerbose)
	{
		if(bVerbose)
		{
			print ("<h1>karaoke_update_tmp_class</h1>");
		}
		musicdb().query("DELETE FROM tmp_class");
		musicdb().query("DELETE FROM tmp_class_2");
		if(bVerbose)
		{
			print ("<h2>classida</h2>");
		}
		tmp_class_update_classida(bVerbose);
		if(bVerbose)
		{
			print ("<h2>2 classida</h2>");
		}
		tmp_class_2_update_classida(bVerbose);
	}

	var database_cache::karaoke_getCodeArray(var classid, var topic, bool bVerbose)
	{
      UNREFERENCED_PARAMETER(bVerbose);
		stringa codea;

		AlphaSelectPerformer * pas = new AlphaSelectPerformer(topic);
		pas->m_strClassId = classid;

		stringa fulla  = pas->code_getFullArray();
		for(int i = 0 ; i < fulla.get_count(); i++)
		{
         string code = fulla[i];
			//if(pas->code_getCount(code, bVerbose))
         if(pas->code_getCount(code))
			{
				codea.add(code);
         }
		}

		return codea;
	}

	var database_cache::karaoke_getCodeArrayField(var classid, var topic, bool bVerbose)
	{
		return karaoke_getCodeArray(classid, topic, bVerbose).implode(";");
	}


	void database_cache::tmp_class_update_classida_item(var topictype, var classid, var classidaParam, bool bVerbose)
	{
      var classida = classidaParam;
		classida.inta().QuickSort();
      stringa stra;
      stra = classida.stra();
      stra.surround("<", ">");
		var parentclass = stra.implode();
/*		for(int i = 0;each($classida as $id)
		{
			$parentclass .= "<$id>";
		}*/

		bool bGo = false;
		if(strlen(classid) == 0)
		{
			bGo = true;
		}
		else
		{
			string sql_select = "SELECT COUNT(*) FROM tmp_class WHERE classid = '" + classid + "' AND parentclassida = '" + parentclass + "' AND topictype = " + topictype;
			var count = musicdb().query_item(sql_select);
			bGo = count == 0;
		}

      var tt_cond;
		 if(topictype == 1)
		 {
				tt_cond = "(topic_song.topictype = 1 OR topic_song.topictype = 1001)";
		 }
		 else
		 {
				tt_cond = "topic_song.topictype = " + topictype;
		 }


		if(bGo)
		{
			var classida2 = classida;
			if(strlen(classid) > 0)
			{
				classida2.inta().add(classid);
			}
			classida2.inta().QuickSort();
			string classcondition = "";
         stringa stra2;
         stra2 = classida2.stra();
         stra2.surround("<", ">");
         var rows;
			if(stra2.get_count() > 0)
			{
				classcondition = musicdb().and_instra("`tmp_song`.`classida`", stra2);
				string sql_select = "SELECT COUNT(DISTINCT topic_person.person), COUNT(DISTINCT tmp_song.song) FROM topic_song INNER JOIN song ON topic_song.song = song.id INNER JOIN tmp_song ON song.id = tmp_song.song INNER JOIN topic_person ON topic_person.topic = topic_song.topic AND topic_person.topictype = topic_song.topictype WHERE "+ tt_cond + "  AND " + classcondition;
				if(bVerbose)
				{
					print(sql_select);
					print("<br>");
				}
				rows = musicdb().query_rows(sql_select);
			}
			else
			{
				string sql_select = "SELECT COUNT(DISTINCT topic_person.person), COUNT(DISTINCT tmp_song.song) FROM topic_song INNER JOIN song ON topic_song.song = song.id INNER JOIN topic_song as ts2 ON ts2.song = song.id INNER JOIN tmp_song ON song.id = tmp_song.song INNER JOIN topic_person ON topic_person.topic = ts2.topic AND topic_person.topictype = ts2.topictype WHERE "+ tt_cond + " GROUP BY topic_person.topictype";
				if(bVerbose)
				{
					print(sql_select);
					print("<br>");
				}
				rows = musicdb().query_rows(sql_select);
			}

			for(int i = 0; i < rows.array_get_count(); i++)
			{
            var row = rows.at(i);
				if(row.at(0) > 0 && row.at(1) > 0)
				{
					var codeafld = karaoke_getCodeArrayField(implode(",", classida2), topictype, bVerbose);
					if(bVerbose)
					{
						print("Insert class=" + classid + ", parentclass=" + parentclass + ": ");
						print("perfomer(" + row.at(0) + ") song(" + row.at(1) + ") type(" + topictype + ")<br>");
					}
					string sql_insert = "INSERT tmp_class (classid, topictype, parentclassida, performercount, songcount, codea) VALUES ('" + classid + "', '" + topictype + "', '" + parentclass + "', '" + row.at(0) + "', '" + row.at(1) + "',  '" + codeafld + "')";
					musicdb().query(sql_insert);

				}
				else
				{
					if(bVerbose)
					{
						print("<b>Not Inserted</b> class=" + classid + ", parentclass=" + parentclass + "!<br>");
					}
				}
			}
		}
	}


	void database_cache::tmp_class_update_classida(bool bVerbose)
	{
		if(bVerbose)
		{
			print("<pre>");
		}

		string strSql = "INSERT IGNORE INTO tmp_song (song) SELECT song.id FROM song";

		musicdb().query(strSql);

		tmp_class_update_classida_item(0, "", array(), bVerbose);
		tmp_class_update_classida_item(1, "", array(), bVerbose);
		tmp_class_update_classida_item(2, "", array(), bVerbose);

		strSql = "SELECT topic_class.topic, topic_class.topictype, topic_class.class FROM topic_class ORDER BY topic_class.topictype, topic_class.topic, topic_class.class;";

		var rows = musicdb().query_rows(strSql);


	   stringa classa;

      string topicid;
      string topictype;
      string classid;
      string cl;
      stringa parent_class;

		if(rows.array_get_count() > 0)
		{
         var row = rows.at(0);
			topicid		= row.at(0);
			topictype	= row.at(1);
			classid		= row.at(2);
			classa.add(classid);
		}

      string oldtopicid;
      string oldtopictype;

		stringa classa_added;
		for(int i = 1; i < rows.array_get_count(); i++)
		{
         var row = rows.at(i);
			topicid		= row.at(0);
			topictype	= row.at(1);
			classid		= row.at(2);
			if(oldtopicid != topicid || topictype != oldtopictype)
			{
				classa.QuickSort();
				string classa_test = classa.implode(",");
				if(!classa_added.contains(classa_test))
				{
					array_ptr_alloc < stringa > a;
               a.remove_all();
               gen::lemon::array_makecombination(a, classa);
					for(int i = 0; i < a.get_count(); i++)
					{
                  stringa & comb = a[i];
						if(comb.get_count() > 0)
						{
							cl = comb[0];
							parent_class = comb;
                     parent_class.remove(cl);
							if(bVerbose)
							{
								print("class = " + cl);
								print(" parent_class =" + parent_class.implode(";"));
								print("\n");
							}
//							tmp_class_update_classida_item($oldtopictype, $class, $parent_class, bVerbose);
							tmp_class_update_classida_item(0, cl, parent_class, bVerbose);
							tmp_class_update_classida_item(1, cl, parent_class, bVerbose);
							tmp_class_update_classida_item(2, cl, parent_class, bVerbose);
						}
					}
					classa_added.add(classa_test);
				}
				classa.remove_all();
 				oldtopicid		= topicid;
				oldtopictype 	= topictype;
			}
			classa.add(classid);
		}

      tmp_class_update_classida_item(0, cl, parent_class, bVerbose);
		tmp_class_update_classida_item(1, cl, parent_class, bVerbose);
		tmp_class_update_classida_item(2, cl, parent_class, bVerbose);
		if(bVerbose)
		{
			print("</pre>");
		}
	}

	void database_cache::tmp_class_2_update_classida(bool bVerbose)
	{

		string strSql = "DELETE FROM tmp_class_2_class";
		musicdb().query(strSql);

		strSql = "SELECT classid, topictype, parentclassida, performercount, songcount,  codea FROM tmp_class";
		var rows = musicdb().query_rows(strSql);
		var class2id = 0;
      stringa parentclassida;
      stringa classida;
		for(int i = 0; i < rows.array_get_count(); i++)
		{
			var row               = rows.at(i);
			string classid          = row.at(0);
			string parentclass      = row.at(2);
			stringa parentclassida  = gen::lemon::x1_decode_ida(parentclass);
			classida                = parentclassida;
         classida.add(classid);
			if(bVerbose)
			{
				print("<h4>");
				print("Insert<*2*> class=" + classid + ", topictype=" + row.at(1) + ", parentclass=" + parentclass + ": ");
				print("performercount("+row.at(3)+"}) songcount("+row.at(4)+") codea("+row.at(5)+")");
				print("</h4>");
			}


			string sql_insert = "INSERT tmp_class_2 (id, classid, topictype, parentclassida, performercount, songcount, codea) VALUES ('"+class2id+"', '"+classid+"', '"+row.at(1)+"', '"+parentclass+"', '"+row.at(3)+"', '"+row.at(4)+"', '{"+row.at(5)+"}')";
			musicdb().query(sql_insert);

			for(int j = 0; j < classida.get_count(); j++)
			{
				strSql = "INSERT IGNORE INTO tmp_class_2_class(class2id, classid) VALUES('"+class2id+"','"+classida[j]+"') ";
				musicdb().query(strSql);
			}

			class2id++;

         array_ptr_alloc < stringa > a;
         a.remove_all();
			gen::lemon::array_permute(a, classida);
			for(int j = 0; j < a.get_count(); j++)
			{
            stringa & ida = a[j];
				classid = ida[0];
				stringa xa;
            ida.slice(xa, 1);
				string x1_ida = gen::lemon::x1_encode_ida(xa);
				if(bVerbose)
				{
					print("<strong>");
					print("Combination: "+classid+" ");
					if(x1_ida.has_char())
					{
						print(" AND "+x1_ida+"");
					}
					print("</strong><br>");
				}
				string sql_check = "SELECT COUNT(classid) FROM tmp_class_2 WHERE classid = '"+classid+"' AND parentclassida = '"+x1_ida+"' AND topictype = '"+row.at(1)+"'";
				var classid_count = musicdb().query_item(sql_check);
				if(bVerbose)
				{
					print("\n");
					print("COUNTCOUNT Count Count count = " + classid_count);
					print("\n");
				}
				if(classid_count == 0)
				{
					if(bVerbose)
					{
						print("<strong> INSERTING </strong>");
					}

	      		string sql_insert = "INSERT tmp_class_2 (id, classid, topictype, parentclassida, performercount, songcount, codea) VALUES ('"+ class2id +"', '"+classid+"', '"+row.at(1)+ "', '" + x1_ida + "', '" + row.at(3) + "', '" + row.at(4) + "', '" + row.at(5)+ "')";
					if(bVerbose)
					{
						print(sql_insert);
					}
					musicdb().query(sql_insert);

					for(int k = 0; k < classida.get_count(); k++)
					{
                  classid = classida[k];
						strSql = "INSERT IGNORE INTO tmp_class_2_class(class2id, classid) VALUES('"+class2id+"','"+classida[k]+"') ";
						musicdb().query(strSql);
					}

					class2id++;

				}
			}
		}
	}



	void database_cache::karaoke_update_tmp_song_lyricscount(bool bVerbose)
	{
		karaoke_update_tmp_song_topictype_count("lyricscount", 1, bVerbose);
	}
	void database_cache::karaoke_update_tmp_song_chordcount(bool bVerbose)
	{
		karaoke_update_tmp_song_topictype_count("chordcount", 2, bVerbose);
	}
	void database_cache::karaoke_update_tmp_song_karaokecount(bool bVerbose)
	{
		karaoke_update_tmp_song_topictype_count("karaokecount", 0, bVerbose);
	}

	void database_cache::karaoke_update_tmp_song_topictype_count(var tmp_song_field, var topictype, bool bVerbose)
	{
      string strSql;
		DWORD time1 = ::GetTickCount();
		if(bVerbose)
		{
			print("<h2>");
			print("karaoke update tmp song topictype count");
			print("</h2>");
			print("<h3>");
			print (tmp_song_field);
			print("</h3>");
		}
		if(topictype == 1)
		{
			strSql = "UPDATE tmp_song SET tmp_song." + tmp_song_field + " = (SELECT COUNT(topic_song.topic) FROM topic_song WHERE topic_song.song = tmp_song.song AND (topic_song.topictype = 1 OR topic_song.topictype = 1001))";
		}
		else
		{
			strSql = "UPDATE tmp_song SET tmp_song." + tmp_song_field + " = (SELECT COUNT(topic_song.topic) FROM topic_song WHERE topic_song.song = tmp_song.song AND topic_song.topictype = " + topictype + ")";
		}
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}
		musicdb().query(strSql);
	}

	void database_cache::update_lyrics(bool bVerbose)
	{
      UNREFERENCED_PARAMETER(bVerbose);
		string strSql = "SELECT lyrics.id FROM lyrics WHERE LENGTH(lyrics.lyrics) = 0";
		var rows = musicdb().query_rows(strSql);

		for(int i = 0; i < rows.array_get_count(); i++)
		{
         var row = rows.at(i);
			var id = row.at(0);
			strSql = "DELETE FROM topic_song WHERE topictype = 1 AND id = " +id+"  LIMIT 1";
			print(strSql);
			musicdb().query(strSql);
			strSql = "DELETE FROM lyrics WHERE id = " +id+"  LIMIT 1";
			print(strSql);
			musicdb().query(strSql);
		}

		strSql = "SELECT lyrics.id FROM lyrics, karfile_lyrics WHERE karfile_lyrics.lyrics = lyrics.lyrics";
		rows = musicdb().query_rows(strSql);

		for(int i = 0; i < rows.array_get_count(); i++)
		{
         var row = rows.at(i);
			var id = row[0];
			strSql = "DELETE FROM topic_song WHERE topictype = 1 AND id =" +id+" LIMIT 1";
			print(strSql);
			musicdb().query(strSql);
			strSql = "DELETE FROM lyrics WHERE id = " +id+"  LIMIT 1";
			print(strSql);
			musicdb().query(strSql);
		}

		strSql = "DELETE FROM topic_song WHERE topictype = 1001";
		musicdb().query(strSql);

		strSql = "INSERT INTO topic_song(topic, topictype, song, topicindex) (SELECT t2.topic, 1001, t2.song, 1 FROM topic_song as t2 INNER JOIN karfile_lyrics ON t2.topictype = 0 AND t2.topic = karfile_lyrics.karfile)";
		musicdb().query(strSql);

		strSql = "DELETE FROM topic_class WHERE topictype = 1001";
		musicdb().query(strSql);

		strSql = "INSERT INTO topic_class(topic, topictype, class) (SELECT t2.topic, 1001, t2.class FROM topic_class as t2 INNER JOIN karfile_lyrics ON t2.topictype = 0 AND t2.topic = karfile_lyrics.karfile)";
		musicdb().query(strSql);

		strSql = "DELETE FROM topic_person WHERE topictype = 1001";
		musicdb().query(strSql);

		strSql = "INSERT INTO topic_person(topic, topictype, person, role) (SELECT t2.topic, 1001, t2.person, t2.role FROM topic_person as t2 INNER JOIN karfile_lyrics ON t2.topictype = 0 AND t2.topic = karfile_lyrics.karfile)";
		musicdb().query(strSql);
	}

	void database_cache::full_song_update(bool bVerbose)
	{
		/*xxxdb_read->set_prop_text("last_partial_update_tmp_song_clickdistinct1", "");
		db_read->set_prop_text("pending_full_song_update", "false");*/
		song_cache_initialize(bVerbose);


		tmp_song_insert(bVerbose);
		karaoke_update_tmp_song_lyricscount(bVerbose);
		karaoke_update_tmp_song_chordcount(bVerbose);
		karaoke_update_tmp_song_karaokecount(bVerbose);
		tmp_song_update_classida(bVerbose);

		string strSql = 	"UPDATE `tmp_song` SET classflag1 = IF(classida LIKE '%<1033>%', classflag1 | 64, classflag1 & ~64)"	;
		if(bVerbose)
		{
			print(strSql);
		}
		musicdb().query(strSql);
		tmp_song_update_performerida(bVerbose);
		karaoke_update_tmp_song_clickdistinct1(bVerbose);
		karaoke_update_tmp_class(bVerbose);
		tmp_performer_update(bVerbose);
		update_tmp_topic(bVerbose);
		update_tmp_topic_click(bVerbose);
	}

	void database_cache::on_song_insertion(bool bVerbose)
	{
		//xxxdb_read->set_prop_text("pending_insertion_update", "false");
		on_song_insertion_1(bVerbose);
		full_song_update(bVerbose);
	}


	void database_cache::on_song_insertion_1(bool bVerbose)
	{
      UNREFERENCED_PARAMETER(bVerbose);
	/*
		strSql = "INSERT IGNORE INTO `tmp_topic_lang_style`(`langid`, `styleid`, `topictype`, `topicid`, `songid`) SELECT langstyle.langid, langstyle.styleid, topic_song.topictype, topic_song.id, topic_song.songid FROM langstyle, topic_song";
		musicdb().query(strSql);
		*/
	}


	void database_cache::update_tmp_song_lang_style_rank(bool bVerbose)
	{
      UNREFERENCED_PARAMETER(bVerbose);
      /*string lastdatetime;
      string strWhere;
		if(strlen(lastdatetime) > 0)
		{
			strWhere = "WHERE `datetime` > 'lastdatetime'";
		}
		else
		{
			strWhere = "";
		}
		if(bVerbose)
		{
			print("<table>");
			print("<tbody>");
			print("<tr>");
			print( "<td style=\"padding-left: 3.0em;\">");

		}

		DWORD time1 = ::GetTickCount();
		if(bVerbose)
		{
			print("<h3>update_tmp_song_lang_style_rank</h3>");

		}


		string strSql = "LOCK TABLES tmp_topic_lang_style_click as tread READ, tmp_topic_lang_style_click WRITE";
		mysql::result * presult = musicdb().query(strSql);

		strSql = "SELECT topictype, langid, styleid, `type` + 0, topic, click FROM tmp_topic_lang_style_click as tread ORDER BY topictype, langid, styleid, `type`, click DESC";
		mysql::result * presult = musicdb().query(strSql);

		$stmt3 =  mysqli->stmt_init();
		strSql = "UPDATE tmp_topic_lang_style_click SET rank = ? WHERE topic = ? AND topictype = ? AND langid = ? AND styleid = ? AND `type` = ? LIMIT 1";
		$stmt3->prepare(strSql);

		// bind parameters for markers
		$stmt3->bind_param("iiiiii", $rank, topicid, $topictype, langid, styleid, $type);

		$ctype 	= -1111111; // start with invalid value;
		langid 	= -1111111; // start with invalid value;
		$style 	= -1111111; // start with invalid value;
		$type 	= -1111111; // start with invalid value;
		while($row = fonto_fetch_row($result))
		{
			if($topictype	!= $row[0]
			|| langid 		!= $row[1]
			|| styleid 	!= $row[2]
			|| $type 		!= $row[3])
			{
				$old_click	= -1;
				$rank 		= 0;
				$topictype 	= $row[0];
				langid 		= $row[1];
				styleid 	= $row[2];
				$type			= $row[3];
				if(bVerbose)
				{
					print("langid: langid, styleid: styleid, type: $type";
					print("<br>");

				}
			}
			topicid = $row[4];
			if($click != $row[5])
			{
				$click = $row[5];
				$rank++;
			}
			$stmt3->execute();
		}
		strSql = "UNLOCK TABLES";
		presult =musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print("<br>");
			print("delta: "+delta+"<br>");

		}

		if(bVerbose)
		{
			print("</td>";
			print("</tr>";
			print("</tbody>";
			print("</table>";

		}	*/
	}


void database_cache::tmp_topic_lang_style_update_top( var top_field, var lastdatetime, bool bVerbose)
{
   string strWhere;
		if(lastdatetime != 0)
		{
			strWhere = "WHERE `datetime` > '" + lastdatetime + "'";
		}
		else
		{
			strWhere = "";
		}
		if(bVerbose)
		{
			print("<table>");
			print("<tbody>");
			print("<tr>");
			print( "<td style=\"padding-left: 3.0em;\">");

		}

		DWORD time1 = ::GetTickCount();
		if(bVerbose)
		{
			print("<h3>tmp_topic_lang_style_update_top: "+top_field + "</h3>");

		}

		string strSql = "INSERT INTO tmp_topic_lang_style_click2 SELECT topic, type, langid, styleid, '" + top_field + "', SUM(click), 0, 0 FROM topic_click_compiled " + strWhere + " GROUP BY topic, type, langid, styleid";
		mysql::result  *presult = musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}
		strSql = "INSERT INTO tmp_topic_lang_style_click SELECT topic, click_type_topic_type.topictype, langid, styleid, '" + top_field + "', SUM(click), 0, 0 FROM tmp_topic_lang_style_click2 INNER JOIN click_type_topic_type ON tmp_topic_lang_style_click2.clicktype = click_type_topic_type.clicktype WHERE tmp_topic_lang_style_click2.type = '" + top_field + "'  GROUP BY topic, click_type_topic_type.topictype, langid, styleid";
		presult =musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}

		if(bVerbose)
		{
			print("</td>");
			print("</tr>");
			print("</tbody>");
			print("</table>");

		}

}


void database_cache::tmp_topic_lang_style_update_top_item(var topicid, var langid, var styleid, var top_field, var lastdatetime, bool bVerbose)
{
		if(bVerbose)
		{
			print("<table>");
			print("<tbody>");
			print("<tr>");
			print( "<td style=\"padding-left: 3.0em;\">");

		}
		DWORD time1 = ::GetTickCount();
		if(bVerbose)
		{
			print("<h3>tmp_topic_lang_style_update_top_item: " + top_field + "</h3>");

		}
      string strWhere;
		if(lastdatetime != 0)
		{
			strWhere = "WHERE topic = "+topicid+" AND `datetime` > '" + lastdatetime + "'";
		}
		else
		{
			strWhere = "WHERE topic = "+topicid;
		}

		string strSql = "REPLACE INTO tmp_topic_lang_style_click SELECT topic, click_type_topic_type.topictype, langid, styleid, '"+top_field+"', SUM(click), 0, 0 FROM topic_click_compiled INNER JOIN click_type_topic_type ON topic_click_compiled.type = click_type_topic_type.clicktype  "+strWhere+" GROUP BY topic, `type`, langid, styleid";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}

		time1 = ::GetTickCount();
		if(bVerbose)
		{
			print("<h3>tmp_topic_lang_style_update_top_item: " + top_field + "</h3>");

		}

/*		if(strlen(lastdatetime) > 0)
		{
			strWhere = "WHERE topic = topicid AND `datetime` > 'lastdatetime'";
		}
		else
		{
			strWhere = "WHERE topic = topicid";
		}

		strSql = "REPLACE INTO tmp_topic_lang_style_click SELECT topic, `type`, langid, styleid, '$top_field', SUM(click), 0, 0 FROM topic_click_compiled strWhere GROUP BY topic, `type`, langid, styleid";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<br>");
			print("delta: "+delta+"<br>");

		}*/

		if(bVerbose)
		{
			print("</td>");
			print("</tr>");
			print("</tbody>");
			print("</table>");

		}


}

var database_cache::get_min_datetime_hour_round_song_click()
{
	string strSql = "SELECT CONCAT(SUBSTRING(datetime, 1, 13), ':00:00') FROM topic_click ORDER BY datetime LIMIT 1";
	return musicdb().query_item(strSql);
}

var database_cache::get_max_datetime_hour_round_song_click()
{
	string strSql = "SELECT CONCAT(SUBSTRING(datetime, 1, 13), ':00:00') FROM topic_click ORDER BY datetime DESC LIMIT 1";
	return musicdb().query_item(strSql);
}

var database_cache::get_min_datetime_topic_click_compiled()
{
	string strSql = "SELECT MIN(datetime) FROM topic_click_compiled";
	return musicdb().query_item(strSql);
}

var database_cache::get_max_datetime_topic_click_compiled()
{
	string strSql = "SELECT MAX(datetime) FROM topic_click_compiled";
	return musicdb().query_item(strSql);
}

void database_cache::update_tmp_topic(bool bVerbose)
{
   DWORD time1;
		if(bVerbose)
		{
			time1 = ::GetTickCount();
			print("<h3>begin: update_tmp_topic: insert</h3>");
		}
		on_song_insertion_1(bVerbose);

		string strSql = "INSERT IGNORE INTO tmp_topic(topic, topictype) SELECT topic, topictype FROM topic_song";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<h3>end: update_tmp_topic: insert</h3>");
			print("delta: "+delta+"<br>");
		}

		if(bVerbose)
		{
			print("<h3>begin: update_tmp_topic: update performerida </h3>");
		}

		var role = 2;
		strSql = "UPDATE tmp_topic SET tmp_topic.performerida = (SELECT DISTINCT CAST(GROUP_CONCAT(DISTINCT CONCAT('<',topic_person.person,'>') ORDER BY topic_person.person SEPARATOR '') AS CHAR) FROM topic_song INNER JOIN topic_person ON topic_person.topic = topic_song.topic AND topic_person.topictype = topic_song.topictype WHERE topic_song.topic = tmp_topic.topic AND topic_song.topictype = tmp_topic.topictype AND topic_person.role = "+role+")";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<h3>end: update_tmp_topic: update performerida </h3>");
			print("delta: "+delta+"<br>");
		}
		strSql = "UPDATE tmp_topic SET tmp_topic.classida = (SELECT DISTINCT CAST(GROUP_CONCAT(DISTINCT CONCAT('<',topic_class.class,'>') ORDER BY topic_class.class SEPARATOR '') AS CHAR) FROM topic_class WHERE topic_class.topic = tmp_topic.topic AND topic_class.topictype = tmp_topic.topictype)";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<h3>end: update_tmp_topic: update classid </h3>");
			print("delta: "+delta+"<br>");
		}

		strSql = "UPDATE tmp_topic SET tmp_topic.language = (SELECT MIN(topic_class.class) FROM topic_class WHERE topic_class.topic = tmp_topic.topic AND topic_class.topictype = tmp_topic.topictype)";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<h3>end: update_tmp_topic: update performerida </h3>");
			print("delta: "+delta+"<br>");
		}

}







void database_cache::update_tmp_topic_click(bool bVerbose)
{
		if(bVerbose)
		{
//			DWORD time1 = ::GetTickCount();
			print("<h3>begin: update_tmp_topic: insert</h3>");
		}

		/*$now = musicdb().query_item("SELECT DATE_FORMAT(NOW(), '%Y-%m-%d %h:00:00')");
		dprint("SQL time = $time<br>");
		lastdatetime = db_read->get_prop_text("last_partial_update_tmp_topic_click");
		$delta_time1 = datetime_formatDateTime(strtotime("-1 day", strtotime(lastdatetime)));
		dprint("time = $time<br>");

		strSql = "LOCK TABLES topic_click WRITE, tmp_topic_click WRITE";
		presult =musicdb().query(strSql);


		db_read->set_prop_text("last_partial_update_tmp_topic_click", datetime_formatDateTime(strtotime($now)));


		strWhere = " topic_click.datetime >= '$delta_time1'";
		strSql = "INSERT IGNORE INTO tmp_topic_click(topicclick) SELECT topic_click.id FROM topic_click WHERE strWhere";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<h3>end: update_tmp_topic: insert</h3>");
			print("delta: "+delta+"<br>");
		}

		strSql = "UPDATE tmp_topic_click SET tmp_topic_click.classida = (SELECT CAST(GROUP_CONCAT(DISTINCT CONCAT('<',topic_class.class,'>') ORDER BY topic_class.class SEPARATOR '') AS CHAR) FROM topic_class INNER JOIN topic_click ON topic_class.topic = topic_click.topic AND topic_class.topictype = topic_click.type WHERE topic_click.id = tmp_topic_click.topicclick AND strWhere)";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<h3>end: update_tmp_topic: update performerida </h3>");
			print("delta: "+delta+"<br>");
		}

		strSql = "UNLOCK TABLES";
		presult =musicdb().query(strSql);

		strSql = "UPDATE topic_click SET topic_click.calc_topictype = (SELECT click_type_topic_type.topictype FROM click_type_topic_type WHERE topic_click.type = click_type_topic_type.clicktype strWhere)";
		musicdb().query(strSql);
		if(bVerbose)
		{
			DWORD time2 = ::GetTickCount();
			var delta = debug_delta(time1, time2);
			time1 = time2;
			print(strSql);
			print("<h3>end: update_tmp_topic: update performerida </h3>");
			print("delta: "+delta+"<br>");
		}*/
}

var database_cache::get_classida_text(var ida)
{
   stringa stra;
   stra =  ida.stra();
	stra.QuickSort();
   stra.surround("<", ">");
   return stra.implode();
}

var database_cache::debug_delta(var time1, var time2)
{
	return  ((DWORD) (int) time2 - (DWORD)(int) time1) * 1000;
}


} // namespace music

} // namespace webserver
