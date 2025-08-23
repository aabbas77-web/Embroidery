/********************************************************************
   The Image Processing Library 98 - IPL98
   Copyright (C) by René Dencker Eriksen - edr@mip.sdu.dk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation. Only
   addition is, that if the library is used in proprietary software
   it must be stated that IPL98 was used.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   More details can be found in the file licence.txt distributed
   with this library.
*********************************************************************/

/* ipl98_cplusplus_algorithms.h, only algorithm classes are
   included, include this file to use the c++ algorithms in
   IPL98, the files ipl98_cplusplus_container.h and
   ipl98_cplusplus_container.cpp must also be included.

   Version 1.60, Last updated 4/7/2002 by edr@mip.sdu.dk */

#ifndef _IPL98_CPP_ALGORITHMS_H
#define _IPL98_CPP_ALGORITHMS_H

#ifndef _IPL98_USING_CPP
#define _IPL98_USING_CPP /* used in the kernel C part to test if namespace ipl should be used */
#endif

/* Include container classes */
#include "ipl98_cplusplus_containers.h"

/* Include IPL98 ansi c headers */
#include "ipl98_algorithms.h"

/************************************************/
/********          Algorithms            ********/
/************************************************/

#include "cpp/algorithms/graphics.h"
#include "cpp/algorithms/statistic.h"
#include "cpp/algorithms/segmentate.h"
#include "cpp/algorithms/feature_extraction.h"
#include "cpp/algorithms/perspective.h"
#include "cpp/algorithms/morphology.h"
#include "cpp/algorithms/mask_operation.h"
#include "cpp/algorithms/local_operation.h"
#include "cpp/algorithms/coordinate_transform.h"
#include "cpp/algorithms/spectral.h"

#include "cpp/algorithms/hough_transform/parameter2d.h"
//#include "cpp/algorithms/hough_transform/prob_rht.h"
#include "cpp/algorithms/hough_transform/str_list.h"

#endif /* _IPL98_CPP_ALGORITHMS_H */