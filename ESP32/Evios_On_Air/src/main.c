//void app_main() {}


//EVIOS State Machine

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
  sysIddle,
  bluetoothMsgTx,
  MQTTMsgTx,
  ConnectivityErr
} EVIOS_states_t;


void EVIOS_StateMachineInit(); //initialises the system



void EVIOS_StateMachine(EVIOS_state_t *state) {
  switch (*state) {
    case SysIddle:
      if (CheckConnectivity()) {
        printf("Check connectivity\n");
        state = bluetoothMsgRx;
      } else {
        state = ConnectivityErr;
      }
      break;
    case bluetoothMsgTx:
      printf("Send message over Bluetooth\n");
//1. Buffer is checked to be ready and consistent
//2. check for paired device
//3. check for connectivity
//4. transmit to the device
//5. full bufer is transmited 

      state = SysIddle;
      break;
    case MQTTMsgTx:
      printf("Send message over MQTT\n");
      state = SysIddle;
      break;
    case ConnectivityErr:
      printf("Retry sending message\n");
      state = SysIddle;
      break;
  }
}

bool bluetoothRx()
{

}
bool MQTTRx()
{
  return true;
  
  //1. mqtt message is received fully
  //2. message is stored in a buffer for bluetooth tx
  //3. ....
}

int main() {
  EVIOS_StateMachineInit();
  EVIOS_state_t activeState;
  while (1)
  {
      if(bluetoothRx())
      {
        activeState = MQTTMsgTx;
        EVIOS_StateMachine(&activeState);
      }else if(MQTTRx()){
        activeState = bluetoothMsgTx;
        EVIOS_StateMachine(&activeState);
      }

  }
  return 0;
}

/*
Initialise the state the state machine


*/

