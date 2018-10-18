PROTOC=grpc_tools_ruby_protoc 
PROTOS_PATH = ../Proto
RUBY_OUT=./lib
GRPC_OUT=./lib
ruby:
	${PROTOC} -I ${PROTOS_PATH} --ruby_out=${RUBY_OUT} --grpc_out=${GRPC_OUT} ${PROTOS_PATH}/Chatter.proto
clean:
	rm ${RUBY_OUT}/*