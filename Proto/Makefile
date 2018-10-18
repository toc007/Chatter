PROTOC=protoc
CPPDIR=CppGenerated
RUBYDIR=RubyGenerated
CPPFLAGS=-I=./ --cpp_out=${CPPDIR}/ --grpc_out=${CPPDIR} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin`

RUBYFLAGS=--ruby_out=${RUBYDIR}/

HASCPPDIR=ls|grep ${CPPDIR} -q
HASRUBYDIR=ls|grep ${RUBYDIR} -q

all: ruby cpp
ruby: Chatter.proto
	rm -rf ${RUBYDIR}
	mkdir ${RUBYDIR}
	${PROTOC} ${RUBYFLAGS} Chatter.proto
cpp: Chatter.proto
	rm -rf ${CPPDIR}
	mkdir ${CPPDIR}
	${PROTOC} ${CPPFLAGS} Chatter.proto
clean: 
	rm -rf *Generated