/*
 * This file is part of the GrapeLabs Arduino Libraries.
 *
 * The contents of this file are subject to the Apache License Version
 * 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is GrapeLabs Arduino Libraries / SRF02.
 *
 * The Initial Developer of the Original Code is
 * Dirk Grappendorf, GrapeLabs (www.grapelabs.de)
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 */

//#include "wiring.h"
#include "Wire.h"
#include "SRF02.h"
#include "arduino.h"
/** How long it takes for a SRF02 to perform a measurement (milli seconds) */
const unsigned int READ_DURATION = 70;

unsigned int SRF02::interval = 1000;

unsigned long SRF02::nextRead = 0;

unsigned long SRF02::nextRequest = 0;

SRF02 *SRF02::first = 0;

SRF02::SRF02(uint8_t deviceId, uint8_t mode)
{
	this->deviceId = deviceId;
	this->mode = mode;
	this->value = 0;
	add ();
}

void SRF02::add()
{
	this->next = first;
	first = this;
}

void SRF02::update()
{
	if (millis() > nextRequest)
	{
		for (SRF02 *i = first; i != 0; i = i->next)
		{
			Wire.beginTransmission(i->deviceId);
			Wire.send(0);
			Wire.send(i->mode);
			Wire.endTransmission();
		}
		nextRead = millis() + READ_DURATION;
		nextRequest = millis() + interval;
	}
	else if (nextRead != 0 && millis() > nextRead)
	{
		for (SRF02 *i = first; i != 0; i = i->next)
		{
			Wire.beginTransmission(i->deviceId);
			Wire.send(2);
			Wire.endTransmission();
			Wire.requestFrom(i->deviceId, (uint8_t) 2);
			i->value = ((unsigned long) Wire.receive()) << 8;
			i->value += (unsigned long) Wire.receive();
		}
		nextRead = 0;
	}
}

void SRF02::configureDeviceId(uint8_t currentDeviceId, uint8_t newDeviceId)
{
	Wire.beginTransmission(currentDeviceId);
	Wire.send(0);
	Wire.send(0xA0);
	Wire.endTransmission();
	Wire.beginTransmission(currentDeviceId);
	Wire.send(0);
	Wire.send(0xAA);
	Wire.endTransmission();
	Wire.beginTransmission(currentDeviceId);
	Wire.send(0);
	Wire.send(0xA5);
	Wire.endTransmission();
	Wire.beginTransmission(currentDeviceId);
	Wire.send(0);
	Wire.send(newDeviceId << 1);
	Wire.endTransmission();
}
