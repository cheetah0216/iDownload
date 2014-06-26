#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <boost/shared_ptr.hpp>

using namespace muduo;
using namespace muduo::net;

const int buffSize = 64*1024; //64kb
const char* g_file = NULL;
typedef boost::shared_ptr<FILE> FilePtr;

class FileServer {
  public:
    FileServer(EventLoop* loop,
        const InetAddress& listenAddr)
      :loop_(loop),
      server_(loop, listenAddr, "FileServer")
    {
      server_.setConnectionCallback(onConnection);
      server_.setWriteCompleteCallback(onWriteComplete);
    }

    void Start() { server_.start(); } 

  private:
    void onConnection(const TcpConnectionPtr& conn);
    void onWriteComplete(const TcpConnectionPtr& conn);

  private:
    EventLoop* loop_;
    TcpServer server_;
};

void FileServer::onConnection(const TcpConnectionPtr& conn)
{
  LOG_INFO << "FileServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
  if (conn->connected())
  {
    LOG_INFO << "FileServer - Sending file " << g_file
             << " to " << conn->peerAddress().toIpPort();
    FILE* fp = ::fopen(g_file, "rb");
    if (fp)
    {
      FilePtr ctx(fp, ::fclose);
      conn->setContext(ctx);
      char buf[kBufSize];
      size_t nread = ::fread(buf, 1, sizeof buf, fp);
      conn->send(buf, static_cast<int>(nread));
    }
    else
    {
      conn->shutdown();
      LOG_INFO << "FileServer - no such file";
    }
  }
}

void FileServer::onWriteComplete(const TcpConnectionPtr& conn)
{
  const FilePtr& fp = boost::any_cast<const FilePtr&>(conn->getContext());
  char buf[kBufSize];
  size_t nread = ::fread(buf, 1, sizeof buf, get_pointer(fp));
  if (nread > 0)
  {
    conn->send(buf, static_cast<int>(nread));
  }
  else
  {
    conn->shutdown();
    LOG_INFO << "FileServer - done";
  }
}

int main(int argc, char* argv[])
{
  LOG_INFO << "pid = " << getpid();
  if (argc > 1)
  {
    g_file = argv[1];

    EventLoop loop;
    InetAddress listenAddr(2021);
    FileServer server(&loop, listenAddr);
    server.Start();
    loop.loop();
  }
  else
  {
    fprintf(stderr, "Usage: %s file_for_downloading\n", argv[0]);
  }
}
