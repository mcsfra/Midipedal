/* 
 * File:   velocities.h
 * Author: marcus
 *
 * Created on 27. März 2014, 20:49
 */

#ifndef __VELOCITIES_H__
#define	__VELOCITIES_H__

#define IN_MIN  80.0
#define IN_MAX  6000.0



#define OUT_MIN 125.0
#define OUT_MAX 5.0

#define OUTOFBOUNDS_LOW  4
#define OUTOFBOUNDS_HIGH 126

//#define VELOCITY_FACTOR (IN_MAX-IN_MIN)/(OUT_MIN-OUT_MAX)


#define  INFACTOR (1.0/(IN_MAX - IN_MIN))
#define OUTFACTOR (1.0/(OUT_MAX-OUT_MIN))





#endif	/* VELOCITIES_H */

