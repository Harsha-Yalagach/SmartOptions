/**
 * @file        SmartOptions.hpp
 *
 * @brief       Implements SmartOptions, the Command Line Parameter processing library.
 *
 * @details     This file holds contains the SmartOptions class which is a utility class for processing
 * command line parameters.
 *
 * @copyright   This content is released under Berkeley Software Distribution license (BSD).
 *
 */

#ifndef _SMARTOPTIONS_H
#define _SMARTOPTIONS_H

/* C Headers */
#include <stdlib.h>
#include <string.h>

/* C++ Headers */
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

/** @cond INTERNAL */
// Macros
#define IS_VALID_STRING(ptr) (ptr && strlen(ptr))
/** @endcond */

/**
 * @mainpage 
 * SmartOptions, the Next Generation Command Line Parameter processing library for C++.
 * 
 * SmartOptions is used for processing command line parameters. It has been inspired by
 * the command line processing in Python.
 *
 * The benefit of SmartOptions is that it parses the command line parameters, and automatically populates
 * the variables, so the developer can concentrate on the business logic, instead of parsing and getting
 * the values from the command line parameters.
 *
 * Salient Features of SmartOptions are:
 * - It handles the POSIX style single character options ( -w ) as well as the newer GNU long options ( --width )
 * - Is platform independent.
 * - Requires minimal effort to parse Command Line Arguments, and allows you to concentrate on business logic.
 * - Retrieves the Command Line arguments and populates the variables automatically.
 * - Supports printing out Help and Usage messages automatically.
 *
 *
 * 
 *
 * SmartOptions processes 3 types of command line arguments:
 * - Option     - has an associated value ( -w 100 )
 * - Flag       - no value, just a boolean flag  ( -nogui )
 * - Positional - has only value ( path )
 *
 * Why not just use getopt() ?
 * - getopt() Its a POSIX standard not part of ANSI-C and hence its not available on platforms like Windows.
 * - Processing Command Line Arguments using getopt() is tedious, time consuming and everything needs to be
 * done by the programmer.
 *
 * <b>Code Sample:</b>
 * @code
    SmartOptions smartOptions = SmartOptions("TestApp", true);

    smartOptions.AddDescription("The Test App...");
    smartOptions.AddUsage("[OPTION]... <POSITIONAL_ARG>");
    
    const char *posArg_1 = NULL;
    smartOptions.AddPositionalArgument("posArg_1", "Positional Argument 1", &posArg_1);

    bool aFlag=false;
    smartOptions.AddFlag('a', NULL, "a-Flag", &aFlag);

    char *bOption = NULL;
    smartOptions.AddOption('b', NULL, "B_VAR", "b-Option", &bOption);

    SMARTOPTIONS_STATUS status = smartOptions.ProcessCommandArgs(SIZE_OF_ARRAY(argV), argV);

    int statusCode = kxSmartOptionsProcessCommandArgs(handle, argc, argv);
    if (SMARTOPTIONS_SUCCESS != status) {
        exit(statusCode);
    }

    if (aFlag) {
        // Do work when 'aFlag' has been set...
    }

    if (bOption) {
        // Do work when bOption has been set...
    }

    // Use posVar1 to do some processing...
    // ...
   
   @endcode
 */

/**
 * @brief The base class for all the various types of command line parameters.
 * @cond INTERNAL
 */
struct SmartOptionsArg {
    /**
     * @brief The Constructor.
     *
     * @param prefixShort A single character used to specify the option in POSIX style
     * @param prefixLong A string used to specify the option in GNU style.
     * @param metaVariable A string which specifies the different option values.
     * @param helpString A string which explains the option in context.
     */
    SmartOptionsArg(char prefixShort, const char *prefixLong, const char *metaVariable, const char *helpString)
    : prefixShort(prefixShort),
      prefixLong(prefixLong),
      metaVariable(metaVariable),
      helpString(helpString)
    {
    }

