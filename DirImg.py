#coding=utf-8
'''
Created on 2016-5-31

@author: Zhao Lu
'''
import os
import time

def GetFileList(dir):
    if os.path.isdir(dir):
       listDir = os.listdir(dir)
       for sCameraDir in listDir:
           theCameraDir = os.path.join(dir, sCameraDir)
           if os.path.isdir(theCameraDir):
               print("相机", sCameraDir, "有照片", len(os.listdir(theCameraDir)), "张。")
             

GetFileList(r"D:\TongYanSuiDao\Image")
time.sleep(10)

#sinput = input ("请按回车键。")

                
            
    
