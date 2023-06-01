
# leo_vcu_CANsniffer
This software runs on LEO_VCU, which utilizes an STM32F105 microcontroller. It has two built-in CANBUS lines that can be used for a man-in-the-middle attack on a vehicle's ADAS system.

* In the normal state, the ECU acts as a bridge, forwarding messages between CAN1 and CAN2.
* Any message on the CANBUS can be modified.
* Messages with a specific ID are captured using the `CAN_GetMessage` function and stored in a queue.
* The `DefaultTask` is responsible for processing the data in the queue. It remains blocked until the queue is not empty, indicating the arrival of a message.
* The software allows you to edit the content of the captured message and send the modified version back onto the CANBUS.
