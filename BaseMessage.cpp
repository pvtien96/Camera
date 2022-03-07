// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMessage.h"

BaseMessage::BaseMessage()
{
}

BaseMessage::~BaseMessage()
{
}

uint16 BaseMessage::getLeng()
{
    return this->length;
}

uint8 BaseMessage::getType()
{
	return this->type;
}

void BaseMessage::setLeng(uint16 length)
{
    this->length = length;
}

void BaseMessage::setType(uint8 typeValue)
{
	this->type = typeValue;
}
