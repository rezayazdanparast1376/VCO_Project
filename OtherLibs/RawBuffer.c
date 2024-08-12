
#include "./RawBuffer.h"

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif



void InitRawBuffer(RawBuffer* mRB, int BufLength_, int Variety_, uint8_t ptr_Data[])
{
	mRB->ERR 		= 0;
	mRB->BufLength 	= BufLength_;
	mRB->Variety 	= Variety_;
	mRB->Readers 	= rbREADERS;
	mRB->Data 		= ptr_Data;

	for(int i = 0; i < mRB->Readers; i++)
		mRB->Read[i] = 0;
}


void rbReset(RawBuffer* mRB)
{
	mRB->Wrtn[0] = 0;
	mRB->ERR 	 = 0;

	int i;
	for(i = 1; i <= (mRB->BufLength * mRB->Variety); i++) //Data[0] used
		mRB->Data[i - 1] = 0;
	for(i = 1; i <= mRB->Readers; i++)
		mRB->Read[i - 1] = 0;
}

int rbGetRemainLength(RawBuffer* mRB, int reader)
{
	int RemainLength;

	RemainLength = mRB->Wrtn[0] - mRB->Read[reader];
	if(RemainLength < 0) RemainLength = 0;
	return RemainLength;
}

int rbGetRemainLengthBeforeChar(RawBuffer* mRB, uint8_t special_char, int len, int reader)
{
	int cursor, i, rem;
	rem = rbGetRemainLength(mRB, reader);
	if(len != 0) {
		len = len > rem ? rem : len; //getting min
	} else //len = 0, auto length
		len = rem;

	for(i = 0; i < len; i++) {
		cursor = (mRB->Read[reader] + i) % mRB->BufLength; //cursor:[0,mRB->BufLength-1]
		if(mRB->Data[cursor] == special_char)
			return i;
	}

	return -1; //not found
}

void rbPush(RawBuffer* mRB, int what, uint8_t* PushData, int PushLength)           //Push Data
{
	if(mRB == NULL)
		return;
	int cursor;
	int firstPieceLen;
	int reader, Wrtn_temp; //changed in rawbuffer3////////////////////////////////


	if(PushLength < 0) {
		mRB->ERR = RAWBUFFER_ERR_PUSHLENGTH_NEGETIVE;
		return;
	}
	if(PushLength > mRB->BufLength) {
		mRB->ERR = RAWBUFFER_ERR_PUSHLENGTH_BIGGER_THAN_BUFFER_SIZE;
		return;
	}

	if(mRB->Wrtn[0] > 2 * mRB->BufLength) {
		Wrtn_temp = mRB->Wrtn[0];
		mRB->Wrtn[0] = (mRB->Wrtn[0] % mRB->BufLength) + mRB->BufLength;
		for(reader = 0; reader < mRB->Readers; reader++)
			mRB->Read[reader] -= (Wrtn_temp - mRB->Wrtn[0]);
	}

	for(reader = 0; reader < mRB->Readers; reader++)
		if(mRB->Read[reader] > mRB->Wrtn[0])
			mRB->Read[reader] = mRB->Wrtn[0];


	cursor = mRB->Wrtn[0] % mRB->BufLength; //cursor:[0,mRB->BufLength-1]
	if(cursor + PushLength <= mRB->BufLength) {
		memcpy(mRB->Data + (what - 1)*mRB->BufLength + cursor, PushData, PushLength);
	} else {
		firstPieceLen = mRB->BufLength - cursor;
		memcpy(mRB->Data + (what - 1)*mRB->BufLength + cursor, PushData, firstPieceLen);
		memcpy(mRB->Data + (what - 1)*mRB->BufLength + 0, PushData + firstPieceLen, PushLength - firstPieceLen);
	}
	mRB->Wrtn[0] += PushLength;

	for(reader = 0; reader < mRB->Readers; reader++)
		if(mRB->Wrtn[0] - mRB->Read[reader] > mRB->BufLength)
			mRB->Read[reader] = mRB->Wrtn[0] - mRB->BufLength;//remaining data is as long as buffer, read bytes increased due to data lost
}

void rbRePush(RawBuffer* mRB, int what, uint8_t* PushData, int PushLength)           //Push Data
{
	if(PushLength < 0) {
		mRB->ERR = RAWBUFFER_ERR_PUSHLENGTH_NEGETIVE;
		return;
	}

	if(PushLength > mRB->BufLength) {
		mRB->ERR = RAWBUFFER_ERR_PUSHLENGTH_BIGGER_THAN_BUFFER_SIZE;
		return;
	}

	mRB->Wrtn[0] -= PushLength;
	rbPush(mRB, what, PushData, PushLength);           //Push Data
}

int rbPull(RawBuffer* mRB, int what, uint8_t* PullData, int maxPullLength, int reader) //Pull data
{
	if(mRB == NULL)
		return 0;
	int cursor, firstPieceLen, remain, PullLength;
	PullLength = maxPullLength;
	remain = rbGetRemainLength(mRB, reader);
	if(PullLength > remain) {
		PullLength = remain;
	}

	cursor = mRB->Read[reader] % mRB->BufLength; //cursor:[0,mRB->BufLength-1]
	if(cursor + PullLength <= mRB->BufLength) {
		memcpy(PullData, mRB->Data + (what - 1)*mRB->BufLength + cursor, PullLength);
	} else {
		firstPieceLen = mRB->BufLength - cursor;
		memcpy(PullData, mRB->Data + (what - 1)*mRB->BufLength + cursor, firstPieceLen);
		memcpy(PullData + firstPieceLen, mRB->Data + (what - 1)*mRB->BufLength + 0, PullLength - firstPieceLen);
	}

	mRB->Read[reader] += PullLength;
	return PullLength;
}

int rbRePull(RawBuffer* mRB, int what, uint8_t* PullData, int PullLength, int reader) //Pull data
{
	mRB->Read[reader] -= PullLength;
	return rbPull(mRB, what, PullData, PullLength, reader); //Pull data
}

#ifdef __cplusplus
}
#endif
