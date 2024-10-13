# Dynamic-Refresh-Rate
Dynamically adjust refresh rate depending on what application is running.

To add an application go to the directory of the project and add the name of the exectuble in "processes.txt", if you do not have this file it will automatically be created when the project has been ran at least once.

To toggle the settings of the project you can go into the .sln and adjust it at the very top.
Default configurations:
Defualt Refresh Rate: 60hz
Dynamic Refresh Rate: 60hz
Sleep: 5000ms

When the application is running you will have a CMD box running displaying the logs.
When an application is opened it will display the refresh rate change.
When closing the application it will detect the refresh rate that it has reverted to.
