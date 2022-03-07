// Fill out your copyright notice in the Description page of Project Settings.

#include "HandleFactory.h"
#include "BaseMessage.h"
#include "CameraHandler.h"
#include "QDebug"

HandleFactory *HandleFactory::instance = nullptr;

HandleFactory::HandleFactory()
{
}


HandleFactory::~HandleFactory()
{
}

HandleFactory *HandleFactory::getInstance()
{
	if (instance == nullptr)
		instance = new HandleFactory();

	return instance;
}

BaseHandler *HandleFactory::createHandler(uint8 type)
{
	switch (type)
	{
    case MSG_TYPE::CAMERA:
        return new CameraHandler();
	default:
		return nullptr;
	}

	return nullptr;
}
