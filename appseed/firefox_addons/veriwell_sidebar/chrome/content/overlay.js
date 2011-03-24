	
	function veriwellSidebarShutdown()
	{
		// empty
	}
	
	function veriwellLoadDefaultUrlInSidebar()
	{
		veriwellLoadUrlInSidebar('http://sidebar.veriwell.net/sidebar/');
	}
	
	function veriwellLoadUrlInSidebar(url)
	{
    	var sidebar = top.document.getElementById("sidebar");
    	var broadcaster = top.document.getElementById('view_veriwell_sidebar');
		if (broadcaster.hasAttribute('checked'))
		{
        	sidebar.style.minWidth = '200px';
        	sidebar.style.width = '200px';
        	sidebar.contentWindow.addEventListener("DOMContentLoaded", function (e) { veriwellContentLoaded(); },  false);
      	sidebar.loadURI(url);
    	}
	}

	function veriwellSidebarStart()
	{
		setTimeout("veriwellLoadDefaultUrlInSidebar()", 2000);
	}
	
	function veriwellContentLoaded()
	{
		veriwellConvertLinks();

		// listen for new additions
/*    	var sidebar = top.document.getElementById("sidebar");
      var table = sidebar.contentDocument.getElementById("veriwell-hidden-content");
      table.addEventListener("DOMNodeRemoved", veriwellConvertLinks(), false);

      // listen for search button clicks
      var searchButton = sidebar.contentDocument.getElementById("jive-veriwell-qbutton");
      searchButton.addEventListener("click", veriwellSubmitSearchForm(), false);

      // listen for search input form submissions
      var searchInput = sidebar.contentDocument.getElementById("jive-veriwell-q");
      searchInput.addEventListener("keypress", veriwellHandleKeyPress(), false);*/

    }

    function veriwellHandleKeyPress (e)
	 {
        if (e.which == 13)
		  {
            veriwellSubmitSearchForm();
        }
    }

    function veriwellSubmitSearchForm()
	 {
        var sidebar = top.document.getElementById("sidebar");
        var searchValue = sidebar.contentDocument.getElementById("veriwell_sidebar_search_query").value;
        var searchURL = 'http://sidebar.veriwell.net/sidebar/search?query=' + searchValue;
        if (searchValue != '')
		  {
            gBrowser.selectedTab = gBrowser.addTab(searchURL);
        }
    }
	function veriwellCreateDefaultSidebarFunction()
	{
		veriwellLoadDefaultUrlInSidebar();
	}
	function veriwellCreateSidebarFunction(sidebarurl, url)
	{
   	return function()
		{
			veriwellLoadUrlInSidebar(sidebarurl);
      	gBrowser.selectedTab = gBrowser.addTab(url);
    	};
	}

	function veriwellCreateOpenFunction(url)
	{
   	return function()
		{
      	gBrowser.selectedTab = gBrowser.addTab(url);
    	};
	}
	function veriwellCreateOpenWithCloseSidebarFunction(url)
	{
   	return function()
		{
      	gBrowser.selectedTab = gBrowser.addTab(url);
			toggleSidebar('view_veriwell_sidebar')
    	};
	}
	function veriwellCreateSetPageFunction(url)
	{
   	return function()
		{
			toggleSidebar('view_veriwell_sidebar')
      	content.document.location.href = url;
    	};
	}
	function veriwellBookmarkFunction()
	{
   	return function()
		{
			toggleSidebar('view_veriwell_sidebar');
	     	content.document.location.href = 'http://bookmark.veriwell.net/bookmark?url=' + content.document.location.href + '&title=' + Url.encode(content.document.title);
    	};
	}

	function veriwellConvertLinks()
	{
   	var sidebar = top.document.getElementById("sidebar");
		var doc = sidebar.contentDocument;
    	var all_links = new Array();
		var links = doc.evaluate("//a", doc, null, XPathResult.ANY_TYPE, null);
	   var link = links.iterateNext();
		while (link)
		{
	   	all_links.push(link);
	      link = links.iterateNext();
	   }

	   for (var i = 0; i < all_links.length; i++)
		{
	   	link = all_links[i];
			if(!link.hasAttribute('onclick') &&
				 link.hasAttribute('href') && link.getAttribute('class').indexOf('defaultsidebar') > -1)
			{
	      	var target = link.getAttribute('href');
	         link.setAttribute('onclick', 'return false;');
	         link.removeAttribute('target');
	         link.addEventListener('click', veriwellCreateDefaultSidebarFunction(), true);
			}
			else if(!link.hasAttribute('onclick') &&
				 link.hasAttribute('href') && link.getAttribute('class').indexOf('sidebarext') > -1)
			{
	      	var target = link.getAttribute('href');
	         link.setAttribute('onclick', 'return false;');
	         link.removeAttribute('target');
	         link.addEventListener('click', veriwellCreateSidebarFunction(target, target + 'body/'), true);
			}
			else if(!link.hasAttribute('onclick') &&
				 link.hasAttribute('href') && link.getAttribute('id') == 'veriwell_bookmark_maker')
			{
	      	var target = link.getAttribute('href');
	         link.setAttribute('onclick', 'return false;');
	         link.removeAttribute('target');
	         link.addEventListener('click', veriwellBookmarkFunction(), true);
			}
	      else if (!link.hasAttribute('onclick') &&
	           link.hasAttribute('href') && link.getAttribute('class').indexOf('setpage') > -1
				  )
			{
	      	var target = link.getAttribute('href');
	         link.setAttribute('onclick', 'return false;');
	         link.removeAttribute('target');
	         link.addEventListener('click', veriwellCreateSetPageFunction(target), true);
         }
	      else if (!link.hasAttribute('onclick') &&
	           link.hasAttribute('href') && link.getAttribute('class').indexOf('closesidebar') > -1
				  )
			{
	      	var target = link.getAttribute('href');
	         link.setAttribute('onclick', 'return false;');
	         link.removeAttribute('target');
	         link.addEventListener('click', veriwellCreateOpenWithCloseSidebarFunction(target), true);
         }
	      else if (!link.hasAttribute('onclick') &&
	           link.hasAttribute('href') && link.getAttribute('class').indexOf('tabbable') > -1
				  )
			{
	      	var target = link.getAttribute('href');
	         link.setAttribute('onclick', 'return false;');
	         link.removeAttribute('target');
	         link.addEventListener('click', veriwellCreateOpenFunction(target), true);
         }
	   }
	}

	function veriwellAddIconToNavbar()
	{
    	try
		{
			var firefoxnav = document.getElementById("nav-bar"); // use "nav-bar" in Firefox 2 and earlier "navigation-toolbar"
   		var curSet = firefoxnav.currentSet;
		   if (curSet.indexOf("veriwellsidebarbutton") == -1)
		   {
				var set;
			  	// Place the button before the urlbar
			  	if (curSet.indexOf("urlbar-container") != -1)
					set = curSet.replace(/urlbar-container/, "veriwellsidebarbutton,urlbar-container");
			  	else  // at the end
					set = firefoxnav.currentSet + ",veriwellsidebarbutton";
			  	firefoxnav.setAttribute("currentset", set);
			  	firefoxnav.currentSet = set;
			  	document.persist("nav-bar", "currentset");
			  	// If you don't do the following call, funny things happen
			  	try
				{
					BrowserToolboxCustomizeDone(true);
			  	}
			  	catch (e)
				{ 
				}
			}
		}
		catch(e)
		{
		}
	}

window.addEventListener("load", function(e) { veriwellAddIconToNavbar(); }, false);
window.addEventListener("load", function(e) { veriwellSidebarStart(); }, false);
window.addEventListener("unload", function(e) { veriwellSidebarShutdown(); }, false);

