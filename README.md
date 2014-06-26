Only support Linux Server.  

**How to Build?**  
**dependent:**  
0.cmake  
sudo apt-get install cmake  
1.Boost  
sudo apt-get install libboost-dev libbost-test-dev    
2.muduo  
downlode muduo source code  
./build.sh -j2  
./build.sh install  

**Set env:**  
export LD_LIBRARY_PATH=".:/home/fliu/build/release-install/lib"  
export CPLUS_INCLUDE_PATH=".:/home/fliu/build/release-install/include"  

**Build:**    
server:  cd server & g++ FileServer.cpp  
client:  python client.py output  
