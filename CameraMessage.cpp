#include "CameraMessage.h"

CameraMessage::CameraMessage()
{
    this->length = 4;
    this->type = MSG_TYPE::CAMERA;
    this->value = CAMERA_TYPE::CAMERA_STOP;
}

CameraMessage::~CameraMessage()
{
}

void CameraMessage::setValue(uint8 value)
{
    this->value = value;
}

uint8 CameraMessage::getValue()
{
    return this->value;
}

int CameraMessage::serialToData(char *dest, int length)
{
    if (length < 1)
        return MSG_RETURN::FAIL;

    memcpy_s(dest, length, (char *)&value, 1);

    return 1;
}

int CameraMessage::parseFromData(char *mesData, int mesLen)
{
    if (mesLen < 1)
        return MSG_RETURN::FAIL;
    uint8 val = 0;
    memcpy_s((char *)&val, 1, mesData, 1);
    this->setValue(val);
    return MSG_RETURN::SUCCESS;
}
