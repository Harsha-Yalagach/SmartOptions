/**
 * @file        OptionsArgTest.h
 *
 * @brief       Test Optional Arguments.
 *
 * @details     This file contains a CxxTest test-suite to test Option Arguments of SmartOptions library.
 *
 * @copyright   This content is released under Berkeley Software Distribution license (BSD).
 *
 */

#include <cxxtest/TestSuite.h>

#include "SmartOptions/SmartOptions.hpp"

#include "CommonData.h"
#include "CommonUtils.h"

class OptionArgTestSuite : public CxxTest::TestSuite
{
public:
    void testOption_1_SS_Pass(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", OPTION_ARGUMENT_1_SS };
        const char *optArg_1 = NULL;
        const char *optArg_2 = NULL;
        
        // Act
        smartOptions.AddOption(OPT_PREFIX_SHORT_1, OPT_PREFIX_LONG_1, OPT_META_1, OPT_HELP_1, &optArg_1);
        smartOptions.AddOption(OPT_PREFIX_SHORT_2, OPT_PREFIX_LONG_2, OPT_META_2, OPT_HELP_2, &optArg_2);

        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_SUCCESS);
        TS_ASSERT_SAME_DATA(optArg_1, OPTION_ARGUMENT_1, strlen(OPTION_ARGUMENT_1));
    }

    void testOption_1_SS_Fail(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", OPTION_ARGUMENT_1_SS };
        //const char *optArg_1 = NULL;
        const char *optArg_2 = NULL;
        
        // Act
        //smartOptions.AddOption(OPT_PREFIX_SHORT_1, OPT_PREFIX_LONG_1, OPT_META_1, OPT_HELP_1, &optArg_1);
        smartOptions.AddOption(OPT_PREFIX_SHORT_2, OPT_PREFIX_LONG_2, OPT_META_2, OPT_HELP_2, &optArg_2);

        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_INVALID_ARGUMENT);
    }

    void testOption_SS_SS_Pass(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", OPTION_ARGUMENT_1_SS, OPTION_ARGUMENT_2_SS };
        const char *optArg_1 = NULL;
        const char *optArg_2 = NULL;
        
        // Act
        smartOptions.AddOption(OPT_PREFIX_SHORT_1, OPT_PREFIX_LONG_1, OPT_META_1, OPT_HELP_1, &optArg_1);
        smartOptions.AddOption(OPT_PREFIX_SHORT_2, OPT_PREFIX_LONG_2, OPT_META_2, OPT_HELP_2, &optArg_2);

        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_SUCCESS);
        TS_ASSERT_SAME_DATA(optArg_1, OPTION_ARGUMENT_1, strlen(OPTION_ARGUMENT_1));
        TS_ASSERT_SAME_DATA(optArg_2, OPTION_ARGUMENT_2, strlen(OPTION_ARGUMENT_2));
    }

    void testOption_SM_SS_Pass(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", OPTION_ARGUMENT_1_SM, OPTION_ARGUMENT_2_SS };
        const char *optArg_1 = NULL;
        const char *optArg_2 = NULL;
        
        // Act
        smartOptions.AddOption(OPT_PREFIX_SHORT_1, OPT_PREFIX_LONG_1, OPT_META_1, OPT_HELP_1, &optArg_1);
        smartOptions.AddOption(OPT_PREFIX_SHORT_2, OPT_PREFIX_LONG_2, OPT_META_2, OPT_HELP_2, &optArg_2);

        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_SUCCESS);
        TS_ASSERT_SAME_DATA(optArg_1, OPTION_ARGUMENT_1, strlen(OPTION_ARGUMENT_1));
        TS_ASSERT_SAME_DATA(optArg_2, OPTION_ARGUMENT_2, strlen(OPTION_ARGUMENT_2));
    }

    void testOption_SS_SM_Pass(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", OPTION_ARGUMENT_1_SS, OPTION_ARGUMENT_2_SM };
        const char *optArg_1 = NULL;
        const char *optArg_2 = NULL;
        
        // Act
        smartOptions.AddOption(OPT_PREFIX_SHORT_1, OPT_PREFIX_LONG_1, OPT_META_1, OPT_HELP_1, &optArg_1);
        smartOptions.AddOption(OPT_PREFIX_SHORT_2, OPT_PREFIX_LONG_2, OPT_META_2, OPT_HELP_2, &optArg_2);

        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_SUCCESS);
        TS_ASSERT_SAME_DATA(optArg_1, OPTION_ARGUMENT_1, strlen(OPTION_ARGUMENT_1));
        TS_ASSERT_SAME_DATA(optArg_2, OPTION_ARGUMENT_2, strlen(OPTION_ARGUMENT_2));
    }

    void testOption_SM_SM_Pass(void)
    {
        // Arrange
        SmartOptions smartOptions = SmartOptions("SmartOptionsTest", false);
        const char *argV[] = { "SmartOptions", OPTION_ARGUMENT_1_SM, OPTION_ARGUMENT_2_SM };
        const char *optArg_1 = NULL;
        const char *optArg_2 = NULL;
        
        // Act
        smartOptions.AddOption(OPT_PREFIX_SHORT_1, OPT_PREFIX_LONG_1, OPT_META_1, OPT_HELP_1, &optArg_1);
        smartOptions.AddOption(OPT_PREFIX_SHORT_2, OPT_PREFIX_LONG_2, OPT_META_2, OPT_HELP_2, &optArg_2);

        SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

        // Assert
        TS_ASSERT_EQUALS(status, SMARTOPTIONS_SUCCESS);
        TS_ASSERT_SAME_DATA(optArg_1, OPTION_ARGUMENT_1, strlen(OPTION_ARGUMENT_1));
        TS_ASSERT_SAME_DATA(optArg_2, OPTION_ARGUMENT_2, strlen(OPTION_ARGUMENT_2));
    }
};
