#include "CameraHandler.h"
#include "QDebug"
#include "transporter.h"

CameraHandler::CameraHandler()
{

}

void CameraHandler::handle()
{
    if (!message)
        {
            qDebug() << "CameraHandler: message is null";
            return;
        }

        if (message->getType() != MSG_TYPE::CAMERA)
        {
            qDebug() << "CameraHandler: cannot process message with type: " << message->getType();
            return;
        }

        CameraMessage *msg = (CameraMessage *)message;
        emit Transporter::getInstance()->sigCamera(msg->getValue());
        message = nullptr;
}
