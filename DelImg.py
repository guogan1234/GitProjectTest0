#-- coding: utf-8 --

import shutil
import os
import time

def DelFile(dirDel):
    if os.path.exists(dirDel) :
        for listDir in os.listdir(dirDel):
            listDirec = os.path.join(dirDel, listDir)
            if os.path.isdir(listDirec):
                print("删除", listDirec, "中的jpg文件。")
                DelFile(listDirec)
            else:
                os.remove(listDirec)
                
DelFile(r"D:\TongYanSuiDao\Image")
time.sleep(10)