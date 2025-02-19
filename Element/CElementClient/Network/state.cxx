#include <winsock2.h>

#include "callid.hxx"
#include "gnproto.h"
#include "gncompress.h"

namespace GNET
{

static GNET::Protocol::Type _state_LoginClient[] =
{
    PROTOCOL_ERRORINFO,
    PROTOCOL_ONLINEANNOUNCE,
    PROTOCOL_CHALLENGE,
    PROTOCOL_KEYEXCHANGE,
    RPC_GAMEZONELIST,
    RPC_ROLEALLLIST,
    RPC_FRIENDALLLIST,
	PROTOCOL_MATRIXCHALLENGE,
};  
    
GNET::Protocol::Manager::Session::State state_LoginClient(_state_LoginClient,
                        sizeof(_state_LoginClient)/sizeof(GNET::Protocol::Type), 6000);
    
static GNET::Protocol::Type _state_DataExchangeClient[] =
{   
    PROTOCOL_SENDMSG,
    PROTOCOL_STATUSANNOUNCE,
    PROTOCOL_QQADDFRIEND_RE,
    RPC_USERGETINFO,
    RPC_USERSETINFO,
    RPC_FRIENDDEL,
    RPC_MSGRETRIEVEOFFLINE,
    RPC_QQADDFRIENDRQST,
	PROTOCOL_ERRORINFO,
	PROTOCOL_DELIVERROLESTATUS,
	RPC_FINDROLEBYNAME,
	PROTOCOL_QQADDFRIEND,
    RPC_GROUPGETINFO,
    RPC_GROUPSETINFO,
	RPC_FINDROLE,
	RPC_FRIENDMOVE,
};

GNET::Protocol::Manager::Session::State state_DataExchangeClient(_state_DataExchangeClient,
                        sizeof(_state_DataExchangeClient)/sizeof(GNET::Protocol::Type), 7200);

static GNET::Protocol::Type _state_GLoginClient[] =
{
    PROTOCOL_ERRORINFO,
    PROTOCOL_CHALLENGE,
    PROTOCOL_KEYEXCHANGE,
    PROTOCOL_ONLINEANNOUNCE,
	PROTOCOL_KEEPALIVE,
	PROTOCOL_ANNOUNCEFORBIDINFO,
	PROTOCOL_UPDATEREMAINTIME,
	PROTOCOL_MATRIXCHALLENGE,
};

GNET::Protocol::Manager::Session::State state_GLoginClient(_state_GLoginClient,
                        sizeof(_state_GLoginClient)/sizeof(GNET::Protocol::Type), 6000);

static GNET::Protocol::Type _state_GSelectRoleClient[] =
{
    PROTOCOL_ERRORINFO,
    PROTOCOL_ROLELIST_RE,
    PROTOCOL_CREATEROLE_RE,
	PROTOCOL_DELETEROLE_RE,
    PROTOCOL_SELECTROLE_RE,
	PROTOCOL_UNDODELETEROLE_RE,
	PROTOCOL_SETCUSTOMDATA_RE,
	PROTOCOL_BINDER,
	PROTOCOL_COMPRESSBINDER,
	PROTOCOL_KEEPALIVE,
	PROTOCOL_GETCUSTOMDATA,
	PROTOCOL_GETCUSTOMDATA_RE,
	PROTOCOL_ANNOUNCEFORBIDINFO,
	PROTOCOL_ACREMOTECODE,
	PROTOCOL_ACQUESTION,
	PROTOCOL_UPDATEREMAINTIME,
	//faction related protocols, faction protocols maybe broadcast 
	PROTOCOL_FACTIONCHAT,
    PROTOCOL_FACTIONACCEPTJOIN_RE,
    PROTOCOL_FACTIONEXPEL_RE,
    PROTOCOL_FACTIONBROADCASTNOTICE_RE,
    PROTOCOL_FACTIONMASTERRESIGN_RE,
    PROTOCOL_FACTIONAPPOINT_RE,
    PROTOCOL_FACTIONLEAVE_RE,
    PROTOCOL_FACTIONUPGRADE_RE,
    PROTOCOL_FACTIONDEGRADE_RE,
	PROTOCOL_FACTIONAPPLYJOIN_RE,
	PROTOCOL_FACTIONDISMISS_RE,
	PROTOCOL_FACTIONRENAME_RE,
	PROTOCOL_FACTIONCHANGPROCLAIM_RE,
	PROTOCOL_FACTIONRESIGN_RE,
    PROTOCOL_FRIENDSTATUS,
    PROTOCOL_CHATMESSAGE,
	PROTOCOL_WORLDCHAT,
    PROTOCOL_GAMEDATASEND,
	PROTOCOL_WEBTRADEPREPOST_RE,
	PROTOCOL_WEBTRADEPRECANCELPOST_RE,
	PROTOCOL_WEBTRADEGETDETAIL_RE,
	PROTOCOL_GETPLAYERIDBYNAME_RE,
	PROTOCOL_ACCOUNTLOGINRECORD,
	RPC_PLAYERPOSITIONRESETRQST,
	PROTOCOL_PLAYERCHANGEDS_RE,
	PROTOCOL_SSOGETTICKET_RE,
	PROTOCOL_WAITQUEUESTATENOTIFY,
	PROTOCOL_CANCELWAITQUEUE_RE,
};

GNET::Protocol::Manager::Session::State state_GSelectRoleClient(_state_GSelectRoleClient,
                        sizeof(_state_GSelectRoleClient)/sizeof(GNET::Protocol::Type), 86400);

static GNET::Protocol::Type _state_GDataExchgClient[] =
{
    PROTOCOL_ERRORINFO,
    PROTOCOL_GAMEDATASEND,
	PROTOCOL_COMPRESSBINDER,
    PROTOCOL_STATUSANNOUNCE,
    PROTOCOL_PLAYERLOGOUT,
    PROTOCOL_CHATMESSAGE,
	PROTOCOL_WORLDCHAT,
	PROTOCOL_PRIVATECHAT,
	PROTOCOL_TRADESTART,
    PROTOCOL_TRADESTART_RE,
    PROTOCOL_TRADEADDGOODS_RE,
    PROTOCOL_TRADEREMOVEGOODS_RE,
    PROTOCOL_TRADESUBMIT_RE,
    PROTOCOL_TRADEMOVEOBJ_RE,
    PROTOCOL_TRADECONFIRM_RE,
    PROTOCOL_TRADEDISCARD_RE,
    PROTOCOL_TRADEEND,
	PROTOCOL_BINDER,
    RPC_TRADESTARTRQST,
	PROTOCOL_PLAYERBASEINFO_RE,
    PROTOCOL_PLAYERBASEINFOCRC_RE,
	PROTOCOL_GETPLAYERBRIEFINFO_RE,
    PROTOCOL_SETCUSTOMDATA_RE,
    PROTOCOL_SETUICONFIG_RE,
	PROTOCOL_GETUICONFIG_RE,
	PROTOCOL_GETCUSTOMDATA,
	PROTOCOL_GETCUSTOMDATA_RE,
	PROTOCOL_KEEPALIVE,
	PROTOCOL_ROLESTATUSANNOUNCE,
	PROTOCOL_GETPLAYERIDBYNAME_RE,
	PROTOCOL_UPDATEREMAINTIME,
	
	PROTOCOL_ADDFRIEND_RE,
	PROTOCOL_GETFRIENDS_RE,
	RPC_ADDFRIENDRQST,
    PROTOCOL_FRIENDSTATUS,
	PROTOCOL_GETFRIENDS_RE,
    PROTOCOL_SETGROUPNAME_RE,
    PROTOCOL_SETFRIENDGROUP_RE,
    PROTOCOL_DELFRIEND_RE,
	PROTOCOL_GETSAVEDMSG_RE,
    PROTOCOL_SETHELPSTATES_RE,
    PROTOCOL_GETHELPSTATES_RE,
    PROTOCOL_CHATROOMCREATE_RE,
    PROTOCOL_CHATROOMINVITE,
    PROTOCOL_CHATROOMINVITE_RE,
    PROTOCOL_CHATROOMJOIN_RE,
    PROTOCOL_CHATROOMLEAVE, 
    PROTOCOL_CHATROOMEXPEL,
    PROTOCOL_CHATROOMSPEAK,
    PROTOCOL_CHATROOMLIST_RE,


	//game master protocols
	PROTOCOL_GMONLINENUM_RE,
    PROTOCOL_GMLISTONLINEUSER_RE,
    PROTOCOL_GMKICKOUTUSER_RE,
    PROTOCOL_GMSHUTUP_RE,
    PROTOCOL_GMRESTARTSERVER,
    PROTOCOL_GMRESTARTSERVER_RE,
	PROTOCOL_GMKICKOUTROLE_RE,
	PROTOCOL_GMSHUTUPROLE_RE,
	PROTOCOL_ANNOUNCEFORBIDINFO,
	PROTOCOL_QUERYUSERPRIVILEGE_RE,
	PROTOCOL_GMTOGGLECHAT_RE,
	PROTOCOL_GMFORBIDROLE_RE,
    PROTOCOL_REPORT2GM_RE,
    PROTOCOL_COMPLAIN2GM_RE,
	PROTOCOL_ACREMOTECODE,
	PROTOCOL_ACQUESTION,

	//faction related protocols
	PROTOCOL_FACTIONCHAT,
    PROTOCOL_FACTIONOPREQUEST_RE,
    PROTOCOL_FACTIONCREATE_RE,
    PROTOCOL_FACTIONACCEPTJOIN_RE,
    PROTOCOL_FACTIONEXPEL_RE,
    PROTOCOL_FACTIONBROADCASTNOTICE_RE,
    PROTOCOL_FACTIONMASTERRESIGN_RE,
    PROTOCOL_FACTIONAPPOINT_RE,
    PROTOCOL_FACTIONLEAVE_RE,
    PROTOCOL_FACTIONUPGRADE_RE,
    PROTOCOL_FACTIONDEGRADE_RE,
    RPC_FACTIONINVITEJOIN,
	PROTOCOL_FACTIONAPPLYJOIN_RE,
	PROTOCOL_FACTIONLISTMEMBER_RE,
	PROTOCOL_GETFACTIONBASEINFO_RE,
	PROTOCOL_FACTIONDISMISS_RE,
    PROTOCOL_GETPLAYERFACTIONINFO,
    PROTOCOL_GETPLAYERFACTIONINFO_RE,
	PROTOCOL_FACTIONRENAME_RE,
	PROTOCOL_FACTIONCHANGPROCLAIM_RE,
	PROTOCOL_FACTIONRESIGN_RE,

	// mail protocols
    PROTOCOL_ANNOUNCENEWMAIL,
    PROTOCOL_GETMAILLIST_RE,
    PROTOCOL_GETMAIL_RE,
    PROTOCOL_GETMAILATTACHOBJ_RE,
    PROTOCOL_DELETEMAIL_RE,
    PROTOCOL_PRESERVEMAIL_RE,
    PROTOCOL_PLAYERSENDMAIL_RE,

	// auction protocols
	PROTOCOL_AUCTIONOPEN_RE,
    PROTOCOL_AUCTIONBID_RE,
    PROTOCOL_AUCTIONCLOSE_RE,
    PROTOCOL_AUCTIONLIST_RE,
    PROTOCOL_AUCTIONGET_RE,
	PROTOCOL_AUCTIONATTENDLIST_RE,
	PROTOCOL_AUCTIONEXITBID_RE,
	PROTOCOL_AUCTIONGETITEM_RE,

	PROTOCOL_BATTLEGETMAP_RE,
	PROTOCOL_BATTLECHALLENGE_RE,
	PROTOCOL_BATTLECHALLENGEMAP_RE,
	PROTOCOL_BATTLEENTER_RE,
	PROTOCOL_BATTLESTATUS_RE,

	//sell point protocols
    PROTOCOL_SELLPOINT_RE,
    PROTOCOL_GETSELLLIST_RE,
    PROTOCOL_FINDSELLPOINTINFO_RE,
    PROTOCOL_ANNOUNCESELLRESULT,
    PROTOCOL_SELLCANCEL_RE,
    PROTOCOL_BUYPOINT_RE,

	PROTOCOL_STOCKCOMMISSION_RE,
	PROTOCOL_STOCKACCOUNT_RE,
	PROTOCOL_STOCKTRANSACTION_RE,
	PROTOCOL_STOCKBILL_RE,
	PROTOCOL_STOCKCANCEL_RE,
	PROTOCOL_CASHLOCK_RE,
	PROTOCOL_CASHPASSWORDSET_RE,
	PROTOCOL_AUTOLOCKSET_RE,
	PROTOCOL_AUCTIONLISTUPDATE,
	PROTOCOL_AUCTIONLISTUPDATE_RE,
	PROTOCOL_REFGETREFERENCECODE_RE,
	PROTOCOL_REFLISTREFERRALS_RE,
	PROTOCOL_REFWITHDRAWBONUS_RE,
	PROTOCOL_GETREWARDLIST_RE,
	PROTOCOL_EXCHANGECONSUMEPOINTS_RE,
	PROTOCOL_REWARDMATURENOTICE,
	//网页交易平台
	PROTOCOL_WEBTRADEPREPOST_RE,
    PROTOCOL_WEBTRADEPRECANCELPOST_RE,
    PROTOCOL_WEBTRADELIST_RE,
    PROTOCOL_WEBTRADEGETITEM_RE,
    PROTOCOL_WEBTRADEATTENDLIST_RE,
    PROTOCOL_WEBTRADEGETDETAIL_RE,
	PROTOCOL_WEBTRADEUPDATE_RE,
	//系统拍卖
    PROTOCOL_SYSAUCTIONLIST_RE,    
	PROTOCOL_SYSAUCTIONGETITEM_RE,
    PROTOCOL_SYSAUCTIONACCOUNT_RE,
    PROTOCOL_SYSAUCTIONBID_RE,
    PROTOCOL_SYSAUCTIONCASHTRANSFER_RE,
	//帮派基地
    PROTOCOL_CREATEFACTIONFORTRESS_RE,
    PROTOCOL_FACTIONFORTRESSLIST_RE,
    PROTOCOL_FACTIONFORTRESSCHALLENGE_RE,
    PROTOCOL_FACTIONFORTRESSBATTLELIST_RE,
    PROTOCOL_FACTIONFORTRESSGET_RE,

    PROTOCOL_FACTIONALLIANCEAPPLY_RE,
    PROTOCOL_FACTIONALLIANCEREPLY_RE,
    PROTOCOL_FACTIONHOSTILEAPPLY_RE,
    PROTOCOL_FACTIONHOSTILEREPLY_RE,
    PROTOCOL_FACTIONREMOVERELATIONAPPLY_RE,
    PROTOCOL_FACTIONREMOVERELATIONREPLY_RE,
	PROTOCOL_FACTIONLISTRELATION_RE,
	PROTOCOL_FACTIONRELATIONRECVAPPLY,
	PROTOCOL_FACTIONRELATIONRECVREPLY,
	PROTOCOL_FACTIONLISTONLINE_RE,

    PROTOCOL_USERCOUPON_RE,
    PROTOCOL_USERCOUPONEXCHANGE_RE,
	PROTOCOL_USERADDCASH_RE,

	PROTOCOL_FRIENDEXTLIST,
	PROTOCOL_SENDAUMAIL_RE,
	PROTOCOL_GMGETPLAYERCONSUMEINFO_RE,
	PROTOCOL_SSOGETTICKET_RE,

	PROTOCOL_COUNTRYBATTLEMOVE_RE,
	PROTOCOL_COUNTRYBATTLESYNCPLAYERLOCATION,
    PROTOCOL_COUNTRYBATTLEGETMAP_RE,
	PROTOCOL_COUNTRYBATTLEGETSCORE_RE,
	PROTOCOL_COUNTRYBATTLEGETCONFIG_RE,
	PROTOCOL_COUNTRYBATTLEPREENTERNOTIFY,
	PROTOCOL_COUNTRYBATTLERESULT,
	PROTOCOL_COUNTRYBATTLESINGLEBATTLERESULT,
	PROTOCOL_COUNTRYBATTLEKINGASSIGNASSAULT_RE,
	PROTOCOL_COUNTRYBATTLEGETBATTLELIMIT_RE,
	PROTOCOL_COUNTRYBATTLEGETKINGCOMMANDPOINT_RE,

	PROTOCOL_QPANNOUNCEDISCOUNT,
	PROTOCOL_QPGETACTIVATEDSERVICES_RE,
	PROTOCOL_QPADDCASH_RE,

	PROTOCOL_GMSETTIMELESSAUTOLOCK_RE,
	PROTOCOL_PLAYERCHANGEDS_RE,
	PROTOCOL_CHANGEDS_RE,
	PROTOCOL_PLAYERRENAME_RE,
	PROTOCOL_PLAYERNAMEUPDATE,

    PROTOCOL_KEGETSTATUS_RE,
    PROTOCOL_KECANDIDATEAPPLY_RE,
    PROTOCOL_KEVOTING_RE,

	PROTOCOL_PLAYERGIVEPRESENT_RE,
	PROTOCOL_PLAYERASKFORPRESENT_RE,
	PROTOCOL_FACTIONDELAYEXPELANNOUNCE,

	PROTOCOL_PSHOPCREATE_RE,
	PROTOCOL_PSHOPBUY_RE,
	PROTOCOL_PSHOPSELL_RE,
	PROTOCOL_PSHOPCANCELGOODS_RE,
	PROTOCOL_PSHOPPLAYERBUY_RE,
	PROTOCOL_PSHOPPLAYERSELL_RE,
	PROTOCOL_PSHOPSETTYPE_RE,
	PROTOCOL_PSHOPACTIVE_RE,
	PROTOCOL_PSHOPMANAGEFUND_RE,
	PROTOCOL_PSHOPDRAWITEM_RE,
	PROTOCOL_PSHOPCLEARGOODS_RE,
	PROTOCOL_PSHOPSELFGET_RE,
	PROTOCOL_PSHOPPLAYERGET_RE,
	PROTOCOL_PSHOPLIST_RE,
	PROTOCOL_PSHOPLISTITEM_RE,

	PROTOCOL_PLAYERPROFILEGETPROFILEDATA_RE,
	PROTOCOL_PLAYERPROFILEGETMATCHRESULT_RE,
	PROTOCOL_UNIQUEDATAMODIFYBROADCAST,
	PROTOCOL_TANKBATTLEPLAYERAPPLY_RE,
	PROTOCOL_TANKBATTLEPLAYERGETRANK_RE,
	PROTOCOL_AUTOTEAMSETGOAL_RE,
	PROTOCOL_AUTOTEAMPLAYERLEAVE,
	PROTOCOL_GETCNETSERVERCONFIG_RE,
	PROTOCOL_PLAYERACCUSE_RE,
#ifdef RESOURCE_BATTLE
	PROTOCOL_FACTIONRESOURCEBATTLEPLAYERQUERYRESULT,
	PROTOCOL_FACTIONRESOURCEBATTLEPLAYERQUERYRESULT,
	PROTOCOL_FACTIONRESOURCEBATTLEGETMAP_RE,
	PROTOCOL_FACTIONRESOURCEBATTLEGETRECORD_RE,
	PROTOCOL_FACTIONRESOURCEBATTLENOTIFYPLAYEREVENT,
#endif
	PROTOCOL_ADDFRIENDREMARKS,
	PROTOCOL_ADDFRIENDREMARKS_RE,
	PROTOCOL_FACTIONRENAMEANNOUNCE,
};

GNET::Protocol::Manager::Session::State state_GDataExchgClient(_state_GDataExchgClient,
                        sizeof(_state_GDataExchgClient)/sizeof(GNET::Protocol::Type), 6000);


};
	
