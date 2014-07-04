#ifndef FILE_SERVER_H
#define FILE_SERVER_H

class FileServer{
  public:
    FileServer(unsigned int port = 2222):
      port(port) {}
    ~FileServer();

  int Start();
  private:
    unsigned int port;
};

#endif

