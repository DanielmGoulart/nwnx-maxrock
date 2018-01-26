#include "StdAfx.h"
#include "types.h"
#include "CAutoMap.h"

//Allocates size bytes and returns a pointer to its start location
extern void * (__cdecl *nwnx_malloc)( unsigned int size );
//Frees memory blocks allocated by nwnx_malloc/calloc/realloc
extern void (__cdecl *nwnx_free)( void * ptr  );

CMiniMapData **CCreatureMaps::ResizeMapList(int NewSize) {
	CMiniMapData **p = (CMiniMapData **) nwnx_malloc( sizeof(CMiniMapData*)*NewSize);
	for (unsigned int i=0; i<this->MiniMapCount; i++) {
		p[i] = this->MiniMap[i];
	}
	nwnx_free(this->MiniMap);

	return p;
}

nwn_objid_t *CCreatureMaps::CopyAreas(int NewSize) {
	nwn_objid_t *p = (nwn_objid_t *) nwnx_malloc( sizeof(nwn_objid_t)*NewSize);
	memcpy(p, this->Areas, this->AreaCount * 4);
	nwnx_free(this->Areas);
	return p;
}

CMiniMapData **CCreatureMaps::Copy(CMiniMapData** CopyFrom, int nSize) {
	CMiniMapData **p = (CMiniMapData **) nwnx_malloc( sizeof(CMiniMapData*) *nSize);
	CMiniMapData *d = NULL;
	for (unsigned int i=0; i<nSize; i++) {
		d = (CMiniMapData *) nwnx_malloc(sizeof(CMiniMapData));
		memcpy(d, CopyFrom[i], 0x80);
		p[i] = d;
	}
	return p;
}

void CCreatureMaps::DeleteMiniMaps() {
	if (MiniMap) {
		if (MiniMapCount > 0) {
			for (int i=0; i<MiniMapCount; i++) {
				nwnx_free( MiniMap[i]);
				MiniMap[i] = NULL;
			}
			nwnx_free(MiniMap);
			MiniMap = NULL;
		}
	}
	MiniMapCount = 0;
}

void CCreatureMaps::DeleteAreas() {
	if (Areas) {
		nwnx_free(Areas);
		Areas = NULL;
	}
	AreaAlloc = 0;
	AreaCount = 0;
}

void CCreatureMaps::AddArea(unsigned areaid) {
	MiniMap = ResizeMapList(MiniMapCount+1);

	MiniMap[MiniMapCount] = (CMiniMapData*) nwnx_malloc(sizeof(CMiniMapData));
	ZeroMemory(MiniMap[MiniMapCount], sizeof(CMiniMapData));
	++MiniMapCount;

	CExoArrayList_uint32___Add((CExoArrayList_uint32*)&Areas, NULL, areaid);
}


void CCreatureMaps::RemoveArea(unsigned areaid) {
	int iIndex = CExoArrayList_uint32_contains((CExoArrayList_uint32*)&Areas, areaid);
	if (iIndex != -1) {

		CMiniMapData **Map = (CMiniMapData**)nwnx_malloc(sizeof(CMiniMapData*)*(MiniMapCount-1));
		int j=0;
		for (int i=0; i<MiniMapCount; i++) {
			if (i != iIndex) {
				Map[j++] = MiniMap[i];
			}
			else {
				nwnx_free(MiniMap[i]);
			}
		}
		nwnx_free(MiniMap);
		MiniMap = Map;
		--MiniMapCount;

		CExoArrayList_uint32___Remove(&Areas, NULL, areaid);
	}
}

CMiniMapData **CTURDMaps::Copy(CMiniMapData** CopyFrom, int nSize) {
	CMiniMapData **p = (CMiniMapData**) nwnx_malloc(sizeof(CMiniMapData*)*nSize);
	CMiniMapData *d = NULL;
	for (unsigned int i=0; i<nSize; i++) {
		d = (CMiniMapData*) nwnx_malloc( sizeof(CMiniMapData));
		memcpy(d, CopyFrom[i], 0x80);
		p[i] = d;
	}
	return p;
}

CMiniMapData **CTURDMaps::ResizeMapList(int NewSize) {
	CMiniMapData **p = (CMiniMapData**) nwnx_malloc(sizeof(CMiniMapData*)*NewSize);
	for (unsigned int i=0; i<this->AreaCount; i++) {
		p[i] = this->MiniMap[i];
	}
	nwnx_free(this->MiniMap);

	return p;
}

nwn_objid_t *CTURDMaps::CopyAreas(int NewSize) {
	nwn_objid_t *p = (nwn_objid_t*) nwnx_malloc(sizeof(nwn_objid_t)*NewSize);
	memcpy(p, this->Areas, this->AreaCount * 4);
	nwnx_free(this->Areas);
	return p;
}


void CTURDMaps::AddArea(unsigned areaid) {
	MiniMap = ResizeMapList(AreaCount+1);
	MiniMap[AreaCount] = (CMiniMapData*) nwnx_malloc(sizeof(CMiniMapData));
	ZeroMemory(MiniMap[AreaCount], sizeof(CMiniMapData));

	Areas = CopyAreas(AreaCount+1);
	Areas[AreaCount] = areaid;

	++AreaCount;
}

void CTURDMaps::RemoveArea(unsigned areaid) {
	int iIndex = CExoArrayList_uint32_contains((CExoArrayList_uint32*)&Areas, areaid);
	if (iIndex != -1) {

		CMiniMapData **Map = (CMiniMapData**)nwnx_malloc( sizeof(CMiniMapData*)*(AreaCount-1));
		int j=0;
		for (int i=0; i<AreaCount; i++) {
			if (i != iIndex) {
				Map[j++] = MiniMap[i];
			}
			else {
				nwnx_free(MiniMap[i]);
			}
		}
		nwnx_free(MiniMap);
		MiniMap = Map;

		nwn_objid_t *areas = (nwn_objid_t*) nwnx_malloc(sizeof(nwn_objid_t)*(AreaCount-1));
		j=0;
		for (int i=0; i<AreaCount; i++) {
			if (i != iIndex) {
				areas[j++] = Areas[i];
			}
		}
		nwnx_free(Areas);
		Areas = areas;
	}
}