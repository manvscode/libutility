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
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "xtd/filesystem.h"

void handle_file( const char* filename, void* args );


int main( int argc, char *argv[] )
{
	if( argc < 1 )
	{
		return -1;
	}

	char* path = argv[ 1 ];
	int count = 0;

	directory_enumerate( path, true, ENUMERATE_FILES, handle_file, &count );


	const char* path1 = "/joe/apps/junk/";
	const char* path2 = "/joe/apps/junk/omg";
	const char* path3 = "/";

	const char* basename_path1 = file_basename( path1 );
	const char* basename_path2 = file_basename( path2 );
	const char* basename_path3 = file_basename( path3 );

	printf( "basename_path1 = %s --> %s\n", path1, basename_path1 );
	printf( "basename_path2 = %s --> %s\n", path2, basename_path2 );
	printf( "basename_path3 = %s --> %s\n", path3, basename_path3 );

	char* path_path1 = directory_path( path1 );
	char* path_path2 = directory_path( path2 );
	char* path_path3 = directory_path( path3 );

	printf( "path_path1 = %s --> %s\n", path1, path_path1 );
	printf( "path_path2 = %s --> %s\n", path2, path_path2 );
	printf( "path_path3 = %s --> %s\n", path3, path_path3 );

	bool dir_created = directory_create( path3 );
	if( dir_created )
	{
		printf( "%s was created.\n", path3);
	}

	return 0;
}

void handle_file( const char* filename, void* args )
{
	bool is_dir = is_directory( filename );


	int* count = (int*) args;
	(*count)++;
	printf( "%3d.) %4s --> %-60s\n", *count, is_dir ? "DIR" : "FILE", filename );
	assert( !is_dir );
}
