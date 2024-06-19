client to join dynata grpc stream and make
messages available on local socket as json.

you'd need to change src/config/config.h for sure
```c++
std::string dynataAccessKey = "";
std::string dynataSecretKey = "";
```