@echo off
for /l %%a in (0, 1, 30) do (
	call :DelImg %%a
)

timeout -t 10

:DelImg
if exist d:\TongYanSuiDao\Image\%1\ (
	echo 正在删除目录 d:\TongYanSuiDao\Image\%1\ 中的jpg文件。
	del d:\TongYanSuiDao\Image\%1\*.jpg
)



