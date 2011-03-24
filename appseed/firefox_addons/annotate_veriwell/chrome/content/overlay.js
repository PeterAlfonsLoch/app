function annotate()
{
	content.window.location.href = "http://annotate.veriwell.net/annotate";
}

function annotate_home()
{
	content.window.location.href = "http://annotate.veriwell.net/";
}

function annotate_veriwell_AddIconToNavbar()
{
try {
   var firefoxnav = document.getElementById("nav-bar"); // use "nav-bar" in Firefox 2 and earlier "navigation-toolbar"
   var curSet = firefoxnav.currentSet;
   if (curSet.indexOf("annotateveriwellbutton") == -1)
   {
     var set;
     // Place the button before the urlbar
     if (curSet.indexOf("veriwellsidebarbutton") != -1)
       set = curSet.replace(/veriwellsidebarbutton/, "annotateveriwellbutton,veriwellsidebarbutton");
     else if (curSet.indexOf("urlbar-container") != -1)
       set = curSet.replace(/urlbar-container/, "annotateveriwellbutton,urlbar-container");
     else  // at the end
       set = firefoxnav.currentSet + ",annotateveriwellbutton";
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
   if (curSet.indexOf("annotateveriwellhomebutton") == -1)
   {
     var set;
     // Place the button before the urlbar
     if (curSet.indexOf("annotateveriwellbutton") != -1)
       set = curSet.replace(/annotateveriwellbutton/, "annotateveriwellbutton,annotateveriwellhomebutton");
     else  // at the end
       set = firefoxnav.currentSet + ",annotateveriwellhomebutton";
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
 
 
 window.addEventListener("load", function(e) { annotate_veriwell_AddIconToNavbar(); }, false);