#include <a_samp>

#define DEBUG_MAP_OBJECTS
#include "st_mapobjects"
#include "izcmd"

new map;

main() {}

public OnPlayerSpawn(playerid)
{
	SetPlayerPos(playerid, -2639.6000976563, 740.5, 31.299999237061);
	return 1;
}

CMD:dlt(playerid, params[])
{
	if (DestroyMap(map))
		SendClientMessage(playerid, -1, "Карта удалена");
	return 1;
}

CMD:crt(playerid, params[])
{
	if ((map = LoadFromMapFile("arena_gofc2official.map")) > -1)
		SendClientMessage(playerid, -1, "Карта загруженна");
	return 1;
}
