@echo off
for /l %%a in (0, 1, 30) do (
	call :DirImg %%a
)

pause

:DirImg
if exist d:\TongYanSuiDao\Image\%1\ (
	set /p ="��� %1 ��ͼƬ   " <nul  
	dir /B /A-D d:\TongYanSuiDao\Image\%1\*.jpg | find /V /C ""
)
