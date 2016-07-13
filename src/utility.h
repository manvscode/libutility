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
#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
#include <stdbool.h>
#include <stdint.h>
#else
#error "Need a C99 compiler."
#endif
#define PATH_REENTRANT  1

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Reference Counting
 */
void* refobj_alloc   ( size_t size, void (*destroy) ( void* ptr ) );
void  refobj_retain  ( void* obj );
void  refobj_release ( void* obj );

/*
 * File IO
 */
typedef void (*file_enumerate_fxn_t) ( const char* filename, void* args );
typedef enum directory_enumerate_mode {
	ENUMERATE_FILES,
	ENUMERATE_DIRECTORIES,
	ENUMERATE_ALL
} directory_enumerate_mode_t;

bool        file_exists              ( const char* path );
bool        file_is_writeable        ( const char* path );
bool        file_is_readable         ( const char* path );
bool        file_is_executable       ( const char* path );
bool        file_copy                ( const char* src_path, const char* dst_path );
bool        file_delete              ( const char* path );
int64_t     file_size                ( const char* path );
const char* file_size_string         ( const char* path, bool use_base_two, int precision );
int64_t     file_age                 ( const char* path ); /* returns -1 on error */
const char* file_basename            ( const char* path );
const char* file_extension           ( const char* filename );
char*       file_load_contents       ( const char* path, size_t* size ); /* allocates memory */
bool        is_file                  ( const char* path );
bool        is_directory             ( const char* path );
bool        directory_exists         ( const char* path );
bool        directory_create         ( const char* path );
char*       directory_path           ( const char* path ); /* allocates memory */
void        directory_enumerate      ( const char* path, bool recursive, directory_enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args );
int         readline                 ( char* buffer, size_t size, FILE* stream );

typedef enum size_unit {
	unit_bytes = 0,

	unit_kilobytes,
	unit_megabytes,
	unit_gigabytes,
	unit_terabytes,
	unit_petabytes,
	unit_exabytes,

	unit_kibibytes,
	unit_mebibytes,
	unit_gibibytes,
	unit_tebibytes,
	unit_exibytes
} size_unit_t;

const char* size_in_unit      ( size_t size, size_unit_t unit, int precision );
const char* size_in_best_unit ( size_t size, bool use_base_two, int precision );

/*
 * Checksums and Hashes
 */
uint32_t java_hash         ( const uint8_t* data, size_t len );
uint32_t xor8              ( const uint8_t* data, size_t len );
uint32_t adler32           ( const uint8_t* data, size_t len );
uint16_t fletcher16_simple ( uint8_t* data, size_t len );
void     fletcher16        ( uint8_t* checkA, uint8_t* checkB, uint8_t* data, size_t len ); /* faster */
uint32_t fletcher32        ( uint16_t* data, size_t len );

/*
 * Compression and encodings.
 */
bool  huffman_encode ( const void* original, size_t original_size, void** compressed, size_t* compressed_size );
bool  huffman_decode ( const void* compressed, size_t compressed_size, void** original, size_t* original_size );
char* base64_encode  ( const void* in, size_t in_size, size_t* out_len );
void* base64_decode  ( const char* in, size_t in_len, size_t* out_size );

/*
 * Strings
 */
typedef enum random_string_type {
	RAND_STRING_ALPHA_NUMERIC = 0,
	RAND_STRING_ALPHA,
	RAND_STRING_HEX,
	RAND_STRING_NUMERIC,
	RAND_STRING_NO_ZERO,
	RAND_STRING_DISTINCT,
} string_random_type_t;

size_t      string_left_trim  ( char* s, const char* delimeters );
size_t      string_right_trim ( char* s, const char* delimeters );
size_t      string_trim       ( char* s, const char* delimeters );
char*       string_to_lower   ( char* s );
char*       string_to_upper   ( char* s );
void        string_random     ( string_random_type_t type, char* string, size_t length );
const char* string_ordinal    ( long number );
char*       string_replace    ( const char* orig, const char* rep, const char* with ); /* result must be freed */
char*       string_substring  ( const char* str, size_t start, size_t end );

/*
 * Console
 */
#define console_fg_normal_black()   "\033[30m"
#define console_fg_normal_red()     "\033[31m"
#define console_fg_normal_green()   "\033[32m"
#define console_fg_normal_yellow()  "\033[33m"
#define console_fg_normal_blue()    "\033[34m"
#define console_fg_normal_magenta() "\033[35m"
#define console_fg_normal_cyan()    "\033[36m"
#define console_fg_normal_white()   "\033[37m"
#define console_fg_bright_black()   "\033[30;1m"
#define console_fg_bright_red()     "\033[31;1m"
#define console_fg_bright_green()   "\033[32;1m"
#define console_fg_bright_yellow()  "\033[33;1m"
#define console_fg_bright_blue()    "\033[34;1m"
#define console_fg_bright_magenta() "\033[35;1m"
#define console_fg_bright_cyan()    "\033[36;1m"
#define console_fg_bright_white()   "\033[37;1m"
#define console_bold()              "\033[1m"
#define console_underline()         "\033[4m"
#define console_reversed()          "\033[7m"
#define console_reset()             "\033[0m"
#define console_save_position( )    "\033[s"
#define console_restore_position( ) "\033[u"
#define console_clear_screen_to_end()    console_clear_screen( 0 ) // clears from cursor to end of screen
#define console_clear_screen_from_beg()  console_clear_screen( 1 ) // clears from cursor to start of screen
#define console_clear_screen_all()       console_clear_screen( 2 ) // clears whole screen
#define console_clear_line_to_end()      console_clear_line( 0 ) // from cursor to end of line
#define console_clear_line_from_beg()    console_clear_line( 1 ) // from cursor to start of line
#define console_clear_line_all()         console_clear_line( 2 ) // clears whole line
typedef void (*console_progress_fxn_t) ( int* percent, void* data );

