
#include "BitUtil.h"

#ifndef __BA_BIT__bufferH__
#define __BA_BIT__bufferH__

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <vector>
#include <iostream>

#define DEFAULT_SIZE 1024

// MARK: 大小端
// <读写字节流不影响，但是要类型化需要关注大小端>
#define BA_BIG_ENDIAN       4321 // __DARWIN_BIG_ENDIAN
#define BA_LITTLE_ENDIAN    1234 // __DARWIN_LITTLE_ENDIAN

namespace binart {
    class BitIterator;

    // MARK: 比特缓冲
class BitBuffer {
    friend class BitIterator;
    // typedef BitIterator iterator;
    // typedef const BitIterator const_iterator;

    private:
        /*
         * Private type definitions
         */
        typedef uint8_t ubyte_t;
        typedef std::vector<ubyte_t> bytes_t;

        /*
         * Array of bytes that handles the storage of all bytes
         * for this class
         */
        bytes_t _buffer;
        uint32_t _pos;
        uint8_t _bitIndex;
        uint32_t _endian;

        /*
         * Appends the data parameter's bits to the buffer (bytes array)
         */
        void _writeBits(const uint32_t data, const size_t bits) {
            static const uint8_t bits_per_byte = 8;

            if (_bitIndex == 0 && bits > 0) {
                _buffer.push_back(0);
            }

            // Not enough bits in this byte to write all the bits required
            if (_bitIndex + bits > bits_per_byte) {
                const uint8_t remainder_bits = _bitIndex + bits - bits_per_byte;
                const uint32_t remainder_value = (data & (0xFF >> (bits_per_byte - remainder_bits)));

                _buffer[_pos] |= (data >> remainder_bits);

                _bitIndex = 0;
                _pos++;

                // Process the remaining bits in the next byte
                _writeBits(remainder_value, remainder_bits);
                
                return;
            }

            const uint8_t offset = bits_per_byte - _bitIndex - bits;
            _buffer[_pos] |= (data << offset);
            _bitIndex += bits;

            if (_bitIndex == bits_per_byte) {
                _bitIndex = 0;
                _pos++;
            }
        }

        template <typename T>
        inline void _write(const T& data) {
            size_t bytes = sizeof(T);

            write_bytes_(data, bytes);
        }

        template <typename T>
        inline void write_bytes_(const T& data, size_t bytes) {
            const uint32_t temp = static_cast<uint32_t>(data);

            // If beginning of a byte, then it can just push bytes
            if (_bitIndex == 0) {
                int i = bytes - 1;
                while (i >= 0) {
                    _buffer.push_back(static_cast<ubyte_t>((temp >> (i * 8))));
                    --i;
                }

                _pos += bytes;
                return;
            }

            // If the current byte has a few bits written to it already, but
            // not all eight bits, then it must process the data bit by bit
            _writeBits(data, bytes * 8);
        }

        uint32_t _readBits(const size_t bit_index, const size_t num_bits, size_t ret) const {
            if (bit_index + num_bits > _buffer.size() * 8) {
                throw;
            }

            uint32_t pos = static_cast<uint32_t>(bit_index / 8);
            uint8_t _bitIndexstart = static_cast<uint8_t>(bit_index - (pos * 8));
            uint32_t _bitIndexend = _bitIndexstart + num_bits - 1;

            // If we exceeded the number of bits that can be read
            // from this byte, then move to the next byte and
            // continue reading the bits from that byte
            if (_bitIndexend >= 8) {
                ubyte_t byte = _buffer[pos];
                int offset = 8 - num_bits - _bitIndexstart;
                if (offset < 0) {
                    ubyte_t mask = (0xFF >> _bitIndexstart);
                    byte &= mask;
                } else {
                    byte >>= offset;
                }

                //ret += byte;
                uint32_t bits_read = 8 - _bitIndexstart;
                uint32_t p = num_bits - bits_read;
                offset = 0;
                while (p < num_bits) {
                    ret += static_cast<uint32_t>(((byte >> offset) & 0x01) * pow(2, p));
                    ++p;
                    ++offset;
                }

                return _readBits(bit_index + bits_read, num_bits - bits_read, ret);
            }


            // Remove everything in front of the starting bit
            ubyte_t byte = _buffer[pos];
            if (_bitIndexstart > 0) {
                ubyte_t mask = ~(0xFF << (8 - _bitIndexstart));
                byte &= mask;
            }

            byte >>= (8 - num_bits - _bitIndexstart);
            ret += static_cast<uint32_t>(byte);

            return ret;
        }

        inline uint32_t _readBytes(const size_t byte_index, const size_t num_bytes) {
            if (byte_index + num_bytes > _buffer.size()) {
                throw;
            }

            return _readBits(byte_index * 8, num_bytes * 8, 0);
        }

