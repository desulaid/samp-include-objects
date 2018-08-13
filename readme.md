### Description
This library will allow you to load MTA map files without converting.

### Uses
Loading:
```pwn
map = LoadFromMapFile("PATH_TO_MAP_FILE");
```

Destroying:
```pwn
DestroyMap(map);
```

Max maps:
If you want to change this limit, then define MAX_MAPS before include
```pwn
#define MAX_MAPS 100
#include "st_mapobjects"
```
