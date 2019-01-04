# FTP
A FTP client and server implementation

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

## commands

|code|names|arguments|description|
|-|-|-|-|
||QUIT, EXIT||close the connection and restore control of the terminal to the shell|
||LIST, LS|filename?|list server's current working directory|
||CWD, CD|path|change server's current working directory. Cannot move above the server's `data` directory.|
||PWD||print the server's current working directory|
||RETRIEVE, GET|filename|request file from remote server, create or overrive local file|
||STORE, PUT|filename|send file to remote server, create or override file on the server|

## architecture

This implementation of FTP is divided into 3 parts, each corresponding to a process on a host.

1) the client

Connects to a server and issues commands.

2) the server listener

Binds to a socket and accepts connections from clients. For each connection, a controller process is created.

3) the server controller

Controls the connection with one specific client.

## state machines

Each of the above parts is represented as a finite state machine.
All 3 share the same set of states, but the transitions differ.
The state of each part determines the action to be called.
But some data, such as connections, commands, etc... persist through state transitions.
Therefore, the concept of a context is introduced.
Each part has its own context, which contains all the data required at runtime.
Eahc process has a context instance.
Context instances can be modified by any action.
Actions may assume some previous modification to have previousky taken place. Ie., the LISTEN state can assume that a listening socket has been created.

### states

Each of the lient, server listener and server controller processes can be in some of the following states.

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

#### server controller process

|current state|action|next states|
|-|-|-|
|COMMAND|recieve and process command|RESPONSE, EXIT, FAILURE, ERROR|
|RESPONSE|send response|DATA, COMMAND, ERROR|
|DATA|send or recieve data|SUCCESS, ERROR|
|ERROR|display error message|EXIT|
|FAILURE|display failure message, send 4xy, 5xy|COMMAND|
|SUCCESS|display success message, send 2xy|COMMAND|
|EXIT|exit|N/A|

### actions

The following is a more detailed description of the state transitons, emphasizing the specific system calls invoked and context updates.
The `->` symbol represents an immediate transition to the specified state.
The `?` symbol represents a conditional branch, ie. matching a specific condition in the current context.

#### client

- COMMAND
	- get command from stdin			-> ERROR
	- process command (if applicable)
		- STOR? open file, command.fd	-> ERROR, FAILURE
	- -> RESPONSE

- RESPONSE
	- get response from conn			-> ERROR
	- process response
		- 1xy							-> DATA
		- 2xy							-> SUCCESS
		- 3xy, 4xy, 5xy					-> ERROR, FAILURE

- DATA
	- STOR?
		- mmap command.fd				-> ERROR
		- write file to connection		-> ERROR, RESPONSE
	- RETR?
		- open(creat/trunc) command.filename	-> ERROR
		- pipe(conn, file)				-> ERROR, RESPONSE
	- ?									-> ?

#### server listener process

- LISTEN
	- accept connection	-> ERROR
	- fork				-> ERROR, COMMAND(child), LISTEN(main)

#### server controller process

- COMMAND
	- get command from conn	-> ERROR
	- process command		-> ERROR, FAILURE
		- STOR?
			- send 1xy		-> ERROR, DATA
		- RETR?
			- validate file	-> ERROR, FAILURE, DATA
		- LIST?
			- validate file	-> ERROR, FAILURE, DATA
		- ?					-> ?

- DATA
	- STOR?
		- open(creat/trunc) command.filename	-> ERROR
		- pipe(conn, file)						-> ERROR, SUCCESS
	- RETR?
		- mmap command.fd						-> ERROR
		- write file to connection				-> ERROR, SUCCESS
	- LIST?
		- readdir to buffer						-> ERROR
		- write buffer to socket				-> ERROR, SUCCESS
	- ?					-> ?

### project structure

```
src
	client
		transitions
			...
		c_main.c
	server
		listener
			transitions
				...
		controller
			transitions
				...
		s_main.c
	shared
		run_state_machine.c
		
inc
	client
		client.h
	server
		server.h
	shared
		shared.h
		states.h
```
