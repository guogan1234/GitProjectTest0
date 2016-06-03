#-- coding: utf-8 --

import fileinput
  
def DelEmptyLine(FileName):
    for lines in fileinput.input(files = FileName, inplace = True):
        if 17 < len(lines) and 25 > len(lines) and lines[:2] == "相机":
            print(lines.strip())

    fileinput.close()
    
DelEmptyLine(r"E:\soft\python\TriggerLog.txt")

