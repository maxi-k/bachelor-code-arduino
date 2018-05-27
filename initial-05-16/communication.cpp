#include "communication.h"

/**
 * Utility functions wrapping the WireCommunicator object
 * so that they can be passed as function pointer callbacks
 * to the Wire library.
 */
namespace Communicator {

  namespace {

    State* state;

    byte* responseData = new byte[MAX_RESPONSE_LENGTH];

    byte* receivedData = new byte[MAX_REQUEST_LENGTH];

    int receivedDataLength = MAX_REQUEST_LENGTH;

    int responseDataLength = MAX_RESPONSE_LENGTH;

    CommunicationCallback receiveCallback;

    CommunicationCallback sendCallback;

  }

  void setup(State* stateStruct,
             CommunicationCallback recvCallback,
             CommunicationCallback sendCallback) {
    setStateStruct(stateStruct);
    setReceiveCallback(recvCallback);
    setSendCallback(sendCallback);

    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
  }

  void setStateStruct(State* stateStruct) {
    state = stateStruct;
  }

  void setReceiveCallback(CommunicationCallback callback) {
    receiveCallback = callback;
  }

  void setSendCallback(CommunicationCallback callback) {
    sendCallback = callback;
  }

  void receiveData(int byteLength) {
    int read = 0;

    while (Wire.available() && read < MAX_REQUEST_LENGTH) {
      receivedData[read] = Wire.read();
      read++;
    }

    if (read >= MAX_REQUEST_LENGTH) {
      // TODO: Error? Too many bytes sent
    }
    receivedDataLength = read;
    // Call the callback
    if (receiveCallback != NULL) {
      receiveCallback(receivedDataLength, receivedData);
    }
  }

  void sendData() {
      serializeData();
      if(sendCallback != NULL) {
        sendCallback(responseDataLength, responseData);
      }
      Wire.write(responseData, responseDataLength);
  }

  void serializeData() {
    int dist_length = NUM_DISTANCE_SENSORS * sizeof(int);
    for (int i = 0; i < NUM_DISTANCE_SENSORS; ++i) {
      int dist = state->getDistanceFor(i);
      int idx = i * sizeof(int);
      responseData[idx] = highByte(dist);
      responseData[idx + 1] = lowByte(dist);
    }
    responseDataLength = dist_length;
  }

}
