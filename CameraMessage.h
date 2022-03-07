#ifndef CAMERAMESSAGE_H
#define CAMERAMESSAGE_H
#include "BaseMessage.h"


class CameraMessage : public BaseMessage
{
public:
    CameraMessage();
    ~CameraMessage();
    void setValue(uint8 value);
    uint8 getValue();
    int serialToData(char *dest, int length); // Serial length, type, and private data member, return number of byte
    int parseFromData(char *mesData, int mesLen); // Parse private data member

private:
    uint8 value;
};

#endif // CAMERAMESSAGE_H
