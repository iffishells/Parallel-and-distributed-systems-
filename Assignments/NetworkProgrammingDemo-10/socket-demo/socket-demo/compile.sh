#!/bin/bash

echo cc -w -o dns_server src/dns_server.c
cc -w -o dns_server src/dns_server.c
echo cc -w -o dns_client src/dns_client.c
cc -w -o dns_client src/dns_client.c
echo cc -w -o file_transfer_server src/file_transfer_server.c
cc -w -o file_transfer_server src/file_transfer_server.c
echo cc -w -o file_transfer_client src/file_transfer_client.c
cc -w -o file_transfer_client src/file_transfer_client.c
