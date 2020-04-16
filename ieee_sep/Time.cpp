///////////////////////////////////////////////////////////
//  Time.cpp
//  Implementation of the Class Time
//  Created on:      13-Apr-2020 2:51:45 PM
//  Original author: kholbroo
///////////////////////////////////////////////////////////

#include "Time.h"


Time::Time() : pollRate(900){
	currentTime = 100;
	dstEndTime = 200;
	dstOffset = 300;
	dstStartTime = 400;
	localTime = 500;
	quality = 1;
	tzOffset = 600;
}



Time::~Time(){

}
