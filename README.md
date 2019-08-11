# FTP
A FTP client and server implementation

## Usage

### Compile

```
make
```

### Client

```
./client host [[ port=8080 ] -v | --help]
```

Once connected, the client can retrive local files and send them over TCP to the server, or request remote files from the server and save them locally.

The following commands are supported

|index|names|arguments|descriptions|
|-|-|-|-|
|n/a|help||print a help message|
|0|quit, exit||exit the program|
|1|ls|[ path ]|list files|
|2|cd|[ path ]|change directory|
|3|pwd||print present working directory
|4|get|remote_path [ local_path ]|download a file from the server|
|5|put|local_path [ remote_path ]|upload a file to the server|
|6|pasv||manually create a data transfer connection with the server|
|7|mkdir|path|create a directory on the server|

### Server

```
./server [[[ host=0.0.0.0 ] port=8080 ] -v | --help]
```

The server listens for TCP connections and handles clients concurently in separate processes. Each of these processes listens and executes commands sent by the client over TCP.

Uploaded files are put in a `./.ftp_data` directory.

## Protocol

The protocol is the set of actions recognized by the client and server.

|index|name|arguments|description|
|-|-|-|-|
|0|QUIT||close the connection and restore control of the terminal to the shell|
|1|LIST|filename?|list server's current working directory|
|2|CWD|path|change server's current working directory. Cannot move above the server's `data` directory.|
|3|PWD||print the server's current working directory|
|4|RETR|path|filename|request file from remote server, create or overrive local file|
|5|STOR|path|send file to remote server, create or override file on the server|
|6|PASV||enable passive mode|
|7|MKD||create directory|
