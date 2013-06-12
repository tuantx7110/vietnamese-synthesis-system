/*
 * File:   constants.h
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:15 AM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

const int kBufferSize = 262144;
const int kLogWord = 5;
const int kWordSize = 1 << kLogWord;
const int kTotalBits = kWordSize * kBufferSize;
const word kFullBitMask = (((word) 1) << kWordSize) - 1;

#endif	/* CONSTANTS_H */

