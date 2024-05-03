::关闭命令行回显
@echo off
::循环分别进入 Objects 和 Listings 文件夹。进行清理
::额外保留的格式。还需要添加则 空格后缀名，如多添加一个text后缀的保留 PreserveExt=hex axf bin text
set Ext=axf hex bin
for %%d in (Objects Listings) do (
	::进入当前bat文件目录下的指定目录
	cd /d "%~dp0build\%%d"
	::指定后缀文件
	::set Ext=hex
	::循环查找，如果不是这个后缀，则删除
	for /f "delims=" %%a in ('dir /a-d/s/b') do (
		if /i not "%%~a"=="%~f0" (
			set "Skip="
			for %%i in (%Ext%) do (
				if /i ".%%~i"=="%%~xa" (
					set Skip=OK
				)
			)
			if not defined Skip (
				echo "Deleting files: %%~a"
				del /f /q "%%~a"
			)
		)
	)
)