    // MARK: - Public
    public:
        /**
         * 构造方法
         */
        BitBuffer(const size_t size = DEFAULT_SIZE): _pos(0), _bitIndex(0), _endian(BIG_ENDIAN) { _buffer.reserve(size); };
        BitBuffer(const ubyte_t *data): _pos(0), _bitIndex(0), _endian(BIG_ENDIAN) { _buffer = bytes2vector(data); };

        virtual ~BitBuffer() {};

        /*
         * The methods below write the data to the byte array
         */
        template <typename T>
        inline void write(const T& data) {
            _write<T>(data);
        }

        template <typename T>
        inline void write_bits(const T& data, const size_t num_bits) {
            _writeBits(static_cast<uint32_t>(data), num_bits);
        }

        void write_byte(const ubyte_t& data) { _write<ubyte_t>(data); };
        void write_char(const char& data) { _write<char>(data); };
        void write_bool(const bool& data) { _write<bool>(data); };
        void write_short(const short& data) { _write<short>(data); };
        void write_int(const uint32_t& data) { _write<uint32_t>(data); };
        void write_long(const uint64_t& data) { _write<uint64_t>(data); };

        /*
         * Returns the value of the bytes starting at byte_index and
         * ending at (byte_index + num_bytes - 1)
         *
         * For example:
         *      bit_buffer bf;
         *      // If two bytes were written to the buffer
         *      bf.write_byte(10);
         *      bf.write_int(20); // 4 bytes
         *
         *      std::cout << bf.read_byte(0) << std::endl;   // Outputs 10
         *      std::cout << bf.read_bytes(1, 4) << std::endl;   // Outputs 20
         */
        uint8_t read_byte(const size_t byte_index) { return _readBytes(byte_index, 1); };
        uint32_t read_bytes(const size_t byte_index, const size_t num_bytes) { return _readBytes(byte_index, num_bytes); };

        /*
         * Returns the value of the bits starting at bit_index and
         * ending at (bit_index + num_bits - 1)
         *
         * For example:
         *      bit_buffer bf;
         *      // If two bytes were written to the buffer
         *      bf.write_byte(10);
         *      bf.write_byte(8);
         *      bf.write_bits(5, 3);
         *
         *      std::cout << bf.read_bits(0, 4) << std::endl;   // Outputs 10
         *      std::cout << bf.read_bits(4, 4) << std::endl;   // Outputs 8
         *      std::cout << bf.read_bits(8, 3) << std::endl;   // Outputs 5
         */
        uint8_t read_bit(const size_t bit_index) { return _readBits(bit_index, 1, 0); };
        uint32_t read_bits(const size_t bit_index, const size_t num_bits) { return _readBits(bit_index, num_bits, 0); };

        inline const bytes_t get_bytes() const { return _buffer; }
        // BitIterator create_iter() const { return BitIterator(*this); };


        /* 
         * For each loop iterator
         */
        // iterator begin() { return BitIterator(*this); };
        // const_iterator begin() const { return BitIterator(*this); };
        // iterator end() { return BitIterator(*this, _buffer.size() * 8); };
        // const_iterator end() const { return BitIterator(*this, _buffer.size() * 8); };

        /*
         * Operator overrides
         */
        bool operator==(const BitBuffer &other) {
            return _buffer == other._buffer;
        }

        bool operator!=(const BitBuffer &other) {
            return _buffer != other._buffer;
        }
};

// MARK: 比特迭代器
class BitIterator {
    private:
        BitBuffer _buffer;
        size_t _bitIndex;

    public:
        explicit BitIterator(const BitBuffer& buffer) :
            _buffer(buffer), _bitIndex(0)
        {}

        BitIterator(const BitBuffer& buffer, const size_t bit_index) :
            _buffer(buffer), _bitIndex(bit_index)
        {}

        inline uint8_t current_bit() const {
            return static_cast<uint8_t>(_buffer._readBits(_bitIndex, 1, 0));
        }

        /*
         * Operator overrides
         */
        BitIterator &operator++() {
            ++_bitIndex;

            return *this;
        }

        BitIterator operator++(int) {
            BitIterator temp = *this;
            ++*this;

            return temp;
        }

        bool operator==(const BitIterator &other) {
            return _bitIndex == other._bitIndex;
        }

        bool operator!=(const BitIterator &other) {
            return _bitIndex != other._bitIndex;
        }

        uint8_t operator*() {
            return current_bit();
        }

        uint8_t operator*() const {
            return current_bit();
        }
    };
}

#endif // __BA_BIT__bufferH__
