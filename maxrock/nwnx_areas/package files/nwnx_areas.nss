// NWNX Areas
// Area instancing plugin
// (c) by virusman, 2006-2010

// Create new area from ResRef
object LoadArea(string sResRef);
// Create new area from ResRef
object CreateArea(string sResRef);
// Destroy area
void DestroyArea(object oArea);
// Set name for oArea
void SetAreaName(object oArea, string sName);


object LoadArea(string sResRef)
{
    SetLocalString(GetModule(), "NWNX!AREAS!CREATE_AREA", sResRef);
    object oRet =  GetLocalObject(GetModule(), "NWNX!AREAS!GET_LAST_AREA_ID");
    DeleteLocalString(GetModule(), "NWNX!AREAS!CREATE_AREA");
    return oRet;
    
}

object CreateArea(string sResRef)
{
    return LoadArea(sResRef);
}

void DestroyArea(object oArea)
{
    SetLocalString(GetModule(), "NWNX!AREAS!DESTROY_AREA", ObjectToString(oArea));
    DeleteLocalString(GetModule(), "NWNX!AREAS!DESTROY_AREA");
}

void SetAreaName(object oArea, string sName)
{
    SetLocalString(oArea, "NWNX!AREAS!SET_AREA_NAME", sName);
    DeleteLocalString(oArea, "NWNX!AREAS!SET_AREA_NAME");
}
