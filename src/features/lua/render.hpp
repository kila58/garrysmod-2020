#pragma once

class LuaRender
{
public:
	static void Start2D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "Start2D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void End2D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "End2D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void Start3D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "Start3D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void End3D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "End3D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void SuppressEngineLighting(ILuaInterface* state, bool suppressLighting)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SuppressEngineLighting");
		state->PushBool(suppressLighting);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void* GetRenderTarget(ILuaInterface* state)
	{
		if (!state)
			return nullptr;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "GetRenderTarget");
		state->PCall(0, 1, 0);

		void* res = (void*)state->GetObject(-1)->GetUserData(); // ITexture*
		state->Pop(state->Top());

		return res;
	}

	static void CopyRenderTargetToTexture(ILuaInterface* state, void* tex)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "CopyRenderTargetToTexture");
		state->PushUserType(tex, Type::TEXTURE);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetRenderTarget(ILuaInterface* state, void* tex)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetRenderTarget");
		state->PushUserType(tex, Type::TEXTURE);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetMaterial(ILuaInterface* state, void* mat)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetMaterial");
		state->PushUserType(mat, Type::MATERIAL);
		//state->PushUserdata(mat);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetColorModulation(ILuaInterface* state, float r, float g, float b)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetColorModulation");
		state->PushNumber(r);
		state->PushNumber(g);
		state->PushNumber(b);
		state->PCall(3, 1, 0);

		state->Pop(state->Top());
	}

	static void SetBlend(ILuaInterface* state, float blend)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetBlend");
		state->PushNumber(blend);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilEnable(ILuaInterface* state, bool enable)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilEnable");
		state->PushBool(enable);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilCompareFunction(ILuaInterface* state, int comparefunction)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilCompareFunction");
		state->PushNumber(comparefunction);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilPassOperation(ILuaInterface* state, int passoperation)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilPassOperation");
		state->PushNumber(passoperation);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilFailOperation(ILuaInterface* state, int failoperation)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilFailOperation");
		state->PushNumber(failoperation);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilZFailOperation(ILuaInterface* state, int zfailoperation)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilZFailOperation");
		state->PushNumber(zfailoperation);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilTestMask(ILuaInterface* state, uint32_t mask)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilTestMask");
		state->PushNumber(mask);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilWriteMask(ILuaInterface* state, uint32_t mask)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilWriteMask");
		state->PushNumber(mask);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetStencilReferenceValue(ILuaInterface* state, int referencevalue)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetStencilReferenceValue");
		state->PushNumber(referencevalue);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void ClearStencil(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "ClearStencil");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}
};