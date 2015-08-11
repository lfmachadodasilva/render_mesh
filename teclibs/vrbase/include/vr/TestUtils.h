/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_TEST_UTILS_H_
#define _VR_TEST_UTILS_H_

//! \file TestUtils.h Utility macros for writing unit tests.

#include "Platform.h"

// when using CppUnit, translate calls accordingly
#ifdef CPPUNIT_ASSERT_EQUAL
#define EXPECT_EQ CPPUNIT_ASSERT_EQUAL
#endif

/*!
	Macros to write tests that check for memory leaks.

	Use the macro VR_BEGIN_CPPUNIT_MEMLEAK_TEST to initialize a memory leak test and the macro
	VR_END_CPPUNIT_MEMLEAK_TEST to finalize it. If a memory leak occurs, then it will report
	the memory usage and trigger a failure using CppUnit.

	Example code:
	\code
		#include "cppunit_utils.h"

		class MemoryLeakTests : public CppUnit::TestFixture
		{
			CPPUNIT_TEST_SUITE( MemoryLeakTests );
			CPPUNIT_TEST( test1MemoryLeak );
			CPPUNIT_TEST_SUITE_END();

		  public:

			void test1MemoryLeak()
			{
				BEGIN_MEMORY_LEAK_TEST;
				malloc(10);
			   END_MEMORY_LEAK_TEST;
			}
		};

		CPPUNIT_TEST_SUITE_REGISTRATION( MemoryLeakTests );
	\endcode
	@{
 */

#if defined(VR_OS_WIN)
#   define _CRTDBG_MAP_ALLOC
#   include <stdlib.h>
#   include <crtdbg.h>
#   if !defined(_DEBUG)
#       define VR_BEGIN_MEMLEAK_TEST
#       define VR_END_MEMLEAK_TEST
#   else
#       define VR_BEGIN_MEMLEAK_TEST \
			{ _CrtMemState __initialState; \
	        _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE ); \
	        _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT ); \
	        _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE ); \
	        _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT ); \
	        /*_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );*/ \
	        /*_CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );*/ \
	        _CrtMemCheckpoint( &__initialState ); {
#       define VR_END_MEMLEAK_TEST \
            } \
            _CrtMemState __finalState, __diffState; \
            _CrtMemCheckpoint( &__finalState ); \
            int leakedMemory = _CrtMemDifference( &__diffState, &__initialState, &__finalState ); \
            if( leakedMemory ) \
            { \
            /*_CrtDumpMemoryLeaks();*/ \
            /*_CrtMemDumpStatistics( &__diffState );*/ \
            _CrtMemDumpAllObjectsSince( &__initialState ); \
            } \
			EXPECT_EQ( leakedMemory, 0 ); }
#   endif
#else
#   define VR_BEGIN_MEMLEAK_TEST
#   define VR_END_MEMLEAK_TEST
#endif

// @}

#endif // _VR_TEST_UTILS_H_
