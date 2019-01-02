# ftp
A FTP client and server implementation

# state machines

## states

Clients and servers can be in some of the following states.

|value|name|decription|
|-|-|-|
|0|START|Initial state|
|1|USER|Awaiting user input|
|2|COMMAND|Sending or awaiting command|
|3|RESPONSE|Sending or awaiting response|
|4|DATA|Sending or awaiting data|
|5|ERROR|There was an internal or network error|
|6|FAILURE|Operation failed|
|7|SUCCESS|Operation succeded|
|8|EXIT|exit process|

## transitions

A transition coresponds to an action that takes a client or server from one state to another.
The appropriate action is selected according to the current state and the process's identy, (client, server main, server child).
The next state is determined by the selected action.

For the client:

|current state|action|next states|
|-|-|-|
|START|intialize client|SUCCESS, ERROR|
|USER|get command|COMMAND, FAILURE, ERROR|
|COMMAND|send command|RESPONSE, ERROR, EXIT|
|RESPONSE|recieve and process response|DATA, SUCCESS, FAILURE, ERROR|
|DATA|send or recieve and process data|SUCCESS, ERROR|
|ERROR|display error message|USER, EXIT|
|FAILURE|display failure message|USER|
|SUCCESS|display success message|USER|
|EXIT|exit|N/A|

For the server main process:

|current state|action|next states|
|-|-|-|
|START|initialize server|LISTEN, ERROR|
|LISTEN|listen for connections, fork|LISTEN(parent), COMMAND(children), ERROR|
|ERROR|display error message|LISTEN, EXIT|
|EXIT|exit|N/A|

For the server child processes:

|current state|action|next states|
|-|-|-|
|START|initialize connection|COMMAND, ERROR|
|COMMAND|recieve and process command|RESPONSE, EXIT, FAILURE, ERROR|
|RESPONSE|send response|DATA, COMMAND, ERROR|
|DATA|send or recieve data|SUCCESS, ERROR|
|ERROR|display error message|EXIT, COMMAND|
|FAILURE|display failure message|COMMAND|
|SUCCESS|display success message|COMMAND|
|EXIT|exit|N/A|

## actions

Actions are function of the curent state, the process's identity, and the current context (command, ...).
They return the next state.

## commands

The same process takes different paths through the state graph depending on the specificities of the command.

