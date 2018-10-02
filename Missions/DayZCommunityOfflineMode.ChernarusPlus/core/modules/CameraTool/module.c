#ifndef COM_MODULES_OLDLOADING
#include "missions\\DayZCommunityOfflineMode.ChernarusPlus\\core\\BaseModuleInclude.c"
#endif

/*
    Define used for optional compilations
*/
#define MODULE_CAMERA_TOOL

/*
    Include of all .c files that belong to this module
*/
#ifdef COM_MODULES_OLDLOADING
#include "missions\\DayZCommunityOfflineMode.ChernarusPlus\\core\\modules\\CameraTool\\CameraTool.c"
#include "missions\\DayZCommunityOfflineMode.ChernarusPlus\\core\\modules\\CameraTool\\gui\\CameraSettings.c"
#include "missions\\DayZCommunityOfflineMode.ChernarusPlus\\core\\modules\\CameraTool\\WidgetStore.c"
#endif

#ifndef COM_MODULES_OLDLOADING
void RegisterModule()
{
    GetModuleManager().RegisterModule( new CameraTool );
}
#endif