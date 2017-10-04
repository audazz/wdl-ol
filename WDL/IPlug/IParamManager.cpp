#include "IParamManager.h"

IParamManager::IParamManager(IPlugBase* pPlug) : mPlug(pPlug)
{
    mHandlers = new ParamChangeHandler [pPlug->NParams()];
    for (int i = 0; i < pPlug->NParams(); ++i) {
        mHandlers[i] = NULL;
        mFreeParamIdxs.push(i);
    }
}

void IParamManager::HandleParamChange(int paramIdx)
{
    ParamChangeHandler handler = mHandlers[paramIdx];
    if (handler != NULL) {
       (mPlug->*handler)(paramIdx);
    }
}

const int IParamManager::AddBool(ParamChangeHandler handler, const char* name, bool defaultVal, const char* label, const char* group)
{
    int paramIdx = GetFreeParamIdx();
    if (paramIdx < 0) return paramIdx;

    mPlug->GetParam(paramIdx)->InitBool(name, defaultVal, label, group);

    SetHandler(paramIdx, handler);

    return paramIdx;
}

const int IParamManager::AddEnum(ParamChangeHandler handler, const char* name, int defaultVal, int nEnums, const char* label, const char* group)
{
    int paramIdx = GetFreeParamIdx();
    if (paramIdx < 0) return paramIdx;

    mPlug->GetParam(paramIdx)->InitEnum(name, defaultVal, nEnums, label, group);

    SetHandler(paramIdx, handler);

    return paramIdx;
}

const int IParamManager::AddInt(ParamChangeHandler handler, const char* name, int defaultVal, int minVal, int maxVal, const char* label, const char* group)
{
    int paramIdx = GetFreeParamIdx();
    if (paramIdx < 0) return paramIdx;

    mPlug->GetParam(paramIdx)->InitInt(name, defaultVal, minVal, maxVal, label, group);

    SetHandler(paramIdx, handler);

    return paramIdx;
}

const int IParamManager::AddDouble(ParamChangeHandler handler, const char* name, double defaultVal, double minVal, double maxVal, double step, const char* label, const char* group, double shape)
{
    int paramIdx = GetFreeParamIdx();
    if (paramIdx < 0) return paramIdx;

    mPlug->GetParam(paramIdx)->InitDouble(name, defaultVal, minVal, maxVal, step, label, group, shape);

    SetHandler(paramIdx, handler);

    return paramIdx;
}

const int IParamManager::GetFreeParamIdx()
{
    if (mFreeParamIdxs.size()) 
    {
        int paramIdx = mFreeParamIdxs.front();
        mFreeParamIdxs.pop();
        return paramIdx;
    } 
    else return -1; // No free params
}
