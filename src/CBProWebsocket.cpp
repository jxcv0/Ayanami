#include "CBProWebsocket.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

Ayanami::CBProWebsocket::CBProWebsocket() {
    baseURI = "ws://ws-feed.exchange.coinbase.com";
};

void Ayanami::CBProWebsocket::connect() {

};

std::string Ayanami::CBProWebsocket::createSubscribeMsg(const std::string& productId, const std::string& channel) {
    
};

Ayanami::LimitOrderBook Ayanami::CBProWebsocket::addLOB(const std::string& productId) {
    Ayanami::LimitOrderBook lob(productId);
    lobs.push_back(lob);
    return lob;
};

void Ayanami::CBProWebsocket::proccessSnapshotMsg(web::websockets::client::websocket_incoming_message msg) {
    
}

int Ayanami::CBProWebsocket::getLOBCount() {
    return lobs.size();
};