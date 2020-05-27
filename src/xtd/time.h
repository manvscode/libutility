/*
 * Copyright (C) 2010 by Joseph A. Marrero. http://www.manvscode.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef _XTD_TIME_H_
#define _XTD_TIME_H_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
# include <stdint.h>
#else
# error "Need a C99 compiler."
#endif

#ifdef __cplusplus
extern "C" {
#endif

double      time_seconds             ( void );
double      time_milliseconds        ( void );
uint64_t    time_secs                ( void );
uint64_t    time_msecs               ( void );
void        time_msleep              ( int milliseconds );
const char* time_iso8601             ( time_t t ); /* not thread safe */
bool        time_iso8601_r           ( time_t t, char* iso_8601, size_t len );
const char* time_iso8601_precision   ( time_t t, unsigned int milliseconds ); /* not thread safe */
bool        time_iso8601_precision_r ( time_t t, unsigned int milliseconds, char* iso_8601, size_t size );
double      time_utc_offset          ( const char* tz ); /* Expects IANA or Windows zone id. */
struct tm*  time_local               ( time_t t, const char* tz ); /* Expects IANA or Windows zone id. */

#ifdef __cplusplus
} /* extern "C" */
namespace utility {
	using ::time_seconds;
	using ::time_milliseconds;
	using ::time_secs;
	using ::time_msecs;
	using ::time_msleep;
	using ::time_iso8601;
	using ::time_iso8601_r;
	using ::time_iso8601_precision;
	using ::time_iso8601_precision_r;
	using ::time_utc_offset;
	using ::time_local;
} /* namespace */
#endif
#endif /* _XTD_TIME_H_ */
