### Description
This library will allow you to load MTA map files without converting.

### Uses
```pwn
public OnGameModeInit()
{
	map = LoadFromMapFile("PATH_TO_MAP_FILE");
	DestroyMap(map);
}
public OnMapLoad(mapid, objectid, bool:dynamic)
{
	printf("[CREATED] mapid: %d, objectid: %d, dynamic: %d", mapid, objectid, _:dynamic);
}

public OnMapDestroy(mapid, objectid, bool:dynamic)
{
	printf("[DESTOYED] mapid: %d, objectid: %d, dynamic: %d", mapid, objectid, _:dynamic);
}
```

Max maps:
If you want to change this limit, then define MAX_MAPS before include
```pwn
#define MAX_MAPS 228
#include "dcm_o"
```
