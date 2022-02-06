#ifndef HUFFMAN_H
#define HUFFMAN_H

#define interface struct
typedef unsigned char byte;

interface IInputStream {
	// Возвращает false, если поток закончился
	virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
	virtual void Write(byte value) = 0;
};

#endif //HUFFMAN_H