/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2006, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
*/
#ifndef	SOCKET_H
#define SOCKET_H

#include <winsock.h>

void initSocket(void);
void closeSocket(void);
int GetHName(char *name);

int socklisten(int port);

int sockconect(char* hostname, int port);

int recv(SOCKET s, char *buf, int len);
int setnonblocking (SOCKET s, int on_off);
int send(SOCKET s, char *buf, int len);
int closesocket(SOCKET s);
int listen(int socket, int backlog);
int accept(int listening);

#endif
