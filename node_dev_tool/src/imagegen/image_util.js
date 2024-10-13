
const path = require('path');
const sharp = require('sharp');

/**
 * 画像を rgb565 形式のソースコードに変換
 * @param input
 * @returns {Promise<string>}
 */
async function convert565(input) {
  // 名前を抽出
  const fileName = path.basename(input);
  const name = path.basename(input).split(".").shift();
  const className = name.replace(/(?:^|_)([a-z])/g, (_match, letter) => letter.toUpperCase());

  // バッファの取得
  const { data, info } = await sharp(input)
    .removeAlpha()
    .raw()
    .toBuffer({ resolveWithObject: true });

  // データの生成
  const res = [];
  for (let i = 0; i < data.length; i += 3) {
    const r = data[i] >> 3;
    const g = data[i + 1] >> 2;
    const b = data[i + 2] >> 3;
    const rgb565 = (r << 11) | (g << 5) | b;
    // little endian形式に変換するために、上位バイトと下位バイトを入れ替える
    const rgb565le = ((rgb565 & 0xFF) << 8) | ((rgb565 >> 8) & 0xFF);
    res.push(`0x${rgb565le.toString(16).padStart(4, '0').toUpperCase()}`);
  }

  // テンプレートに流し込んで返却
  return `// {{FILE_NAME}}
const uint16_t {{NAME}}Width = {{WIDTH}};
const uint16_t {{NAME}}Height = {{HEIGHT}};
const unsigned short {{NAME}}[{{DATA_LENGTH}}] PROGMEM = {{{DATA}}};
class {{CLASS_NAME}}Bitmap : public hsbs::Bitmap565 { public: {{CLASS_NAME}}Bitmap(): hsbs::Bitmap565({{NAME}}, {{NAME}}Width, {{NAME}}Height) {} };
`
    .split('{{FILE_NAME}}').join(fileName)
    .split('{{NAME}}').join(name)
    .split('{{CLASS_NAME}}').join(className)
    .split('{{WIDTH}}').join(info.width)
    .split('{{HEIGHT}}').join(info.height)
    .split('{{DATA_LENGTH}}').join(res.length)
    .split('{{DATA}}').join(res.join(', '));

}

/**
 * 画像を 1bit (1バイトに押し込んだデータ) 形式のソースコードに変換
 * @param {*} input 
 * @returns 
 */
async function convertMono(input) {
  // 名前を抽出
  const fileName = path.basename(input);
  const name = path.basename(input).split(".").shift();
  const className = name.replace(/(?:^|_)([a-z])/g, (_match, letter) => letter.toUpperCase());

  // バッファの取得
  const { data, info } = await sharp(input)
    .removeAlpha()
    .greyscale()
    .raw()
    .toBuffer({ resolveWithObject: true });

  // データの生成
  const { width, height } = info;
  const widthInBytes = Math.ceil(width / 8);
  const bitmap = new Buffer.alloc(widthInBytes * height).fill(0);
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      const index = y * width + x;
      if (data[index] > 0) { // 閾値を基にビットをセット
        const byteIndex = y * widthInBytes + Math.floor(x / 8);
        const bitPosition = 7 - (x % 8);
        bitmap[byteIndex] |= (1 << bitPosition);
      }
    }
  }
  const res = Array.from(bitmap).map((num) => (`0x${num.toString(16).padStart(2, '0').toUpperCase()}`));

  // テンプレートに流し込んで返却
  return `// {{FILE_NAME}}
const uint16_t {{NAME}}Width = {{WIDTH}};
const uint16_t {{NAME}}Height = {{HEIGHT}};
const uint8_t {{NAME}}[{{DATA_LENGTH}}] PROGMEM = {{{DATA}}};
class {{CLASS_NAME}}Bitmap : public hsbs::BitmapMono { public: {{CLASS_NAME}}Bitmap(): hsbs::BitmapMono({{NAME}}, {{NAME}}Width, {{NAME}}Height) {} };
`
    .split('{{FILE_NAME}}').join(fileName)
    .split('{{NAME}}').join(name)
    .split('{{CLASS_NAME}}').join(className)
    .split('{{WIDTH}}').join(width)
    .split('{{HEIGHT}}').join(height)
    .split('{{DATA_LENGTH}}').join(res.length)
    .split('{{DATA}}').join(res.join(', '));
}

/**
 * 画像ファイルをソースファイルに変換
 * @param files
 * @returns {Promise<string>}
 */
async function createImageProgmem(params) {
  const bmp565Files = params.bmp565 || [];
  const bmpBlackFiles = params.bmpBlack || [];
  const array = [
    '#ifndef _IMAGE_PROGMEM_H_INCLUDE_',
    '#define _IMAGE_PROGMEM_H_INCLUDE_',
    '',
    '#include <pgmspace.h>',
    '#include <stdint.h>',
    '#include "hsbs/display/BitmapMono.h"',
    '#include "hsbs/display/Bitmap565.h"',
    '',
    'namespace Img {',
    ''
  ];
  array.push("//----------------------------------------------------------");
  array.push("// Bitmap Black");
  array.push("//----------------------------------------------------------");
  array.push("namespace Mono {");
  for (let i = 0; i < bmpBlackFiles.length; i++) {
    array.push(await convertMono(bmpBlackFiles[i]));
  }
  array.push('} // end namespace Mono');
  array.push("//----------------------------------------------------------");
  array.push("// Bitmap Color RGB565 (little endian)");
  array.push("//----------------------------------------------------------");
  array.push("namespace Rgb565 {");
  for (let i = 0; i < bmp565Files.length; i++) {
    array.push(await convert565(bmp565Files[i]));
  }
  array.push('} // end namespace Rgb565');
  array.push('} // end namespace Img');
  array.push('#endif');
  return array.join('\n');
}

exports.createImageProgmem = createImageProgmem;