    /**
     * @brief The Destructor.
     */
    virtual ~SmartOptionsArg()=0 ;

    // Member Variables
    char prefixShort;       //!< @brief A single character used to specify the option, POSIX style.
    const char *prefixLong;     //!< @brief The string used to specify the option, GNU style.
    const char *metaVariable;   //!< @brief The string which specifies the different option values.
    const char *helpString;     //!< @brief The string which explains the option in context.
};

/*
 * Giving it an empty implementation... http://stackoverflow.com/questions/1219607/why-do-we-need-a-pure-virtual-destructor-in-c
 */
SmartOptionsArg::~SmartOptionsArg() {}

/**
 *  @brief The class which holds the Optional Command line parameter.
 */
struct SmartOptionsOptionArg: public SmartOptionsArg {
    /**
     * @brief The Constructor.
     *
     * @param prefixShort A single character used to specify the option in POSIX style
     * @param prefixLong A string used to specify the option in GNU style.
     * @param metaVariable A string which specifies the different option values.
     * @param helpString A string which explains the option in context.
     * @param destVariable A pointer, where the retrieved value is stored into.
     */
    SmartOptionsOptionArg(char prefixShort, const char *prefixLong, const char *metaVariable, const char *helpString, const char **destVariable) 
    : SmartOptionsArg(prefixShort, prefixLong, metaVariable, helpString) {
       // Initialize the derived class members...
        this->destVariable  = destVariable;
        (*this->destVariable) = NULL;
    }

    // Member Variables
    const char **destVariable;        //!< @brief A pointer, where the retrieved value is stored into.
};

typedef std::list<SmartOptionsOptionArg> SmartOptionsOptionArgList;

/**
 * @brief The class which holds the Flag Command line parameter.
 */
struct SmartOptionsFlagArg : public SmartOptionsArg {
    /**
     * @brief The Constructor.
     *
     * @param prefixShort A single character used to specify the option in POSIX style
     * @param prefixLong A string used to specify the option in GNU style.
     * @param helpString A string which explains the option in context.
     * @param destVariable A pointer, where the retrieved value is stored into.
     */
    SmartOptionsFlagArg(char prefixShort, const char *prefixLong, const char *helpString, bool *destVariable) 
    : SmartOptionsArg(prefixShort, prefixLong, metaVariable, helpString) {
        // Initialize the derived class members...
        this->destVariable = destVariable;
        (*this->destVariable) = false;
    }

    // Member Variables
    bool *destVariable;       //!< @brief A pointer, where the retrieved value is stored into.
};

typedef std::list<SmartOptionsFlagArg> SmartOptionsFlagArgList;

/**
 * @brief The class which holds the Positional Command line parameter.
 */
struct SmartOptionsPositionalArg : public SmartOptionsArg {
    /**
     * @brief The Constructor.
     *
     * @param metaVariable A string which specifies the different option values.
     * @param helpString A string which explains the option in context.
     * @param destVariable A pointer, where the retrieved value is stored into.
     */
    SmartOptionsPositionalArg(const char *metaVariable, const char *helpString, const char **destVariable) 
    : SmartOptionsArg(0, NULL, metaVariable, helpString) {
        // Initialize the derived class members...
        this->destVariable = destVariable;
    }

    // Member Variables
    const char **destVariable;        //!< @brief A pointer, where the retrieved value is stored into.
};

typedef std::vector<SmartOptionsPositionalArg> SmartOptionsPositionalArgList;

/** @endcond */

/** 
 * @brief The various status code used by SmartOptions library(). 
 */
