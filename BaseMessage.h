// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "constant.h"
#include "cstring"

enum MSG_RETURN
{
	FAIL = -1,
	SUCCESS = 0
};

enum MSG_TYPE
{
	SPEED = 0,
	RPM,
	ACCELERATE,
	FUEL,
	TIME_OF_DAY,
	RAIN,
	SNOW,
	FOG,
	SYSTEM_STATE,
	CONNECTION_STATE,
	REPLAY_TIME_PERCENT,
	DRIVER_MODE = 50, // 1: Auto, 0: Manual
	LESSON,
	DIRECTION_VIEW,
	B2_INFO, // Inform error and other status when driving in b2 lesson: error, get in lesson, get out lesson, check point,...
	HEARTBEAT,
	ROTATION,
	INCIDENT,
	DRUNK_MODE,
	VOLUME,
	TRANSFORM_2D,
	VEHICLE_DENSITY,
	BRAKE = 100,
	THROTTLE,
	STEERING,
	CLUTCH,
	HAND_BRAKE,
	HORN,
	WIPER,
	HEAD_LIGHT,
	SIDE_LIGHT,
	WARNING_LIGHT,
	IGNITION,
	GEAR,
	FOG_LIGHT,
	SPRAY_WATER,
	GEAR_AUTO,
	SEAT_BELT,
	HAND_BRAKE_2,
	MIRROR,
    CAMERA = 150,
    FRAME,
	STEERING_FORCE = 200,
	CALIB_STEERING,
	OPEN_GATE,
	CHECK_GATE,
	LIGHT_SIGNAL,
	ERROR_INFO = 250,
	UPDATE_FIRMWARE
};

enum CAMERA_TYPE
{
    CAMERA_STOP = 0,
    CAMERA_IMAGE,
    CAMERA_VIDEO,
};

//enum B2_INFO_TYPE // This enum is synchronized with B2_OUTPUT in SaHinhType.h and being used in message sent to Manager
//{
//	B2_IN_L1 = 1,
//	B2_IN_L2 = 2,
//	B2_IN_L3 = 3,
//	B2_IN_L4 = 4,
//	B2_IN_L5 = 5,
//	B2_IN_L6 = 6,
//	B2_IN_L7 = 7,
//	B2_IN_L8 = 8,
//	B2_IN_L9 = 9,
//	B2_IN_L10 = 10,
//	B2_IN_L11 = 11,
//	B2_OUT_L1 = 12,
//	B2_OUT_L2 = 13,
//	B2_OUT_L3 = 14,
//	B2_OUT_L4 = 15,
//	B2_OUT_L5_1 = 16,
//	B2_OUT_L5_2 = 17,
//	B2_OUT_L5_3 = 18,
//	B2_OUT_L5_4 = 19,
//	B2_OUT_L6 = 20,
//	B2_OUT_L7 = 21,
//	B2_OUT_L8 = 22,
//	B2_OUT_L9 = 23,
//	B2_OUT_L10 = 24,
//	B2_OUT_L11 = 25,
//	B2_MINUS_POINT_1 = 26,
//	B2_MINUS_POINT_5 = 27,
//	B2_MINUS_POINT_10 = 28,
//	B2_ENGINE_STOP = 29,
//	B2_WARNING_POSITION = 30,
//	B2_FAIL_EXAM = 31,
//	B2_FAIL_EXAM_IMMEDIATELY = 32,
//	B2_PASS_EXAM = 33,
//	B2_TIME_TOTAL_OVER = 34,
//	B2_START_EXAM = 35,
//	B2_CHECK_POSITION = 36,
//	B2_CAR_RUN_IN_TRUCK_WAY = 37,
//	B2_IN_ILLEGAL_LINE = 38,
//	B2_WRONG_LESSON = 39,
//	B2_PARK_WRONG_POS = 40,
//	B2_SPEED_OR_GEAR_NOT_OK = 41,
//	B2_SEATBELT_OFF = 42,
//	B2_CAR_RUN_OUT_WAY = 43,
//	B2_RPM_OVER_4000 = 44,
//	B2_SPEED_OVER_24_DURING_3_SECOND = 45,
//	B2_TIME_UP_FOR_CAR_STOP_WHEN_WARNING = 46,
//	B2_TIME_UP_FOR_WARNING_LIGHT_WHEN_WARNING = 47,
//	B2_RUN_CAR_WHEN_WARNING_LIGHT_ON = 48,
//	B2_DONT_PASS_START_LINE_IN_20_SECOND = 49,
//	B2_DONT_PASS_START_LINE_IN_30_SECOND = 50,
//	B2_RUN_WHEN_NOT_RECEIVED_START_EXAM = 51,
//	B2_DONT_TURN_ON_LEFT_SIDE_LIGHT = 52,
//	B2_DONT_TURN_OFF_SIDE_LIGHT = 53,
//	B2_DONT_STOP_CAR_WHEN_NEEDED = 54,
//	B2_DONT_STOP_CAR_AT_POSITION = 55,
//	B2_STOP_CAR_AT_WRONG_POSITION = 56,
//	B2_DONT_FINISH_LESSON_IN_30S_SINCE_CAR_STOP = 57,
//	B2_CAR_RUN_BACK_50CM = 58,
//	B2_TIME_LESSON_OVER = 59,
//	B2_IN_ILLEGAL_LINE_5S = 60,
//	B2_CAR_PASS_LINE_AT_RED_TRAFFIC = 61,
//	B2_WRONG_SIDE_LIGHT = 62,
//	B2_DONT_PARK_CAR = 63,
//	B2_WRONG_GEAR = 64,
//	B2_INFORM_TOTAL_POINT = 65,
//	B2_CAR_RUN_OUT_TRACE = 66,
//	B2_RESET_POINT = 67,
//	B2_IN_L4_C = 68,
//	B2_IN_L4_D = 69,
//	B2_IN_L4_E = 70,
//	B2_OUT_L4_C = 71,
//	B2_OUT_L4_D = 72,
//	B2_OUT_L4_E = 73,
//	B2_IN_L6_C = 74,
//	B2_IN_L6_D = 75,
//	B2_IN_L6_E = 76,
//	B2_OUT_L6_C = 77,
//	B2_OUT_L6_D = 78,
//	B2_OUT_L6_E = 79,
//	B2_IN_L7_C = 80,
//	B2_IN_L7_D = 81,
//	B2_IN_L7_E = 82,
//	B2_OUT_L7_C = 83,
//	B2_OUT_L7_D = 84,
//	B2_OUT_L7_E = 85
//};

/**
 * 
 */
class  BaseMessage
{
public:
	BaseMessage();
    ~BaseMessage();
	uint16 getLeng();
	uint8 getType();
	void setLeng(uint16 leng);
	void setType(uint8 type);

	virtual int serialToData(char *dest, int length) = 0; // Serial length, type, and private data member, return number of byte
	virtual int parseFromData(char *mesData, int mesLen) = 0; // Parse private data member

protected:
    uint16 length;
	uint8 type;
};
