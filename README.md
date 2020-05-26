## cpprest based server, serving csv file
cpprest based server serving get request and returns csv file in response.
Tested on Ubuntu 20.04.


### On Ubuntu 20.04
First, install the package needed.
```
sudo apt install libssl-dev   
sudo apt-get install libcpprest-dev
```

Then,to compile and run,
```
rm CMakeCache.txt 
cmake .
make
./cpprest_GetCSVServer
```

### On Mac, 
```
brew install cpprestsdk
brew install openssl
```
Note: There might be some openssl lib issue on mac. To fix them, update the cmake accordingly. 
To run on mac, you can compile the project in CLion or usual cmake.