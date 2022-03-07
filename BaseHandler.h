// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



class BaseMessage;
/**
 * 
 */
class BaseHandler
{
public:
	BaseHandler();	
	~BaseHandler();
	void setMessage(BaseMessage *message);
	virtual void handle() = 0;

protected:
	BaseMessage *message;
};
