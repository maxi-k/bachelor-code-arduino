#ifndef COMMUNICATION_H_DEFINED
#define COMMUNICATION_H_DEFINED

#include <Arduino.h>
#include <Wire.h>
#include "state.h"

typedef void (*CommunicationCallback)(int, byte*);

namespace Communicator {

  const int MAX_RESPONSE_LENGTH = 32;

  const int MAX_REQUEST_LENGTH = 32;

  const int SLAVE_ADDRESS = 0x04;

  enum messageFlag {
    // message with distance data [int, int, int]
    msgDistData = 'd',
    // command for setting the speed
    cmdSpeed = 's',
    // command for sending back update (probably distance data)
    cmdUpdate = 'u'
  };

  void setup(State* state,
             CommunicationCallback recvCallback,
             CommunicationCallback sendCallback);

  void setStateStruct(State* state);

  void setReceiveCallback(CommunicationCallback callback);

  void setSendCallback(CommunicationCallback callback);

  void receiveData(int byteLength);

  void sendData();

  void serializeData();

};

#endif
