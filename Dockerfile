FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y socat

ADD . .
RUN chmod 777 ./main

CMD ["socat -v tcp-l:7777,fork system:./main"]