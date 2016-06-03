#-- coding: utf-8 --

import shutil
import os

def DelFile(dirDel):
    if os.path.exists(dirDel) :
        for listDir in os.listdir(dirDel):
            listDirec = os.path.join(dirDel, listDir)
            if os.path.isdir(listDirec):
                print(listDirec)
                DelFile(listDirec)
            else:
                os.remove(listDirec)
                
DelFile(r"F:\TongYanSuiDao\Image")
DelFile(r"D:\TongYanSuiDao\Image")
