//!
//! @file 				GetOpt.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created			2013/03/19
//! @last-modified 		2014/03/21
//! @brief 				Clide's own getopt() function. It was decided not to reply on the standard C version of this as the implementation varied between "standard" C libraries.
//! @details
//!						See README.rst in repo root dir for more info.

//======= ORIGINAL LICENSE =========//

/* Getopt for GNU.
   NOTE: getopt is part of the C library, so if you don't know what
   "Keep this file name-space clean" means, talk to drepper@gnu.org
   before changing it!
   Copyright (C) 1987-2013 Free Software Foundation, Inc.
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

#include <stddef.h>
#include <string.h>
#include <alloca.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/Config.hpp"
#include "../include/Global.hpp"
#include "../include/Print.hpp"
#include "../include/GetOpt.hpp"

namespace Clide
{

	#ifndef attribute_hidden
		#define attribute_hidden
	#endif
	

/* This version of `getopt' appears to the caller like standard Unix `getopt'
   but it behaves differently for the user, since it allows the user
   to intersperse the options with the other arguments.

   As `getopt' works, it permutes the elements of ARGV so that,
   when it is done, all the options precede everything else.  Thus
   all application programs are extended to handle flexible argument order.

   Setting the environment variable POSIXLY_CORRECT disables permutation.
   Then the behavior is completely standard.

   GNU application programs can use a third alternative mode in which
   they can distinguish the relative order of options and other arguments.  */


	

	/* For communication from `getopt' to the caller.
	   When `getopt' finds an option that takes an argument,
	   the argument value is returned here.
	   Also, when `ordering' is RETURN_IN_ORDER,
	   each non-option ARGV-element is returned here.  */

	char* GetOpt::optarg;

	/* Index in ARGV of the next element to be scanned.
	   This is used for communication to and from the caller
	   and for communication between successive calls to `getopt'.

	   On entry to `getopt', zero means this is the first call; initialize.

	   When `getopt' returns -1, this is the index of the first of the
	   non-option elements that the caller should itself scan.

	   Otherwise, `optind' communicates from one call to the next
	   how much of ARGV has been scanned so far.  */

	/* 1003.2 says this must be 1 before any call.  */
	int GetOpt::optind = 1;

	/* Callers store zero here to inhibit the error message
	   for unrecognized options.  */

	int GetOpt::opterr = 1;

	/* Set to an option character which was unrecognized.
	   This must be initialized on some systems to avoid linking in the
	   system's own getopt implementation.  */

	int GetOpt::optopt = '?';

	/* Keep a Clide::Global copy of all internal members of getopt_data.  */

	GetOpt::_getopt_data GetOpt::getopt_data;

	#ifndef __GNU_LIBRARY__

	// Avoid depending on library functions or files
	// whose names are inconsistent.

	/* Commented out by gbmhunter 2014/01/06, as getenv() doesn't make sense in an embedded environment
	#ifndef getenv
	extern char *getenv ();
	#endif
	*/

	#endif /* not __GNU_LIBRARY__ */

	# define SWAP_FLAGS(ch1, ch2)

	/* Exchange two adjacent subsequences of ARGV.
	   One subsequence is elements [first_nonopt,last_nonopt)
	   which contains all the non-options that have been skipped so far.
	   The other is elements [last_nonopt,optind), which contains all
	   the options processed since those non-options were skipped.

	   `first_nonopt' and `last_nonopt' are relocated so that they describe
	   the new indices of the non-options in ARGV after they are moved.  */
	void GetOpt::exchange(char **argv, GetOpt::_getopt_data *d)
	{
		int bottom = d->__first_nonopt;
		int middle = d->__last_nonopt;
		int top = d->optind;
		char *tem;

		/* Exchange the shorter segment with the far end of the longer segment.
		 That puts the shorter segment into the right place.
		 It leaves the longer segment in the right place overall,
		 but it consists of two parts that need to be swapped next.  */

		while (top > middle && middle > bottom)
		{
			if (top - middle > middle - bottom)
			{
				/* Bottom segment is the short one.  */
				int len = middle - bottom;
				int i;

				/* Swap it with the top part of the top segment.  */
				for (i = 0; i < len; i++)
				{
					tem = argv[bottom + i];
					argv[bottom + i] = argv[top - (middle - bottom) + i];
					argv[top - (middle - bottom) + i] = tem;
					SWAP_FLAGS (bottom + i, top - (middle - bottom) + i);
				}
				/* Exclude the moved bottom segment from further swapping.  */
				top -= len;
			}
			else
			{
				/* Top segment is the short one.  */
				int len = top - middle;
				int i;

				/* Swap it with the bottom part of the bottom segment.  */
				for (i = 0; i < len; i++)
				{
					tem = argv[bottom + i];
					argv[bottom + i] = argv[middle + i];
					argv[middle + i] = tem;
					SWAP_FLAGS (bottom + i, middle + i);
				}
				// Exclude the moved top segment from further swapping.
				bottom += len;
			}
		}

		// Update records for the slots the non-options now occupy. 

		d->__first_nonopt += (d->optind - d->__last_nonopt);
		d->__last_nonopt = d->optind;
	}

	// Initialize the internal data when the first call is made.

	const char* GetOpt::_getopt_initialize(
		int argc,
		char *const *argv,
		const char *optstring,
		_getopt_data *d,
		int posixly_correct)
	{
		// Start processing options with ARGV-element 1 (since ARGV-element 0
		// is the program name); the sequence of previously skipped
		// non-option ARGV-elements is empty.

		d->__first_nonopt = d->__last_nonopt = d->optind;

		d->__nextchar = NULL;

		// Old, deleted by gbmhunter 2014/01/06, getenv() doesn't make sense in an embedded environment
		// d->__posixly_correct = posixly_correct | !!getenv ("POSIXLY_CORRECT");
		d->__posixly_correct = posixly_correct;

		// Determine how to handle the ordering of options and non-options.

		if (optstring[0] == '-')
		{
			d->__ordering = _getopt_data::RETURN_IN_ORDER;
			++optstring;
		}
		else if (optstring[0] == '+')
		{
			d->__ordering = _getopt_data::REQUIRE_ORDER;
			++optstring;
		}
		else if (d->__posixly_correct)
			d->__ordering = _getopt_data::REQUIRE_ORDER;
		else
			d->__ordering = _getopt_data::PERMUTE;

		return optstring;
	}

	/* Scan elements of ARGV (whose length is ARGC) for option characters
	   given in OPTSTRING.

	   If an element of ARGV starts with '-', and is not exactly "-" or "--",
	   then it is an option element.  The characters of this element
	   (aside from the initial '-') are option characters.  If `getopt'
	   is called repeatedly, it returns successively each of the option characters
	   from each of the option elements.

	   If `getopt' finds another option character, it returns that character,
	   updating `optind' and `nextchar' so that the next call to `getopt' can
	   resume the scan with the following option character or ARGV-element.

	   If there are no more option characters, `getopt' returns -1.
	   Then `optind' is the index in ARGV of the first ARGV-element
	   that is not an option.  (The ARGV-elements have been permuted
	   so that those that are not options now come last.)

	   OPTSTRING is a string containing the legitimate option characters.
	   If an option character is seen that is not listed in OPTSTRING,
	   return '?' after printing an error message.  If you set `opterr' to
	   zero, the error message is suppressed but we still return '?'.

	   If a char in OPTSTRING is followed by a colon, that means it wants an arg,
	   so the following text in the same ARGV-element, or the text of the following
	   ARGV-element, is returned in `optarg'.  Two colons mean an option that
	   wants an optional arg; if there is text in the current ARGV-element,
	   it is returned in `optarg', otherwise `optarg' is set to zero.

	   If OPTSTRING starts with `-' or `+', it requests different methods of
	   handling the non-option ARGV-elements.
	   See the comments about RETURN_IN_ORDER and REQUIRE_ORDER, above.

	   Long-named options begin with `--' instead of `-'.
	   Their names may be abbreviated as long as the abbreviation is unique
	   or is an exact match for some defined option.  If they have an
	   argument, it follows the option name in the same ARGV-element, separated
	   from the option name by a `=', or else the in next ARGV-element.
	   When `getopt' finds a long-named option, it returns 0 if that option's
	   `flag' field is nonzero, the value of the option's `val' field
	   if the `flag' field is zero.

	   The elements of ARGV aren't really const, because we permute them.
	   But we pretend they're const in the prototype to be compatible
	   with other systems.

	   LONGOPTS is a vector of `struct option' terminated by an
	   element containing a name which is zero.

	   LONGIND returns the index in LONGOPT of the long-named option found.
	   It is only valid when a long-named option has been found by the most
	   recent call.

	   If LONG_ONLY is nonzero, '-' as well as '--' can introduce
	   long-named options.  */

	int	GetOpt::_getopt_internal_r (
		int argc,
		char *const *argv,
		const char *optstring,
		const struct option *longopts,
		int *longind,
		int long_only,
		_getopt_data *d,
		int posixly_correct)
	{
		#if(clide_DEBUG_PRINT_VERBOSE == 1)
			Print::PrintDebugInfo("CLIDE: GetOpt() called.\r\n",
					Print::DebugPrintingLevel::VERBOSE);
		#endif
	
		#if(clide_DEBUG_PRINT_VERBOSE == 1)
			snprintf (
				Clide::Global::debugBuff,
				sizeof(Clide::Global::debugBuff),
				"CLIDE: GetOpt data.optind = '%i'. argc = '%i'.\r\n",
				d->optind,
				argc);
			Print::PrintDebugInfo(Clide::Global::debugBuff,
					Print::DebugPrintingLevel::VERBOSE);
		#endif
	
		int print_errors = d->opterr;

		if (argc < 1)
			return -1;

		d->optarg = NULL;

		// Initialisation
		if (d->optind == 0 || !d->__initialized)
		{
			#if(clide_DEBUG_PRINT_VERBOSE == 1)
				Print::PrintDebugInfo("CLIDE: Initialising GetOpt().\r\n",
						Print::DebugPrintingLevel::VERBOSE);
			#endif
			// Don't scan ARGV[0], the program name. 
			if (d->optind == 0)
				d->optind = 1;	
			
			optstring = _getopt_initialize (argc, argv, optstring, d,
						  posixly_correct);
			d->__initialized = 1;
		}
		else if (optstring[0] == '-' || optstring[0] == '+')
			optstring++;
		if (optstring[0] == ':')
			print_errors = 0;
		
		#if(clide_DEBUG_PRINT_VERBOSE == 1)
			snprintf (
				Clide::Global::debugBuff,
				sizeof(Clide::Global::debugBuff),
				"CLIDE: Testing whether argv['%i'] ('%s') points to a non-option argument.\r\n",
				d->optind,
				argv[d->optind]);
			Print::PrintDebugInfo(Clide::Global::debugBuff,
					Print::DebugPrintingLevel::VERBOSE);
		#endif
			
		  /* Test whether ARGV[optind] points to a non-option argument.
			 Either it does not have option syntax, or there is an environment flag
			 from the shell indicating it is not an option.  The later information
			 is only used when the used in the GNU libc.  */

		# define NONOPTION_P (argv[d->optind][0] != '-' || argv[d->optind][1] == '\0')

		if (d->__nextchar == NULL || *d->__nextchar == '\0')
		{
			// Advance to the next ARGV-element. 

			/* Give FIRST_NONOPT & LAST_NONOPT rational values if OPTIND has been
			moved back by the user (who may also have changed the arguments).  */
			if (d->__last_nonopt > d->optind)
				d->__last_nonopt = d->optind;
			if (d->__first_nonopt > d->optind)
				d->__first_nonopt = d->optind;

			if (d->__ordering == _getopt_data::PERMUTE)
			{
				/* If we have just processed some options following some non-options,
				 exchange them so that the options come first.  */

				if (d->__first_nonopt != d->__last_nonopt
				  && d->__last_nonopt != d->optind)
					exchange ((char **) argv, d);
				else if (d->__last_nonopt != d->optind)
					d->__first_nonopt = d->optind;

				/* Skip any additional non-options
				and extend the range of non-options previously skipped.  */

				while (d->optind < argc && NONOPTION_P)
					d->optind++;
				d->__last_nonopt = d->optind;
			}

			// The special ARGV-element `--' means premature end of options.
			// Skip it like a null option,
			// then exchange with previous non-options as if it were an option,
			//then skip everything else like a non-option.

			if (d->optind != argc && !strcmp (argv[d->optind], "--"))
			{
				d->optind++;

				if (d->__first_nonopt != d->__last_nonopt
					&& d->__last_nonopt != d->optind)
					exchange ((char **) argv, d);
				else if (d->__first_nonopt == d->__last_nonopt)
					d->__first_nonopt = d->optind;
				d->__last_nonopt = argc;

				d->optind = argc;
			}

			// If we have done all the ARGV-elements, stop the scan
			// and back over any non-options that we skipped and permuted.
			if (d->optind == argc)
			{
				// Set the next-arg-index to point at the non-options
				// that we previously skipped, so the caller will digest them.
				if (d->__first_nonopt != d->__last_nonopt)
					d->optind = d->__first_nonopt;
				{
					#if(clide_DEBUG_PRINT_VERBOSE == 1)
						Print::PrintDebugInfo("CLIDE: GetOpt() finished. optind == argc. Returning -1.\r\n",
								Print::DebugPrintingLevel::VERBOSE);
					#endif
					return -1;
				}
				
			}

			// If we have come to a non-option and did not permute it,
			// either stop the scan or describe it to the caller and pass it by.
			if (NONOPTION_P)
			{
				if (d->__ordering == _getopt_data::REQUIRE_ORDER)
				{
					#if(clide_DEBUG_PRINT_VERBOSE == 1)
						Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning -1.\r\n",
								Print::DebugPrintingLevel::VERBOSE);
					#endif
					return -1;
				}
				d->optarg = argv[d->optind++];
				#if(clide_DEBUG_PRINT_VERBOSE == 1)
					Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning 1.\r\n",
							Print::DebugPrintingLevel::VERBOSE);
				#endif
				return 1;
			}

				// We have found another option-ARGV-element.
				// Skip the initial punctuation.

				d->__nextchar = (argv[d->optind] + 1
					+ (longopts != NULL && argv[d->optind][1] == '-'));
			}

			// Decode the current option-ARGV-element.

			/* Check whether the ARGV-element is a long option.

			 If long_only and the ARGV-element has the form "-f", where f is
			 a valid short option, don't consider it an abbreviated form of
			 a long option that starts with f.  Otherwise there would be no
			 way to give the -f short option.

			 On the other hand, if there's a long option "fubar" and
			 the ARGV-element is "-fu", do consider that an abbreviation of
			 the long option, just like "--fu", and not "-f" with arg "u".

			 This distinction seems to be the most useful approach.  */

			if (longopts != NULL
				&& (argv[d->optind][1] == '-'
				|| (long_only && (argv[d->optind][2]
				|| !strchr (optstring, argv[d->optind][1])))))
			{
				char *nameend;
				unsigned int namelen;
				const struct option *p;
				const struct option *pfound = NULL;
				
				struct option_list
				{
					const struct option *p;
					struct option_list *next;
				} *ambig_list = NULL;
				
				int exact = 0;
				int indfound = -1;
				int option_index;

				for (nameend = d->__nextchar; *nameend && *nameend != '='; nameend++)
				// Do nothing. 
					;
				
				namelen = nameend - d->__nextchar;

				  /* Test all long options for either exact match
				 or abbreviated matches.  */
				for (p = longopts, option_index = 0; p->name; p++, option_index++)
					if (!strncmp (p->name, d->__nextchar, namelen))
					{
						if (namelen == (unsigned int) strlen (p->name))
						{
							/* Exact match found.  */
							pfound = p;
							indfound = option_index;
							exact = 1;
							break;
						}
						else if (pfound == NULL)
						{
							/* First nonexact match found.  */
							pfound = p;
							indfound = option_index;
						}
						else if (long_only
							 || pfound->has_arg != p->has_arg
							 || pfound->flag != p->flag
							 || pfound->val != p->val)
						{
							// Second or later nonexact match found. 
							struct option_list *newp = (struct option_list*)alloca(sizeof (*newp));
							newp->p = p;
							newp->next = ambig_list;
							ambig_list = newp;
						}
					}

				if (ambig_list != NULL && !exact)
				{
					if (print_errors)
					{
						struct option_list first;
						first.p = pfound;
						first.next = ambig_list;
						ambig_list = &first;
						#if(clide_DEBUG_PRINT_ERROR == 1)
							snprintf (
								Clide::Global::debugBuff,
								sizeof(Clide::Global::debugBuff),
								"%s: option '%s' is ambiguous; possibilities:",
								argv[0], argv[d->optind]);
							Print::PrintError(Clide::Global::debugBuff);
						#endif
						do
						{
							#if(clide_DEBUG_PRINT_ERROR == 1)
								snprintf (
									Clide::Global::debugBuff,
									sizeof(Clide::Global::debugBuff),
									" '--%s'",
									ambig_list->p->name);
								ambig_list = ambig_list->next;
								Print::PrintError(Clide::Global::debugBuff);
							#endif
						}
						while (ambig_list != NULL);

							#if(clide_DEBUG_PRINT_ERROR == 1)
								snprintf(
									Clide::Global::debugBuff,
									sizeof(Clide::Global::debugBuff),
									"%s"
									"\n");
								Print::PrintError(Clide::Global::debugBuff);
							#endif
					}
					d->__nextchar += strlen (d->__nextchar);
					d->optind++;
					d->optopt = 0;
					#if(clide_DEBUG_PRINT_VERBOSE == 1)
						Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning ?.\r\n",
								Print::DebugPrintingLevel::VERBOSE);
					#endif
					return '?';
				}

				if (pfound != NULL)
				{
					option_index = indfound;
					d->optind++;
					if (*nameend)
					{
						/* Don't test has_arg with >, because some C compilers don't
						allow it to be used on enums.  */
						if (pfound->has_arg)
						d->optarg = nameend + 1;
						else
						{
							if (print_errors)
							{

								if (argv[d->optind - 1][1] == '-')
								{
									// --option
									#if(clide_DEBUG_PRINT_ERROR == 1)
										snprintf (
											Clide::Global::debugBuff,
											sizeof(Clide::Global::debugBuff),
											"%s: option '--%s' doesn't allow an argument\n",
											argv[0],
											pfound->name);
										Print::PrintError(Clide::Global::debugBuff);
									#endif
								}
								  else
								{
									// +option or -option
									#if(clide_DEBUG_PRINT_ERROR == 1)
										snprintf (
											Clide::Global::debugBuff,
											sizeof(Clide::Global::debugBuff),
											"%s: option '%c%s' doesn't allow an argument\n",
											argv[0], argv[d->optind - 1][0],
											pfound->name);
										Print::PrintError(Clide::Global::debugBuff);
									#endif
								}
							}

							d->__nextchar += strlen (d->__nextchar);

							d->optopt = pfound->val;
							#if(clide_DEBUG_PRINT_VERBOSE == 1)
								Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning ?.\r\n",
										Print::DebugPrintingLevel::VERBOSE);
							#endif
							return '?';
						}
					}
					else if (pfound->has_arg == 1)
					{
						if (d->optind < argc)
							d->optarg = argv[d->optind++];
						else
						{
							if (print_errors)
							{
								#if(clide_DEBUG_PRINT_ERROR == 1)
									snprintf (
										Clide::Global::debugBuff,
										sizeof(Clide::Global::debugBuff),
									   "%s: option '--%s' requires an argument\n",
									   argv[0], pfound->name);
									Print::PrintError(Clide::Global::debugBuff);
								#endif
							}
							d->__nextchar += strlen (d->__nextchar);
							d->optopt = pfound->val;
							#if(clide_DEBUG_PRINT_VERBOSE == 1)
								Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning : or ?.\r\n",
										Print::DebugPrintingLevel::VERBOSE);
							#endif
							return optstring[0] == ':' ? ':' : '?';
						}
					}
					d->__nextchar += strlen (d->__nextchar);
					if (longind != NULL)
						*longind = option_index;
					if (pfound->flag)
					{
						*(pfound->flag) = pfound->val;
						#if(clide_DEBUG_PRINT_VERBOSE == 1)
							Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning 0.\r\n",
									Print::DebugPrintingLevel::VERBOSE);
						#endif
						return 0;
					}
					return pfound->val;
				}

				  /* Can't find it as a long option.  If this is not getopt_long_only,
				 or the option starts with '--' or is not a valid short
				 option, then it's an error.
				 Otherwise interpret it as a short option.  */
				if (!long_only || argv[d->optind][1] == '-'
					|| strchr (optstring, *d->__nextchar) == NULL)
				{
					if (print_errors)
					{

						if (argv[d->optind][1] == '-')
						{
							// --option 
							#if(clide_DEBUG_PRINT_ERROR == 1)
								snprintf (
									Clide::Global::debugBuff,
									sizeof(Clide::Global::debugBuff),
									"%s: unrecognized option '--%s'\n",
									argv[0], 
									d->__nextchar);
								Print::PrintError(Clide::Global::debugBuff);
							#endif
						}
						else
						{
							// +option or -option
							#if(clide_DEBUG_PRINT_ERROR == 1)
								snprintf (
									Clide::Global::debugBuff,
									sizeof(Clide::Global::debugBuff),
									"%s: unrecognized option '%c%s'\n",
									argv[0],
									argv[d->optind][0],
									d->__nextchar);
								Print::PrintError(Clide::Global::debugBuff);
							#endif
						}
					}
					d->__nextchar = (char *) "";
					d->optind++;
					d->optopt = 0;
					#if(clide_DEBUG_PRINT_VERBOSE == 1)
						Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning ?.\r\n",
								Print::DebugPrintingLevel::VERBOSE);
					#endif
					return '?';
				}
			}

		// Look at and handle the next short option-character.

		{
			char c = *d->__nextchar++;
			char *temp = (char*)strchr(optstring, c);

			// Increment `optind' when we start to process its last character.
			if (*d->__nextchar == '\0')
				++d->optind;

			if (temp == NULL || c == ':' || c == ';')
			{
				if(print_errors)
				{

					#if(clide_DEBUG_PRINT_ERROR == 1)
						snprintf (
							Clide::Global::debugBuff,
							sizeof(Clide::Global::debugBuff),
							"%s: invalid option -- '%c'\n",
							argv[0],
							c);
						Print::PrintError(Clide::Global::debugBuff);
					#endif
				}
				d->optopt = c;
				#if(clide_DEBUG_PRINT_VERBOSE == 1)
					Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning ?.\r\n",
							Print::DebugPrintingLevel::VERBOSE);
				#endif
				return '?';
			}
			// Convenience. Treat POSIX -W foo same as long option --foo
			if (temp[0] == 'W' && temp[1] == ';')
			{
				char *nameend;
				const struct option *p;
				const struct option *pfound = NULL;
				int exact = 0;
				int ambig = 0;
				int indfound = 0;
				int option_index;
			
				if (longopts == NULL)
					goto no_longs;

				// This is an option that requires an argument.
				if (*d->__nextchar != '\0')
				{
					d->optarg = d->__nextchar;
					// If we end this ARGV-element by taking the rest as an arg,
					// we must advance to the next element now.
					d->optind++;
				}
				else if (d->optind == argc)
				{
					if (print_errors)
					{
						#if(clide_DEBUG_PRINT_ERROR == 1)
							snprintf (
								Clide::Global::debugBuff,
								sizeof(Clide::Global::debugBuff),
								"%s: option requires an argument -- '%c'\n",
								argv[0],
								c);
							Print::PrintError(Clide::Global::debugBuff);
						#endif
					}
					d->optopt = c;
					if (optstring[0] == ':')
						c = ':';
					else
						c = '?';
						#if(clide_DEBUG_PRINT_VERBOSE == 1)
							Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning ?.\r\n",
									Print::DebugPrintingLevel::VERBOSE);
						#endif
						return c;
				}
				else
					// We already incremented `d->optind' once;
					// increment it again when taking next ARGV-elt as argument.
					d->optarg = argv[d->optind++];

				// optarg is now the argument, see if it's in the
				// table of longopts.

				for (d->__nextchar = nameend = d->optarg; *nameend && *nameend != '=';
					 nameend++)
					// Do nothing.  
					;

				// Test all long options for either exact match
				// or abbreviated matches. 
				for (p = longopts, option_index = 0; p->name; p++, option_index++)
					if (!strncmp (p->name, d->__nextchar, nameend - d->__nextchar))
					{
						if ((unsigned int) (nameend - d->__nextchar) == strlen (p->name))
						{
							/* Exact match found.  */
							pfound = p;
							indfound = option_index;
							exact = 1;
							break;
						}
						else if (pfound == NULL)
						{
							// First nonexact match found.
							pfound = p;
							indfound = option_index;
						}
						else if (long_only
							   || pfound->has_arg != p->has_arg
							   || pfound->flag != p->flag
							   || pfound->val != p->val)
						// Second or later nonexact match found.
						ambig = 1;
					}
				if (ambig && !exact)
				{
					if (print_errors)
					{
						#if(clide_DEBUG_PRINT_ERROR == 1)
							snprintf (
								Clide::Global::debugBuff,
								sizeof(Clide::Global::debugBuff),
								"%s: option '-W %s' is ambiguous\n",
								argv[0],
								d->optarg);
							Print::PrintError(Clide::Global::debugBuff);
						#endif
					}
					d->__nextchar += strlen (d->__nextchar);
					d->optind++;
					#if(clide_DEBUG_PRINT_VERBOSE == 1)
						Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning ?.\r\n",
								Print::DebugPrintingLevel::VERBOSE);
					#endif
					return '?';
				}
				if (pfound != NULL)
				{
					option_index = indfound;
					if (*nameend)
					{
						// Don't test has_arg with >, because some C compilers don't
						// allow it to be used on enums.
						if (pfound->has_arg)
							d->optarg = nameend + 1;
						else
						{
							if (print_errors)
							{
								#if(clide_DEBUG_PRINT_ERROR == 1)
									snprintf (
										Clide::Global::debugBuff,
										sizeof(Clide::Global::debugBuff),
										"%s: option '-W %s' doesn't allow an argument\n",
										argv[0],
										pfound->name);
									Print::PrintError(Clide::Global::debugBuff);
								#endif
							}

							d->__nextchar += strlen (d->__nextchar);
							#if(clide_DEBUG_PRINT_VERBOSE == 1)
								Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning ?.\r\n",
										Print::DebugPrintingLevel::VERBOSE);
							#endif
							return '?';
						}
					}
					else if (pfound->has_arg == 1)
					{
						if (d->optind < argc)
							d->optarg = argv[d->optind++];
						else
						{
							if (print_errors)
							{
								#if(clide_DEBUG_PRINT_ERROR == 1)
									snprintf (
										Clide::Global::debugBuff,
										sizeof(Clide::Global::debugBuff),
										"%s: option '-W %s' requires an argument\n",
										argv[0],
										pfound->name);
									Print::PrintError(Clide::Global::debugBuff);
								#endif
							}
							d->__nextchar += strlen (d->__nextchar);
							#if(clide_DEBUG_PRINT_VERBOSE == 1)
								Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning : or ?.\r\n",
										Print::DebugPrintingLevel::VERBOSE);
							#endif
							return optstring[0] == ':' ? ':' : '?';
						}
					}
					else
						d->optarg = NULL;
					d->__nextchar += strlen (d->__nextchar);
					if (longind != NULL)
						*longind = option_index;
					if (pfound->flag)
					{
						*(pfound->flag) = pfound->val;
						#if(clide_DEBUG_PRINT_VERBOSE == 1)
							Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning 0.\r\n",
									Print::DebugPrintingLevel::VERBOSE);
						#endif
						return 0;
					}
					return pfound->val;
				}
				
				

				no_longs:
				d->__nextchar = NULL;
				return 'W';	/* Let the application handle it.   */
			}
			if (temp[1] == ':')
			{
				if (temp[2] == ':')
				{
					/* This is an option that accepts an argument optionally.  */
					if (*d->__nextchar != '\0')
					  {
					d->optarg = d->__nextchar;
					d->optind++;
					  }
					else
					  d->optarg = NULL;
					d->__nextchar = NULL;
				}
				else
				{
					// This is an option that requires an argument.
					if (*d->__nextchar != '\0')
					{
						d->optarg = d->__nextchar;
						/* If we end this ARGV-element by taking the rest as an arg,
						   we must advance to the next element now.  */
						d->optind++;
					}
					else if (d->optind == argc)
					{
						if (print_errors)
						{

							#if(clide_DEBUG_PRINT_ERROR == 1)
								snprintf (
									Clide::Global::debugBuff,
									sizeof(Clide::Global::debugBuff),
									"%s: option requires an argument -- '%c'\n",
									argv[0],
									c);
								Print::PrintError(Clide::Global::debugBuff);
							#endif
						}
						d->optopt = c;
						if (optstring[0] == ':')
							c = ':';
						else
							c = '?';
					  }
					else
					  /* We already incremented `optind' once;
					 increment it again when taking next ARGV-elt as argument.  */
					  d->optarg = argv[d->optind++];
					d->__nextchar = NULL;
				}
			}
			#if(clide_DEBUG_PRINT_VERBOSE == 1)
				Print::PrintDebugInfo("CLIDE: GetOpt() finished. Returning character.\r\n",
						Print::DebugPrintingLevel::VERBOSE);
			#endif
			return c;
		}
	}

	int	GetOpt::_getopt_internal(
		int argc,
		char *const *argv,
		const char *optstring,
		const struct option *longopts,
		int *longind,
		int long_only,
		int posixly_correct)
	{
		int result;

		getopt_data.optind = optind;
		getopt_data.opterr = opterr;

		result = _getopt_internal_r (argc, argv, optstring, longopts,
			longind, long_only, &getopt_data,
			posixly_correct);

		optind = getopt_data.optind;
		optarg = getopt_data.optarg;
		optopt = getopt_data.optopt;

		return result;
	}
	
	int	GetOpt::getopt_long(
		int argc,
		char *const *argv,
		const char *options,
		const struct option *long_options,
		int *opt_index)
	{
	  return _getopt_internal (
		argc,
		argv,
		options,
		long_options,
		opt_index,
		0,
		0);
	}
	
	extern int GetOpt::_getopt_internal(
		int ___argc,
		char *const *___argv,
		const char *__shortopts,
		const struct option *__longopts,
		int *__longind,
		int __long_only,
		int posixly_correct);

					 
	// Reentrant versions which can handle parsing multiple argument
	// vectors at the same time.

	

	/* The initializer is necessary to set OPTIND and OPTERR to their
	   default values and to clear the initialization flag.  */
	#define _GETOPT_DATA_INITIALIZER	{ 1, 1 }

		/*
	extern int _getopt_internal_r(
		int ___argc,
		char *const *___argv,
		const char *__shortopts,
		const struct option *__longopts,
		int *__longind,
		int __long_only,
		struct _getopt_data *__data,
		int posixly_correct);

	extern int _getopt_long_r(
		int ___argc,
		char *const *___argv,
		const char *__shortopts,
		const struct option *__longopts,
		int *__longind,
		struct _getopt_data *__data);

	extern int _getopt_long_only_r(
		int ___argc,
		char *const *___argv,
		const char *__shortopts,
		const struct option *__longopts,
		int *__longind,
		struct _getopt_data *__data);
*/
	/*
	int	_getopt_long_r(
		int argc,
		char *const *argv,
		const char *options,
		const struct option *long_options,
		int *opt_index,
		struct _getopt_data *d)
	{
		return _getopt_internal_r(
			argc,
			argv,
			options,
			long_options,
			opt_index,
			0,
			d,
			0);
	}
	*/
	
	/*
	int
	getopt (int argc, char *const *argv, const char *optstring)
	{
	  return _getopt_internal (argc, argv, optstring,
				   (const struct option *) 0,
				   (int *) 0,
				   0, 0);
	}
	*/
	/*
	#ifdef _LIBC
	int
	__posix_getopt (int argc, char *const *argv, const char *optstring)
	{
	  return _getopt_internal (argc, argv, optstring,
				   (const struct option *) 0,
				   (int *) 0,
				   0, 1);
	}
	#endif
	*/
	
} // namespace ClideGetOpt