typedef enum SMARTOPTIONS_STATUS {
   SMARTOPTIONS_SUCCESS             = 0x00,  /*!< Returned when we are able to successfully parse the command line without any issues. */
   SMARTOPTIONS_INVALID_ARGUMENT,            /*!< Returned when we have invalid command line parameters passed to the program. */
   SMARTOPTIONS_INVALID_NUMBEROF_ARGUMENTS,  /*!< Returned when the number of command line parameters is not as per the usage guidelines. */
   SMARTOPTIONS_SYSTEM_ERROR                 /*!< Returned when there is a system error like malloc failure... Check errno in such cases... */
} SMARTOPTIONS_STATUS;

/**
 * @brief SmartOptions, the next generation of Command Line Parameter processing library.
 * @details SmartOptions is used for processing command line parameters. It has been inspired by
 * the command line processing in Python.
 */
class SmartOptions {
public: // Public Member Functions...
    /**
     * @brief The Constructor
     * @param programName The name of the program to be used while printing auto help...
     * @param autoPrintHelp Prints the help message automatically by using the available data.
     */
    SmartOptions(const char *programName, bool autoPrintHelp) {
        this->argC = 0;
        this->argV = NULL;

        this->appName = programName;
        this->usage = NULL;
        this->description = NULL;
        this->autoPrintHelp = autoPrintHelp;
    }

    /**
     * @brief Sets the description string for the current program.
     *
     * @param description The description string for the current program.
     */
    void AddDescription(const char *description) {
        this->description = description;
    }

    /**
     * @brief Sets the usage string for the current program.
     *
     * @param usage The usage string for the current program.
     */
    void AddUsage(const char *usage ) {
        this->usage = usage;
    }

    /**
     * @brief Adds a command line options to the processing engine.
     *
     * @param prefixShort A single character used to specify the option in POSIX style
     * @param prefixLong A string used to specify the option in GNU style.
     * @param metaVariable A string which specifies the meta variable which indicates the acceptable values.
     * @param helpString A string which explains the option in context.
     * @param destVariable A pointer, where the retrieved value is stored into.
     */
    void AddOption(char prefixShort, const char *prefixLong, const char *metaVariable, const char *helpString, const char **destVariable) {
        SmartOptionsOptionArg option(prefixShort, prefixLong, metaVariable, helpString, destVariable);
        this->options.push_back(option);
    }

    /**
     * @brief Adds a command line flag to the processing engine.
     *
     * @param prefixShort A single character used to specify the option in POSIX style
     * @param prefixLong A string used to specify the option in GNU style.
     * @param helpString A string which explains the option in context.
     * @param destVariable A pointer, where the value is retrieved and stored into.
     */
    void AddFlag(char prefixShort, const char *prefixLong, const char *helpString, bool *destVariable) {
        SmartOptionsFlagArg flag(prefixShort, prefixLong, helpString, destVariable);
        this->flags.push_back(flag);
    }

    /**
     * @brief Add a positional parameter to the processing engine.
     *
     * @param metaVariable A string which specifies the meta variable which indicates may indicate the acceptable values.
     * @param helpString A string which explains the option in context.
     * @param destVariable A pointer, where the value is retrieved and stored into.
     */
    void AddPositionalArgument(const char *metaVariable, const char *helpString, const char **destVariable) {
        SmartOptionsPositionalArg pos(metaVariable, helpString, destVariable);
        this->posArgs.push_back(pos);
    }

