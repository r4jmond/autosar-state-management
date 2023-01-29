/** @file tests_communication_group_server.cpp
 * @brief Tests of the Communication Group Server interface. */

#include "sm_tests.h"

/** @brief Fills SWS_Platform_Health_Management] */
TEST_F(smTests, testCommunicationGroupServer){
std::string retVal;
ara::com::PowerMode powerMode1;
ara::com::PowerMode powerMode2;
ara::com::TriggerIn triggerIn;
ara::sm::PowerModeRespMsg respondMsg;

std::map<std::string, ara::com::PowerMode*> map;
std::vector<std::string> listOfClients;
bool errorStatus;

errorStatus = mySM.communicationGroupServer.AddClientToGroup("client0", &powerMode1);
EXPECT_EQ(errorStatus, true);
errorStatus = mySM.communicationGroupServer.AddClientToGroup("client0", &powerMode1);
EXPECT_EQ(errorStatus, false);
errorStatus = mySM.communicationGroupServer.AddClientToGroup("client1", &powerMode2);
EXPECT_EQ(errorStatus, true);

mySM.communicationGroupServer.Broadcast("On");
powerMode1.TryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "On");
powerMode1.Event(ara::sm::PowerModeRespMsg::kDone);
powerMode2.TryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "On");
powerMode2.Event(ara::sm::PowerModeRespMsg::kDone);
map = mySM.communicationGroupServer.Response();

for(auto k : map){
    k.second->TryGetPowerMsgResponse(&respondMsg);
    EXPECT_EQ(respondMsg, ara::sm::PowerModeRespMsg::kDone);
}

listOfClients = mySM.communicationGroupServer.ListClients();

EXPECT_EQ(listOfClients[0], "client0");
EXPECT_EQ(listOfClients[1], "client1");

errorStatus = mySM.communicationGroupServer.Message("client0", "Off");
EXPECT_EQ(errorStatus, true);
powerMode1.TryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "Off");
powerMode1.Event(ara::sm::PowerModeRespMsg::kBusy);
map = mySM.communicationGroupServer.Response();
map["client0"]->TryGetPowerMsgResponse(&respondMsg);
EXPECT_EQ(respondMsg, ara::sm::PowerModeRespMsg::kBusy);

errorStatus = mySM.communicationGroupServer.Message("client2", "Off");
EXPECT_EQ(errorStatus, false);

errorStatus = powerMode1.TryGetPowerMsg(&retVal);
EXPECT_EQ(errorStatus, false);

errorStatus = map["client0"]->TryGetPowerMsgResponse(&respondMsg);
EXPECT_EQ(errorStatus, false);

errorStatus = mySM.communicationGroupServer.Message("client0", "abcd");
EXPECT_EQ(errorStatus, false);
}
