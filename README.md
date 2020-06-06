## Simple cpprestsdk based server, serving csv file

cpprest based server serving get request and returns csv file in response.
Place the csv files in spectrum folder. Tested on Ubuntu 20.04.

It only supports a get api at the moment.

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
