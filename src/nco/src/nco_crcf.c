/*
 * Copyright (c) 2007, 2008, 2009, 2010, 2013 Joseph Gaeddert
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// numerically-controlled oscillator (nco) API, floating point precision
//

#include "liquid.internal.h"

#define LIQUID_FPM              (0)
#define NCO(name)               LIQUID_CONCAT(nco_crcf,name)
#define T                       float
#define TC                      float complex

// supporting objects/methods
#define SIN                     sinf
#define COS                     cosf
#define IIRFILT_RRR(name)       LIQUID_CONCAT(iirfilt_rrrf,   name)
#define IIRFILTSOS_RRR(name)    LIQUID_CONCAT(iirfiltsos_rrrf,name)

// constants, etc.
#define NCO_ONE                 (1.0f)
#define NCO_PI                  (M_PI)
#define NCO_2PI                 (2.0f*M_PI)

#include "nco.c"
