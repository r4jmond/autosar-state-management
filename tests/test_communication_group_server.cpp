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


/** @test Adding clients to server */
/** Add unique client to client lists */
errorStatus = mySM.communicationGroupServer.AddClientToGroup("client0", &powerMode1);
EXPECT_EQ(errorStatus, true);
/** Add another unique client to client lists */
errorStatus = mySM.communicationGroupServer.AddClientToGroup("client0", &powerMode1);
EXPECT_EQ(errorStatus, false);
/** Try to add client with duplicated ID to client lists */
errorStatus = mySM.communicationGroupServer.AddClientToGroup("client1", &powerMode2);
EXPECT_EQ(errorStatus, true);


/** @test Broadcast message and clients messages readout and response */
/** Broadcast power state message */
mySM.communicationGroupServer.Broadcast("On");
/** Read message from first client */
powerMode1.TryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "On");
/** Respond to message from first client */
powerMode1.Event(ara::sm::PowerModeRespMsg::kDone);

/** Read message from second client */
powerMode2.TryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "On");
/** Respond to message from first client */
powerMode2.Event(ara::sm::PowerModeRespMsg::kDone);

/** Get responses from clients and check if they are correct*/
map = mySM.communicationGroupServer.Response();
for(auto k : map){
    k.second->TryGetPowerMsgResponse(&respondMsg);
    EXPECT_EQ(respondMsg, ara::sm::PowerModeRespMsg::kDone);
}


/** @test Get list of all clients and check if its correct */
listOfClients = mySM.communicationGroupServer.ListClients();

EXPECT_EQ(listOfClients[0], "client0");
EXPECT_EQ(listOfClients[1], "client1");

/** @test Send message to one client and check response */
/** Send message to client */
errorStatus = mySM.communicationGroupServer.Message("client0", "Off");
EXPECT_EQ(errorStatus, true);

/** Read message in client */
powerMode1.TryGetPowerMsg(&retVal);
EXPECT_EQ(retVal, "Off");

/** Send response from client */
powerMode1.Event(ara::sm::PowerModeRespMsg::kBusy);

/** Get responses from clients and check if they are correct */
map = mySM.communicationGroupServer.Response();
/** Check response from specified client */
map["client0"]->TryGetPowerMsgResponse(&respondMsg);
EXPECT_EQ(respondMsg, ara::sm::PowerModeRespMsg::kBusy);


/** @test Try to send message to non-existing client */
errorStatus = mySM.communicationGroupServer.Message("client2", "Off");
EXPECT_EQ(errorStatus, false);


/** @test Try to read message when none is available */
errorStatus = powerMode1.TryGetPowerMsg(&retVal);
EXPECT_EQ(errorStatus, false);


/** @test Try to read response when none is available */
errorStatus = map["client0"]->TryGetPowerMsgResponse(&respondMsg);
EXPECT_EQ(errorStatus, false);


/** @test Try to send Invalid message*/
errorStatus = mySM.communicationGroupServer.Message("client0", "abcd");
EXPECT_EQ(errorStatus, false);

/** @test Try to broadcast invalid message and clients messages readout and response */
/** Broadcast power state message */
mySM.communicationGroupServer.Broadcast("abcd");
/** Read message from first client */
errorStatus = powerMode1.TryGetPowerMsg(&retVal);
EXPECT_EQ(errorStatus, false);


/** Read message from second client */
errorStatus = powerMode2.TryGetPowerMsg(&retVal);
EXPECT_EQ(errorStatus, false);

/** Get responses from clients and check if they are correct*/
map = mySM.communicationGroupServer.Response();
for(auto k : map){
    errorStatus = k.second->TryGetPowerMsgResponse(&respondMsg);
    EXPECT_EQ(errorStatus, false);
}
}
