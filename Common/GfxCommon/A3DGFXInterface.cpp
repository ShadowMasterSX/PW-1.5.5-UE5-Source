/*
 * FILE: A3DGFXInterface.cpp
 *
 * DESCRIPTION: 
 *
 * CREATED BY: zhangyachuan, 2011/2/24
 *
 * HISTORY:
 *
 * Copyright (c) 2011 Archosaur Studio, All Rights Reserved.	
 */

#include "stdafx.h"
#include "A3DGFXInterface.h"

///////////////////////////////////////////////////////////////////////////
//
//	Define and Macro
//
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//
//	Reference to External variables and functions
//
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//
//	Local Types and Variables and Global variables
//
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//
//	Local functions
//
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//
//	Implement A3DGFXInterfaceDefImpl
//
///////////////////////////////////////////////////////////////////////////

bool A3DGFXInterfaceDefImpl::PlaySkillGfx(const PARAM_PLAYSKILLGFX* param)
{
	return AfxPlaySkillGfx(
		param->strAtkFile,
		param->SerialID,
		param->nCasterID,
		param->nCastTargetID,
		&param->vFixedPoint,
		param->nDivisions,
		(*param->pTargets));
}

A3DGFXInterfaceDefImpl2::A3DGFXInterfaceDefImpl2(AudioEngine::EventSystem* pEventSystem)
: m_pEventSystem(pEventSystem)
, m_iCurActEventInstanceNum(0)
{

}

AudioEngine::EventInstance* A3DGFXInterfaceDefImpl2::CreateAudioEventInstance(const char* szEventFullPath) const
{
#ifdef _USEAUDIOENGINE
	if (!m_pEventSystem)
		return NULL;

	if (AudioEngine::Event* pEvent = m_pEventSystem->GetEvent(szEventFullPath))
	{
		AudioEngine::EventInstance* pNewInst = pEvent->CreateInstance(false);
		//	记录当前活动状态下的EventInstance的数量
		if (pNewInst)
		{
			InterlockedIncrement(&m_iCurActEventInstanceNum);
		}

		return pNewInst;
	}

	return NULL;
#else
	return NULL;
#endif
}

void A3DGFXInterfaceDefImpl2::ReleaseAudioEventInstance(AudioEngine::EventInstance*& pInstance) const
{
#ifdef _USEAUDIOENGINE
	if (pInstance)
	{
		pInstance->GetEvent()->DestroyInstance(pInstance);
		InterlockedDecrement(&m_iCurActEventInstanceNum);
		pInstance = NULL;
	}
#endif
}

#ifdef GFX_EDITOR

bool EditorGFXInterfaceDefImpl::PlaySkillGfx( const PARAM_PLAYSKILLGFX* param )
{
	using namespace _SGC;
	A3DSkillGfxComposerMan* pMan = AfxGetSkillGfxComposerMan();
	A3DSkillGfxMan* pEventMan = AfxGetSkillGfxEventMan();

	pMan->Play(
		param->strAtkFile,
		param->SerialID,
		param->nCasterID,
		param->nCastTargetID,
		&param->vFixedPoint,
		0.0f,
		enumAttBothFlyHit | enumAttHitGround,
		0,
		0,
		param->nAttIndex);

	A3DSkillGfxEvent* pEvent = pEventMan->GetSkillGfxEvent(param->nCasterID, param->SerialID);

	if (!pEvent)
		return true;

	pEvent = pEvent->GetLast();
	pEvent->SetDivisions(param->nDivisions);

	TARGET_DATA td;
	td.idTarget = 2;
	td.nDamage = 100;
	td.dwModifier = 0;
	pEvent->AddOneTarget(td);
	return true;
}

#endif
