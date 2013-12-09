#include <iostream>
#include <string>

using namespace std;


class IServer {
protected:
    string protocol;
public:
    virtual void reponse() = 0;
    virtual void acceptRequest(string message) = 0;
};

class Server1 : public IServer {
public:
    Server1(string protocol_) {
        // does not work as normal constructor variable
        protocol = protocol_; 
        cout << "Server constructor with protocol: " << protocol << endl;
        
    }
    void reponse(){
        cout << "Server Responding with protocol: " << protocol << endl;
    }
    void acceptRequest(string message){
        cout << "Server accepted message with protocol: " << protocol << endl;
        cout << "Message: " << message << endl;
    }
};


class Client {
private:
    string id;
    IServer *server;
public:
    Client(string clientId) : id(clientId){
       cout << "Client constructor with id: " << clientId << endl;
    }
    void setServer(IServer *server_){
        server = server_;
    }
    void request(string message) {
        server->acceptRequest(message);
        server->reponse();
    }
};

int main_cc2 (void)  {
    Server1 s("DummyProtocol");

    Client c("Dummy Client");
    c.setServer(&s);
    c.request("Dummy Message!");

    return 0;
}
