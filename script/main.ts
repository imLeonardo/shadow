import * as fs from 'fs';

function walk(path:string, fileName:string) {
    const filePath = path + '/' + fileName;
    const states = fs.statSync(filePath);
    //是否是文件夹
    if (states.isDirectory()) {
        getSpace(filePath);
    } else {
        const fileNameArray = fileName.split("-");
        const fileNumber = fileNameArray[0].slice(0, 3);
        const name = fileNameArray[0].slice(3, 6);
        let newFilePath = path + "/" + name + "-" + fileNumber + "-" + fileNameArray[1];
        if (fileNameArray[2]) {
            newFilePath += "-" + fileNameArray[2];
        }
        console.log(newFilePath);
        fs.rename(filePath, newFilePath, function (ret, err) {
            console.error(err);
        });
    }
}

function getSpace(path:string) {
    //读取文件夹下内容
    let files = fs.readdirSync(path);
    //遍历文件
    files.forEach(function (fileName:any, index:any) {
        walk(path, fileName)
    });
}

getSpace("D:\\Downloads\\小说\\三体\\三体丨中央广播电视总台多人有声\\wma");
