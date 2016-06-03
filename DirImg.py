#coding=utf-8
'''
Created on 2016-5-31

@author: Zhao Lu
'''
import os

def GetFileList(dir):
    if os.path.isdir(dir):
       listDir = os.listdir(dir)
       for sCameraDir in listDir:
           theCameraDir = os.path.join(dir, sCameraDir)
           if os.path.isdir(theCameraDir):
               print(sCameraDir, "有照片", len(os.listdir(theCameraDir)), "张。")
             

GetFileList(r"F:\TongYanSuiDao\Image")
GetFileList(r"D:\TongYanSuiDao\Image")
sinput = input ("请按回车键。")

                
            
    
