#Build编译
##linux
	make linux LUAPKG="/usr/local"
	make install INSTALLDIR="/usr/local/luaextend"
	LUAPKG为安装lua的路径。默认为/usr/local
	INSTALLDIR程序安装路径。默认为/usr/local/luaextend
##windows
编译需要安装[mingw](http://www.mingw.org/).或者在这[下载](http://download.csdn.net/detail/qq_19079937/9710172)。找到msys.bat并运行

	make w32 LUAPKG=lua的安装路径
	make install INSTALLDIR=程序安装路径

详细文档请点击[这里](https://github.com/liyonglion/luaextend/wiki/manual)