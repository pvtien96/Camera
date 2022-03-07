#ifndef CAMERAHANDER_H
#define CAMERAHANDER_H
#include "BaseHandler.h"
#include "CameraMessage.h"

class CameraHandler : public BaseHandler
{
public:
    CameraHandler();
    void handle() override;
};

#endif // CAMERAHANDER_H
