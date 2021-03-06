/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
* Copyright (c) 2015 Justin Hoffman https://github.com/jhoffman0x/Box2D-MT
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <pulsar/Log.hpp>
#include "Box2D/Common/b2Settings.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

b2Version b2_mtVersion = {0, 1, 0};

b2Version b2_version = {2, 3, 2};

// Memory allocators. Modify these to use your own allocator.
void* b2Alloc(int32 size)
{
	return malloc(size);
}

void b2Free(void* mem)
{
	free(mem);
}

// You can modify this to use your logging facility.
void b2Log(const char* string, ...)
{
	va_list args;
	va_start(args, string);

	const auto size = std::snprintf(nullptr, 0, string, args);
	std::vector<char> buff(size + 1);
	std::snprintf(&buff[0], buff.size(), string, args);
	std::string str(buff.begin(), buff.end());

	va_end(args);

	PL_LOG(PL_INFO, "{0}.", str);
}
