
vmsseps.dll: dlldata.obj vmsse_p.obj vmsse_i.obj
	link /dll /out:vmsseps.dll /def:vmsseps.def /entry:DllMain dlldata.obj vmsse_p.obj vmsse_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del vmsseps.dll
	@del vmsseps.lib
	@del vmsseps.exp
	@del dlldata.obj
	@del vmsse_p.obj
	@del vmsse_i.obj