    /**
     * @brief Process the command line parameters and populate the appropriate variables with the
     * results of the processing automatically.
     *
     * @param argc The number of command line parameters that are there in the argv array.
     * @param argv The string array which contains all the command line parameters passed.
     *
     * @returns Based on the processing of the command line parameters, the functions returns the
     * following codes.
     *
     * @retval SMARTOPTIONS_SUCCESS if successful.
     * @retval SMARTOPTIONS_INVALID_ARGUMENT if the processing engine encounters an invalid argument.
     * @retval SMARTOPTIONS_INVALID_NUMBEROF_ARGUMENTS if the processing engine encounters less or
     * more number of arguments that the normal.
     */
    SMARTOPTIONS_STATUS ProcessCommandArgs(int argc, const char **argv) {

        this->useCommandArgs(argc, argv);

        size_t posArgsCount = 0;
        SmartOptionsPositionalArgList::iterator posArgsIt = this->posArgs.begin();

        std::string strPosArgErrMsg;
        std::string strOptArgErrMsg;

        std::string strErrMessage;

        for (int index = 1; index < argc; index++) {/* ignore first argv */
            const char *token = this->argV[index];
            bool isTokenProcessed = false;
            if ('-' == token[0])
            {
                token++; // increment the token pointer
                isTokenProcessed = false; // reset...

                // First Process Flags...
                if (false == isTokenProcessed) {
                    for (SmartOptionsFlagArgList::iterator flagsIt =  this->flags.begin();
                            flagsIt != this->flags.end();
                            flagsIt++)
                    {
                        if ( (*flagsIt).prefixShort == (*(char*)token) ) {
                            // Update the variable that has been passed while configuring...
                            (*flagsIt->destVariable) = true;
     
                            isTokenProcessed = true;
                            break;
                        }
                    }
                }

                // Second Process Options...
                if (false == isTokenProcessed) {
                    for (SmartOptionsOptionArgList::iterator optionsIt =  this->options.begin();
                            optionsIt != this->options.end();
                            optionsIt++)
                    {
                        if ( (*optionsIt).prefixShort == (*(char*)token) ) {
                            SmartOptionsOptionArg optionArg = (SmartOptionsOptionArg)(*optionsIt);
                            
                            // Update the variable that has been passed while configuring...
                            if (SmartOptions::NULL_TERMINATE != token[1]) {
                                // If the argument provided is not separated by space...
                                *(optionArg.destVariable) = ++token;
                                isTokenProcessed = true;
                            }
                            else if (index >= (argc-1)) {
                                strErrMessage = std::string(": Error, missing value for '-") + (*optionsIt).prefixShort + "' option.";
                            } else {
                                // If the argument provided is separated by space...
                                const char *optionStr = this->argV[++index];
                                *(optionArg.destVariable) = optionStr;
                                isTokenProcessed = true;
                            }
                        }

                        if (isTokenProcessed) break;
                    }
                }

                // Flag error, if the token is not processed...
                if (false == isTokenProcessed) {
                    if (this->autoPrintHelp) {
                        if (strErrMessage.empty() == false)
                            std::cout << std::string(this->appName) << strErrMessage << std::endl;
                        else
                            std::cout << std::string(this->appName) << ": Error, invalid argument '-" << token[0] << "'." << std::endl;
                    }
                    AutoPrintHelp();
                    return SMARTOPTIONS_INVALID_ARGUMENT;
                }
            } else {
                // lastly process the Positional arguments...
                if (posArgsIt < this->posArgs.end()) {
                    SmartOptionsPositionalArg posArg = (SmartOptionsPositionalArg)(*posArgsIt);

                    // Update the variable that has been passed while configuring...
                    *(posArg.destVariable) = token;
                    
                    posArgsIt++;
                }
                else {
                    if (strPosArgErrMsg.empty() == true) {
                        strPosArgErrMsg = std::string(this->appName) + ": Error, invalid number of mandatory arguments (" + token;
                    }
                    else {
                        strPosArgErrMsg += std::string(", ") + token;
                    }
                }
                posArgsCount++;
            }
        }

        // This means that we have extra positional arguments, hence fix the error message.
        if (strPosArgErrMsg.empty() == false) {
            strPosArgErrMsg += ")";
            size_t loc = strPosArgErrMsg.rfind(",");
            strPosArgErrMsg.replace(loc, 1, " &"); // Replace a single comma with space and ampersand.
        }

        // Post processing validations...
        if ( posArgsCount != this->posArgs.size() ) {

            // In case where in we don't have sufficient mandatory parameters...
            if (strPosArgErrMsg.empty() == true) {
                strPosArgErrMsg = std::string(this->appName) + ": Error, invalid number of mandatory arguments";
            }

            if (this->autoPrintHelp) {
                if (this->posArgs.size() == 1) {
                    strPosArgErrMsg += ". The only mandatory parameter is '" + std::string(this->posArgs.begin()->metaVariable) + "'";
                }
                else {
                    strPosArgErrMsg += ". The mandatory parameters are ";   
                    for (posArgsIt =  this->posArgs.begin(); posArgsIt != this->posArgs.end(); posArgsIt++) {
                        SmartOptionsPositionalArg posArg = (SmartOptionsPositionalArg)(*posArgsIt);
                        strPosArgErrMsg += std::string("'") + posArg.metaVariable + "', ";
                    }
                    strPosArgErrMsg.erase(strPosArgErrMsg.size() -2); // Remove last 2 characters ", ".
                    size_t loc = strPosArgErrMsg.rfind(",");
                    strPosArgErrMsg.replace(loc, 1, " &"); // Replace a single comma with space and ampersand.
                    strPosArgErrMsg += ".";
                }
                std::cout << strPosArgErrMsg << std::endl;
            }

            this->AutoPrintHelp();
            return SMARTOPTIONS_INVALID_NUMBEROF_ARGUMENTS;
        }

        return SMARTOPTIONS_SUCCESS;
    }

