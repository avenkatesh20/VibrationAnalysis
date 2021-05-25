#include <phidget22.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *PHIDGETDATA;

static void CCONV writeToFile(PhidgetAccelerometerHandle ch, void * ctx, const double acceleration[3], double timestamp){

//  PHIDGETDATA = fopen("./phidgetdata.txt", "w+");

  char accelstr[] = "(";
  char div[] = " | ";
  const char fmt[] = "%f";
//  fputs(accelstr, PHIDGETDATA);

  for (int i = 0; i < 3; i ++){
    int size = snprintf(0,0,fmt,acceleration[i]);
    char datapoint[size + 1];
    sprintf(datapoint,fmt, acceleration[i]);
  //  printf(datapoint);

    fputs(datapoint, PHIDGETDATA);
    fputs(",", PHIDGETDATA);

    //strncat(accelstr, &div, sizeof(div))
  }
  int timesize = snprintf(0,0,fmt,timestamp);
  char time[timesize + 1];
  sprintf(time,fmt, timestamp);
  fputs(time, PHIDGETDATA);
  fputs(",", PHIDGETDATA);
//  fputs(")\n", PHIDGETDATA);
  //str_append(acceleration, sprintf(acceleration[0]));
//  fputs("Acceleration: \t%lf  |  %lf  |  %lf\n", acceleration[0], acceleration[1], acceleration[2]);
//	fputs("Timestamp: %lf\n", timestamp);

}

static void CCONV onAccelerationChange(PhidgetAccelerometerHandle ch, void * ctx, const double acceleration[3], double timestamp) {
  //Convert GForce into m/s^2
  float acceleration_conv [3];
  for (int i = 0; i < 3; i++){
    double curr_acc = acceleration[i];
    acceleration_conv[i] = curr_acc/9.8;
  }
  //Convet time from ms to s
  timestamp = timestamp/1000;
  writeToFile(ch, ctx, acceleration, timestamp);
  printf("Acceleration: \t%lf  |  %lf  |  %lf (m/s^2)\n", acceleration[0], acceleration[1], acceleration[2]);
	printf("Timestamp: %lf (s)\n", timestamp);
	printf("----------\n");

}


int main() {
	PhidgetAccelerometerHandle accelerometer0;

	PhidgetAccelerometer_create(&accelerometer0);
  PHIDGETDATA = fopen("./phidgetdata.txt", "w+");
	PhidgetAccelerometer_setOnAccelerationChangeHandler(accelerometer0, onAccelerationChange, NULL);

	Phidget_openWaitForAttachment((PhidgetHandle)accelerometer0, 5000);

	//Wait until Enter has been pressed before exiting
	getchar();
  fclose(PHIDGETDATA);
	Phidget_close((PhidgetHandle)accelerometer0);

	PhidgetAccelerometer_delete(&accelerometer0);
}
