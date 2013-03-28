/*
 * Copyright (C) 2013 r4 for Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2013, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
 */

#ifndef SOUND_H
#define SOUND_H

void SOUNDinit(void);
void SOUNDend(void);

int createAudioPlayer(char *utf8);
void releaseAudioPlayer(int nro);

void setPlayState(int nro,int state);
int getPlayState(int nro);
void SNDplay(int nro);
void SNDstop(int nro);
void SNDpause(int nro);
int isPlaying(int nro);
void seekTo(int nro,int position);
int getDuration(int nro);
int getPosition(int nro);
void setPitch(int nro,int rate);
void setRate(int nro,int rate);
int getRate(int nro);
int setLoop(int nro,int startPos, int endPos);
int setNoLoop(int nro);

#endif
