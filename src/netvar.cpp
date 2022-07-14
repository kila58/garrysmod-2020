#include "netvar.hpp"

#include "garrysmod.hpp"

bool NetVar::Init()
{
	return true;
}

ptr NetVar::Get(const char* name, RecvTable* table)
{
	if (ptr offset = offsets[name])
	{
		return offset;
	}

	for (int i = 0; i < table->m_nProps; i++)
	{
		RecvProp& prop = table->m_pProps[i];
		RecvTable* child = prop.m_pDataTable;

		if (child && child->m_nProps)
		{
			ptr offset = Get(name, child);

			if (offset)
			{
				ptr final = prop.m_Offset + offset;

				offsets[name] = final;

				return final;
			}
		}

		if (!std::strcmp(prop.m_pVarName, name))
		{
			ptr final = prop.m_Offset;

			offsets[name] = final;

			return final;
		}
	}

	return 0;
}

RecvProp* NetVar::GetRecvProp(const char* name, RecvTable* table)
{
	for (int i = 0; i < table->m_nProps; i++)
	{
		RecvProp& prop = table->m_pProps[i];
		RecvTable* child = prop.m_pDataTable;

		if (child && child->m_nProps)
		{
			ptr offset = Get(name, child);

			if (offset)
			{
				return &prop;
			}
		}

		if (!std::strcmp(prop.m_pVarName, name))
		{
			return &prop;
		}
	}

	return NULL;
}

RecvTable* NetVar::GetTable(const char* tablename)
{
	RecvTable* table = nullptr;
	ClientClass* clientclass;
	
	for (clientclass = client->GetAllClasses(); clientclass; clientclass = clientclass->m_pNext)
	{
		table = clientclass->m_pRecvTable;

		if (table && std::strcmp(table->m_pNetTableName, tablename) == 0)
			return table;
	}

	return nullptr;
}

bool NetVar::HookProp(const char* tablename, const char* propname, RecvVarProxyFn fn, NetPropBackup& oldprop)
{
	RecvTable* table = GetTable(tablename);
	if (!table)
		return false;

	auto& prop = oldprop.first = GetRecvProp(propname, table);
	if (!prop)
		return false;
	
	oldprop.second = (RecvVarProxyFn)prop->m_ProxyFn;
	prop->m_ProxyFn = fn;
	
	return true;
}

void NetVar::Destroy()
{

}

NetVar netvars;
