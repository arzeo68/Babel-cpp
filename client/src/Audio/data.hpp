//
// Created by alexis on 28/09/2020.
//

#ifndef BABEL_DATA_HPP
#define BABEL_DATA_HPP

#include <vector>
#include <ctime>

namespace Babel
{
    namespace Audio
    {
        class soundEncoded
        {
            public:
            soundEncoded(int size = 0, std::vector<unsigned char> buffer = {}) {

            }
            int getSize() const
            {
                return _size;
            }

            void setSize(int size)
            {
                _size = size;
            }

            std::vector<unsigned char> &getEncodedBuffer()
            {
                return _encodedBuffer;
            }

            void setEncodedBuffer(std::vector<unsigned char> &encodedBuffer)
            {
                _encodedBuffer = encodedBuffer;
            }

            void resizeBuffer(int newSize)
            {
                _encodedBuffer.resize(newSize);
            }

            private:
            int _size;
            std::vector<unsigned char> _encodedBuffer;
        };

        class soundDecoded
        {
            public:

            soundDecoded(int size = 0, std::vector<float> soundBuffer = {}): _size(size), _soundBuffer(soundBuffer) {

            };

            ~soundDecoded() {
                _soundBuffer.clear();
            };

            int getSize() const {
                return _size;
            };

            void setSize(int size) {
                _size = size;
            };

            std::vector<float> &getSoundBuffer(){
                return _soundBuffer;
            };

            void setSoundBuffer(std::vector<float> &soundBuffer) {
                _soundBuffer = soundBuffer;
            };

            void resizeBuffer(int newSize)
            {
                _soundBuffer.resize(newSize);
            }

            float *getData()
            {
                return _soundBuffer.data();
            }

            private:
            int _size;
            std::vector<float> _soundBuffer;
        };
        #pragma pack(push,1)
        typedef struct packageAudio_s {
            uint16_t magicByte;
            uint16_t idSender;
            std::time_t timestamp;
            unsigned char voice[960];
        } packageAudio_t;
        #pragma pack(pop)
    }
}


#endif //BABEL_DATA_HPP
