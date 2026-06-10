#ifndef CONFIG_H
#define CONFIG_H

// Unique ID of the node
#define NODE_ID 1

// speed at which to run I2C clock (if unstable measurement reliability -> lower it)
#define I2C_CLOCK 400000

// UART and later RS485 baudrate
#define BUS_BAUD 115200

// rolling average window of measurements (more -> slower response, less -> jumpy measurements)
#define NUM_MEAS 16

// built in LED pin for WeAct STM32G030F6P6 Core board
// https://www.aliexpress.com/item/1005005748496495.html
#define MY_LED PA4

#endif // end CONFIG_H
