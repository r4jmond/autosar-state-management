#include "sm_tests.h"

/** @brief Fills SWS_Platform_Health_Management] */
TEST_F(smTests, testCommunicationGroupServer)
{
std::string retVal;
ara::com::PowerMode powerMode1;
ara::com::PowerMode powerMode2;
ara::com::TriggerIn triggerIn;
ara::sm::PowerModeRespMsg respondMsg;

std::map<std::string, ara::com::PowerMode*> map;
std::vector<std::string> listOfClients;
bool errorStatus;

errorStatus = mySM.communicationGroupServer.addClientToGroup("client0", &powerMode1);
EXPECT_EQ(errorStatus, true);
errorStatus = mySM.communicationGroupServer.addClientToGroup("client0", &powerMode1);
EXPECT_EQ(errorStatus, false);
errorStatus = mySM.communicationGroupServer.addClientToGroup("client1", &powerMode2);
EXPECT_EQ(errorStatus, true);

mySM.communicationGroupServer.broadcast("On");
powerMode1.tryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "On");
powerMode1.event(ara::sm::PowerModeRespMsg::kDone);
powerMode2.tryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "On");
powerMode2.event(ara::sm::PowerModeRespMsg::kDone);
map = mySM.communicationGroupServer.response();

for(auto k : map){
    k.second->tryGetPowerMsgResponse(&respondMsg);
    EXPECT_EQ(respondMsg, ara::sm::PowerModeRespMsg::kDone);
}

listOfClients = mySM.communicationGroupServer.listClients();

EXPECT_EQ(listOfClients[0], "client0");
EXPECT_EQ(listOfClients[1], "client1");

errorStatus = mySM.communicationGroupServer.message("client0", "Off");
EXPECT_EQ(errorStatus, true);
powerMode1.tryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "Off");
powerMode1.event(ara::sm::PowerModeRespMsg::kBusy);
map = mySM.communicationGroupServer.response();
map["client0"]->tryGetPowerMsgResponse(&respondMsg);
EXPECT_EQ(respondMsg, ara::sm::PowerModeRespMsg::kBusy);

errorStatus = mySM.communicationGroupServer.message("client2", "Off");
EXPECT_EQ(errorStatus, false);

errorStatus = powerMode1.tryGetPowerMsg(&retVal);
EXPECT_EQ(errorStatus, false);

errorStatus = map["client0"]->tryGetPowerMsgResponse(&respondMsg);
EXPECT_EQ(errorStatus, false);

errorStatus = mySM.communicationGroupServer.message("client0", "abcd");
EXPECT_EQ(errorStatus, false);
}
