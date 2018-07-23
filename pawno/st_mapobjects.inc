/* Copyright (c) 2018 Anton Styazhkin
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <a_samp>

#if defined st_mapobjects
	#endinput
#endif

#define st_mapobjects

#if !defined MAX_MAPS
	#define MAX_MAPS 100
#endif

static const
	MAP_OBJECT_COUNT = 0,
	MAP_LAST_OBJECT_ID = 1;

static stock 
	map_last_id,
	map_data[MAX_MAPS][2] = {-1, ...};
	
static stock
	IsElementObject(string[], start)
{
	return (string[start + 0] == 'o' // :3
		&&	string[start + 1] == 'b'
		&&	string[start + 2] == 'j'
		&&	string[start + 3] == 'e'
		&&	string[start + 4] == 'c'
		&&	string[start + 5] == 't'
	);
}

static stock
	Float:GetMapElement(string[], const find[], const size = sizeof string)
{
	new 
		pos, start_pos, end_pos, 
		buff[128];

	start_pos = pos = strfind(string, find) + strlen(find) + 2;

	while(string[pos++] != '\"') { }
	
	end_pos = pos;
	strmid(buff, string, start_pos, end_pos - 1, size);
	return floatstr(buff);
}

stock
	DestroyMap(mapid)
{
	if (map_data[mapid][MAP_OBJECT_COUNT] == -1)
		return 0;
	
	for (new i = map_data[mapid][MAP_OBJECT_COUNT]; i > -1; i--)
	{
		DestroyObject(i);
		#if defined DEBUG_MAP_OBJECTS
			printf("[ST'S MAP] deleted %d", map_data[mapid][MAP_LAST_OBJECT_ID] - i);
		#endif
	}
	map_data[mapid][MAP_LAST_OBJECT_ID] = -1;
	return 1;
}

stock
	LoadFromMapFile(path[])
{
	if (!fexist(path))
		return -1;
	
	new
		File:handle = fopen(path, io_read),
		str[1024],
		i = 0,
		model,
		Float:pos_x, Float:pos_y, Float:pos_z,
		Float:pos_rx, Float:pos_ry, Float:pos_rz;
	
	while (fread(handle, str))
	{
		while (str[i++] == ' ') { }

		if (IsElementObject(str, i))
		{
			model = floatround(GetMapElement(str, "model"));
			pos_x = GetMapElement(str, "posX");
			pos_y = GetMapElement(str, "posY");
			pos_z = GetMapElement(str, "posZ");
			pos_rx = GetMapElement(str, "rotX");
			pos_ry = GetMapElement(str, "rotY");
			pos_rz = GetMapElement(str, "rotZ");
			++map_data[map_last_id][MAP_OBJECT_COUNT];
			map_data[map_last_id][MAP_LAST_OBJECT_ID] = CreateObject(
				model,
				pos_x, pos_y, pos_z,
				pos_rx, pos_ry, pos_rz
			);
			#if defined DEBUG_MAP_OBJECTS
				printf("[ST'S MAP] [slot %d/ object %d] %d, %f, %f, %f, %f, %f, %f",
					map_last_id, map_data[map_last_id][MAP_LAST_OBJECT_ID],
					model,
					pos_x, pos_y, pos_z,
					pos_rx, pos_ry, pos_rz
				);
			#endif
		}
		
		i = 0;
	}
	
	fclose(handle);
	return map_last_id++;
}