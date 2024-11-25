/*
 *  AmbientSimplePost.ino  - Example for the Ambient library for Sony Spresense -
 *  Copyright 2020 Yoshinori Oota
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  This sketch connects to a website via LTE. Specifically,
 *  this example downloads the URL "http://www.arduino.cc/asciilogo.txt" and
 *  prints it to the Serial monitor.
 */

#include <Arduino.h>
#include <GNSS.h>
#include "Ambient_SpresenseLTEM.h"

/* Change the settings according to your sim card */
#define APN_NAME "your.apn.name"
#define APN_USRNAME "your.apn.usrname"
#define APN_PASSWD "your.apn.passwd"

/* Change the settings accroding to your ambient channel */
#define AMBI_CHANNEL 00000
#define AMBI_WRITEKEY "your.ambient.writekey"

void setup() {
  Serial.begin(115200);
   
  bool ret = theAmbient.begin(APN_NAME ,APN_USRNAME ,APN_PASSWD);
  if (ret == false) {
    Serial.println("theAmbient begin failed");
    theAmbient.end(); while(1);
  }

  theAmbient.setupChannel(AMBI_CHANNEL, AMBI_WRITEKEY);

}

void loop()
{
  static float data = 0.1;

  theAmbient.set( 1, String(data).c_str());
  int ret = theAmbient.send();

  Serial.print("data=");
  Serial.println(data);

  if (ret == 0) {
      Serial.println("*** ERROR! LTE reboot! ***\n");
      theAmbient.end();
      while(1) {
        Serial.println("Connecting Network...");
        if (theAmbient.begin(APN_NAME ,APN_USRNAME ,APN_PASSWD)) {
          break;
        }
      }
  }

  data++;
  sleep(10);
 
}
