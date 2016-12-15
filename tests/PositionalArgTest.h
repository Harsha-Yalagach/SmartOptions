/**
 * @file        PositionalArgTest.h
 *
 * @brief       Test Positional Arguments.
 *
 * @details     This file contains a CxxTest test-suite to test Positional Arguments of SmartOptions library.
 *
 * @copyright   This content is released under Berkeley Software Distribution license (BSD).
 *
 */

#include <cxxtest/TestSuite.h>

#include "SmartOptions/SmartOptions.hpp"

#include "CommonData.h"
#include "CommonUtils.h"

class PositionalArgTestSuite : public CxxTest::TestSuite
{
public:
    void testPositionalArgument_1(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", POSITIONAL_ARGUMENT_1 };
        const char *posArg_1 = NULL;
        
        // Act
        smartOptions.AddPositionalArgument("posArg_1", "Positional Argument 1", &posArg_1);
        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_SUCCESS);
        TS_ASSERT_SAME_DATA(posArg_1, POSITIONAL_ARGUMENT_1, strlen(POSITIONAL_ARGUMENT_1));
    }

    void testPositionalArgument_2(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", POSITIONAL_ARGUMENT_1, POSITIONAL_ARGUMENT_2 };
        const char *posArg_1 = NULL;
        const char *posArg_2 = NULL;
        
        // Act
        smartOptions.AddPositionalArgument("posArg_1", "Positional Argument 1", &posArg_1);
        smartOptions.AddPositionalArgument("posArg_1", "Positional Argument 2", &posArg_2);
        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_SUCCESS);
        TS_ASSERT_SAME_DATA(posArg_1, POSITIONAL_ARGUMENT_1, strlen(POSITIONAL_ARGUMENT_1));
        TS_ASSERT_SAME_DATA(posArg_2, POSITIONAL_ARGUMENT_2, strlen(POSITIONAL_ARGUMENT_2));
    }

    void testPositionalArgument_1_2_Fail(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", POSITIONAL_ARGUMENT_1, POSITIONAL_ARGUMENT_2 };
        const char *posArg_1 = NULL;
        
        // Act
        smartOptions.AddPositionalArgument("posArg_1", "Positional Argument 1", &posArg_1);
        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_INVALID_NUMBEROF_ARGUMENTS);
        TS_ASSERT_SAME_DATA(posArg_1, POSITIONAL_ARGUMENT_1, strlen(POSITIONAL_ARGUMENT_1));
    }

    void testPositionalArgument_2_1_Fail(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", POSITIONAL_ARGUMENT_1 };
        const char *posArg_1 = NULL;
        const char *posArg_2 = NULL;
        
        // Act
        smartOptions.AddPositionalArgument("posArg_1", "Positional Argument 1", &posArg_1);
        smartOptions.AddPositionalArgument("posArg_2", "Positional Argument 2", &posArg_2);
        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_INVALID_NUMBEROF_ARGUMENTS);
        TS_ASSERT_SAME_DATA(posArg_1, POSITIONAL_ARGUMENT_1, strlen(POSITIONAL_ARGUMENT_1));
    }
};
