/*
 * statusflags.h
 *
 *  Created on: Jan 27, 2016
 *  Author: logan Myers
 *
 *  Version     :1.0
 *  Description	:This file contains access to C, N, Z status flags
 * 
 *
 */

#ifndef _STATUSFLAGS_H
#define _STATUSFLAGS_H

class Statusflags
{
public:
	Statusflags();
  ~Statusflags();
  void checkz(char checkvalue);
  void checkn(char checkvalue);
  void checkc(int addsub, char val1, char val2, int Cin);
  bool getz();
  bool getn();
  bool getc();
  void setc(bool checkvalue);

protected:
  bool C, Z, N;
};

#endif
