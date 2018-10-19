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
- pingPong: for each input the user sends, server will respond with either "ping" or "pong" depending on internal state

## Ruby Client

- simple user interface
- type :echo to call Echo on server
- type :necho to call nEcho on server
- type :pingPong to call pingPong on server