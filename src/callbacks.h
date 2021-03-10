/***************************************************************************//**
* @file callbacks.h
* @author Paul Hinker
* @brief Contain all callback function prototypes.
*******************************************************************************/
#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "util.h"

/// Callback for the display event
void display();

/// Callback for the reshape event
void reshape( const int x, const int y );

/// Common function for collecting event information

/// Function that's called on a timer
void ticktock( int value );

/// Called when openGL is closing
void onClose();

/// Called when a key is pressed
void keyboard( unsigned char key, int x, int y );

#endif
