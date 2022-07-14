#pragma once

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30),
};

enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
};

class MatRenderContext
{
public:
	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;
};

class ITexture
{
public:

};

class IMaterial
{
public:
	void IncrementReferenceCount()
	{
		return (GetVirtual<void (__thiscall*)(void*)>(this, 12))(this);
	}

	void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on)
	{
		return (GetVirtual<void (__thiscall*)(void*, MaterialVarFlags_t, bool) >(this, 29))(this, flag, on);
	}
};

class MaterialSystem
{
public:
	IMaterial* CreateMaterial(char const* name)
	{
		return (GetVirtual<IMaterial* (__thiscall*)(void*, char const*, void*)>(this, 74))(this, name, nullptr);
	}

	MatRenderContext* GetRenderContext()
	{
		return GetVirtual<MatRenderContext* (__thiscall*)(void*)>(this, 98)(this);
	}
};

class EngineModel
{
public:
	void ForceMaterialOverride(IMaterial* newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL)
	{
		return GetVirtual<void(__thiscall*)(void*, IMaterial*, OverrideType_t)>(this, 1)(this, newMaterial, nOverrideType);
	}
};