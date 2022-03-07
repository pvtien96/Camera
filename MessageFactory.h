// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ManagerController.h"

class BaseMessage;

class  MessageFactory
{
public:

	MessageFactory();
	~MessageFactory();
	static MessageFactory *getInstance();
    BaseMessage *createMessage(uint8 type);

private:

	static MessageFactory *instance;
};
