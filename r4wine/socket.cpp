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
#include "socket.h"


void initSocket(void)
{
unsigned short wVersionRequested = MAKEWORD(2,0);
WSADATA wsaData;
WSAStartup(wVersionRequested, &wsaData);
}

void closeSocket(void)
{
WSACleanup();
}

int iserror;

int GetHName(char *name)
{
int size=64;
iserror = gethostname(name,size) ? WSAGetLastError() : 0;
if (iserror==0) return strlen(name);
return 0;
}

struct sockaddr_in sinhim; // = { AF_INET };

int open_service(int port)
{
int fd;
memset((char *)&sinhim,0,sizeof(sinhim));
sinhim.sin_family = AF_INET;
sinhim.sin_addr.s_addr = INADDR_ANY;
sinhim.sin_port = htons(port);
if ((fd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
   {iserror=WSAGetLastError(); return (int)-1;}
if (bind(fd,(struct sockaddr *)&sinhim,sizeof(sinhim)) == SOCKET_ERROR)
   {iserror=WSAGetLastError(); return (int)-1;}
iserror=0; return fd;
}

int open_server(char* hostname, int port)
{
int fd; struct hostent *hp;
if ((fd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
   {iserror=WSAGetLastError(); return (int)-1;}
sinhim.sin_family = AF_INET;
sinhim.sin_port = htons(port);
hp = gethostbyname (hostname);
if (hp == NULL) {iserror=WSAGetLastError(); return (int)-1;}
memcpy(&sinhim.sin_addr,hp->h_addr,hp->h_length);
if (connect(fd,(struct sockaddr *)&sinhim,sizeof(sinhim))==SOCKET_ERROR)
   {iserror=WSAGetLastError(); return (int)-1;}
iserror=0; return fd;
}

int recv(SOCKET s, char *buf, int len)
{
int numbytes=recv(s,buf,len,0);
if (numbytes==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
iserror=0; return numbytes;
}

int setnonblocking(SOCKET s, int on_off)
{
iserror = ioctlsocket (s,FIONBIO,(u_long *)&on_off);
if (iserror==SOCKET_ERROR) iserror=WSAGetLastError();
return iserror;
}

int send(SOCKET s, char *buf, int len)
{
iserror=send (s,buf,len,0);
if (iserror==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
return iserror=0;
}

int closesocket(SOCKET s)
{
if (closesocket(s)==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
return iserror=0;
}

int listen(int socket, int backlog)
{
if (listen(socket,backlog) < 0) return errno;
return 0;
}

int accept(int listening)
{
int socket,alen=sizeof(sinhim);
if ((socket=accept(listening,(struct sockaddr *)&sinhim,&alen)) < 0)
   {iserror=errno; return (int)-1;}
iserror=0; return socket;
}

