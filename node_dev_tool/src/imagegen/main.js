
const path = require('path');
const fs = require("fs");
const { createImageProgmem } = require("./image_util");


(async function () {

  // 第一引数
  const inputDir = process.argv[2];
  const outputDir = process.argv[3] || inputDir;

  const filterImg = (file) => {
    const ext = path.extname(file).toLowerCase();
    if (ext === '.png') return true;
    if (ext === '.jpg') return true;
    if (ext === '.bmp') return true;
    return false;
  };

  // RGB 565
  const bmp565 = fs.readdirSync(path.join(inputDir, "bmp_color565"))
    .filter(filterImg)
    .map((p) => path.join(path.join(inputDir, "bmp_color565"), p));

  // 黒の単色
  const bmpBlack = fs.readdirSync(path.join(inputDir, "bmp_black"))
    .filter(filterImg)
    .map((p) => path.join(path.join(inputDir, "bmp_black"), p));

  fs.writeFileSync(
    path.join(outputDir, 'image_progmem.h'),
    await createImageProgmem({ bmp565, bmpBlack })
  );


})();