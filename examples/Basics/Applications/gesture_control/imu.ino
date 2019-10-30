/**
 * CI-N5-V
 * @author: Hugo J. Marquez
 * @description: Gesture Control IMU module
 *
 */

 /* Sample rate for accelerometer */
 const unsigned int sampleRateHZ = 256;

 /* No. of bytes that one neuron can hold */
 const unsigned int vectorNumBytes = 128;

 /* Number of processed samples (1 sample == accel x, y, z)
  * that can fit inside a neuron */
 const unsigned int samplesPerVector = (vectorNumBytes / 3);

 const unsigned int sensorBufSize = 1024;
 const int IMULow = -32768;
 const int IMUHigh = 32767;

 byte getAverageSample(byte samples[], unsigned int num, unsigned int pos, unsigned int step) {
   unsigned int ret;
   unsigned int size = step * 2;

   if (pos < (step * 3) || pos > (num * 3) - (step * 3)) {
     ret = samples[pos];
   } else {
     ret = 0;
     pos -= (step * 3);
     for (unsigned int i = 0; i < size; ++i) {
       ret += samples[pos - (3 * i)];
     }
     ret /= size;
   }
   return (byte)ret;
 }


 void undersample(byte input[], int numSamples, byte vector[]) {
   unsigned int oi = 0; /* Current position in output sample buffer */
   unsigned int ii = 0; /* Current position in input sample buffer */
   unsigned int step = numSamples / samplesPerVector;

   for (unsigned int i = 0; i < samplesPerVector; ++i) {
     for (unsigned int j = 0; j < 3; ++j) {
       //vector[oi + j] = input[ii + j];
       vector[oi + j] = getAverageSample(input, numSamples, ii + j, step);
     }
     /* Skip 'step' samples */
     ii += (step * 3);
     oi += 3;
   }
 }

 void readIMU(byte vector[]) {
   // raw x, y, z
   int16_t raw[3];
   unsigned int i = 0;
   unsigned int samples = 0;
   byte bytemap[sensorBufSize];
   uint16_t timer = 1000; // ~1 sec

   while(timer > 0) {
     timer -= 1;
     M5.Imu.getAccelAdc(&raw[0], &raw[1], &raw[2]);
     /* Map raw values to 0-255 */
     bytemap[i]     = (byte) map(raw[0], IMULow, IMUHigh, 0, 255);
     bytemap[i + 1] = (byte) map(raw[1], IMULow, IMUHigh, 0, 255);
     bytemap[i + 2] = (byte) map(raw[2], IMULow, IMUHigh, 0, 255);
     i += 3;
     ++samples;
     if (i + 3 > sensorBufSize) {
       break;
     }
   }
   undersample(bytemap, samples, vector);
 }

 void rawIMU(int16_t vector[]) {
   // raw x, y, z
   int16_t raw[3];
   unsigned int i = 0;
   unsigned int samples = 0;
   uint16_t timer = 1000; // ~1 sec

   while(timer > 0) {
     timer -= 1;
     M5.Imu.getAccelAdc(&raw[0], &raw[1], &raw[2]);
     vector[i]     = raw[0];
     vector[i + 1] = raw[1];
     vector[i + 2] = raw[2];
     i += 3;
     ++samples;
     if (i + 3 > sensorBufSize) {
       break;
     }
   }
 }
