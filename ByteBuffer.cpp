// Fill out your copyright notice in the Description page of Project Settings.

#include "ByteBuffer.h"
#include <algorithm>
#include <cassert>
#include <cstring>


static const int DEFAULT_SIZE = 4096;

ByteBuffer::ByteBuffer() 
{
	start_ = 0;
	end_ = 0;
	size_ = DEFAULT_SIZE;
	bytes_ = new char[size_];
}

ByteBuffer::ByteBuffer(const char *bytes, size_t len) 
{
	start_ = 0;
	end_ = len;
	size_ = len;
	bytes_ = new char[size_];
	memcpy_s(bytes_, size_, bytes, end_);
}

ByteBuffer::~ByteBuffer() 
{
	delete[] bytes_;
}

bool ByteBuffer::ReadUInt8(uint8 &val) 
{
	return ReadBytes(reinterpret_cast<char *>(&val), 1);
}

bool ByteBuffer::ReadUInt16(uint16 &val) 
{
	return ReadBytes(reinterpret_cast<char *>(&val), 2);
}

bool ByteBuffer::ReadUInt32(uint32 &val) 
{
	return ReadBytes(reinterpret_cast<char *>(&val), 4);
}

bool ByteBuffer::ReadFloat(float &val) 
{
	return ReadBytes(reinterpret_cast<char *>(&val), 4);
}

bool ByteBuffer::ReadString(std::string &val, size_t len) 
{
	if (len > Length()) 
	{
		return false;
	}
	else 
	{
		val.append(bytes_ + start_, len);
		start_ += len;
		return true;
	}
}

bool ByteBuffer::ReadBytes(char *val, size_t len) 
{
	if (len > Length()) 
	{
		return false;
	}
	else 
	{
		memcpy_s(val, len, bytes_ + start_, len);
		start_ += len;
		return true;
	}
}

bool ByteBuffer::PeekUInt16(uint16 &val) 
{
	return PeekBytes(reinterpret_cast<char *>(&val), 2);
}

bool ByteBuffer::PeekUInt8(uint8 &val)
{
	return PeekBytes(reinterpret_cast<char *>(&val), 1);
}

bool ByteBuffer::PeekBytes(char *val, size_t len) 
{
	if (len > Length()) 
	{
		return false;
	}
	else 
	{
		memcpy_s(val, len, bytes_ + start_, len);
		return true;
	}
}


void ByteBuffer::WriteUInt8(uint8 val) 
{
	WriteBytes(reinterpret_cast<const char *>(&val), 1);
}

void ByteBuffer::WriteUInt16(uint16 val) 
{
	WriteBytes(reinterpret_cast<const char*>(&val), 2);
}

void ByteBuffer::WriteUInt32(uint32 val) 
{
	WriteBytes(reinterpret_cast<const char*>(&val), 4);
}

void ByteBuffer::WriteFloat(float val) 
{
	WriteBytes(reinterpret_cast<const char *>(&val), 4);
}

void ByteBuffer::WriteString(const std::string &val) 
{
	WriteBytes(val.c_str(), val.size());
}

void ByteBuffer::WriteBytes(const char *val, size_t len) 
{
	if (Length() + len > Capacity())
		Resize(Length() + len);

	memcpy_s(bytes_ + end_, len, val, len);
	end_ += len;
}

void ByteBuffer::Resize(size_t size) 
{
	if (size > size_)
		size = _max(size, 3 * size_ / 2);

	size_t len = _min(end_ - start_, size);
	char* new_bytes = new char[size];
	memcpy_s(new_bytes, len, bytes_ + start_, len);
	delete[] bytes_;

	start_ = 0;
	end_ = len;
	size_ = size;
	bytes_ = new_bytes;
}

void ByteBuffer::Shift(size_t size) 
{
	if (size > Length())
		return;

	end_ = Length() - size;
	memmove(bytes_, bytes_ + start_ + size, end_);
	start_ = 0;
}
