/*
 *
 * author: Zachary Ankenman
 * version 0.1
 */

#ifndef _SR_H
#define _SR_H

#include <stdbool.h>

/*
 * Set carry flag
 *
 * input: if false, clear carry bit
 * 	  if true, set carry bit
 */
void setC(bool input);

/*
 * Get carry flag
 */
bool getC();

/*
 * Set negative flag
 *
 * input: if false, clear carry bit
 * 	  if true, set carry bit
 */
void setN(bool input);

/*
 * Get negative flag
 */
bool getN();

/*
 * Set zero flag
 *
 * input: if false, clear carry bit
 * 	  if true, set carry bit
 */
void setZ(bool input);

/*
 * Get zero flag
 */
bool getZ();

#endif
