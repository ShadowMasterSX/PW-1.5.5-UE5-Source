/*
 * FILE: A3DAbsTrackMaker.h
 *
 * DESCRIPTION: 
 *
 * CREATED BY: Duyuxin, 2007/1/29
 *
 * HISTORY: 
 *
 * Copyright (c) 2007 Archosaur Studio, All Rights Reserved.
 */

#ifndef _A3DABSTRACKMAKER_H_
#define _A3DABSTRACKMAKER_H_

#include "A3DQuaternion.h"

///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Types and Global variables
//	
///////////////////////////////////////////////////////////////////////////

class A3DSkeleton;
class A3DSklTrackSet;

///////////////////////////////////////////////////////////////////////////
//	
//	Declare of Global functions
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Class A3DAbsTrackMaker
//	
///////////////////////////////////////////////////////////////////////////

class A3DAbsTrackMaker
{
public:		//	Types

public:		//	Constructor and Destructor

	A3DAbsTrackMaker(A3DSkeleton* pSkeleton, A3DSklTrackSet* pTrackSet);
	virtual ~A3DAbsTrackMaker();

public:		//	Attributes

public:		//	Operations

	//	Make absolute track
	bool Make(int iNumJoint, int* aJoints);

protected:	//	Attributes

	A3DSkeleton*	m_pSkeleton;
	A3DSklTrackSet*	m_pTrackSet;

protected:	//	Operations

	//	Get position and orientation of specified time
	bool GetBoneStateOnTrack(int idJoint, int iAbsTime, A3DVECTOR3& vPos, A3DQUATERNION& quRot);
};

///////////////////////////////////////////////////////////////////////////
//	
//	Inline functions
//	
///////////////////////////////////////////////////////////////////////////

#endif	//	_A3DABSTRACKMAKER_H_
