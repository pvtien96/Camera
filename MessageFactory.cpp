// Fill out your copyright notice in the Description page of Project Settings.
#include "MessageFactory.h"
#include "BaseMessage.h"
#include "CameraMessage.h"

MessageFactory *MessageFactory::instance = nullptr;

MessageFactory::MessageFactory(void)
{
}

MessageFactory::~MessageFactory(void)
{
}

MessageFactory *MessageFactory::getInstance()
{
	if (instance == nullptr)
		instance = new MessageFactory();

	return instance;
}

BaseMessage *MessageFactory::createMessage(uint8 type)
{
	switch (type)
	{
    case MSG_TYPE::CAMERA:
        return new CameraMessage();

	default:
		return nullptr;
	}

	return nullptr;
}