    /**
     * @brief Prints the description and help message based on the various flags, options, and positional arguments
     * that have been added/configured.
     */
    void PrintHelp() {
        printf("%s %s \n", this->appName, this->usage);
        //printf("%s \n", this->description);

        char leftContent[64] = {0};

        for (SmartOptionsOptionArgList::iterator optionsIt =  this->options.begin();
                optionsIt != this->options.end();
                optionsIt++)
        {
            SmartOptionsOptionArg option = (SmartOptionsOptionArg)(*optionsIt);

            sprintf(leftContent, "  -%c <%s> ", option.prefixShort, option.metaVariable);
            printf("%-32s %s \n", leftContent, option.helpString);
        }

        for (SmartOptionsFlagArgList::iterator flagsIt =  this->flags.begin();
                                    flagsIt != this->flags.end();
                                    flagsIt++)
        {
            SmartOptionsFlagArg flag = (SmartOptionsFlagArg) (*flagsIt);
            sprintf(leftContent, "  -%c", flag.prefixShort);
            printf("%-32s %s \n", leftContent, flag.helpString);
        }
    }

private: // Private Member functions...
    /**
     * @brief Sets the internal member variables to use the passed variables, and also extracts and sets the program name...
     *
     * @param argC An integer value specifying the number of entries in the argV array.
     * @param argV A string array containing the list of command line parameters to be processed.
     */
    void useCommandArgs(int argC, const char **argV) {
        this->argC = argC;
        this->argV = argV;
    }

    /**
     * @brief Print help if Auto-Help option is enabled...
     */
    void AutoPrintHelp() {
        if (true == this->autoPrintHelp) {
            this->PrintHelp();
        }
    }

private: // Private Member variables...

    int     argC;           //!< @brief command line arguments count.
    const char    **argV;   //!< @brief command line arguments.

    const char  *appName;       //!< @brief The application name from argv[0].
    const char  *usage;         //!< @brief The string which contains the usage help.
    const char  *description;   //!< @brief The short description of the current program.
    bool      autoPrintHelp;  //!< @brief Prints the help message automatically by using the available data.

    SmartOptionsOptionArgList       options;    //!< @brief A list containing all the Command Line Options argument rules.
    SmartOptionsFlagArgList         flags;      //!< @brief A list containing all the Command Line Flag argument rules.
    SmartOptionsPositionalArgList   posArgs;    //!< @brief A list containing all the Command Line Positional argument rules.

    static const char NULL_TERMINATE = '\0';

};

#endif /* _SMARTOPTIONS_H */