# Chatter  

One to one (many may come soon) chat application using GRPC that uses a C++ server and a ruby client.

## Proto

- Defined messages
  - Empty (used for ping)
  - ChatMessage
    - To/From
      - store hash or user name?
      - prevent man in middle attack
    - MessageType
      - chat request
      - message
    - Payload
- Defined methods
  - Ping
  - SendMessage

## C++ Server

- ping client
- forward message
- send chat request

## Ruby Client

- encode/decode message (local function)
  - use xor encode/decode with user's hash
- online (server stream)
  - called when client comes online
  - sends server Empty message, server replies with stream of ChatMessages
- send/recieve message (bi-directional?)
- sendOffline (simple request)
  - end client not online
