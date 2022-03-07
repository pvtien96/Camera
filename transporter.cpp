#include "transporter.h"

Transporter *Transporter::instance = nullptr;

Transporter::Transporter()
{

}

Transporter *Transporter::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Transporter();
    }
    return instance;
}
