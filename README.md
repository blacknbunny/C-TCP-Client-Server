# C-TCP-Client-Server



## Compiling TCP Server

``` gcc tcpserver.c -o tcpserver ```


## Compiling TCP Client

``` gcc tcpclient.c -o tcpclient ```

------

## Usage :

Type | Usage
------------ | -------------
TCP Server | ./tcpserver [port]
TCP Client | ./tcpclient [local_ip] [local_or_remote_port]

------

## This If Structure Used for 'Bind: Address already in use' Error.

```c
if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
   perror("Setsockopt ");
   exit(1);
}
```
