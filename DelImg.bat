@echo off
for /l %%a in (0, 1, 30) do (
	call :DelImg %%a
)

timeout -t 10

:DelImg
if exist d:\TongYanSuiDao\Image\%1\ (
	echo ����ɾ��Ŀ¼ d:\TongYanSuiDao\Image\%1\ �е�jpg�ļ���
	del d:\TongYanSuiDao\Image\%1\*.jpg
)



