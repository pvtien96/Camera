#ifndef FRAMEMESSAGE_H
#define FRAMEMESSAGE_H
#include "BaseMessage.h"

class FrameMessage : public BaseMessage
{
public:
    FrameMessage(uint16 dataLength);
    ~FrameMessage();

    char *getData() const;
    void setData(char *data);
    int serialToData(char *dest, int length); // Serial length, type, and private data member, return number of byte
    int parseFromData(char *mesData, int mesLen); // Parse private data member

private:
    char *data;

};

#endif // FRAMEMESSAGE_H
