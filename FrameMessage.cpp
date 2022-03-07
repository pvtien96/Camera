#include "FrameMessage.h"
#include "QDebug"

FrameMessage::FrameMessage(uint16 dataLength)
{
    this->length = dataLength + 3; //Bytes: length=2, type=1, dataLength=2, data=?
    this->type = MSG_TYPE::FRAME;
}

FrameMessage::~FrameMessage()
{
}

char *FrameMessage::getData() const
{
    return this->data;
}

void FrameMessage::setData(char *data)
{
    this->data = data;
}

int FrameMessage::serialToData(char *dest, int length)
{
    if (length < 1)
        return MSG_RETURN::FAIL;
    memcpy_s(dest, length, data, this->length-3);

    return MSG_RETURN::SUCCESS;
}

int FrameMessage::parseFromData(char *mesData, int mesLen)
{
    if (mesLen < 1)
        return MSG_RETURN::FAIL;
    this->data = new char[mesLen];
    memcpy_s(data, mesLen, mesData, mesLen);

    return MSG_RETURN::SUCCESS;
}
