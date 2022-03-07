// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHandler.h"

BaseHandler::BaseHandler()
{
	message = nullptr;
}

BaseHandler::~BaseHandler()
{
}

void BaseHandler::setMessage(BaseMessage * messageRef)
{
	this->message = messageRef;
}
