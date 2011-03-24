function onBookmark()
{
	var title = content.document.title;
	var url = content.window.location.href.toString();
	content.window.location.href = "http://bookmark.veriwell.net/bookmark?url=" + Url.encode(url) + 
	"&title=" + Url.encode(title);
/*	var params = {inn:{url:url, title:title, description:""}, out:null};       
	window.openDialog("chrome://bookmark_veriwell/chrome/content/dialog.xul", "",
    "chrome, dialog, modal, resizable=yes", params).focus();
  if (params.out) {
    // User clicked ok. Process changed arguments; e.g. write them to disk or whatever
  }
  else {
    // User clicked cancel. Typically, nothing is done here.
  }*/
}

function onBookmarkList()
{
	content.window.location.href = "http://bookmark.veriwell.net/";
}