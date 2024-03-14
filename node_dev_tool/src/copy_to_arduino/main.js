
const path = require('path');
const fs = require("fs");
const archiver = require('archiver');
const { getFilesRecursive } = require("../util");
const TEMP_PATH = "../arduino";
const TEMP_PROJECT_PATH = "../arduino/seamonsue";
const TEMP_PROJECT_SRC_PATH = "../arduino/seamonsue/src";
const LIB_DIR = "../lib/";
const SRC_DIR = "../src/";


/**
 * テンポラリーにソースファイルを複製
 */
function copyFilesToTempDir() {
  const srcFileList = [];
  fs.readdirSync(LIB_DIR)
    .map((filePath) => (path.join(LIB_DIR, filePath)))
    .filter((filePath) => (fs.statSync(filePath).isDirectory()))
    .concat([SRC_DIR])
    .forEach((parentDir) => {
      getFilesRecursive(parentDir, ['h', 'hpp', 'cpp'])
        .forEach(
          (p) => {
            srcFileList.push({
              i: path.join(process.cwd(), p),
              o: path.join(TEMP_PROJECT_SRC_PATH, path.relative(parentDir, p))
            });
          }
        )
    });
  srcFileList.forEach((object) => {
    const dir = fs.statSync(object.i).isDirectory() ? object.o : path.join(object.o, '../');
    if (!fs.existsSync(dir)) fs.mkdirSync(dir, { recursive: true });
    fs.copyFileSync(object.i, object.o);
  });
}

/**
 * lib も src もすべて Arduino プロジェクトの src にまとめた後で、パスを相対パスに置換する
 */
function replaceIncludePath() {
  const libNameList = [];
  const libDirList = fs.readdirSync(LIB_DIR)
    .map((filePath) => (path.join(LIB_DIR, filePath)))
    .filter((filePath) => (fs.statSync(filePath).isDirectory()));
  libDirList.forEach((dir) => {
    fs.readdirSync(dir)
      .filter((filePath) => (fs.statSync(path.join(dir, filePath)).isDirectory()))
      .forEach((p) => {
        libNameList.push(p);
      });
  });
  const srcList = getFilesRecursive(TEMP_PROJECT_SRC_PATH, ['h', 'hpp', 'cpp']);
  while (srcList.length) {
    const file = srcList.shift();
    let content = fs.readFileSync(file, 'utf8');
    const lines = content.split('\n');
    let includeLines = lines.filter(line => line.trim().startsWith('#include'));
    includeLines = includeLines.map((str) => (str.trim()));
    includeLines = includeLines.map((str) => (str.split(' ').pop() || str));
    includeLines = includeLines.filter((str) => (str.indexOf("<") !== 0));
    includeLines = includeLines.map((str) => (str.split('"').join('')));
    includeLines.forEach((str) => {
      libNameList.forEach((libName) => {
        if (str.indexOf(libName) === 0) {
          const keyword = str;
          const replaceWord = path.relative(
            path.join(file, "../"),
            path.join(TEMP_PROJECT_SRC_PATH, str)
          );
          content = content.split(keyword).join(replaceWord);
        }
      });
    })
    fs.writeFileSync(file, content, 'utf8');
  }
}

/**
 * Ino ファイルを作成
 */
function createInoFile() {
  const mainCppPath = path.join(TEMP_PROJECT_SRC_PATH, "main.cpp");
  const inoPath = path.join(path.join(TEMP_PROJECT_SRC_PATH, "../"), "seamonsue.ino");
  fs.renameSync(mainCppPath, inoPath);
  let content = fs.readFileSync(inoPath, 'utf8');
  const lines = content.split('\n');
  let includeLines = lines.filter(line => line.trim().startsWith('#include'));
  includeLines = includeLines.map((str) => (str.trim()));
  includeLines = includeLines.map((str) => (str.split(' ').pop() || str));
  includeLines = includeLines.filter((str) => (str.indexOf("<") !== 0));
  includeLines = includeLines.map((str) => (str.split('"').join('')));
  includeLines.forEach((str) => {
    if (str.indexOf(str) !== 'src') {
      content = content.split(str).join(path.join("src", str));
    }
  })
  fs.writeFileSync(inoPath, content, 'utf8');
}

/**
 * Zipに圧縮してテンポラリーを削除
 */

function createZipFile() {
  const inputDir = path.join(TEMP_PATH);
  const outputPath = path.join(path.join(TEMP_PATH, "../arduino_seamonsue.zip"));
  const output = fs.createWriteStream(outputPath);
  const archive = archiver('zip', { zlib: { level: 9 } });
  output.on('close', function () {
    if (fs.existsSync(TEMP_PATH)) {
      fs.rmSync(TEMP_PATH, { recursive: true });
    }
  });
  output.on('end', function () {
    console.log('Data has been drained');
  });
  archive.on('warning', function (err) {
    if (err.code === 'ENOENT') {
      console.log(err);
    } else {
      throw err;
    }
  });
  archive.on('error', function (err) {
    throw err;
  });
  archive.pipe(output);
  archive.directory(inputDir, false);
  archive.finalize();
}


copyFilesToTempDir();
replaceIncludePath();
createInoFile();
createZipFile();