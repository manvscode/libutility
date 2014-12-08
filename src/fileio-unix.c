/*
 * Copyright (C) 2010-2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "utility.h"

bool file_exists( const char* path )
{
	assert( path );
	return access( path, F_OK ) == 0;
}

bool file_is_writeable( const char* path )
{
	assert( path );
	return access( path, W_OK ) == 0;
}

bool file_is_readable( const char* path )
{
	assert( path );
	return access( path, R_OK ) == 0;
}

bool file_is_executable( const char* path )
{
	assert( path );
	return access( path, X_OK ) == 0;
}

bool file_delete( const char* path )
{
	assert( path );

	if( is_directory(path) )
	{
		DIR* d = opendir( path );
		int result = 1;

		if( d )
		{
			struct dirent* p_file = readdir( d );
			result &= file_delete( p_file->d_name );
		}

		closedir( d );
		return result;
	}
	else
	{
		return unlink( path ) == 0;
	}
}

int64_t file_size( const char* path )
{
    struct stat s;
	assert( path );

    if( stat( path, &s ) == 0 )
	{
        return s.st_size;
    }

	return 0L;
}

long file_age( const char* path ) // Return age of file in seconds. -1 = doesnt exist or error
{
    struct stat s;
	assert( path );

    if( stat( path, &s ) == 0 )
	{
    	return time(NULL) - s.st_mtime;
    }

	return -1;
}

extern const char* basename( const char* path, char dir_separator );

const char* file_basename( const char* filename )
{
	assert( filename );
	return basename( filename, '/' );
}

bool is_file( const char* path )
{
	struct stat s;
	assert( path );

	if( stat( path, &s ) == 0 )
	{
		return S_ISREG( s.st_mode );
	}

	return false;
}

bool is_directory( const char* path )
{
    struct stat s;
	assert( path );

    if( stat( path, &s ) == 0 )
	{
        return S_ISDIR(s.st_mode);
    }

	return false;
}

bool directory_exists( const char* path )
{
    struct stat s;
	assert( path );
    return stat( path, &s ) != -1;
}

bool directory_create( const char* path )
{
	bool result = false;
	assert( path );

	if( !directory_exists( path ) )
	{
		result = mkdir( path, 0700 ) == 0;
	}

	return result;
}

extern char* path( const char* path, char dir_separator );

char* directory_path( const char* path )
{
	assert( path );
	return path( path, '/' );
}

