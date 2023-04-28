# -*- coding: utf-8 -*-
import os
import time
import shutil
import hashlib


class FileTool:
    def __init__(self):
        self.fileMD5Map = {}

    def getFileMD5(self, file):
        fileObject = open(file, 'rb')
        fileContent = fileObject.read()
        fileObject.close()
        fileMD5 = hashlib.md5(fileContent)
        return fileMD5.hexdigest()

    def rename(self, path):
        for file in os.listdir(path):
            fileName = int(file.split("-")[0]) + 117
            if fileName < 10:
                fileName = "00" + str(fileName)
            elif fileName < 100:
                fileName = "0" + str(fileName)
            # elif int(filename) < 1000:
            #   filename = "0" + str(int(filename))
            os.rename(os.path.join(path, file), os.path.join(path, str(fileName) + ".mp3"))

    def moveFileByMtime(self, path):
        fileNum = 0
        for file in os.listdir(path):
            filePath = os.path.join(path, file)
            if os.path.isdir(filePath):
                fileNum = fileNum + self.moveFileByMtime(filePath)
            else:
                fileNum = fileNum + 1
                mtime = (os.path.getmtime(filePath))
                year = time.localtime(mtime).tm_year
                dstPath = "D:\\Downloads\\" + str(year)
                if not os.path.exists(dstPath):
                    os.mkdir(dstPath)
                if os.path.exists(os.path.join(dstPath, file)):
                    os.chdir(path)
                    fileName = file.split(".")
                    newName = fileName[0] + "_bak." + fileName[1]
                    os.rename(file, newName)
                    filePath = os.path.join(path, newName)
                shutil.move(filePath, dstPath)
        return fileNum

    def traverseDir(self, path):
        fileNum = 0
        for file in os.listdir(path):
            filePath = os.path.join(path, file)
            if os.path.isdir(filePath):
                fileNum = fileNum + self.traverseDir(filePath)
            else:
                fileNum = fileNum + 1
                fileMD5 = self.getFileMD5(filePath)
                print("{}:{}".format(filePath, fileMD5))
        return fileNum

    def printRepeatFile(self, path):
        fileNum, repeatFileNum = 0, 0
        for file in os.listdir(path):
            filePath = os.path.join(path, file)
            if os.path.isdir(filePath):
                fileNum_, repeatFileNum_ = self.printRepeatFile(filePath)
                fileNum = fileNum + fileNum_
                repeatFileNum = repeatFileNum + repeatFileNum_
            else:
                fileNum = fileNum + 1
                fileMD5 = self.getFileMD5(filePath)
                if fileMD5 in self.fileMD5Map:
                    print("{}:{}-{}".format(fileMD5, self.fileMD5Map[fileMD5], filePath))
                    repeatFileNum = repeatFileNum + 1
                else:
                    self.fileMD5Map[fileMD5] = filePath
        return fileNum, repeatFileNum


def main():
    path = "D:\\Downloads"
    fileNum, repeatFileNum = 0, 0
    fileTool = FileTool()
    # fileNum = fileTool.moveFileByMtime(path)
    # fileNum = fileTool.traverseDir(path)
    fileNum, repeatFileNum = fileTool.printRepeatFile(path)
    print("fileNum:{}, repeatFileNum:{}".format(fileNum, repeatFileNum))


if __name__ == "__main__":
    main()
