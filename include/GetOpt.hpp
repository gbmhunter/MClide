//!
//! @file 			GetOpt.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013/03/19
//! @last-modified 	2014/01/14
//! @brief 			Header file for the getopt() function.
//! @details
//!					See README.rst in repo root dir for more info.

//======= ORIGINAL LICENSE =========//

/* Declarations for getopt.
   Copyright (C) 1989-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif
  
#ifndef CLIDE_GETOPT_H
#define CLIDE_GETOPT_H 1
   
namespace Clide
{


	class GetOpt
	{
		public:
		
			//! @brief		For communication from `getopt' to the caller.
			//! @details	When `getopt' finds an option that takes an argument,
			//!				the argument value is returned here.
			//!				Also, when `ordering' is RETURN_IN_ORDER,
			//!				each non-option ARGV-element is returned here.
			static char *optarg;

		/* Index in ARGV of the next element to be scanned.
		   This is used for communication to and from the caller
		   and for communication between successive calls to `getopt'.

		   On entry to `getopt', zero means this is the first call; initialize.

		   When `getopt' returns -1, this is the index of the first of the
		   non-option elements that the caller should itself scan.

		   Otherwise, `optind' communicates from one call to the next
		   how much of ARGV has been scanned so far.  */
			static int optind;

			//! @brief		Callers store zero here to inhibit the error message `getopt' prints
			//!				for unrecognized options.
			static int opterr;

			//! @brief 		Set to an option character which was unrecognized.
			static int optopt;

		/* Describe the long-named options requested by the application.
		   The LONG_OPTIONS argument to getopt_long or getopt_long_only is a vector
		   of `struct option' terminated by an element containing a name which is
		   zero.

		   The field `has_arg' is:
		   no_argument		(or 0) if the option does not take an argument,
		   required_argument	(or 1) if the option requires an argument,
		   optional_argument 	(or 2) if the option takes an optional argument.

		   If the field `flag' is not NULL, it points to a variable that is set
		   to the value given in the field `val' when the option is found, but
		   left unchanged if the option is not found.

		   To have a long-named option do something other than set an `int' to
		   a compiled-in constant, such as set a value from `optarg', set the
		   option's `flag' field to zero and its `val' field to a nonzero
		   value (the equivalent single-letter option character, if there is
		   one).  For long options that have a zero `flag' field, `getopt'
		   returns the contents of the `val' field.  */

			struct option
			{
				const char *name;
				// has_arg can't be an enum because some compilers complain about
				// type mismatches in all the code that assumes it is an int. 
				int has_arg;
				int *flag;
				int val;
			};

			/* Names for the values of the `has_arg' field of `struct option'.  */

			# define no_argument		0
			# define required_argument	1
			# define optional_argument	2


		/* Get definitions and prototypes for functions to process the
		   arguments in ARGV (ARGC of them, minus the program name) for
		   options given in OPTS.

		   Return the option character from OPTS just read.  Return -1 when
		   there are no more options.  For unrecognized options, or options
		   missing arguments, `optopt' is set to the option letter, and '?' is
		   returned.

		   The OPTS string is a list of characters which are recognized option
		   letters, optionally followed by colons, specifying that that letter
		   takes an argument, to be placed in `optarg'.

		   If a letter in OPTS is followed by two colons, its argument is
		   optional.  This behavior is specific to the GNU `getopt'.

		   The argument `--' causes premature termination of argument
		   scanning, explicitly telling `getopt' that there are no more
		   options.

		   If OPTS begins with `--', then non-option arguments are treated as
		   arguments to the option '\0'.  This behavior is specific to the GNU
		   `getopt'.  */

		/* Many other libraries have conflicting prototypes for getopt, with
		   differences in the consts, in stdlib.h.  To avoid compilation
		   errors, only prototype getopt for the GNU C library.  */
			static int getopt(
				int ___argc,
				char *const *___argv,
				const char *__shortopts);
		
			static int getopt_long(
				int ___argc,
				char *const *___argv,
				const char *__shortopts,
				const struct option *__longopts,
				int *__longind);
				
		private:
		
			// Data type for reentrant functions.
			typedef struct
			{
				/* These have exactly the same meaning as the corresponding global
				variables, except that they are used for the reentrant
				versions of getopt.  */
				int optind;
				int opterr;
				int optopt;
				char *optarg;

				/* Internal members.  */

				/* True if the internal members have been initialized.  */
				int __initialized;

				/* The next char to be scanned in the option-element
				in which the last option character we returned was found.
				This allows us to pick up the scan where we left off.

				If this is zero, or a null string, it means resume the scan
				by advancing to the next ARGV-element.  */
				char *__nextchar;

				/* Describe how to deal with options that follow non-option ARGV-elements.

				If the caller did not specify anything,
				the default is REQUIRE_ORDER if the environment variable
				POSIXLY_CORRECT is defined, PERMUTE otherwise.

				REQUIRE_ORDER means don't recognize them as options;
				stop option processing when the first non-option is seen.
				This is what Unix does.
				This mode of operation is selected by either setting the environment
				variable POSIXLY_CORRECT, or using `+' as the first character
				of the list of option characters.

				PERMUTE is the default.  We permute the contents of ARGV as we
				scan, so that eventually all the non-options are at the end.
				This allows options to be given in any order, even with programs
				that were not written to expect this.

				RETURN_IN_ORDER is an option available to programs that were
				written to expect options and other ARGV-elements in any order
				and that care about the ordering of the two.  We describe each
				non-option ARGV-element as if it were the argument of an option
				with character code 1.  Using `-' as the first character of the
				list of option characters selects this mode of operation.

				The special argument `--' forces an end of option-scanning regardless
				of the value of `ordering'.  In the case of RETURN_IN_ORDER, only
				`--' can cause `getopt' to return -1 with `optind' != ARGC.  */

				enum
				{
					REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
				} __ordering;

				/* If the POSIXLY_CORRECT environment variable is set.  */
				int __posixly_correct;


				/* Handle permutation of arguments.  */

				/* Describe the part of ARGV that contains non-options that have
				been skipped.  `first_nonopt' is the index in ARGV of the first
				of them; `last_nonopt' is the index after the last of them.  */

				int __first_nonopt;
				int __last_nonopt;

			} _getopt_data;
			
			static _getopt_data getopt_data;
			
			static void exchange(char **argv, GetOpt::_getopt_data *d);
			
			static const char* _getopt_initialize(
				int argc,
				char *const *argv,
				const char *optstring,
				_getopt_data *d,
				int posixly_correct);
				
			static int _getopt_internal_r(
				int argc,
				char *const *argv,
				const char *optstring,
				const struct option *longopts,
				int *longind,
				int long_only,
				_getopt_data *d,
				int posixly_correct);
				
			static int _getopt_internal(
				int argc,
				char *const *argv,
				const char *optstring,
				const struct option *longopts,
				int *longind,
				int long_only,
				int posixly_correct);
	};
}

#endif // #ifndef CLIDE_GETOPT_H
