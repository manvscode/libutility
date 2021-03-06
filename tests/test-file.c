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
#include <time.h>
#include "xtd/filesystem.h"
#include "xtd/memory.h"
#include "xtd/console.h"


int main( int argc, char *argv[] )
{
	if( argc < 1 )
	{
		return -1;
	}

	char* file = argv[ 1 ];
	size_t size = 12425672300;
	printf( "size = %s\n", size_in_unit( size, unit_bytes, 0 ) );
	printf( "size = %s\n", size_in_unit( size, unit_megabytes, 2 ) );
	printf( "size = %s\n", size_in_unit( size, unit_mebibytes, 2 ) );
	printf( "app size = %s\n", size_in_best_unit( size, false, 1 ) );

	size_t text_size = 0;
	char* text = file_slurp( file, &text_size );
	if( text )
	{
        console_fg_color_8( stdout, CONSOLE_COLOR8_BRIGHT_GREEN );
		console_print_divider( stdout, file );
		printf( "%s", text );
		console_print_divider( stdout, NULL );
        console_reset( stdout );
		free( text );
	}

	const char* path1 = "/joe/apps/junk/";
	const char* path2 = "/joe/tests/omg";
	const char* path3 = "/ok.txt";
	const char* path4 = "/";

	const char* basename_path1 = file_basename( path1 );
	printf( "basename_path1 = \"%s\" --> \"%s\"\n", path1, basename_path1 );

	const char* basename_path2 = file_basename( path2 );
	printf( "basename_path2 = \"%s\" --> \"%s\"\n", path2, basename_path2 );

	const char* basename_path3 = file_basename( path3 );
	printf( "basename_path3 = \"%s\" --> \"%s\"\n", path3, basename_path3 );

	char* path_path1 = directory_path( path1 );
	printf( "path_path1 = \"%s\" --> \"%s\"\n", path1, path_path1 );
	free( path_path1 );

	char buffer[ 256 ];
	directory_path_r( path2, buffer, sizeof(buffer) );
	printf( "path_path2 = \"%s\" --> \"%s\"\n", path2, buffer );

	char* path_path3 = directory_path( path3 );
	printf( "path_path3 = \"%s\" --> \"%s\"\n", path3, path_path3 );
	free( path_path3 );

	directory_path_r( path4, buffer, sizeof(buffer) );
	printf( "path_path4 = \"%s\" --> \"%s\"\n", path4, buffer );

	const char* dir = "/tmp/foobar/0/a/b/c";

	if( directory_exists( dir ) )
	{
		file_delete( dir );
	}

	if( directory_create( dir ) )
	{
		printf( "Created %s successfully.\n", dir );
	}
	else
	{
		printf( "Failed to create %s.\n", dir );
	}

	if( directory_delete( "/tmp/foobar", true ) )
	{
		printf( "Deleted %s successfully.\n", dir );
	}
	else
	{
		printf( "Failed to delete %s.\n", dir );
	}

	return 0;
}