void console_fg_color_256          ( int color );
void console_bg_color_256          ( int color );
void console_move_up               ( int n );
void console_move_down             ( int n );
void console_move_left             ( int n );
void console_move_right            ( int n );
void console_bar_graph             ( int bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent );
void console_progress_indicator_ex ( const char* task, int progress_bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, console_progress_fxn_t fxn, void* data );
typedef enum progress_indictor_style {
    PROGRESS_INDICATOR_STYLE_BLUE,
    PROGRESS_INDICATOR_STYLE_FADE,
    PROGRESS_INDICATOR_STYLE_INTENSITY,
} progress_indictor_style_t;
void console_progress_indicator    ( const char* task, progress_indictor_style_t style, console_progress_fxn_t fxn, void* data );
void console_next_line             ( int n );
void console_prev_line             ( int n );
void console_set_column            ( int x );
void console_goto                  ( int x, int y );
void console_clear_screen          ( int type );
void console_clear_line            ( int type );
void print_divider                 ( FILE* fd, const char* title );


/*
 * Misscellaneous
 */

const char* byte_to_binary         ( uint8_t x );
void        buffer_scramble        ( const char* key, void* buffer, size_t size, unsigned short pivot );
void        buffer_unscramble      ( const char* key, void* buffer, size_t size, unsigned short pivot );
void        xor_bytes              ( const void* a, size_t a_size, const void* b, size_t b_size, void* result );
void        swap                   ( void* left, void* right, size_t size );
bool        is_big_endian          ( void );
void        hton                   ( void* mem, size_t size );
void        ntoh                   ( void* mem, size_t size );
char*       debug_buffer_to_string ( const void* data, size_t size, size_t grouping, bool with_spaces ); /* allocates memory */

/*
 *  Timer
 */
double   time_seconds      ( void );
double   time_milliseconds ( void );
uint64_t time_secs         ( void );
uint64_t time_msecs        ( void );
void     time_msleep       ( int milliseconds );

/*
 *  Encryption
 */
void caesar_cypher_encrypt_buffer ( void* buffer, size_t size, int n );
void caesar_cypher_decrypt_buffer ( void* buffer, size_t size, int n );
void caesar_cypher_encrypt_text   ( char* text, size_t size, int n );
void caesar_cypher_decrypt_text   ( char* text, size_t size, int n );

/*
 * Macros
 */
#define Ob(x)                           ((unsigned)Ob_(0 ## x ## uL))
#define Ob_(x)                          (x & 1 | x >> 2 & 2 | x >> 4 & 4 | x >> 6 & 8 | x >> 8 & 16 | x >> 10 & 32 | x >> 12 & 64 | x >> 14 & 128)
#define bit_is_disabled( flag, flags )  (!bit_is_set(flag, flags))
#define bit_is_enabled( flag, flags )   (bit_is_set(flag, flags))
#define bit_is_set( flag, flags )       (((flags) & (flag)) != 0)
#define bit_toggle( flag, flags )       ((flags) ^= (flag))
#define bit_set( flag, flags )          ((flags) |= (flag))
#define bit_unset( flag, flags )        ((flags) &= ~(flag))


#ifdef __cplusplus
} /* extern "C" */
namespace utility {
	using ::file_exists;
	using ::file_is_writeable;
	using ::file_is_readable;
	using ::file_is_executable;
	using ::file_copy;
	using ::file_delete;
	using ::file_size;
	using ::file_size_string;
	using ::file_age;
	using ::file_basename;
	using ::file_load_contents;
	using ::is_file;
	using ::is_directory;
	using ::directory_exists;
	using ::directory_create;
	using ::directory_path;
	using ::directory_enumerate;
	using ::file_enumerate_fxn_t;
	using ::size_unit_t;
	using ::size_in_unit;
	using ::size_in_best_unit;
	using ::java_hash;
	using ::xor8;
	using ::adler32;
	using ::fletcher16_simple;
	using ::fletcher16;
	using ::fletcher32;
	using ::huffman_encode;
	using ::huffman_decode;
	using ::string_random_type_t;
	using ::print_divider;
	using ::byte_to_binary;
	using ::buffer_scramble;
	using ::buffer_unscramble;
	using ::string_random;
	using ::string_ordinal;
	using ::xor_bytes;
	using ::swap;
	using ::is_big_endian;
	using ::hton;
	using ::ntoh;
	using ::debug_buffer_to_string;
	using ::time_seconds;
	using ::time_milliseconds;
	using ::time_secs;
	using ::time_msecs;
	using ::time_msleep;
	using ::caesar_cypher_encrypt_buffer;
	using ::caesar_cypher_decrypt_buffer;
	using ::caesar_cypher_encrypt_text;
	using ::caesar_cypher_decrypt_text;
} /* namespace */
#endif
#endif /* _UTILITY_H_ */
