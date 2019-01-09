# FTP
A FTP client and server implementation

## TODO

- [ ] accept url
- [ ] send correct ip in pasv_handler
- [ ] `!<local_cmd>` in client
- [ ] log level option

## usage

### compile

```
make
```

### client

```
./client [ host=localhost [ port=2222 ]] [-l loglevel=1]
```

### server

```
./server [ port=2222 ] [-l loglevel=1]
```

## architecture

### protocol

The protocol is the set of actions recognized by the client and server.

|index|name|arguments|description|
|-|-|-|-|
|0|QUIT||close the connection and restore control of the terminal to the shell|
|1|LIST|filename?|list server's current working directory|
|2|CWD|path|change server's current working directory. Cannot move above the server's `data` directory.|
|3|PWD||print the server's current working directory|
|4|RETR|path|filename|request file from remote server, create or overrive local file|
|5|STOR|path|send file to remote server, create or override file on the server|

### client

#### commands

Commands map user input to an entry in the protocol table.

|index|names|arguments|
|-|-|-|
|0|quit, exit||
|1|ls|[ path ]|
|2|cd|[ path ]|
|3|pwd||
|4|get|remote_path [ local_path ]|
|5|put|local_path [ remote_path ]|

#### handlers

On the client, handlers are functions that take a specifc command and carry out the communication with the server.
There is one handler per protocol entry.

1. find protocol entry

2. validate arguments (verify that files exist, have permissions...)

3. send to server over the control connection

4. wait for reply

5. process data over the data connection, if applicable

6. return status

<<<<<<< HEAD
### server
=======
|value|name|decription|
|-|-|-|
|0|START|Initial state|
|1|USER|Awaiting user input|
|2|LISTEN|Awaiting connection|
|3|COMMAND|Sending or awaiting command|
|4|RESPONSE|Sending or awaiting response|
|5|DATA|Sending or awaiting data|
|6|ERROR|There was an internal or network error|
|7|FAILURE|Operation failed|
|8|SUCCESS|Operation succeded|
|9|EXIT|exit process|

### transitions

A transition coresponds to a sequence of action that takes a process from one state to another.
The appropriate action is selected according to the current state, the context (ie. the command) and the process's identy, (client, server main, server child).
Transitions return the next state depending on the result of the action.

#### client

|current state|action|next states|
|-|-|-|
|START|intialize client|SUCCESS, ERROR|
|USER|get command|COMMAND, FAILURE, ERROR|
|COMMAND|send command|RESPONSE, ERROR, EXIT|
|RESPONSE|recieve and process response|DATA, SUCCESS, FAILURE, ERROR|
|DATA|send or recieve and process data|RESPONSE, ERROR|
|ERROR|display error message|EXIT|
|FAILURE|display failure message|USER|
|SUCCESS|display success message|USER|
|EXIT|exit|N/A|

#### server lister process

|current state|action|next states|
|-|-|-|
|START|initialize server|LISTEN, ERROR|
|LISTEN|listen for connections, fork|LISTEN(parent), COMMAND(children), ERROR|
|ERROR|display error message|EXIT|
|EXIT|exit|N/A|
>>>>>>> 3737f6306911c26f351d93077127045075f09459

The server listens on the main process and forks after each client connection.
The forked process is refered to as the controller, the main process is the listener.

#### handlers

On the controller, handlers are functions that take a protocol entry and carry out the comunication with the client.
There is one handler per protocol entry.

The controller reads a request from the control connection and finds the apropriate handler, which follows these steps.

1. validate arguments

2. if applicable, open data connection, write to control connection (status 1xy)

3. if applicable, process data over the data connection

4. if applicable, write to control connection (2xy)

5. close data connection

