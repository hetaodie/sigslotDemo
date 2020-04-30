#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "sigslot.h"
using namespace std;

class CSender {
public:
    sigslot::signal2<string, int> m_pfnsigDanger;

    void Panic() {
        static int nVal = 0;
        char szVal[20] = {0};

        sprintf(szVal, "help--%d", nVal);

        m_pfnsigDanger(szVal, nVal++);
    }
};

class CReceiver: public sigslot::has_slots<> {
public:
    void OnDanger(string strMsg, int nVal) {
        cout << strMsg.c_str() << " ==> " << nVal << endl;
    }
};

class Recerver: public sigslot::has_slots<> {
public:
    void testRecerver(string strMsg, int nVal) {
        cout << "testRecerver :" << strMsg.c_str() << "------->" << nVal << endl;
    }
};

int main(int argc , char ** argv) {
    int count = 5;
    CSender sender;
    CReceiver recerver;
    Recerver *recerver1 = new Recerver();

    sender.m_pfnsigDanger.connect(&recerver, &CReceiver::OnDanger);
    sender. m_pfnsigDanger.connect(recerver1,&Recerver::testRecerver);
    cout << "connect success !" << std::endl;

    while (count-- > 0) {
        cout << "in while..." <<endl;
        sender.Panic();
        sleep(2);
        cout << "end of sleep" << endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
