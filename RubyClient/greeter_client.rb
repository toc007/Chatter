#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Sample app that connects to a Greeter service.
#
# Usage: $ path/to/greeter_client.rb

this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(this_dir, 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

require 'grpc'
require 'Chatter_services_pb'

class Client
  @@numClient = 0
  def initialize(name, stub)
    name.strip
    puts "Hello #{name}"
    @name = name
    @stub = stub
    @@numClient += 1
    #exit unless pingServer
    self.runClient
  end

  def pingServer
    begin
      puts "Pinging Server"
      @stub.ping(Chatter::Empty.new())
    rescue GRPC::Unavailable
      puts "Ping Failed! Abort!"
      return false
    else
      puts "Server Pinged!"
    end
    return true 
  end

  def runClient
    loop do
      userInput = $stdin.gets.strip
      splitUserInput = userInput.split(' ', 2)
      case splitUserInput[0]
      when ":help", ":h"
        puts "Chatter Ruby Client"
        puts "\t:echo <msg>\t\tEchos <msg> back to client"
        puts "\t:necho <n> <msg>\tEchos <msg> back to client n times"
      when ":q"
        puts "Exiting chat"
        break
      when ":echo"
        msg = Chatter::ChatMessage.new(sender: @user.to_s, reciever: "Server", payload: splitUserInput[1])
        serverResponse = @stub.echo(msg).payload
        puts "[Server]: #{serverResponse}"
      when ":necho"
        n, msg = splitUserInput[1].split(" ", 2)
        n = n.to_i
        puts n
        puts msg
        if n==0 or msg == nil then
          puts "ur a dumbass"
        end
        chatMsg = Chatter::ChatMessage.new(
          sender: @user.to_s, 
          reciever: "Server", 
          payload: msg, 
          timesRepeated: n)
          serverResponse = @stub.n_echo(chatMsg)
          serverResponse.each {
            |resp|
            puts "[Server]: #{resp.payload}"
          }
      # when ":w" // write chat history to a file
      # when ":wq" // write chat history to file and quit
      else
        self.sendMsg(userInput)
      end
    end
  end


  def sendMsg(msgToSend)
    puts "[#{@name}]: #{msgToSend}"
  end
end

def main
  puts "Starting Client"
	stub = Chatter::ServerServices::Stub.new('0.0.0.0:50051', :this_channel_is_insecure)
  user = ARGV.size > 0 ?  ARGV[0] : 'world'
  client = Client.new("Ash Hole", stub)
  # message = stub.ping(Chatter::PingRequest.new(from: user)).from
  # p "Greeting: #{message}"
end

main