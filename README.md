# SmartOptions
**SmartOptions**, the Next Generation Command Line Parameter processing library for C++.

SmartOptions is used for processing command line parameters. It has been inspired by the command line processing in Python.

The benefit of SmartOptions is that it parses the command line parameters, and automatically populates the variables, so the developer can concentrate on the business logic, instead of parsing and getting the values from the command line parameters.

#### Salient Features of SmartOptions are:
* It handles the POSIX style single character options ( -w ) as well as the newer GNU long options ( –width )
* Is platform independent.
* Requires minimal effort to parse Command Line Arguments, and allows you to concentrate on business logic.
* Retrieves the Command Line arguments and populates the variables automatically.
* Supports printing out Help and Usage messages automatically.


#### SmartOptions processes 3 types of command line arguments:
* Option - has an associated value ( -w 100 )
* Flag - no value, just a boolean flag ( -nogui )
* Positional - has only value ( path )

#### Why not just use getopt() ?

* getopt() Its a POSIX standard not part of ANSI-C and hence its not available on platforms like Windows.
* Processing Command Line Arguments using getopt() is tedious, time consuming and everything needs to be done by the programmer.

#### Code Sample:

```cpp
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
```

#### Documentation
Browse [Doxygen Documentation](https://harsha-yalagach.github.io/SmartOptions/html/index.html)