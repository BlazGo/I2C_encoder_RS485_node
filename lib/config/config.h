#ifndef CONFIG_H
#define CONFIG_H

// Unique ID of the node
#define NODE_ID 1

#define MY_LED PA4 // Built in led of the WeAct STM32G030 dev board
#define EN_PIN PA5 // Pin to enable the MAX485 in transmit mode (by default in receive mode always)

#define I2C_ENCODER_ADDRESS 0x06
#define I2C_SPEED 400000
#define UART_BAUDRATE 921600

#define NUM_MEAS 8 // Number of encoder angle measurements to average over (rolling average of raw values)
#define DEG_TO_RAD 0.017453292519943295769236907684886

#endif // CONFIG_H
