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
// Interface de sonido para ANDROID OpenSL

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>

#include "sound.h"

// engine interfaces
static SLObjectItf engineObject = 0;
static SLEngineItf engineEngine;

static int cntSOUND=0;
#define MAXSOUND 256
// URI player interfaces
static SLObjectItf uriPlayerObject[MAXSOUND];
static SLPlayItf uriPlayerPlay[MAXSOUND];
static SLSeekItf uriPlayerSeek[MAXSOUND];
static SLPlaybackRateItf uriPlaybackRate[MAXSOUND];

// output mix interfaces
static SLObjectItf outputMixObject = 0;

// playback rate (default 1x:1000)
static SLpermille playbackMinRate = 500;
static SLpermille playbackMaxRate = 2000;
static SLpermille playbackRateStepSize;

//Pitch
static SLPitchItf uriPlaybackPitch[MAXSOUND];
static SLpermille playbackMinPitch = 500;
static SLpermille playbackMaxPitch = 2000;

// create the engine and output mix objects
void SOUNDinit(void)
{
SLresult result;
result = slCreateEngine(&engineObject, 0, 0, 0, 0, 0);
result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE,&engineEngine);
const SLInterfaceID ids[1] = {SL_IID_PLAYBACKRATE};
const SLboolean req[1] = {SL_BOOLEAN_FALSE};
result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1,ids, req);
result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
cntSOUND=0;
}


void SOUNDend(void)
{
    // destroy URI audio player object, and invalidate all associated interfaces
int i;
for (i=0;i<cntSOUND;i++)
    if (uriPlayerObject[i] != 0) {
        (*uriPlayerObject[i])->Destroy(uriPlayerObject[i]);
        uriPlayerObject[i] = 0;
        uriPlayerPlay[i] = 0;
        uriPlayerSeek[i] = 0;
    }
    // destroy output mix object, and invalidate all associated interfaces
if (outputMixObject != 0) {
    (*outputMixObject)->Destroy(outputMixObject);
    outputMixObject = 0;
    }
    // destroy engine object, and invalidate all associated interfaces
if (engineObject != 0) {
    (*engineObject)->Destroy(engineObject);
    engineObject = 0;
    engineEngine = 0;
    }
}


void playStatusCallback(SLPlayItf play, void* context, SLuint32 event) {}

// create URI audio player
int createAudioPlayer(char *utf8)
{
SLresult result;
    // configure audio source
    // (requires the INTERNET permission depending on the uri parameter)
SLDataLocator_URI loc_uri = { SL_DATALOCATOR_URI, (SLchar *) utf8 };
SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, 0,SL_CONTAINERTYPE_UNSPECIFIED };
SLDataSource audioSrc = { &loc_uri, &format_mime };
    // configure audio sink
SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX,outputMixObject };
SLDataSink audioSnk = { &loc_outmix, 0 };
    // create audio player
const SLInterfaceID ids[2] = { SL_IID_SEEK, SL_IID_PLAYBACKRATE };
const SLboolean req[2] = { SL_BOOLEAN_FALSE, SL_BOOLEAN_TRUE };
result = (*engineEngine)->CreateAudioPlayer(engineEngine, &uriPlayerObject[cntSOUND],&audioSrc, &audioSnk, 2, ids, req);
    // note that an invalid URI is not detected here, but during prepare/prefetch on Android,
    // or possibly during Realize on other platforms
    // realize the player
result = (*uriPlayerObject[cntSOUND])->Realize(uriPlayerObject[cntSOUND], SL_BOOLEAN_FALSE);
    // this will always succeed on Android, but we check result for portability to other platforms
if (SL_RESULT_SUCCESS != result) {
    (*uriPlayerObject[cntSOUND])->Destroy(uriPlayerObject[cntSOUND]);
    uriPlayerObject[cntSOUND] = 0;
    return -1;
    }
    // get the play interface
result = (*uriPlayerObject[cntSOUND])->GetInterface(uriPlayerObject[cntSOUND], SL_IID_PLAY,&uriPlayerPlay[cntSOUND]);
    // get the seek interface
result = (*uriPlayerObject[cntSOUND])->GetInterface(uriPlayerObject[cntSOUND], SL_IID_SEEK,&uriPlayerSeek[cntSOUND]);
    // get playback rate interface
result = (*uriPlayerObject[cntSOUND])->GetInterface(uriPlayerObject[cntSOUND],SL_IID_PLAYBACKRATE, &uriPlaybackRate[cntSOUND]);
    // register callback function
result = (*uriPlayerPlay[cntSOUND])->RegisterCallback(uriPlayerPlay[cntSOUND],playStatusCallback, 0);
result = (*uriPlayerPlay[cntSOUND])->SetCallbackEventsMask(uriPlayerPlay[cntSOUND],SL_PLAYEVENT_HEADATEND); // head at end
SLmillisecond msec;
result = (*uriPlayerPlay[cntSOUND])->GetDuration(uriPlayerPlay[cntSOUND], &msec);
    // no loop
