// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "constant.h"
#include <string>


/**
 * 
 */
template<class T> inline T _min(T a, T b) { return (a > b) ? b : a; }
template<class T> inline T _max(T a, T b) { return (a < b) ? b : a; }

class  ByteBuffer
{
public:

	ByteBuffer();
	ByteBuffer(const char* bytes, size_t len);
	~ByteBuffer();

	const char* Data() const { return bytes_ + start_; }
	size_t Length() { return end_ - start_; }
	size_t Capacity() { return size_ - start_; }
	void Reset() { end_ = 0; start_ = 0; }

	bool ReadUInt8(uint8 &val);
	bool ReadUInt16(uint16 &val);
	bool ReadUInt32(uint32 &val);
	bool ReadFloat(float &val);
	bool ReadString(std::string &val, size_t len); // append to val
	bool ReadBytes(char *val, size_t len);

	bool PeekUInt16(uint16 &val);
	bool PeekUInt8(uint8 &val);
	bool PeekBytes(char *val, size_t len);

	void WriteUInt8(uint8 val);
	void WriteUInt16(uint16 val);
	void WriteUInt32(uint32 val);
	void WriteFloat(float val);
	void WriteString(const std::string &val);
	void WriteBytes(const char *val, size_t len);

	void Resize(size_t size);
	void Shift(size_t size);

private:

	char* bytes_;
	size_t size_;
	size_t start_;
	size_t end_;
};
