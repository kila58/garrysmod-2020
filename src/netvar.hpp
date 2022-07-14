#pragma once

#include <unordered_map>
#include <utility>

#include "definitions.hpp"

struct RecvTable;
class CRecvProxyData;
struct RecvProp;

typedef void* (*CreateClientClassFn)(int entnum, int serialNum);
typedef void* (*CreateEventFn)();

typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);
using NetPropBackup = std::pair<RecvProp*, RecvVarProxyFn>;

class NetVar
{
private:
	std::unordered_map<const char*, int> offsets;
public:
	bool Init();
	ptr Get(const char* name, RecvTable* table);
	RecvProp* GetRecvProp(const char* name, RecvTable* table);
	RecvTable* GetTable(const char* tablename);
	bool HookProp(const char* tablename, const char* propname, RecvVarProxyFn fn, NetPropBackup& oldprop);
	void Destroy();
};

struct RecvProp
{
	const char* m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};

class DVariant
{
public:
	union
	{
		float	m_Float;
		long	m_Int;
		char	*m_pString;
		void	*m_pData;
		float	m_Vector[3];
	};
};

class NetvarValue
{
public:
	union
	{
		float	m_Float;
		long	m_Int;
		char*	m_pString;
		void*	m_pData;
		float	m_Vector[3];
	};

	int			m_Type;
};

class CRecvProxyData
{
public:
	const RecvProp* m_pRecvProp;
	NetvarValue		m_Value;
	int				m_iElement;
	int				m_ObjectID;
};

struct RecvTable
{
	RecvProp*	m_pProps;
	int			m_nProps;
	void*		m_pDecoder;
	const char*	m_pNetTableName;
	bool		m_bInitialized;
	bool		m_bInMainList;
};

class ClientClass
{
public:
	void*			m_pCreateFn;
	void*			m_pCreateEventFn;
	const char*		m_pNetworkName;
	RecvTable*		m_pRecvTable;
	ClientClass*	m_pNext;
	int				m_ClassID;
};

extern NetVar netvars;
