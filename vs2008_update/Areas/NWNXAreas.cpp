/***************************************************************************
    Chat plugin for NWNX - Implementation of the CNWNXEvents class.
    (c) 2005 dumbo (dumbo@nm.ru)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***************************************************************************/

#include <stdio.h>
#include "stdafx.h"
#include "NWNXAreas.h"
#include "HookFunc.h"
#include "../NWNXdll/IniFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNWNXAreas::CNWNXAreas()
{
	confKey = "AREAS";
}

CNWNXAreas::~CNWNXAreas()
{
}

BOOL CNWNXAreas::OnCreate (const char* LogDir)
{
	// call the base class function
	char log[MAX_PATH];
	sprintf (log, "%s\\nwnx_areas.txt", LogDir);
	if (!CNWNXBase::OnCreate(log))
		return false;

	// write copy information to the log file
	Log (0, "NWNX Areas version 0.2.2 for Windows.\n");
	Log (0, "(c) 2006-2008 by virusman (virusman@virusman.ru)\n");
	
	return HookFunctions();
}

char* CNWNXAreas::OnRequest (char* gameObject, char* Request, char* Parameters)
{
	this->pGameObject = gameObject;
	this->nGameObjectID = *(dword *)(gameObject+0x4);
	if (strncmp(Request, "CREATE_AREA", 11) == 0) 	
	{
		NWNXCreateArea(gameObject, Parameters);
		return NULL;
	}
	else if (strncmp(Request, "DESTROY_AREA", 12) == 0) 	
	{
		NWNXDestroyArea(gameObject, strtol(Parameters, (char **)NULL, 16));
		return NULL;
	}
	return NULL;
}

unsigned long CNWNXAreas::OnRequestObject (char *gameObject, char* Request)
{
	if (strncmp(Request, "GET_LAST_AREA_ID", 16) == 0) 	
	{
		return nLastAreaID;
	}
	return OBJECT_INVALID;
}

BOOL CNWNXAreas::OnRelease ()
{
	Log ("o Shutdown.\n");
	// call base class function
	return CNWNXBase::OnRelease();
}