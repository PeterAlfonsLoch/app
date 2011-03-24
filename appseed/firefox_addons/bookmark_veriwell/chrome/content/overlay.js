function bookmark()
{
	var title = content.document.title;
	var url = content.window.location.href.toString();
	content.window.location.href = "http://bookmark.veriwell.net/bookmark?url=" + Url.encode(url) + 
	"&title=" + Url.encode(title);
}

function bookmark_home()
{
	content.window.location.href = "http://bookmark.veriwell.net/";
}
function bookmark_veriwell_AddIconToNavbar()
{
try {
   var firefoxnav = document.getElementById("nav-bar"); // use "nav-bar" in Firefox 2 and earlier "navigation-toolbar"
   var curSet = firefoxnav.currentSet;
   if (curSet.indexOf("bookmarkveriwellbutton") == -1
	 || (curSet.indexOf("annotateveriwellbutton") != -1 && (curSet.indexOf("annotateveriwellbutton") < curSet.indexOf("bookmarkveriwellbutton")) )
	 	 || (curSet.indexOf("veriwellsidebarbutton") != -1 && (curSet.indexOf("veriwellsidebarbutton") < curSet.indexOf("bookmarkveriwellbutton") )))
   {
     var set;
	  curSet = curSet.replace(/bookmarkveriwellbutton[,]/g, "");
     // Place the button before the urlbar
     if (curSet.indexOf("annotateveriwellbutton") != -1)
       set = curSet.replace(/annotateveriwellbutton/, "bookmarkveriwellbutton,annotateveriwellbutton");
     else if (curSet.indexOf("veriwellsidebarbutton") != -1)
       set = curSet.replace(/veriwellsidebarbutton/, "bookmarkveriwellbutton,veriwellsidebarbutton");
     else if (curSet.indexOf("urlbar-container") != -1)
       set = curSet.replace(/urlbar-container/, "bookmarkveriwellbutton,urlbar-container");
     else  // at the end
       set = curSet + ",bookmarkveriwellbutton";
     firefoxnav.setAttribute("currentset", set);
     firefoxnav.currentSet = set;
     document.persist("nav-bar", "currentset");
     // If you don't do the following call, funny things happen
     try {
       BrowserToolboxCustomizeDone(true);
     }
     catch (e) { }
   }
   curSet = firefoxnav.currentSet;
   if (curSet.indexOf("bookmarkveriwellhomebutton") == -1
 || (curSet.indexOf("bookmarkveriwellhomebutton") != (curSet.indexOf("bookmarkveriwellbutton") +  23)))
   {
     var set;
	  alert(curSet);
	  curSet = curSet.replace(/bookmarkveriwellhomebutton[,]/g, "");
	  alert(curSet);
     // Place the button before the urlbar
     if (curSet.indexOf("bookmarkveriwellbutton") != -1)
       set = curSet.replace(/bookmarkveriwellbutton/, "bookmarkveriwellbutton,bookmarkveriwellhomebutton");
     else  // at the end
       set = curSet + ",bookmarkveriwellhomebutton";
     firefoxnav.setAttribute("currentset", set);
     firefoxnav.currentSet = set;
     document.persist("nav-bar", "currentset");
     // If you don't do the following call, funny things happen
     try {
       BrowserToolboxCustomizeDone(true);
     }
     catch (e) { }
   }
 }
 catch(e) { }
}
 
 
 window.addEventListener("load", function(e) { bookmark_veriwell_AddIconToNavbar(); }, false);