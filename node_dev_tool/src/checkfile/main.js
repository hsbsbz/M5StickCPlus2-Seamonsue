

const { getFilesRecursive, checkIfndefSyntax, checkVirtualDestructor } = require("../util");


const dirList = [
  '../lib/hsbslib',
  '../src',
];

dirList.forEach((parentPath) => {
  const headerFileList = getFilesRecursive(parentPath, ['h']);
  // ヘッダーのマクロ名をチェック
  headerFileList.forEach((filePath) => {
    checkIfndefSyntax(parentPath, filePath);
  });
  // デストラクタの virtual 漏れをコンソールにだす
  headerFileList.forEach((filePath) => {
    checkVirtualDestructor(parentPath, filePath);
  });
});