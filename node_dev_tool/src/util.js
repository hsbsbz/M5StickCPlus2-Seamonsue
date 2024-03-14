
const path = require('path');
const fs = require("fs");
const { type } = require('os');
const { execFile } = require('child_process');

/**
 * ファイルを列挙する
 * @param {} dirPath 
 * @returns 
 */
exports.getFilesRecursive = function getFilesRecursive(dirPath, extList) {
  let files = fs.readdirSync(dirPath);
  let filePaths = [];
  files.forEach(function (file) {
    if (fs.statSync(dirPath + "/" + file).isDirectory()) {
      filePaths = filePaths.concat(getFilesRecursive(dirPath + "/" + file, extList));
    } else {
      filePaths.push(path.join(dirPath, "/", file));
    }
  });
  extList = (typeof extList === 'string') ? [extList] : (extList || []);
  if (extList.length) {
    filePaths = filePaths.filter(filterByExt(extList));
  }
  return filePaths;
};

/**
 * 拡張子でフィルター
 */
function filterByExt(extList) {
  return function (filePath) {
    return extList.includes(path.extname(filePath).substring(1));
  }
}

/**
 * ファイルから行ごとの文字列を取得
 * @param {*} lines 
 * @returns 
 */
function getFileLines(filePath) {
  return fs.readFileSync(filePath, 'utf8').split('\n');
}

/**
 * キーワードから始まる行のキーワード以降を抽出
 * @param {*} lines 
 * @param {*} keyword 
 * @returns 
 */
function getValueByStartsWith(lines, keyword) {
  return lines
    .filter((line) => (line.trim()))
    .filter((line) => (line.startsWith(keyword)))
    .map((line) => (line.substr(line.indexOf(keyword) + keyword.length).trim()));
}


exports.checkIfndefSyntax = function (parentPath, filePath) {
  const macroName = '_' + path
    .relative(parentPath, filePath)
    .replace(/(?<=[a-z])(?=[A-Z])/g, '_')
    .toUpperCase()
    .split('\\')
    .join('__')
    .split('.')
    .shift()
    .toUpperCase()
    .trim() + '_H_INCLUDE_';

  const lines = getFileLines(filePath);

  console.assert(
    macroName == getValueByStartsWith(lines, '#ifndef'),
    `\n'#ifndef' macro name invalid > "${filePath}"`,
    `\n Correct: "${macroName}"\n`
  );

  console.assert(
    macroName == getValueByStartsWith(lines, "#define"),
    `\n'#define' macro name invalid > "${filePath}"`,
    `\n Correct: "${macroName}"\n`
  );

}


exports.checkVirtualDestructor = function (parentPath, filePath) {
  const lines = getFileLines(filePath);
  lines.filter((line) => {
    return !!(line.match(/\~[0-9a-zA-Z].*\(\)/g) || []).join('').trim();
  })
    .forEach((line) => {
      if (!line.includes('virtual')) {
        console.log(line);
      }
    });
}