/**
 * @file encoders.h
 * @author Chris Jerrett, Christian Desimone
 * @date 9/9/2017
 * @brief wrapper around encoder functions
 **/
#ifndef _ENCODERS_H_
#define _ENCODERS_H_

#include <API.h>

/**
 * @brief The number of IMEs.
 * This number is compared against the number detect in init_encoders
 * @see init_encoders()
 * @author Chris Jerrett
 * @date 9/9/2017
 * @see IME_NUMBER
 **/
#define IME_NUMBER 4

/**
 * @brief Initializes all motor encoders
 * @author Chris Jerrett
 * @date 9/9/2017
 * @see IME_NUMBER
 **/
bool init_encoders();

/**
 * @brief Gets the encoder ticks since last reset
 * @author Chris Jerrett
 * @date 9/15/2017
 **/
int get_encoder_ticks(const unsigned char address);

/**
 * @brief Gets the encoder reads
 * @author Chris Jerrett
 * @date 9/15/2017
 **/
int get_encoder_velocity(const unsigned char address);

/**
 * @brief Gets the average of four encoders or the value of one encoder
 * @date 4/10/2017
 **/
int img_get_average(bool multi);

int ime_get_right_dist();

int ime_get_left_dist();

int ime_get_right_vel();

int ime_get_left_vel();

#endif
