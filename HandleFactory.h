// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BaseHandler.h"
#include "constant.h"

/**
 * 
 */
class  HandleFactory
{
public:

	HandleFactory();
	~HandleFactory();
	static HandleFactory *getInstance();
	BaseHandler *createHandler(uint8 type);

private:

	static HandleFactory *instance;
};
