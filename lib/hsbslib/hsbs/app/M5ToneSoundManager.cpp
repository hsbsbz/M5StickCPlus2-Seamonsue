
#include "M5ToneSoundManager.h"

namespace hsbs {

void M5ToneSoundManager::pushTone(float frequency, int duration, int channel) {
  M5ToneSoundQueue *queue = new M5ToneSoundQueue();
  queue->frequency = frequency;
  queue->duration = duration;
  queue->channel = channel;
  queue->stopCurrentSound = true;
  this->_list.push(queue);
}

void M5ToneSoundManager::pushWait(int duration) {
  M5ToneSoundQueue *queue = new M5ToneSoundQueue();
  queue->frequency = 0;
  queue->duration = duration;
  this->_list.push(queue);
}

void M5ToneSoundManager::update() {
  const long now = millis();
  while (this->_list.length() > 0) {
    M5ToneSoundQueue *queue = this->_list.getAt(0);
    if (queue->playing) {
      if (now < queue->endTime) {
        return;
      }
      this->_list.shift();
      delete queue;
    } else {
      queue->playing = true;
      queue->endTime = now + queue->duration;
      if (queue->frequency > 0) {
        M5.Speaker.setChannelVolume(0, this->getVolumeBiasByFrequency(queue->frequency));
        M5.Speaker.tone(queue->frequency, queue->duration, 0, queue->stopCurrentSound);
      }
    }
  }
}

void M5ToneSoundManager::stop() {
  M5.Speaker.stop();
  while (this->_list.length() > 0) {
    delete this->_list.pop();
  }
}

uint8_t M5ToneSoundManager::getVolumeBiasByFrequency(float frequency) {
  // 4400 Hz を中心に音量を小さく（体感的に一番大きく聞こえた周波数）
  float n = (frequency - 4400);
  if (n > 0) {
    // 高音側は +8000 Hz かけて音量を大きく
    n = n / 8000;
    n = n < 0 ? -n : n;                                       // abs
    n = n > 1 ? 1 : n;                                        // 丸め込み
    n = 1 - n;                                                // 反転
    n = hsbs::applyEaseFunction(hsbs::Ease::IN_OUT_CUBIC, n); // イージングによるバイアス（やや急な曲線）
  } else {
    // 低音側は -1000 Hz かけて音量を大きく
    n = n / 1000;
    n = n < 0 ? -n : n;                                      // abs
    n = n > 1 ? 1 : n;                                       //  丸め込み
    n = 1 - n;                                               // 反転
    n = hsbs::applyEaseFunction(hsbs::Ease::IN_OUT_SINE, n); // イージングによるバイアス（緩やかな曲線）
  }
  // 4400 Hz で最大 50% 音量を絞る
  return (uint8_t)(255.0f - n * 128.0f);
}

} // namespace hsbs
