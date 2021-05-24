#include <phidget22.h>
#include <stdio.h>

static void CCONV onAccelerationChange(PhidgetAccelerometerHandle ch, void * ctx, const double acceleration[3], double timestamp) {
	printf("Acceleration: \t%lf  |  %lf  |  %lf\n", acceleration[0], acceleration[1], acceleration[2]);
	printf("Timestamp: %lf\n", timestamp);
	printf("----------\n");
}

int main() {
	PhidgetAccelerometerHandle accelerometer0;

	PhidgetAccelerometer_create(&accelerometer0);

	PhidgetAccelerometer_setOnAccelerationChangeHandler(accelerometer0, onAccelerationChange, NULL);

	Phidget_openWaitForAttachment((PhidgetHandle)accelerometer0, 5000);

	//Wait until Enter has been pressed before exiting
	getchar();

	Phidget_close((PhidgetHandle)accelerometer0);

	PhidgetAccelerometer_delete(&accelerometer0);
}
