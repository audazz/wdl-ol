#ifndef _IPARAMMANAGER_
#define _IPARAMMANAGER_

#include "IPlugBase.h"
#include <queue>

// IParamManager is a simple way of automatically delgating param idxs and
// registering handlers for param changes. This class must be used entirely for
// param idxs as this class doesn't directly communicate with the plug

// void IPlug member functions that take a param idx as an argument
typedef void (IPlugBase::*ParamChangeHandler) (int);

class IParamManager
{
public:
    IParamManager(IPlugBase* pPlug);
    ~IParamManager() { delete[] mHandlers; }

    // Should be called by OnParamChange
    void HandleParamChange(int paramIdx);

    // Defines a new parameter on a free param Idx; returns -1 if there are no free params left
    const int AddBool(ParamChangeHandler handler, const char* name, bool defaultVal, const char* label = "", const char* group = "");
    const int AddEnum(ParamChangeHandler handler, const char* name, int defaultVal, int nEnums, const char* label = "", const char* group = "");
    const int AddInt(ParamChangeHandler handler, const char* name, int defaultVal, int minVal, int maxVal, const char* label = "", const char* group = "");
    const int AddDouble(ParamChangeHandler handler, const char* name, double defaultVal, double minVal, double maxVal, double step, const char* label = "", const char* group = "", double shape = 1.);

    const int GetFreeParamIdx (void);

    inline void SetHandler(int paramIdx, ParamChangeHandler handler) { mHandlers[paramIdx] = handler; }
    inline ParamChangeHandler GetHandler(int paramIdx) { return mHandlers[paramIdx]; }

    inline IPlugBase* GetPlug() { return mPlug; }

private:
    ParamChangeHandler* mHandlers;
    std::queue<int> mFreeParamIdxs;

    IPlugBase* mPlug;
};

#endif 
