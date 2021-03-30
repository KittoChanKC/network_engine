//#include "Core/Socket.h"
//bool isServer = true;
//
//void TCPServer()
//{
//    _network::Socket listenSocket;
//    listenSocket.CreateTCP();
//
//    _network::SocketAddress addr;
//    addr.SetIPv4(0, 0, 0, 0);
//    addr.SetPortNum(3000);
//
//    listenSocket.Bind(addr);
//    listenSocket.Listen();
//
//    _network::Socket client;
//    listenSocket.Accept(client);
//
//    std::vector<char> buf;
//
//    for(;;) {
//        size_t n = client.AvailableBytesToRead();
//
//        if(n == 0) {
//            Sleep(0);
//            continue;
//        }
//
//        client.Recv(buf, n);
//        buf.push_back(0);
//        printf_s("recv %d : %s \n", (int)n, buf.data());
//
//        client.Send(buf);
//    }
//}
//
//void TCPClient()
//{
//    _network::Socket socket;
//    socket.CreateTCP();
//
//    _network::SocketAddress addr;
//    addr.SetIPv4(127, 0, 0, 1);
//    addr.SetPortNum(3000);
//    socket.Connect(addr);
//
//    socket.Send("ggg");
//    
//    std::vector<char> buf;
//
//    for(;;) {
//        size_t n = socket.AvailableBytesToRead();
//        if(n == 0) {
//            Sleep(0);
//            continue;
//        }
//
//        socket.Recv(buf, n);
//        buf.push_back(0);
//        printf("recv %d: %s\n", (int)n, buf.data());
//    }
//}
//void TestTCP()
//{
//    if(isServer) {
//        TCPServer();
//    }
//    else {
//        TCPClient();
//    }
//}
//
//int main(int argv, const char* argc[])
//{
//    if(argv > 1 && 0 == strcmp(argc[1], "-client")) {
//        isServer = false;
//        printf("Client");
//    }
//
//    TestTCP();
//
//    printf("\n======= Program Ended ======\n");
//
//    return 0;
//}