result = (*uriPlayerSeek[cntSOUND])->SetLoop(uriPlayerSeek[cntSOUND], SL_BOOLEAN_TRUE, 0, msec);
SLuint32 capa;
result = (*uriPlaybackRate[cntSOUND])->GetRateRange(uriPlaybackRate[cntSOUND], 0,&playbackMinRate, &playbackMaxRate, &playbackRateStepSize, &capa);
result = (*uriPlaybackRate[cntSOUND])->SetPropertyConstraints(uriPlaybackRate[cntSOUND],SL_RATEPROP_PITCHCORAUDIO);

SNDstop(cntSOUND);
setNoLoop(cntSOUND);

cntSOUND++;
return (cntSOUND-1);
}

void releaseAudioPlayer(int nro)    // destroy URI audio player object, and invalidate all associated interfaces
{
if (nro==-1) return;
if (uriPlayerObject[nro] != 0) {
    (*uriPlayerObject[nro])->Destroy(uriPlayerObject[nro]);
    uriPlayerObject[nro]= 0;
    uriPlayerPlay[nro]= 0;
    uriPlayerSeek[nro]= 0;
    uriPlaybackRate[nro]= 0;
    }
}

void setPlayState(int nro, int state)
{
SLresult result;
    // make sure the URI audio player was created
if (uriPlayerPlay[nro]!=0) {
        // set the player's state
    result = (*uriPlayerPlay[nro])->SetPlayState(uriPlayerPlay[nro], (SLuint32)state);
    }
}

int getPlayState(int nro)
{
SLresult result;
    // make sure the URI audio player was created
if (0 != uriPlayerPlay[nro]) {
    SLuint32 state;
    result = (*uriPlayerPlay[nro])->GetPlayState(uriPlayerPlay[nro], &state);
    return (int)state;
    }
return 0;
}

// play
void SNDplay(int nro)
{
setPlayState(nro,SL_PLAYSTATE_PLAYING);
}

// stop
void SNDstop(int nro)
{
setPlayState(nro,SL_PLAYSTATE_STOPPED);
}

// pause
void SNDpause(int nro)
{
setPlayState(nro,SL_PLAYSTATE_PAUSED);
}

// pause
int isPlaying(int nro)
{
return (getPlayState(nro) == SL_PLAYSTATE_PLAYING);
}

// set position
void seekTo(int nro,int position)
{
if (uriPlayerPlay[nro]!=0) {
        //SLuint32 state = getPlayState();
        //setPlayState(SL_PLAYSTATE_PAUSED);
    SLresult result;
    result = (*uriPlayerSeek[nro])->SetPosition(uriPlayerSeek[nro], position,SL_SEEKMODE_FAST);
        //setPlayState(state);
    }
}

// get duration
int getDuration(int nro)
{
if (uriPlayerPlay[nro]!=0) {
        SLresult result;
        SLmillisecond msec;
        result = (*uriPlayerPlay[nro])->GetDuration(uriPlayerPlay[nro], &msec);
        return msec;
    }
return 0.0f;
}

// get current position
int getPosition(int nro)
{
    if (uriPlayerPlay[nro]!=0) {
        SLresult result;
        SLmillisecond msec;
        result = (*uriPlayerPlay[nro])->GetPosition(uriPlayerPlay[nro], &msec);
        return msec;
    }
return 0.0f;
}

void setPitch(int nro,int rate)
{
if (uriPlaybackPitch[nro]!=0) {
    SLresult result;
    result = (*uriPlaybackPitch[nro])->SetPitch(uriPlaybackPitch[nro], rate);
    }
}

void setRate(int nro,int rate)
{
if (0 != uriPlaybackRate[nro]) {
        SLresult result;
        result = (*uriPlaybackRate[nro])->SetRate(uriPlaybackRate[nro], rate);
    }
}

int getRate(int nro)
{
 if (0 != uriPlaybackRate[nro]) {
        SLresult result;
        SLpermille rate;
        result = (*uriPlaybackRate[nro])->GetRate(uriPlaybackRate[nro], &rate);
        return rate;
    }
return 0;
}

// create URI audio player
int setLoop(int nro,int startPos, int endPos)
{
SLresult result;
result = (*uriPlayerSeek[nro])->SetLoop(uriPlayerSeek[nro], SL_BOOLEAN_TRUE, startPos,endPos);
return 1;
}

// create URI audio player
int setNoLoop(int nro)
{
SLresult result;
if (0 != uriPlayerSeek[nro]) { // enable whole file looping
    result = (*uriPlayerSeek[nro])->SetLoop(uriPlayerSeek[nro], SL_BOOLEAN_TRUE, 0,SL_TIME_UNKNOWN);
    }
return 1;
}
