//Murtadha Alobaidi
#include <stdio.h>
#include "brick.h"
#include <unistd.h>

//1m=7sek, HASTIGHET 300//

//#define sleep is needed for 1000ms=1sec//
#define Sleep( msec ) usleep(( msec ) * 1000 )

//#define  is needed for the "robot"  to know which motor/sensor is connected to which port//
#define MOTOR_RIGHT             OUTA
#define MOTOR_LEFT              OUTB
#define MOTOR_C                 OUTC
#define MOTOR_D                 OUTD
#define SENSOR_1                IN1
#define SENSOR_2                IN2
#define SENSOR_US               IN3
#define SENSOR_GYRO             IN4

#define MOTOR_BOTH      (MOTOR_LEFT | MOTOR_RIGHT)
#define MOTOR_ALL       (MOTOR_BOTH | MOTOR_C)

//here are all our functions declared//
void init(void);
void move(int, int);
void stop_motors();
float get_gyro_value(void);
void turn_by_angle(float);
void hold_book(int);
void drop_book();
float get_ultra_value();
void find_wall();

//uint8_t is needed for the gyro  function to work.//
uint8_t sn;

void main(void) {
//in our main we we only declare the functions//
        brick_init();
        init();


        brick_uninit();
}
//function to get gyro start value//
float get_gyro_value() {
  int gyro_start;
    if(ev3_search_sensor(LEGO_EV3_GYRO, &sn, 0)) {
      if(get_sensor_value(0, sn, &gyro_start)) {
        return (gyro_start);
        }
    }
}

//function to get "ultraljud" start value//
float get_ultra_value() {
  int dist;
    if(ev3_search_sensor(LEGO_EV3_US, &sn, 0 )) {
     if(get_sensor_value(0, sn, &dist )) {
       return dist;
       }
   }
}

//function to stop within 30cm of the wall//
void find_wall() {
        move(100, 100);
        while(get_ultra_value() > 300) {
                Sleep(200);
        }
                stop_motors();
}

//function to make the robot turn//
void turn_by_angle(float angle) {
        float start, current;
        get_sensor_value0(SENSOR_GYRO,&start);

        start = get_gyro_value();
        current = start;

        move(50, -50);

        while (current < start + angle) {
                printf("%0.f < %0.f + %0.f\n", current, start, angle);
                get_sensor_value0(SENSOR_GYRO, &current);
                current = get_gyro_value();
        }

        stop_motors();
}

//function for the motor that lifts up the book//
void hold_book(int lift_speed) {
        tacho_set_speed_sp(MOTOR_C, lift_speed);
        tacho_run_forever(MOTOR_C);
}

//function for the motor to drop  the book//
void drop_book() {
        tacho_stop(MOTOR_C);

}
//function to stop the motors//
void stop_motors() {
        tacho_stop(MOTOR_BOTH);
}

//function to make the robot move forward/backward//
void move(int l_speed, int r_speed) {
        tacho_set_speed_sp(MOTOR_LEFT, l_speed);
        tacho_set_speed_sp(MOTOR_RIGHT, r_speed);
        tacho_run_forever(MOTOR_BOTH);
}

//code needed for the motors/sensors to work//
void init() {
        tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_);
        sensor_is_plugged(SENSOR_GYRO, SENSOR_TYPE__NONE_);
        tacho_is_plugged(MOTOR_LEFT, TACHO_TYPE__NONE_);
        tacho_is_plugged(MOTOR_RIGHT, TACHO_TYPE__NONE_);
        tacho_is_plugged(MOTOR_C, TACHO_TYPE__NONE_);
        tacho_is_plugged(MOTOR_ALL, TACHO_TYPE__NONE_);
        sensor_is_plugged(SENSOR_US, SENSOR_TYPE__NONE_);
}




