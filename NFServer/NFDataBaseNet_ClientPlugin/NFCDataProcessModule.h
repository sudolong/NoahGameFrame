// -------------------------------------------------------------------------
//    @FileName      :    NFCDataProcessModule.h
//    @Author           :    LvSheng.Huang
//    @Date             ��    2013-10-03
//    @Module           :    NFCDataProcessModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFC_DATAPROCESS_MODULE_H
#define NFC_DATAPROCESS_MODULE_H

#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIGameLogicModule.h"
#include "NFComm/NFPluginModule/NFIDataProcessModule.h"
#include "NFComm/NFPluginModule/NFIClusterModule.h"
#include "NFComm/NFPluginModule/NFIUUIDModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFMessageDefine/NFMsgBase.pb.h"
#include "NFComm/NFPluginModule/NFILogicClassModule.h"
#include "NFComm/NFPluginModule/NFILogModule.h"
#include "NFComm/NFPluginModule/NFIElementInfoModule.h"
#include "NFComm/NFPluginModule/NFIAsyClusterModule.h"

class NFCDataProcessModule
    : public NFIDataProcessModule
{
public:

    NFCDataProcessModule(NFIPluginManager* p)
    {
        pPluginManager = p;

        mstrRoleTable = "Player";
        mstrAccountTable = "AccountInfo";
        mnLoadCount = 0;
    }
    virtual ~NFCDataProcessModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

    virtual const NFGUID CreateRole(const std::string& strAccount, const std::string& strName, const int nRace, const int nJob, const int nSex);
    virtual const bool DeleteRole(const std::string& strAccount, const NFGUID xID);
    virtual const NFGUID GetChar(const std::string& strAccount, const std::vector<std::string>& xFieldVec, std::vector<std::string>& xValueVec);

    //////////////////////////////////////////////////////////////////////////

    virtual bool RegisterAutoSave(const std::string& strClassName);
    virtual const bool LoadDataFormSql(const NFGUID& self , const std::string& strClassName);
    virtual const bool SaveDataToSql(const NFGUID& self);

    virtual const bool LoadDataFormSqlAsy( const NFGUID& self , const std::string& strClassName, const LOADDATA_RETURN_FUNCTOR& xFun, const std::string& strUseData);
    void LoadDataFormSqlAsySucess( const NFGUID& self, const int nResult, const std::vector<std::string>& vFieldVec, const std::vector<std::string>& vValueVec, const std::string& strUserData);

    virtual const bool SaveDataToSqlAsy( const NFGUID& self);
    void SaveDataToSqlAsySucess( const NFGUID& self, const int nRet, const std::string&strUseData);

private:
	const bool AttachData( const NFGUID& self );
	const bool ConvertPBToRecord(const NFMsg::PlayerRecordBase& xRecordData, NF_SHARE_PTR<NFIRecord> xRecord);

    int OnObjectClassEvent( const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var );

    void OnOnline(const NFGUID& self);
    void OnOffline(const NFGUID& self);

private:
    NFIKernelModule* m_pKernelModule;
    NFIClusterModule* m_pClusterSQLModule;
    NFIAsyClusterModule* m_pAsyClusterSQLModule;
	NFIUUIDModule* m_pUUIDModule;
	NFILogicClassModule* m_pLogicClassModule;
	NFILogModule* m_pLogModule;
    NFIElementInfoModule* m_pElementInfoModule;

private:
	NFMapEx<NFGUID, NFMapEx<std::string, std::string> > mtObjectCache;

    std::string mstrRoleTable;
    std::string mstrAccountTable;

private:
    struct LoadData
    {
        LOADDATA_RETURN_FUNCTOR mFunc;
        std::string strUseData;
    };

    NFINT64 mnLoadCount;
    NFMapEx<NFINT64, LoadData> mmLoadlisReq;
};


#endif
