#include "qtemulatorclient.h"

int main(int argc, char *argv[])
{    
    QTEmulatorClient client(argc, argv);
    return client.Start();
}
