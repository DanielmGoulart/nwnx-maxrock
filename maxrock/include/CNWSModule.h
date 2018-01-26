#ifndef _NX_NWN_STRUCT_CNWSMODULE_
#define _NX_NWN_STRUCT_CNWSMODULE_

struct CNWSModule_s { //: public CResHelper_s { //, public CGameObject {
	uint32_t					*pVTable;			// 0000 
	uint32_t 					bIsRequestPending;  // 0004 not quite sure
	void 						*pRes;    			// 0008
	char 					sResRef[16];	        // 000C 
    uint32_t                    obj_type;			// 001C			   //	28	1C
    nwn_objid_t					obj_id;				// 0020			   //	32	20
    uint32_t                    field_24;			// 0024			   //	36	24
    uint32_t                    field_28;			// 0028			   //	40	28
    uint32_t                    field_2C;							   //	44	2C
    uint32_t                    field_30;							   //	48	30
    nwn_objid_t                 *mod_areas;							   //	52	34
    uint32_t                    mod_areas_len;						   //	56	38
    uint32_t                    field_3C;							   //	60	3C
    uint32_t                    field_40;							   //	64	40
    uint32_t                    field_44;							   //	68	44
    CExoLinkedList              mod_PlayerTURDList;					   //	72	48
    uint32_t                    field_4C;							   //	76	4C
    uint32_t                    field_50;							   //	80	50
    uint32_t                    field_54;							   //	84	54
    uint32_t                    field_58;							   //	88	58
    uint32_t                    field_5C;							   //	92	5C
    uint32_t                    field_60;							   //	96	60
    uint32_t			        field_64;							   //	100	64
    uint32_t                    field_68;							   //	104	68
    uint32_t                    field_6C;							   //	108	6C
    uint32_t                    field_70;							   //	112	70
    uint32_t                    field_74;							   //	116	74
    uint32_t                    field_78;							   //	120	78
    uint32_t                    field_7C;							   //	124	7C
    uint32_t                    field_80;							   //	128	80
    uint32_t                    field_84;							   //	132	84
    uint32_t                    field_88;							   //	136	88
    uint32_t                    field_8C;							   //	140	8C
    uint32_t                    field_90;							   //	144	90
    uint32_t                    field_94;							   //	148	94
    uint32_t                    field_98;							   //	152	98
    uint32_t                    field_9C;							   //	156	9C
    uint32_t                    field_A0;							   //	160	A0
    CNWSScriptVarTable          mod_vartable;	/* 0x0088 */		   //	164	A4
    																   //	168	A8
    uint32_t                    field_AC;							   //	172	AC
    uint32_t                    field_B0;							   //	176	B0

	CExoString					Mod_OnHeartbeat;
	CExoString					Mod_OnUsrDefined;
	CExoString					Mod_OnModLoad;
	CExoString					Mod_OnModStart;
	CExoString					Mod_OnClientEntr;
	CExoString					Mod_OnClientLeav;
	CExoString					Mod_OnActvtItem;
	CExoString					Mod_OnAcquirItem;
	CExoString					Mod_OnUnAqreItem;
	CExoString					Mod_OnPlrDeath;
	CExoString					Mod_OnPlrDying;
	CExoString					Mod_OnSpawnBtnDn;
	CExoString					Mod_OnPlrRest;
	CExoString					Mod_OnPlrLvlUp;
	CExoString					Mod_OnCutsnAbort;
	CExoString					Mod_OnPlrEqItm;
	CExoString					Mod_OnPlrUnEqItm;
	CExoString					Mod_OnPlrChat;    

    uint32_t					spacer1[2];					/* 0x0090 */
    
    void						*mod_objlist;					/* 0x0130 */
    uint32_t					mod_objlist_len;				/* 0x0134 */
    uint32_t					mod_objlist_alloc;				/* 0x0138 */
    
    uint32_t					spacer2_01;						/* 0x013C */
    uint32_t					spacer2_02;						/* 0x0140 */
    uint32_t					spacer2_03;						/* 0x0144 */
    uint32_t					spacer2_04;						/* 0x0148 */
    CLookupTableObject			*lookuptable;					/* 0x014C */
    uint32_t					lookuptable_len;				/* 0x0150 */
    uint32_t					lookuptable_alloc;				/* 0x0154 */
    uint32_t					spacer2[26];					/* 0x0158 */
    
    uint32_t					mod_date_year;					/* 0x01DC */
    uint32_t					mod_date_month;					/* 0x01E0 */
    uint32_t					mod_date_day;					/* 0x01E4 */
    uint32_t					mod_time_hour;					/* 0x01E8 */
    
    uint32_t					field_1EC;
    uint8_t						mod_timeofday;					/* 0x1F0 */
    uint8_t						mod_dawnhour;
    uint8_t						mod_duskhour;
    uint8_t						field_1D7l;

    uint32_t					mod_LL_date;					/* 0x01D8 */
    uint32_t					mod_LL_time;					/* 0x01DC */
    
    uint32_t	getModuleTime() {
    	return (mod_LL_date * 2880000LL) + mod_LL_time;
    }

	void				AddObjectToLimbo(nwn_objid_t oID);
	int 				AddObjectToLookupTable(CExoString Tag, nwn_objid_t oID);
	CNWSArea * 			GetArea(nwn_objid_t oID);
	CNWSPlayerTURD* 	GetPlayerTURDFromList(CNWSPlayer *Player);
	void 				SetScriptName(int iScript, CExoString ScriptName);
	int 				RemoveObjectFromLookupTable(CExoString Tag, nwn_objid_t oID);
	nwn_objid_t			FindObjectByTagOrdinal(CExoString *sTag, int nNth);
};

#endif

