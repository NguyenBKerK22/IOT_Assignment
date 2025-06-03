// #include "DFRobot_BNO055.h"
// #include <Adafruit_BNO055.h>
// #include <Wire.h>

// typedef DFRobot_BNO055_IIC    BNO;    // ******** use abbreviations instead of full names ********

// BNO   bno(&Wire, 0x28);    // input TwoWire interface and IIC address
const float mag_decl = 0.0116; // Ho Chi Minh City declination
// // show last sensor operate status
// void printLastOperateStatus(BNO::eStatus_t eStatus)
// {
//   switch(eStatus) {
//   case BNO::eStatusOK:    Serial.println("everything ok"); break;
//   case BNO::eStatusErr:   Serial.println("unknow error"); break;
//   case BNO::eStatusErrDeviceNotDetect:    Serial.println("device not detected"); break;
//   case BNO::eStatusErrDeviceReadyTimeOut: Serial.println("device ready time out"); break;
//   case BNO::eStatusErrDeviceStatus:       Serial.println("device internal status error"); break;
//   default: Serial.println("unknow status"); break;
//   }
// }
// void MotionCal_display(BNO::sAxisAnalog_t *accel_event, BNO::sAxisAnalog_t  *gyro_event, BNO::sAxisAnalog_t *mag_event)
// {
//     /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
//     Serial.print("Raw:");
//     Serial.print(int(accel_event->x * 8192 / 9.8));
//     Serial.print(",");
//     Serial.print(int(accel_event->y * 8192 / 9.8));
//     Serial.print(",");
//     Serial.print(int(accel_event->z * 8192 / 9.8));
//     Serial.print(",");

//     Serial.print(int(gyro_event->x * (180.0 / 3.141592653589793238463) * 16));
//     Serial.print(",");
//     Serial.print(int(gyro_event->y * (180.0 / 3.141592653589793238463) * 16));
//     Serial.print(",");
//     Serial.print(int(gyro_event->z * (180.0 / 3.141592653589793238463) * 16));
//     Serial.print(",");

//     Serial.print(int(mag_event->x * 10));
//     Serial.print(",");
//     Serial.print(int(mag_event->y * 10));
//     Serial.print(",");
//     Serial.print(int(mag_event->z * 10));
//     Serial.println("");

//     Serial.print("Uni:");
//     Serial.print(accel_event->x);
//     Serial.print(",");
//     Serial.print(accel_event->y);
//     Serial.print(",");
//     Serial.print(accel_event->z);
//     Serial.print(",");

//     Serial.print(gyro_event->x, 4);
//     Serial.print(",");
//     Serial.print(gyro_event->y, 4);
//     Serial.print(",");
//     Serial.print(gyro_event->z, 4);
//     Serial.print(",");

//     Serial.print(mag_event->x);
//     Serial.print(",");
//     Serial.print(mag_event->y);
//     Serial.print(",");
//     Serial.print(mag_event->z);
//     Serial.println("");
// }
// float calculateHeading(BNO::sAxisAnalog_t *mag_data_sensor)
// {
//     float heading = 0;
//     // Calculate angle for heading, assuming board is parallel to
//     // the ground and  Y points toward heading.
//     heading = atan2(mag_data_sensor->y, mag_data_sensor->x);

//     // Apply magnetic declination to convert magnetic heading
//     // to geographic heading
//     heading += mag_decl;

//     heading = heading * 180 / M_PI;
//     // Convert heading to 0..360 degrees
//     if (heading < 0)
//     {
//         heading += 360;
//     }
//     else if (heading > 360)
//     {
//         heading -= 360;
//     }
//     return heading;
// }
// void setup()
// {
//   Serial.begin(115200);
//   bno.reset();
//   while(bno.begin() != BNO::eStatusOK) {
//     Serial.println("bno begin faild");
//     printLastOperateStatus(bno.lastOperateStatus);
//     delay(2000);
//   }
//   Serial.println("bno begin success");
// }

// void loop()
// {
//   BNO::sAxisAnalog_t  sAcc, sMag, sGyr;
//   sAcc = bno.getAxis(BNO::eAxisAcc);
//   sMag = bno.getAxis(BNO::eAxisMag);
//   sGyr = bno.getAxis(BNO::eAxisGyr);
//   // Serial.print("Acc: ");
//   // Serial.print("X:");
//   // Serial.print(sAcc.x, 3);
//   // Serial.print(" ");
//   // Serial.print("Y:");
//   // Serial.print(sAcc.y, 3);
//   // Serial.print(" ");
//   // Serial.print("Z:");
//   // Serial.print(sAcc.z, 3);
//   // Serial.println(" ");

//   // Serial.print("Mag: ");
//   // Serial.print("X:");

//   // Serial.print(sMag.x, 3);
//   // Serial.print(" ");
//   // // Serial.print("Y:");
//   // Serial.print(sMag.y, 3);
//   // Serial.print(" ");
//   // // Serial.print("Z:");
//   // Serial.print(sMag.z, 3);
//   // Serial.println(" ");
//   // Serial.print("Heading: ");
//   Serial.println(calculateHeading(&sMag));
//   // MotionCal_display(&sAcc, &sGyr, &sMag);

//   // Serial.print("Gyro: ");
//   // Serial.print("X:");
//   // Serial.print(sGyr.x, 3);
//   // Serial.print(" ");
//   // Serial.print("Y:");
//   // Serial.print(sGyr.y, 3);
//   // Serial.print(" ");
//   // Serial.print("Z:");
//   // Serial.print(sGyr.z, 3);
//   // Serial.println(" ");
//   // Serial.println(" ");
//   // BNO::sEulAnalog_t   sEul;
//   // sEul = bno.getEul();
//   // Serial.print(sEul.pitch, 3);
//   // Serial.print(",");
//   // Serial.print(sEul.roll, 3);
//   // Serial.print(",");
//   // Serial.print(sEul.head, 3);
//   // Serial.println(" ");
//   delay(80);
// }

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* This driver reads raw data from the BNO055

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);
/*
    Display sensor calibration status
*/
/**************************************************************************/
void displayCalStatus(void)
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print("\t");
  if (!system)
  {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.println(mag, DEC);
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);

  while (!Serial) delay(10);  // wait for serial port to open!

  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  imu::Vector<3> gyr = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  /* Display the floating point data */
  Serial.print(acc.x());
  Serial.print(",");
  Serial.print(acc.y());
  Serial.print(",");
  Serial.print(acc.z());
  Serial.print(",");
  Serial.print(mag.x());
  Serial.print(",");
  Serial.print(mag.y());
  Serial.print(",");
  Serial.print(mag.z());
  Serial.print(",");
  Serial.print(gyr.x());
  Serial.print(",");
  Serial.print(gyr.y());
  Serial.print(",");
  Serial.print(gyr.z());

  /* Display calibration status for each sensor. */
  Serial.print("\t\t");
  displayCalStatus();
  delay(BNO055_SAMPLERATE_DELAY_MS);
}