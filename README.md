# Chatter  

One to one (many may come soon) chat application using GRPC that uses a C++ server and a ruby client.

## Proto

- Defined messages
  - Empty (used for ping)
  - ChatMessage
    - sender
    - reciever
    - payload
- Defined methods
  - Ping
  - Echo
  - nEcho

## C++ Server

- Ping: replies to the client an empty message (simple request)
- Echo: replies the same message back to the client (simple request)
- nEcho: replies the same message n times back to the client (server streaming)

## Ruby Client

- encode/decode message (local function)
  - use xor encode/decode with user's hash
- online (server stream)
  - called when client comes online
  - sends server Empty message, server replies with stream of ChatMessages
- send/recieve message (bi-directional?)
- sendOffline (simple request)
  - end client not online
