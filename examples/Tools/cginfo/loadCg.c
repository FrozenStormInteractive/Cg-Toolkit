#include "loadCg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN 1
# endif
# ifndef NOGDI
#   define NOGDI 1
# endif
# include <windows.h>
#elif defined(__APPLE__)
# include <AvailabilityMacros.h>
# ifndef MAC_OS_X_VERSION_10_3
#   include <mach-o/dyld.h>
# else
#   include <dlfcn.h>
# endif
#else
# define __USE_GNU 1
# define _GNU_SOURCE
# include <dlfcn.h>
#endif

LcgHandle
lcgLoadLibrary(const char *filename)
{
#ifdef __APPLE__
  char *framework = NULL;

  /* 1. Try loading bare framework name */

# if defined(MAC_OS_X_VERSION_10_3)
  LcgHandle ret = (LcgHandle) dlopen(filename, RTLD_LAZY);
# else
  LcgHandle ret = (LcgHandle) NSAddImage(filename, NSADDIMAGE_OPTION_NONE);
# endif
  if (ret)
    return ret;

  /* 2. Try loading framework in Name.framework/Name */

  framework = (char *) malloc(strlen(filename)*2+12);
  sprintf(framework,"%s.framework/%s",filename,filename);

# if defined(MAC_OS_X_VERSION_10_3)
  ret = (LcgHandle) dlopen(framework, RTLD_LAZY);
# else
  ret = (LcgHandle) NSAddImage(framework, NSADDIMAGE_OPTION_NONE);
# endif

  free(framework);
  return ret;

#elif _WIN32
  return (LcgHandle) LoadLibraryA(filename);
#else
  return (LcgHandle) dlopen(filename, RTLD_LAZY);
#endif
}

int
lcgFreeLibrary(LcgHandle handle)
{
#ifdef _WIN32
  return FreeLibrary((HMODULE)handle) ? 1 : 0;
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_3)
  return 1;
#else
  return dlclose(handle) ? 0 : 1;
#endif
}

void *
lcgGetProcAddress(LcgHandle handle, const char *name)
{
#ifdef _WIN32
  return handle ? GetProcAddress((HMODULE)handle, name) : NULL;
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_3)
  return NSIsSymbolNameDefined(name) ? NSAddressOfSymbol(NSLookupAndBindSymbol(name)) : NULL;
#else
  return dlsym(handle, name);
#endif
}

const char *
lcgGetProcName(void **function)
{
  if (!function || !*function) return NULL;
  if (function==(void **) &cgAddStateEnumerant)                                         return "cgAddStateEnumerant";
  if (function==(void **) &cgCallStateResetCallback)                                    return "cgCallStateResetCallback";
  if (function==(void **) &cgCallStateSetCallback)                                      return "cgCallStateSetCallback";
  if (function==(void **) &cgCallStateValidateCallback)                                 return "cgCallStateValidateCallback";
  if (function==(void **) &cgCombinePrograms)                                           return "cgCombinePrograms";
  if (function==(void **) &cgCombinePrograms2)                                          return "cgCombinePrograms2";
  if (function==(void **) &cgCombinePrograms3)                                          return "cgCombinePrograms3";
  if (function==(void **) &cgCombinePrograms4)                                          return "cgCombinePrograms4";
  if (function==(void **) &cgCombinePrograms5)                                          return "cgCombinePrograms5";
  if (function==(void **) &cgCompileProgram)                                            return "cgCompileProgram";
  if (function==(void **) &cgConnectParameter)                                          return "cgConnectParameter";
  if (function==(void **) &cgCopyEffect)                                                return "cgCopyEffect";
  if (function==(void **) &cgCopyProgram)                                               return "cgCopyProgram";
  if (function==(void **) &cgCreateArraySamplerState)                                   return "cgCreateArraySamplerState";
  if (function==(void **) &cgCreateArrayState)                                          return "cgCreateArrayState";
  if (function==(void **) &cgCreateBuffer)                                              return "cgCreateBuffer";
  if (function==(void **) &cgCreateContext)                                             return "cgCreateContext";
  if (function==(void **) &cgCreateEffect)                                              return "cgCreateEffect";
  if (function==(void **) &cgCreateEffectAnnotation)                                    return "cgCreateEffectAnnotation";
  if (function==(void **) &cgCreateEffectFromFile)                                      return "cgCreateEffectFromFile";
  if (function==(void **) &cgCreateEffectParameter)                                     return "cgCreateEffectParameter";
  if (function==(void **) &cgCreateEffectParameterArray)                                return "cgCreateEffectParameterArray";
  if (function==(void **) &cgCreateEffectParameterMultiDimArray)                        return "cgCreateEffectParameterMultiDimArray";
  if (function==(void **) &cgCreateObj)                                                 return "cgCreateObj";
  if (function==(void **) &cgCreateObjFromFile)                                         return "cgCreateObjFromFile";
  if (function==(void **) &cgCreateParameter)                                           return "cgCreateParameter";
  if (function==(void **) &cgCreateParameterAnnotation)                                 return "cgCreateParameterAnnotation";
  if (function==(void **) &cgCreateParameterArray)                                      return "cgCreateParameterArray";
  if (function==(void **) &cgCreateParameterMultiDimArray)                              return "cgCreateParameterMultiDimArray";
  if (function==(void **) &cgCreatePass)                                                return "cgCreatePass";
  if (function==(void **) &cgCreatePassAnnotation)                                      return "cgCreatePassAnnotation";
  if (function==(void **) &cgCreateProgram)                                             return "cgCreateProgram";
  if (function==(void **) &cgCreateProgramAnnotation)                                   return "cgCreateProgramAnnotation";
  if (function==(void **) &cgCreateProgramFromEffect)                                   return "cgCreateProgramFromEffect";
  if (function==(void **) &cgCreateProgramFromFile)                                     return "cgCreateProgramFromFile";
  if (function==(void **) &cgCreateSamplerState)                                        return "cgCreateSamplerState";
  if (function==(void **) &cgCreateSamplerStateAssignment)                              return "cgCreateSamplerStateAssignment";
  if (function==(void **) &cgCreateState)                                               return "cgCreateState";
  if (function==(void **) &cgCreateStateAssignment)                                     return "cgCreateStateAssignment";
  if (function==(void **) &cgCreateStateAssignmentIndex)                                return "cgCreateStateAssignmentIndex";
  if (function==(void **) &cgCreateTechnique)                                           return "cgCreateTechnique";
  if (function==(void **) &cgCreateTechniqueAnnotation)                                 return "cgCreateTechniqueAnnotation";
  if (function==(void **) &cgDestroyBuffer)                                             return "cgDestroyBuffer";
  if (function==(void **) &cgDestroyContext)                                            return "cgDestroyContext";
  if (function==(void **) &cgDestroyEffect)                                             return "cgDestroyEffect";
  if (function==(void **) &cgDestroyObj)                                                return "cgDestroyObj";
  if (function==(void **) &cgDestroyParameter)                                          return "cgDestroyParameter";
  if (function==(void **) &cgDestroyProgram)                                            return "cgDestroyProgram";
  if (function==(void **) &cgDisconnectParameter)                                       return "cgDisconnectParameter";
  if (function==(void **) &cgEvaluateProgram)                                           return "cgEvaluateProgram";
  if (function==(void **) &cgGetAnnotationName)                                         return "cgGetAnnotationName";
  if (function==(void **) &cgGetAnnotationType)                                         return "cgGetAnnotationType";
  if (function==(void **) &cgGetArrayDimension)                                         return "cgGetArrayDimension";
  if (function==(void **) &cgGetArrayParameter)                                         return "cgGetArrayParameter";
  if (function==(void **) &cgGetArraySize)                                              return "cgGetArraySize";
  if (function==(void **) &cgGetArrayTotalSize)                                         return "cgGetArrayTotalSize";
  if (function==(void **) &cgGetArrayType)                                              return "cgGetArrayType";
  if (function==(void **) &cgGetAutoCompile)                                            return "cgGetAutoCompile";
  if (function==(void **) &cgGetBehavior)                                               return "cgGetBehavior";
  if (function==(void **) &cgGetBehaviorString)                                         return "cgGetBehaviorString";
  if (function==(void **) &cgGetBoolAnnotationValues)                                   return "cgGetBoolAnnotationValues";
  if (function==(void **) &cgGetBoolStateAssignmentValues)                              return "cgGetBoolStateAssignmentValues";
  if (function==(void **) &cgGetBooleanAnnotationValues)                                return "cgGetBooleanAnnotationValues";
  if (function==(void **) &cgGetBufferSize)                                             return "cgGetBufferSize";
  if (function==(void **) &cgGetCompilerIncludeCallback)                                return "cgGetCompilerIncludeCallback";
  if (function==(void **) &cgGetConnectedParameter)                                     return "cgGetConnectedParameter";
  if (function==(void **) &cgGetConnectedStateAssignmentParameter)                      return "cgGetConnectedStateAssignmentParameter";
  if (function==(void **) &cgGetConnectedToParameter)                                   return "cgGetConnectedToParameter";
  if (function==(void **) &cgGetContextBehavior)                                        return "cgGetContextBehavior";
  if (function==(void **) &cgGetDependentAnnotationParameter)                           return "cgGetDependentAnnotationParameter";
  if (function==(void **) &cgGetDependentProgramArrayStateAssignmentParameter)          return "cgGetDependentProgramArrayStateAssignmentParameter";
  if (function==(void **) &cgGetDependentStateAssignmentParameter)                      return "cgGetDependentStateAssignmentParameter";
  if (function==(void **) &cgGetDomain)                                                 return "cgGetDomain";
  if (function==(void **) &cgGetDomainString)                                           return "cgGetDomainString";
  if (function==(void **) &cgGetEffectContext)                                          return "cgGetEffectContext";
  if (function==(void **) &cgGetEffectName)                                             return "cgGetEffectName";
  if (function==(void **) &cgGetEffectParameterBuffer)                                  return "cgGetEffectParameterBuffer";
  if (function==(void **) &cgGetEffectParameterBySemantic)                              return "cgGetEffectParameterBySemantic";
  if (function==(void **) &cgGetEnum)                                                   return "cgGetEnum";
  if (function==(void **) &cgGetEnumString)                                             return "cgGetEnumString";
  if (function==(void **) &cgGetError)                                                  return "cgGetError";
  if (function==(void **) &cgGetErrorCallback)                                          return "cgGetErrorCallback";
  if (function==(void **) &cgGetErrorHandler)                                           return "cgGetErrorHandler";
  if (function==(void **) &cgGetErrorString)                                            return "cgGetErrorString";
  if (function==(void **) &cgGetFirstDependentParameter)                                return "cgGetFirstDependentParameter";
  if (function==(void **) &cgGetFirstEffect)                                            return "cgGetFirstEffect";
  if (function==(void **) &cgGetFirstEffectAnnotation)                                  return "cgGetFirstEffectAnnotation";
  if (function==(void **) &cgGetFirstEffectParameter)                                   return "cgGetFirstEffectParameter";
  if (function==(void **) &cgGetFirstError)                                             return "cgGetFirstError";
  if (function==(void **) &cgGetFirstLeafEffectParameter)                               return "cgGetFirstLeafEffectParameter";
  if (function==(void **) &cgGetFirstLeafParameter)                                     return "cgGetFirstLeafParameter";
  if (function==(void **) &cgGetFirstParameter)                                         return "cgGetFirstParameter";
  if (function==(void **) &cgGetFirstParameterAnnotation)                               return "cgGetFirstParameterAnnotation";
  if (function==(void **) &cgGetFirstPass)                                              return "cgGetFirstPass";
  if (function==(void **) &cgGetFirstPassAnnotation)                                    return "cgGetFirstPassAnnotation";
  if (function==(void **) &cgGetFirstProgram)                                           return "cgGetFirstProgram";
  if (function==(void **) &cgGetFirstProgramAnnotation)                                 return "cgGetFirstProgramAnnotation";
  if (function==(void **) &cgGetFirstSamplerState)                                      return "cgGetFirstSamplerState";
  if (function==(void **) &cgGetFirstSamplerStateAssignment)                            return "cgGetFirstSamplerStateAssignment";
  if (function==(void **) &cgGetFirstState)                                             return "cgGetFirstState";
  if (function==(void **) &cgGetFirstStateAssignment)                                   return "cgGetFirstStateAssignment";
  if (function==(void **) &cgGetFirstStructParameter)                                   return "cgGetFirstStructParameter";
  if (function==(void **) &cgGetFirstTechnique)                                         return "cgGetFirstTechnique";
  if (function==(void **) &cgGetFirstTechniqueAnnotation)                               return "cgGetFirstTechniqueAnnotation";
  if (function==(void **) &cgGetFirstUniformBufferParameter)                            return "cgGetFirstUniformBufferParameter";
  if (function==(void **) &cgGetFloatAnnotationValues)                                  return "cgGetFloatAnnotationValues";
  if (function==(void **) &cgGetFloatStateAssignmentValues)                             return "cgGetFloatStateAssignmentValues";
  if (function==(void **) &cgGetIntAnnotationValues)                                    return "cgGetIntAnnotationValues";
  if (function==(void **) &cgGetIntStateAssignmentValues)                               return "cgGetIntStateAssignmentValues";
  if (function==(void **) &cgGetLastErrorString)                                        return "cgGetLastErrorString";
  if (function==(void **) &cgGetLastListing)                                            return "cgGetLastListing";
  if (function==(void **) &cgGetLockingPolicy)                                          return "cgGetLockingPolicy";
  if (function==(void **) &cgGetMatrixParameterOrder)                                   return "cgGetMatrixParameterOrder";
  if (function==(void **) &cgGetMatrixParameterdc)                                      return "cgGetMatrixParameterdc";
  if (function==(void **) &cgGetMatrixParameterdr)                                      return "cgGetMatrixParameterdr";
  if (function==(void **) &cgGetMatrixParameterfc)                                      return "cgGetMatrixParameterfc";
  if (function==(void **) &cgGetMatrixParameterfr)                                      return "cgGetMatrixParameterfr";
  if (function==(void **) &cgGetMatrixParameteric)                                      return "cgGetMatrixParameteric";
  if (function==(void **) &cgGetMatrixParameterir)                                      return "cgGetMatrixParameterir";
  if (function==(void **) &cgGetMatrixSize)                                             return "cgGetMatrixSize";
  if (function==(void **) &cgGetNamedEffect)                                            return "cgGetNamedEffect";
  if (function==(void **) &cgGetNamedEffectAnnotation)                                  return "cgGetNamedEffectAnnotation";
  if (function==(void **) &cgGetNamedEffectParameter)                                   return "cgGetNamedEffectParameter";
  if (function==(void **) &cgGetNamedEffectUniformBuffer)                               return "cgGetNamedEffectUniformBuffer";
  if (function==(void **) &cgGetNamedParameter)                                         return "cgGetNamedParameter";
  if (function==(void **) &cgGetNamedParameterAnnotation)                               return "cgGetNamedParameterAnnotation";
  if (function==(void **) &cgGetNamedPass)                                              return "cgGetNamedPass";
  if (function==(void **) &cgGetNamedPassAnnotation)                                    return "cgGetNamedPassAnnotation";
  if (function==(void **) &cgGetNamedProgramAnnotation)                                 return "cgGetNamedProgramAnnotation";
  if (function==(void **) &cgGetNamedProgramParameter)                                  return "cgGetNamedProgramParameter";
  if (function==(void **) &cgGetNamedProgramUniformBuffer)                              return "cgGetNamedProgramUniformBuffer";
  if (function==(void **) &cgGetNamedSamplerState)                                      return "cgGetNamedSamplerState";
  if (function==(void **) &cgGetNamedSamplerStateAssignment)                            return "cgGetNamedSamplerStateAssignment";
  if (function==(void **) &cgGetNamedState)                                             return "cgGetNamedState";
  if (function==(void **) &cgGetNamedStateAssignment)                                   return "cgGetNamedStateAssignment";
  if (function==(void **) &cgGetNamedStructParameter)                                   return "cgGetNamedStructParameter";
  if (function==(void **) &cgGetNamedSubParameter)                                      return "cgGetNamedSubParameter";
  if (function==(void **) &cgGetNamedTechnique)                                         return "cgGetNamedTechnique";
  if (function==(void **) &cgGetNamedTechniqueAnnotation)                               return "cgGetNamedTechniqueAnnotation";
  if (function==(void **) &cgGetNamedUniformBufferParameter)                            return "cgGetNamedUniformBufferParameter";
  if (function==(void **) &cgGetNamedUserType)                                          return "cgGetNamedUserType";
  if (function==(void **) &cgGetNextAnnotation)                                         return "cgGetNextAnnotation";
  if (function==(void **) &cgGetNextEffect)                                             return "cgGetNextEffect";
  if (function==(void **) &cgGetNextLeafParameter)                                      return "cgGetNextLeafParameter";
  if (function==(void **) &cgGetNextParameter)                                          return "cgGetNextParameter";
  if (function==(void **) &cgGetNextPass)                                               return "cgGetNextPass";
  if (function==(void **) &cgGetNextProgram)                                            return "cgGetNextProgram";
  if (function==(void **) &cgGetNextState)                                              return "cgGetNextState";
  if (function==(void **) &cgGetNextStateAssignment)                                    return "cgGetNextStateAssignment";
  if (function==(void **) &cgGetNextTechnique)                                          return "cgGetNextTechnique";
  if (function==(void **) &cgGetNumConnectedToParameters)                               return "cgGetNumConnectedToParameters";
  if (function==(void **) &cgGetNumDependentAnnotationParameters)                       return "cgGetNumDependentAnnotationParameters";
  if (function==(void **) &cgGetNumDependentProgramArrayStateAssignmentParameters)      return "cgGetNumDependentProgramArrayStateAssignmentParameters";
  if (function==(void **) &cgGetNumDependentStateAssignmentParameters)                  return "cgGetNumDependentStateAssignmentParameters";
  if (function==(void **) &cgGetNumParentTypes)                                         return "cgGetNumParentTypes";
  if (function==(void **) &cgGetNumProgramDomains)                                      return "cgGetNumProgramDomains";
  if (function==(void **) &cgGetNumStateEnumerants)                                     return "cgGetNumStateEnumerants";
  if (function==(void **) &cgGetNumSupportedProfiles)                                   return "cgGetNumSupportedProfiles";
  if (function==(void **) &cgGetNumUserTypes)                                           return "cgGetNumUserTypes";
  if (function==(void **) &cgGetParameterBaseResource)                                  return "cgGetParameterBaseResource";
  if (function==(void **) &cgGetParameterBaseType)                                      return "cgGetParameterBaseType";
  if (function==(void **) &cgGetParameterBufferIndex)                                   return "cgGetParameterBufferIndex";
  if (function==(void **) &cgGetParameterBufferOffset)                                  return "cgGetParameterBufferOffset";
  if (function==(void **) &cgGetParameterClass)                                         return "cgGetParameterClass";
  if (function==(void **) &cgGetParameterClassEnum)                                     return "cgGetParameterClassEnum";
  if (function==(void **) &cgGetParameterClassString)                                   return "cgGetParameterClassString";
  if (function==(void **) &cgGetParameterColumns)                                       return "cgGetParameterColumns";
  if (function==(void **) &cgGetParameterContext)                                       return "cgGetParameterContext";
  if (function==(void **) &cgGetParameterDefaultValuedc)                                return "cgGetParameterDefaultValuedc";
  if (function==(void **) &cgGetParameterDefaultValuedr)                                return "cgGetParameterDefaultValuedr";
  if (function==(void **) &cgGetParameterDefaultValuefc)                                return "cgGetParameterDefaultValuefc";
  if (function==(void **) &cgGetParameterDefaultValuefr)                                return "cgGetParameterDefaultValuefr";
  if (function==(void **) &cgGetParameterDefaultValueic)                                return "cgGetParameterDefaultValueic";
  if (function==(void **) &cgGetParameterDefaultValueir)                                return "cgGetParameterDefaultValueir";
  if (function==(void **) &cgGetParameterDirection)                                     return "cgGetParameterDirection";
  if (function==(void **) &cgGetParameterEffect)                                        return "cgGetParameterEffect";
  if (function==(void **) &cgGetParameterIndex)                                         return "cgGetParameterIndex";
  if (function==(void **) &cgGetParameterName)                                          return "cgGetParameterName";
  if (function==(void **) &cgGetParameterNamedType)                                     return "cgGetParameterNamedType";
  if (function==(void **) &cgGetParameterOrdinalNumber)                                 return "cgGetParameterOrdinalNumber";
  if (function==(void **) &cgGetParameterProgram)                                       return "cgGetParameterProgram";
  if (function==(void **) &cgGetParameterResource)                                      return "cgGetParameterResource";
  if (function==(void **) &cgGetParameterResourceIndex)                                 return "cgGetParameterResourceIndex";
  if (function==(void **) &cgGetParameterResourceName)                                  return "cgGetParameterResourceName";
  if (function==(void **) &cgGetParameterResourceSize)                                  return "cgGetParameterResourceSize";
  if (function==(void **) &cgGetParameterResourceType)                                  return "cgGetParameterResourceType";
  if (function==(void **) &cgGetParameterRows)                                          return "cgGetParameterRows";
  if (function==(void **) &cgGetParameterSemantic)                                      return "cgGetParameterSemantic";
  if (function==(void **) &cgGetParameterSettingMode)                                   return "cgGetParameterSettingMode";
  if (function==(void **) &cgGetParameterType)                                          return "cgGetParameterType";
  if (function==(void **) &cgGetParameterValuedc)                                       return "cgGetParameterValuedc";
  if (function==(void **) &cgGetParameterValuedr)                                       return "cgGetParameterValuedr";
  if (function==(void **) &cgGetParameterValuefc)                                       return "cgGetParameterValuefc";
  if (function==(void **) &cgGetParameterValuefr)                                       return "cgGetParameterValuefr";
  if (function==(void **) &cgGetParameterValueic)                                       return "cgGetParameterValueic";
  if (function==(void **) &cgGetParameterValueir)                                       return "cgGetParameterValueir";
  if (function==(void **) &cgGetParameterValues)                                        return "cgGetParameterValues";
  if (function==(void **) &cgGetParameterVariability)                                   return "cgGetParameterVariability";
  if (function==(void **) &cgGetParentType)                                             return "cgGetParentType";
  if (function==(void **) &cgGetPassName)                                               return "cgGetPassName";
  if (function==(void **) &cgGetPassProgram)                                            return "cgGetPassProgram";
  if (function==(void **) &cgGetPassTechnique)                                          return "cgGetPassTechnique";
  if (function==(void **) &cgGetProfile)                                                return "cgGetProfile";
  if (function==(void **) &cgGetProfileDomain)                                          return "cgGetProfileDomain";
  if (function==(void **) &cgGetProfileProperty)                                        return "cgGetProfileProperty";
  if (function==(void **) &cgGetProfileSibling)                                         return "cgGetProfileSibling";
  if (function==(void **) &cgGetProfileString)                                          return "cgGetProfileString";
  if (function==(void **) &cgGetProgramBuffer)                                          return "cgGetProgramBuffer";
  if (function==(void **) &cgGetProgramBufferMaxIndex)                                  return "cgGetProgramBufferMaxIndex";
  if (function==(void **) &cgGetProgramBufferMaxSize)                                   return "cgGetProgramBufferMaxSize";
  if (function==(void **) &cgGetProgramContext)                                         return "cgGetProgramContext";
  if (function==(void **) &cgGetProgramDomain)                                          return "cgGetProgramDomain";
  if (function==(void **) &cgGetProgramDomainProfile)                                   return "cgGetProgramDomainProfile";
  if (function==(void **) &cgGetProgramDomainProgram)                                   return "cgGetProgramDomainProgram";
  if (function==(void **) &cgGetProgramInput)                                           return "cgGetProgramInput";
  if (function==(void **) &cgGetProgramOptions)                                         return "cgGetProgramOptions";
  if (function==(void **) &cgGetProgramOutput)                                          return "cgGetProgramOutput";
  if (function==(void **) &cgGetProgramOutputVertices)                                  return "cgGetProgramOutputVertices";
  if (function==(void **) &cgGetProgramProfile)                                         return "cgGetProgramProfile";
  if (function==(void **) &cgGetProgramStateAssignmentValue)                            return "cgGetProgramStateAssignmentValue";
  if (function==(void **) &cgGetProgramString)                                          return "cgGetProgramString";
  if (function==(void **) &cgGetResource)                                               return "cgGetResource";
  if (function==(void **) &cgGetResourceString)                                         return "cgGetResourceString";
  if (function==(void **) &cgGetSamplerStateAssignmentParameter)                        return "cgGetSamplerStateAssignmentParameter";
  if (function==(void **) &cgGetSamplerStateAssignmentState)                            return "cgGetSamplerStateAssignmentState";
  if (function==(void **) &cgGetSamplerStateAssignmentValue)                            return "cgGetSamplerStateAssignmentValue";
  if (function==(void **) &cgGetSemanticCasePolicy)                                     return "cgGetSemanticCasePolicy";
  if (function==(void **) &cgGetStateAssignmentIndex)                                   return "cgGetStateAssignmentIndex";
  if (function==(void **) &cgGetStateAssignmentPass)                                    return "cgGetStateAssignmentPass";
  if (function==(void **) &cgGetStateAssignmentState)                                   return "cgGetStateAssignmentState";
  if (function==(void **) &cgGetStateContext)                                           return "cgGetStateContext";
  if (function==(void **) &cgGetStateEnumerant)                                         return "cgGetStateEnumerant";
  if (function==(void **) &cgGetStateEnumerantName)                                     return "cgGetStateEnumerantName";
  if (function==(void **) &cgGetStateEnumerantValue)                                    return "cgGetStateEnumerantValue";
  if (function==(void **) &cgGetStateLatestProfile)                                     return "cgGetStateLatestProfile";
  if (function==(void **) &cgGetStateName)                                              return "cgGetStateName";
  if (function==(void **) &cgGetStateResetCallback)                                     return "cgGetStateResetCallback";
  if (function==(void **) &cgGetStateSetCallback)                                       return "cgGetStateSetCallback";
  if (function==(void **) &cgGetStateType)                                              return "cgGetStateType";
  if (function==(void **) &cgGetStateValidateCallback)                                  return "cgGetStateValidateCallback";
  if (function==(void **) &cgGetString)                                                 return "cgGetString";
  if (function==(void **) &cgGetStringAnnotationValue)                                  return "cgGetStringAnnotationValue";
  if (function==(void **) &cgGetStringAnnotationValues)                                 return "cgGetStringAnnotationValues";
  if (function==(void **) &cgGetStringParameterValue)                                   return "cgGetStringParameterValue";
  if (function==(void **) &cgGetStringStateAssignmentValue)                             return "cgGetStringStateAssignmentValue";
  if (function==(void **) &cgGetSupportedProfile)                                       return "cgGetSupportedProfile";
  if (function==(void **) &cgGetTechniqueEffect)                                        return "cgGetTechniqueEffect";
  if (function==(void **) &cgGetTechniqueName)                                          return "cgGetTechniqueName";
  if (function==(void **) &cgGetTextureStateAssignmentValue)                            return "cgGetTextureStateAssignmentValue";
  if (function==(void **) &cgGetType)                                                   return "cgGetType";
  if (function==(void **) &cgGetTypeBase)                                               return "cgGetTypeBase";
  if (function==(void **) &cgGetTypeClass)                                              return "cgGetTypeClass";
  if (function==(void **) &cgGetTypeSizes)                                              return "cgGetTypeSizes";
  if (function==(void **) &cgGetTypeString)                                             return "cgGetTypeString";
  if (function==(void **) &cgGetUniformBufferBlockName)                                 return "cgGetUniformBufferBlockName";
  if (function==(void **) &cgGetUniformBufferParameter)                                 return "cgGetUniformBufferParameter";
  if (function==(void **) &cgGetUserType)                                               return "cgGetUserType";
  if (function==(void **) &cgIsAnnotation)                                              return "cgIsAnnotation";
  if (function==(void **) &cgIsBuffer)                                                  return "cgIsBuffer";
  if (function==(void **) &cgIsContext)                                                 return "cgIsContext";
  if (function==(void **) &cgIsEffect)                                                  return "cgIsEffect";
  if (function==(void **) &cgIsInterfaceType)                                           return "cgIsInterfaceType";
  if (function==(void **) &cgIsParameter)                                               return "cgIsParameter";
  if (function==(void **) &cgIsParameterGlobal)                                         return "cgIsParameterGlobal";
  if (function==(void **) &cgIsParameterReferenced)                                     return "cgIsParameterReferenced";
  if (function==(void **) &cgIsParameterUsed)                                           return "cgIsParameterUsed";
  if (function==(void **) &cgIsParentType)                                              return "cgIsParentType";
  if (function==(void **) &cgIsPass)                                                    return "cgIsPass";
  if (function==(void **) &cgIsProfileSupported)                                        return "cgIsProfileSupported";
  if (function==(void **) &cgIsProgram)                                                 return "cgIsProgram";
  if (function==(void **) &cgIsProgramCompiled)                                         return "cgIsProgramCompiled";
  if (function==(void **) &cgIsState)                                                   return "cgIsState";
  if (function==(void **) &cgIsStateAssignment)                                         return "cgIsStateAssignment";
  if (function==(void **) &cgIsTechnique)                                               return "cgIsTechnique";
  if (function==(void **) &cgIsTechniqueValidated)                                      return "cgIsTechniqueValidated";
  if (function==(void **) &cgMapBuffer)                                                 return "cgMapBuffer";
  if (function==(void **) &cgResetPassState)                                            return "cgResetPassState";
  if (function==(void **) &cgSetArraySize)                                              return "cgSetArraySize";
  if (function==(void **) &cgSetAutoCompile)                                            return "cgSetAutoCompile";
  if (function==(void **) &cgSetBoolAnnotation)                                         return "cgSetBoolAnnotation";
  if (function==(void **) &cgSetBoolArrayStateAssignment)                               return "cgSetBoolArrayStateAssignment";
  if (function==(void **) &cgSetBoolStateAssignment)                                    return "cgSetBoolStateAssignment";
  if (function==(void **) &cgSetBufferData)                                             return "cgSetBufferData";
  if (function==(void **) &cgSetBufferSubData)                                          return "cgSetBufferSubData";
  if (function==(void **) &cgSetCompilerIncludeCallback)                                return "cgSetCompilerIncludeCallback";
  if (function==(void **) &cgSetCompilerIncludeFile)                                    return "cgSetCompilerIncludeFile";
  if (function==(void **) &cgSetCompilerIncludeString)                                  return "cgSetCompilerIncludeString";
  if (function==(void **) &cgSetContextBehavior)                                        return "cgSetContextBehavior";
  if (function==(void **) &cgSetEffectName)                                             return "cgSetEffectName";
  if (function==(void **) &cgSetEffectParameterBuffer)                                  return "cgSetEffectParameterBuffer";
  if (function==(void **) &cgSetErrorCallback)                                          return "cgSetErrorCallback";
  if (function==(void **) &cgSetErrorHandler)                                           return "cgSetErrorHandler";
  if (function==(void **) &cgSetFloatAnnotation)                                        return "cgSetFloatAnnotation";
  if (function==(void **) &cgSetFloatArrayStateAssignment)                              return "cgSetFloatArrayStateAssignment";
  if (function==(void **) &cgSetFloatStateAssignment)                                   return "cgSetFloatStateAssignment";
  if (function==(void **) &cgSetIntAnnotation)                                          return "cgSetIntAnnotation";
  if (function==(void **) &cgSetIntArrayStateAssignment)                                return "cgSetIntArrayStateAssignment";
  if (function==(void **) &cgSetIntStateAssignment)                                     return "cgSetIntStateAssignment";
  if (function==(void **) &cgSetLastListing)                                            return "cgSetLastListing";
  if (function==(void **) &cgSetLockingPolicy)                                          return "cgSetLockingPolicy";
  if (function==(void **) &cgSetMatrixParameterdc)                                      return "cgSetMatrixParameterdc";
  if (function==(void **) &cgSetMatrixParameterdr)                                      return "cgSetMatrixParameterdr";
  if (function==(void **) &cgSetMatrixParameterfc)                                      return "cgSetMatrixParameterfc";
  if (function==(void **) &cgSetMatrixParameterfr)                                      return "cgSetMatrixParameterfr";
  if (function==(void **) &cgSetMatrixParameteric)                                      return "cgSetMatrixParameteric";
  if (function==(void **) &cgSetMatrixParameterir)                                      return "cgSetMatrixParameterir";
  if (function==(void **) &cgSetMultiDimArraySize)                                      return "cgSetMultiDimArraySize";
  if (function==(void **) &cgSetParameter1d)                                            return "cgSetParameter1d";
  if (function==(void **) &cgSetParameter1dv)                                           return "cgSetParameter1dv";
  if (function==(void **) &cgSetParameter1f)                                            return "cgSetParameter1f";
  if (function==(void **) &cgSetParameter1fv)                                           return "cgSetParameter1fv";
  if (function==(void **) &cgSetParameter1i)                                            return "cgSetParameter1i";
  if (function==(void **) &cgSetParameter1iv)                                           return "cgSetParameter1iv";
  if (function==(void **) &cgSetParameter2d)                                            return "cgSetParameter2d";
  if (function==(void **) &cgSetParameter2dv)                                           return "cgSetParameter2dv";
  if (function==(void **) &cgSetParameter2f)                                            return "cgSetParameter2f";
  if (function==(void **) &cgSetParameter2fv)                                           return "cgSetParameter2fv";
  if (function==(void **) &cgSetParameter2i)                                            return "cgSetParameter2i";
  if (function==(void **) &cgSetParameter2iv)                                           return "cgSetParameter2iv";
  if (function==(void **) &cgSetParameter3d)                                            return "cgSetParameter3d";
  if (function==(void **) &cgSetParameter3dv)                                           return "cgSetParameter3dv";
  if (function==(void **) &cgSetParameter3f)                                            return "cgSetParameter3f";
  if (function==(void **) &cgSetParameter3fv)                                           return "cgSetParameter3fv";
  if (function==(void **) &cgSetParameter3i)                                            return "cgSetParameter3i";
  if (function==(void **) &cgSetParameter3iv)                                           return "cgSetParameter3iv";
  if (function==(void **) &cgSetParameter4d)                                            return "cgSetParameter4d";
  if (function==(void **) &cgSetParameter4dv)                                           return "cgSetParameter4dv";
  if (function==(void **) &cgSetParameter4f)                                            return "cgSetParameter4f";
  if (function==(void **) &cgSetParameter4fv)                                           return "cgSetParameter4fv";
  if (function==(void **) &cgSetParameter4i)                                            return "cgSetParameter4i";
  if (function==(void **) &cgSetParameter4iv)                                           return "cgSetParameter4iv";
  if (function==(void **) &cgSetParameterSemantic)                                      return "cgSetParameterSemantic";
  if (function==(void **) &cgSetParameterSettingMode)                                   return "cgSetParameterSettingMode";
  if (function==(void **) &cgSetParameterValuedc)                                       return "cgSetParameterValuedc";
  if (function==(void **) &cgSetParameterValuedr)                                       return "cgSetParameterValuedr";
  if (function==(void **) &cgSetParameterValuefc)                                       return "cgSetParameterValuefc";
  if (function==(void **) &cgSetParameterValuefr)                                       return "cgSetParameterValuefr";
  if (function==(void **) &cgSetParameterValueic)                                       return "cgSetParameterValueic";
  if (function==(void **) &cgSetParameterValueir)                                       return "cgSetParameterValueir";
  if (function==(void **) &cgSetParameterVariability)                                   return "cgSetParameterVariability";
  if (function==(void **) &cgSetPassProgramParameters)                                  return "cgSetPassProgramParameters";
  if (function==(void **) &cgSetPassState)                                              return "cgSetPassState";
  if (function==(void **) &cgSetProgramBuffer)                                          return "cgSetProgramBuffer";
  if (function==(void **) &cgSetProgramOutputVertices)                                  return "cgSetProgramOutputVertices";
  if (function==(void **) &cgSetProgramProfile)                                         return "cgSetProgramProfile";
  if (function==(void **) &cgSetProgramStateAssignment)                                 return "cgSetProgramStateAssignment";
  if (function==(void **) &cgSetSamplerState)                                           return "cgSetSamplerState";
  if (function==(void **) &cgSetSamplerStateAssignment)                                 return "cgSetSamplerStateAssignment";
  if (function==(void **) &cgSetSemanticCasePolicy)                                     return "cgSetSemanticCasePolicy";
  if (function==(void **) &cgSetStateCallbacks)                                         return "cgSetStateCallbacks";
  if (function==(void **) &cgSetStateLatestProfile)                                     return "cgSetStateLatestProfile";
  if (function==(void **) &cgSetStringAnnotation)                                       return "cgSetStringAnnotation";
  if (function==(void **) &cgSetStringParameterValue)                                   return "cgSetStringParameterValue";
  if (function==(void **) &cgSetStringStateAssignment)                                  return "cgSetStringStateAssignment";
  if (function==(void **) &cgSetTextureStateAssignment)                                 return "cgSetTextureStateAssignment";
  if (function==(void **) &cgSetUniformBufferParameter)                                 return "cgSetUniformBufferParameter";
  if (function==(void **) &cgUnmapBuffer)                                               return "cgUnmapBuffer";
  if (function==(void **) &cgUpdatePassParameters)                                      return "cgUpdatePassParameters";
  if (function==(void **) &cgUpdateProgramParameters)                                   return "cgUpdateProgramParameters";
  if (function==(void **) &cgValidateTechnique)                                         return "cgValidateTechnique";

  return NULL;
}

extern int
lcgHasVersion(void ***version)
{
  void ***i = version;

  if (!i)
    return 0;

  /* Check if any of the function pointers are NULL */

  for (; *i; ++i)
  {
    if (!**i)
      return 0;
  }

  return 1;
}

const char *
lcgGetModuleFileName(LcgHandle handle, void *function)
{
#ifdef _WIN32
  static char buffer[4096];
  if (GetModuleFileNameA((HMODULE)handle, buffer, 4095))
  {
    buffer[4095] = '\0';
    return buffer;
  }
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_3)
#else
  Dl_info info;
  if (dladdr(function,&info))
    return info.dli_fname;
#endif
  return NULL;
}

/* Entry Points */

PFNCGADDSTATEENUMERANTPROC cgAddStateEnumerant = NULL;
PFNCGCALLSTATERESETCALLBACKPROC cgCallStateResetCallback = NULL;
PFNCGCALLSTATESETCALLBACKPROC cgCallStateSetCallback = NULL;
PFNCGCALLSTATEVALIDATECALLBACKPROC cgCallStateValidateCallback = NULL;
PFNCGCOMBINEPROGRAMSPROC cgCombinePrograms = NULL;
PFNCGCOMBINEPROGRAMS2PROC cgCombinePrograms2 = NULL;
PFNCGCOMBINEPROGRAMS3PROC cgCombinePrograms3 = NULL;
PFNCGCOMBINEPROGRAMS4PROC cgCombinePrograms4 = NULL;
PFNCGCOMBINEPROGRAMS5PROC cgCombinePrograms5 = NULL;
PFNCGCOMPILEPROGRAMPROC cgCompileProgram = NULL;
PFNCGCONNECTPARAMETERPROC cgConnectParameter = NULL;
PFNCGCOPYEFFECTPROC cgCopyEffect = NULL;
PFNCGCOPYPROGRAMPROC cgCopyProgram = NULL;
PFNCGCREATEARRAYSAMPLERSTATEPROC cgCreateArraySamplerState = NULL;
PFNCGCREATEARRAYSTATEPROC cgCreateArrayState = NULL;
PFNCGCREATEBUFFERPROC cgCreateBuffer = NULL;
PFNCGCREATECONTEXTPROC cgCreateContext = NULL;
PFNCGCREATEEFFECTPROC cgCreateEffect = NULL;
PFNCGCREATEEFFECTANNOTATIONPROC cgCreateEffectAnnotation = NULL;
PFNCGCREATEEFFECTFROMFILEPROC cgCreateEffectFromFile = NULL;
PFNCGCREATEEFFECTPARAMETERPROC cgCreateEffectParameter = NULL;
PFNCGCREATEEFFECTPARAMETERARRAYPROC cgCreateEffectParameterArray = NULL;
PFNCGCREATEEFFECTPARAMETERMULTIDIMARRAYPROC cgCreateEffectParameterMultiDimArray = NULL;
PFNCGCREATEOBJPROC cgCreateObj = NULL;
PFNCGCREATEOBJFROMFILEPROC cgCreateObjFromFile = NULL;
PFNCGCREATEPARAMETERPROC cgCreateParameter = NULL;
PFNCGCREATEPARAMETERANNOTATIONPROC cgCreateParameterAnnotation = NULL;
PFNCGCREATEPARAMETERARRAYPROC cgCreateParameterArray = NULL;
PFNCGCREATEPARAMETERMULTIDIMARRAYPROC cgCreateParameterMultiDimArray = NULL;
PFNCGCREATEPASSPROC cgCreatePass = NULL;
PFNCGCREATEPASSANNOTATIONPROC cgCreatePassAnnotation = NULL;
PFNCGCREATEPROGRAMPROC cgCreateProgram = NULL;
PFNCGCREATEPROGRAMANNOTATIONPROC cgCreateProgramAnnotation = NULL;
PFNCGCREATEPROGRAMFROMEFFECTPROC cgCreateProgramFromEffect = NULL;
PFNCGCREATEPROGRAMFROMFILEPROC cgCreateProgramFromFile = NULL;
PFNCGCREATESAMPLERSTATEPROC cgCreateSamplerState = NULL;
PFNCGCREATESAMPLERSTATEASSIGNMENTPROC cgCreateSamplerStateAssignment = NULL;
PFNCGCREATESTATEPROC cgCreateState = NULL;
PFNCGCREATESTATEASSIGNMENTPROC cgCreateStateAssignment = NULL;
PFNCGCREATESTATEASSIGNMENTINDEXPROC cgCreateStateAssignmentIndex = NULL;
PFNCGCREATETECHNIQUEPROC cgCreateTechnique = NULL;
PFNCGCREATETECHNIQUEANNOTATIONPROC cgCreateTechniqueAnnotation = NULL;
PFNCGDESTROYBUFFERPROC cgDestroyBuffer = NULL;
PFNCGDESTROYCONTEXTPROC cgDestroyContext = NULL;
PFNCGDESTROYEFFECTPROC cgDestroyEffect = NULL;
PFNCGDESTROYOBJPROC cgDestroyObj = NULL;
PFNCGDESTROYPARAMETERPROC cgDestroyParameter = NULL;
PFNCGDESTROYPROGRAMPROC cgDestroyProgram = NULL;
PFNCGDISCONNECTPARAMETERPROC cgDisconnectParameter = NULL;
PFNCGEVALUATEPROGRAMPROC cgEvaluateProgram = NULL;
PFNCGGETANNOTATIONNAMEPROC cgGetAnnotationName = NULL;
PFNCGGETANNOTATIONTYPEPROC cgGetAnnotationType = NULL;
PFNCGGETARRAYDIMENSIONPROC cgGetArrayDimension = NULL;
PFNCGGETARRAYPARAMETERPROC cgGetArrayParameter = NULL;
PFNCGGETARRAYSIZEPROC cgGetArraySize = NULL;
PFNCGGETARRAYTOTALSIZEPROC cgGetArrayTotalSize = NULL;
PFNCGGETARRAYTYPEPROC cgGetArrayType = NULL;
PFNCGGETAUTOCOMPILEPROC cgGetAutoCompile = NULL;
PFNCGGETBEHAVIORPROC cgGetBehavior = NULL;
PFNCGGETBEHAVIORSTRINGPROC cgGetBehaviorString = NULL;
PFNCGGETBOOLANNOTATIONVALUESPROC cgGetBoolAnnotationValues = NULL;
PFNCGGETBOOLSTATEASSIGNMENTVALUESPROC cgGetBoolStateAssignmentValues = NULL;
PFNCGGETBOOLEANANNOTATIONVALUESPROC cgGetBooleanAnnotationValues = NULL;
PFNCGGETBUFFERSIZEPROC cgGetBufferSize = NULL;
PFNCGGETCOMPILERINCLUDECALLBACKPROC cgGetCompilerIncludeCallback = NULL;
PFNCGGETCONNECTEDPARAMETERPROC cgGetConnectedParameter = NULL;
PFNCGGETCONNECTEDSTATEASSIGNMENTPARAMETERPROC cgGetConnectedStateAssignmentParameter = NULL;
PFNCGGETCONNECTEDTOPARAMETERPROC cgGetConnectedToParameter = NULL;
PFNCGGETCONTEXTBEHAVIORPROC cgGetContextBehavior = NULL;
PFNCGGETDEPENDENTANNOTATIONPARAMETERPROC cgGetDependentAnnotationParameter = NULL;
PFNCGGETDEPENDENTPROGRAMARRAYSTATEASSIGNMENTPARAMETERPROC cgGetDependentProgramArrayStateAssignmentParameter = NULL;
PFNCGGETDEPENDENTSTATEASSIGNMENTPARAMETERPROC cgGetDependentStateAssignmentParameter = NULL;
PFNCGGETDOMAINPROC cgGetDomain = NULL;
PFNCGGETDOMAINSTRINGPROC cgGetDomainString = NULL;
PFNCGGETEFFECTCONTEXTPROC cgGetEffectContext = NULL;
PFNCGGETEFFECTNAMEPROC cgGetEffectName = NULL;
PFNCGGETEFFECTPARAMETERBUFFERPROC cgGetEffectParameterBuffer = NULL;
PFNCGGETEFFECTPARAMETERBYSEMANTICPROC cgGetEffectParameterBySemantic = NULL;
PFNCGGETENUMPROC cgGetEnum = NULL;
PFNCGGETENUMSTRINGPROC cgGetEnumString = NULL;
PFNCGGETERRORPROC cgGetError = NULL;
PFNCGGETERRORCALLBACKPROC cgGetErrorCallback = NULL;
PFNCGGETERRORHANDLERPROC cgGetErrorHandler = NULL;
PFNCGGETERRORSTRINGPROC cgGetErrorString = NULL;
PFNCGGETFIRSTDEPENDENTPARAMETERPROC cgGetFirstDependentParameter = NULL;
PFNCGGETFIRSTEFFECTPROC cgGetFirstEffect = NULL;
PFNCGGETFIRSTEFFECTANNOTATIONPROC cgGetFirstEffectAnnotation = NULL;
PFNCGGETFIRSTEFFECTPARAMETERPROC cgGetFirstEffectParameter = NULL;
PFNCGGETFIRSTERRORPROC cgGetFirstError = NULL;
PFNCGGETFIRSTLEAFEFFECTPARAMETERPROC cgGetFirstLeafEffectParameter = NULL;
PFNCGGETFIRSTLEAFPARAMETERPROC cgGetFirstLeafParameter = NULL;
PFNCGGETFIRSTPARAMETERPROC cgGetFirstParameter = NULL;
PFNCGGETFIRSTPARAMETERANNOTATIONPROC cgGetFirstParameterAnnotation = NULL;
PFNCGGETFIRSTPASSPROC cgGetFirstPass = NULL;
PFNCGGETFIRSTPASSANNOTATIONPROC cgGetFirstPassAnnotation = NULL;
PFNCGGETFIRSTPROGRAMPROC cgGetFirstProgram = NULL;
PFNCGGETFIRSTPROGRAMANNOTATIONPROC cgGetFirstProgramAnnotation = NULL;
PFNCGGETFIRSTSAMPLERSTATEPROC cgGetFirstSamplerState = NULL;
PFNCGGETFIRSTSAMPLERSTATEASSIGNMENTPROC cgGetFirstSamplerStateAssignment = NULL;
PFNCGGETFIRSTSTATEPROC cgGetFirstState = NULL;
PFNCGGETFIRSTSTATEASSIGNMENTPROC cgGetFirstStateAssignment = NULL;
PFNCGGETFIRSTSTRUCTPARAMETERPROC cgGetFirstStructParameter = NULL;
PFNCGGETFIRSTTECHNIQUEPROC cgGetFirstTechnique = NULL;
PFNCGGETFIRSTTECHNIQUEANNOTATIONPROC cgGetFirstTechniqueAnnotation = NULL;
PFNCGGETFIRSTUNIFORMBUFFERPARAMETERPROC cgGetFirstUniformBufferParameter = NULL;
PFNCGGETFLOATANNOTATIONVALUESPROC cgGetFloatAnnotationValues = NULL;
PFNCGGETFLOATSTATEASSIGNMENTVALUESPROC cgGetFloatStateAssignmentValues = NULL;
PFNCGGETINTANNOTATIONVALUESPROC cgGetIntAnnotationValues = NULL;
PFNCGGETINTSTATEASSIGNMENTVALUESPROC cgGetIntStateAssignmentValues = NULL;
PFNCGGETLASTERRORSTRINGPROC cgGetLastErrorString = NULL;
PFNCGGETLASTLISTINGPROC cgGetLastListing = NULL;
PFNCGGETLOCKINGPOLICYPROC cgGetLockingPolicy = NULL;
PFNCGGETMATRIXPARAMETERORDERPROC cgGetMatrixParameterOrder = NULL;
PFNCGGETMATRIXPARAMETERDCPROC cgGetMatrixParameterdc = NULL;
PFNCGGETMATRIXPARAMETERDRPROC cgGetMatrixParameterdr = NULL;
PFNCGGETMATRIXPARAMETERFCPROC cgGetMatrixParameterfc = NULL;
PFNCGGETMATRIXPARAMETERFRPROC cgGetMatrixParameterfr = NULL;
PFNCGGETMATRIXPARAMETERICPROC cgGetMatrixParameteric = NULL;
PFNCGGETMATRIXPARAMETERIRPROC cgGetMatrixParameterir = NULL;
PFNCGGETMATRIXSIZEPROC cgGetMatrixSize = NULL;
PFNCGGETNAMEDEFFECTPROC cgGetNamedEffect = NULL;
PFNCGGETNAMEDEFFECTANNOTATIONPROC cgGetNamedEffectAnnotation = NULL;
PFNCGGETNAMEDEFFECTPARAMETERPROC cgGetNamedEffectParameter = NULL;
PFNCGGETNAMEDEFFECTUNIFORMBUFFERPROC cgGetNamedEffectUniformBuffer = NULL;
PFNCGGETNAMEDPARAMETERPROC cgGetNamedParameter = NULL;
PFNCGGETNAMEDPARAMETERANNOTATIONPROC cgGetNamedParameterAnnotation = NULL;
PFNCGGETNAMEDPASSPROC cgGetNamedPass = NULL;
PFNCGGETNAMEDPASSANNOTATIONPROC cgGetNamedPassAnnotation = NULL;
PFNCGGETNAMEDPROGRAMANNOTATIONPROC cgGetNamedProgramAnnotation = NULL;
PFNCGGETNAMEDPROGRAMPARAMETERPROC cgGetNamedProgramParameter = NULL;
PFNCGGETNAMEDPROGRAMUNIFORMBUFFERPROC cgGetNamedProgramUniformBuffer = NULL;
PFNCGGETNAMEDSAMPLERSTATEPROC cgGetNamedSamplerState = NULL;
PFNCGGETNAMEDSAMPLERSTATEASSIGNMENTPROC cgGetNamedSamplerStateAssignment = NULL;
PFNCGGETNAMEDSTATEPROC cgGetNamedState = NULL;
PFNCGGETNAMEDSTATEASSIGNMENTPROC cgGetNamedStateAssignment = NULL;
PFNCGGETNAMEDSTRUCTPARAMETERPROC cgGetNamedStructParameter = NULL;
PFNCGGETNAMEDSUBPARAMETERPROC cgGetNamedSubParameter = NULL;
PFNCGGETNAMEDTECHNIQUEPROC cgGetNamedTechnique = NULL;
PFNCGGETNAMEDTECHNIQUEANNOTATIONPROC cgGetNamedTechniqueAnnotation = NULL;
PFNCGGETNAMEDUNIFORMBUFFERPARAMETERPROC cgGetNamedUniformBufferParameter = NULL;
PFNCGGETNAMEDUSERTYPEPROC cgGetNamedUserType = NULL;
PFNCGGETNEXTANNOTATIONPROC cgGetNextAnnotation = NULL;
PFNCGGETNEXTEFFECTPROC cgGetNextEffect = NULL;
PFNCGGETNEXTLEAFPARAMETERPROC cgGetNextLeafParameter = NULL;
PFNCGGETNEXTPARAMETERPROC cgGetNextParameter = NULL;
PFNCGGETNEXTPASSPROC cgGetNextPass = NULL;
PFNCGGETNEXTPROGRAMPROC cgGetNextProgram = NULL;
PFNCGGETNEXTSTATEPROC cgGetNextState = NULL;
PFNCGGETNEXTSTATEASSIGNMENTPROC cgGetNextStateAssignment = NULL;
PFNCGGETNEXTTECHNIQUEPROC cgGetNextTechnique = NULL;
PFNCGGETNUMCONNECTEDTOPARAMETERSPROC cgGetNumConnectedToParameters = NULL;
PFNCGGETNUMDEPENDENTANNOTATIONPARAMETERSPROC cgGetNumDependentAnnotationParameters = NULL;
PFNCGGETNUMDEPENDENTPROGRAMARRAYSTATEASSIGNMENTPARAMETERSPROC cgGetNumDependentProgramArrayStateAssignmentParameters = NULL;
PFNCGGETNUMDEPENDENTSTATEASSIGNMENTPARAMETERSPROC cgGetNumDependentStateAssignmentParameters = NULL;
PFNCGGETNUMPARENTTYPESPROC cgGetNumParentTypes = NULL;
PFNCGGETNUMPROGRAMDOMAINSPROC cgGetNumProgramDomains = NULL;
PFNCGGETNUMSTATEENUMERANTSPROC cgGetNumStateEnumerants = NULL;
PFNCGGETNUMSUPPORTEDPROFILESPROC cgGetNumSupportedProfiles = NULL;
PFNCGGETNUMUSERTYPESPROC cgGetNumUserTypes = NULL;
PFNCGGETPARAMETERBASERESOURCEPROC cgGetParameterBaseResource = NULL;
PFNCGGETPARAMETERBASETYPEPROC cgGetParameterBaseType = NULL;
PFNCGGETPARAMETERBUFFERINDEXPROC cgGetParameterBufferIndex = NULL;
PFNCGGETPARAMETERBUFFEROFFSETPROC cgGetParameterBufferOffset = NULL;
PFNCGGETPARAMETERCLASSPROC cgGetParameterClass = NULL;
PFNCGGETPARAMETERCLASSENUMPROC cgGetParameterClassEnum = NULL;
PFNCGGETPARAMETERCLASSSTRINGPROC cgGetParameterClassString = NULL;
PFNCGGETPARAMETERCOLUMNSPROC cgGetParameterColumns = NULL;
PFNCGGETPARAMETERCONTEXTPROC cgGetParameterContext = NULL;
PFNCGGETPARAMETERDEFAULTVALUEDCPROC cgGetParameterDefaultValuedc = NULL;
PFNCGGETPARAMETERDEFAULTVALUEDRPROC cgGetParameterDefaultValuedr = NULL;
PFNCGGETPARAMETERDEFAULTVALUEFCPROC cgGetParameterDefaultValuefc = NULL;
PFNCGGETPARAMETERDEFAULTVALUEFRPROC cgGetParameterDefaultValuefr = NULL;
PFNCGGETPARAMETERDEFAULTVALUEICPROC cgGetParameterDefaultValueic = NULL;
PFNCGGETPARAMETERDEFAULTVALUEIRPROC cgGetParameterDefaultValueir = NULL;
PFNCGGETPARAMETERDIRECTIONPROC cgGetParameterDirection = NULL;
PFNCGGETPARAMETEREFFECTPROC cgGetParameterEffect = NULL;
PFNCGGETPARAMETERINDEXPROC cgGetParameterIndex = NULL;
PFNCGGETPARAMETERNAMEPROC cgGetParameterName = NULL;
PFNCGGETPARAMETERNAMEDTYPEPROC cgGetParameterNamedType = NULL;
PFNCGGETPARAMETERORDINALNUMBERPROC cgGetParameterOrdinalNumber = NULL;
PFNCGGETPARAMETERPROGRAMPROC cgGetParameterProgram = NULL;
PFNCGGETPARAMETERRESOURCEPROC cgGetParameterResource = NULL;
PFNCGGETPARAMETERRESOURCEINDEXPROC cgGetParameterResourceIndex = NULL;
PFNCGGETPARAMETERRESOURCENAMEPROC cgGetParameterResourceName = NULL;
PFNCGGETPARAMETERRESOURCESIZEPROC cgGetParameterResourceSize = NULL;
PFNCGGETPARAMETERRESOURCETYPEPROC cgGetParameterResourceType = NULL;
PFNCGGETPARAMETERROWSPROC cgGetParameterRows = NULL;
PFNCGGETPARAMETERSEMANTICPROC cgGetParameterSemantic = NULL;
PFNCGGETPARAMETERSETTINGMODEPROC cgGetParameterSettingMode = NULL;
PFNCGGETPARAMETERTYPEPROC cgGetParameterType = NULL;
PFNCGGETPARAMETERVALUEDCPROC cgGetParameterValuedc = NULL;
PFNCGGETPARAMETERVALUEDRPROC cgGetParameterValuedr = NULL;
PFNCGGETPARAMETERVALUEFCPROC cgGetParameterValuefc = NULL;
PFNCGGETPARAMETERVALUEFRPROC cgGetParameterValuefr = NULL;
PFNCGGETPARAMETERVALUEICPROC cgGetParameterValueic = NULL;
PFNCGGETPARAMETERVALUEIRPROC cgGetParameterValueir = NULL;
PFNCGGETPARAMETERVALUESPROC cgGetParameterValues = NULL;
PFNCGGETPARAMETERVARIABILITYPROC cgGetParameterVariability = NULL;
PFNCGGETPARENTTYPEPROC cgGetParentType = NULL;
PFNCGGETPASSNAMEPROC cgGetPassName = NULL;
PFNCGGETPASSPROGRAMPROC cgGetPassProgram = NULL;
PFNCGGETPASSTECHNIQUEPROC cgGetPassTechnique = NULL;
PFNCGGETPROFILEPROC cgGetProfile = NULL;
PFNCGGETPROFILEDOMAINPROC cgGetProfileDomain = NULL;
PFNCGGETPROFILEPROPERTYPROC cgGetProfileProperty = NULL;
PFNCGGETPROFILESIBLINGPROC cgGetProfileSibling = NULL;
PFNCGGETPROFILESTRINGPROC cgGetProfileString = NULL;
PFNCGGETPROGRAMBUFFERPROC cgGetProgramBuffer = NULL;
PFNCGGETPROGRAMBUFFERMAXINDEXPROC cgGetProgramBufferMaxIndex = NULL;
PFNCGGETPROGRAMBUFFERMAXSIZEPROC cgGetProgramBufferMaxSize = NULL;
PFNCGGETPROGRAMCONTEXTPROC cgGetProgramContext = NULL;
PFNCGGETPROGRAMDOMAINPROC cgGetProgramDomain = NULL;
PFNCGGETPROGRAMDOMAINPROFILEPROC cgGetProgramDomainProfile = NULL;
PFNCGGETPROGRAMDOMAINPROGRAMPROC cgGetProgramDomainProgram = NULL;
PFNCGGETPROGRAMINPUTPROC cgGetProgramInput = NULL;
PFNCGGETPROGRAMOPTIONSPROC cgGetProgramOptions = NULL;
PFNCGGETPROGRAMOUTPUTPROC cgGetProgramOutput = NULL;
PFNCGGETPROGRAMOUTPUTVERTICESPROC cgGetProgramOutputVertices = NULL;
PFNCGGETPROGRAMPROFILEPROC cgGetProgramProfile = NULL;
PFNCGGETPROGRAMSTATEASSIGNMENTVALUEPROC cgGetProgramStateAssignmentValue = NULL;
PFNCGGETPROGRAMSTRINGPROC cgGetProgramString = NULL;
PFNCGGETRESOURCEPROC cgGetResource = NULL;
PFNCGGETRESOURCESTRINGPROC cgGetResourceString = NULL;
PFNCGGETSAMPLERSTATEASSIGNMENTPARAMETERPROC cgGetSamplerStateAssignmentParameter = NULL;
PFNCGGETSAMPLERSTATEASSIGNMENTSTATEPROC cgGetSamplerStateAssignmentState = NULL;
PFNCGGETSAMPLERSTATEASSIGNMENTVALUEPROC cgGetSamplerStateAssignmentValue = NULL;
PFNCGGETSEMANTICCASEPOLICYPROC cgGetSemanticCasePolicy = NULL;
PFNCGGETSTATEASSIGNMENTINDEXPROC cgGetStateAssignmentIndex = NULL;
PFNCGGETSTATEASSIGNMENTPASSPROC cgGetStateAssignmentPass = NULL;
PFNCGGETSTATEASSIGNMENTSTATEPROC cgGetStateAssignmentState = NULL;
PFNCGGETSTATECONTEXTPROC cgGetStateContext = NULL;
PFNCGGETSTATEENUMERANTPROC cgGetStateEnumerant = NULL;
PFNCGGETSTATEENUMERANTNAMEPROC cgGetStateEnumerantName = NULL;
PFNCGGETSTATEENUMERANTVALUEPROC cgGetStateEnumerantValue = NULL;
PFNCGGETSTATELATESTPROFILEPROC cgGetStateLatestProfile = NULL;
PFNCGGETSTATENAMEPROC cgGetStateName = NULL;
PFNCGGETSTATERESETCALLBACKPROC cgGetStateResetCallback = NULL;
PFNCGGETSTATESETCALLBACKPROC cgGetStateSetCallback = NULL;
PFNCGGETSTATETYPEPROC cgGetStateType = NULL;
PFNCGGETSTATEVALIDATECALLBACKPROC cgGetStateValidateCallback = NULL;
PFNCGGETSTRINGPROC cgGetString = NULL;
PFNCGGETSTRINGANNOTATIONVALUEPROC cgGetStringAnnotationValue = NULL;
PFNCGGETSTRINGANNOTATIONVALUESPROC cgGetStringAnnotationValues = NULL;
PFNCGGETSTRINGPARAMETERVALUEPROC cgGetStringParameterValue = NULL;
PFNCGGETSTRINGSTATEASSIGNMENTVALUEPROC cgGetStringStateAssignmentValue = NULL;
PFNCGGETSUPPORTEDPROFILEPROC cgGetSupportedProfile = NULL;
PFNCGGETTECHNIQUEEFFECTPROC cgGetTechniqueEffect = NULL;
PFNCGGETTECHNIQUENAMEPROC cgGetTechniqueName = NULL;
PFNCGGETTEXTURESTATEASSIGNMENTVALUEPROC cgGetTextureStateAssignmentValue = NULL;
PFNCGGETTYPEPROC cgGetType = NULL;
PFNCGGETTYPEBASEPROC cgGetTypeBase = NULL;
PFNCGGETTYPECLASSPROC cgGetTypeClass = NULL;
PFNCGGETTYPESIZESPROC cgGetTypeSizes = NULL;
PFNCGGETTYPESTRINGPROC cgGetTypeString = NULL;
PFNCGGETUNIFORMBUFFERBLOCKNAMEPROC cgGetUniformBufferBlockName = NULL;
PFNCGGETUNIFORMBUFFERPARAMETERPROC cgGetUniformBufferParameter = NULL;
PFNCGGETUSERTYPEPROC cgGetUserType = NULL;
PFNCGISANNOTATIONPROC cgIsAnnotation = NULL;
PFNCGISBUFFERPROC cgIsBuffer = NULL;
PFNCGISCONTEXTPROC cgIsContext = NULL;
PFNCGISEFFECTPROC cgIsEffect = NULL;
PFNCGISINTERFACETYPEPROC cgIsInterfaceType = NULL;
PFNCGISPARAMETERPROC cgIsParameter = NULL;
PFNCGISPARAMETERGLOBALPROC cgIsParameterGlobal = NULL;
PFNCGISPARAMETERREFERENCEDPROC cgIsParameterReferenced = NULL;
PFNCGISPARAMETERUSEDPROC cgIsParameterUsed = NULL;
PFNCGISPARENTTYPEPROC cgIsParentType = NULL;
PFNCGISPASSPROC cgIsPass = NULL;
PFNCGISPROFILESUPPORTEDPROC cgIsProfileSupported = NULL;
PFNCGISPROGRAMPROC cgIsProgram = NULL;
PFNCGISPROGRAMCOMPILEDPROC cgIsProgramCompiled = NULL;
PFNCGISSTATEPROC cgIsState = NULL;
PFNCGISSTATEASSIGNMENTPROC cgIsStateAssignment = NULL;
PFNCGISTECHNIQUEPROC cgIsTechnique = NULL;
PFNCGISTECHNIQUEVALIDATEDPROC cgIsTechniqueValidated = NULL;
PFNCGMAPBUFFERPROC cgMapBuffer = NULL;
PFNCGRESETPASSSTATEPROC cgResetPassState = NULL;
PFNCGSETARRAYSIZEPROC cgSetArraySize = NULL;
PFNCGSETAUTOCOMPILEPROC cgSetAutoCompile = NULL;
PFNCGSETBOOLANNOTATIONPROC cgSetBoolAnnotation = NULL;
PFNCGSETBOOLARRAYSTATEASSIGNMENTPROC cgSetBoolArrayStateAssignment = NULL;
PFNCGSETBOOLSTATEASSIGNMENTPROC cgSetBoolStateAssignment = NULL;
PFNCGSETBUFFERDATAPROC cgSetBufferData = NULL;
PFNCGSETBUFFERSUBDATAPROC cgSetBufferSubData = NULL;
PFNCGSETCOMPILERINCLUDECALLBACKPROC cgSetCompilerIncludeCallback = NULL;
PFNCGSETCOMPILERINCLUDEFILEPROC cgSetCompilerIncludeFile = NULL;
PFNCGSETCOMPILERINCLUDESTRINGPROC cgSetCompilerIncludeString = NULL;
PFNCGSETCONTEXTBEHAVIORPROC cgSetContextBehavior = NULL;
PFNCGSETEFFECTNAMEPROC cgSetEffectName = NULL;
PFNCGSETEFFECTPARAMETERBUFFERPROC cgSetEffectParameterBuffer = NULL;
PFNCGSETERRORCALLBACKPROC cgSetErrorCallback = NULL;
PFNCGSETERRORHANDLERPROC cgSetErrorHandler = NULL;
PFNCGSETFLOATANNOTATIONPROC cgSetFloatAnnotation = NULL;
PFNCGSETFLOATARRAYSTATEASSIGNMENTPROC cgSetFloatArrayStateAssignment = NULL;
PFNCGSETFLOATSTATEASSIGNMENTPROC cgSetFloatStateAssignment = NULL;
PFNCGSETINTANNOTATIONPROC cgSetIntAnnotation = NULL;
PFNCGSETINTARRAYSTATEASSIGNMENTPROC cgSetIntArrayStateAssignment = NULL;
PFNCGSETINTSTATEASSIGNMENTPROC cgSetIntStateAssignment = NULL;
PFNCGSETLASTLISTINGPROC cgSetLastListing = NULL;
PFNCGSETLOCKINGPOLICYPROC cgSetLockingPolicy = NULL;
PFNCGSETMATRIXPARAMETERDCPROC cgSetMatrixParameterdc = NULL;
PFNCGSETMATRIXPARAMETERDRPROC cgSetMatrixParameterdr = NULL;
PFNCGSETMATRIXPARAMETERFCPROC cgSetMatrixParameterfc = NULL;
PFNCGSETMATRIXPARAMETERFRPROC cgSetMatrixParameterfr = NULL;
PFNCGSETMATRIXPARAMETERICPROC cgSetMatrixParameteric = NULL;
PFNCGSETMATRIXPARAMETERIRPROC cgSetMatrixParameterir = NULL;
PFNCGSETMULTIDIMARRAYSIZEPROC cgSetMultiDimArraySize = NULL;
PFNCGSETPARAMETER1DPROC cgSetParameter1d = NULL;
PFNCGSETPARAMETER1DVPROC cgSetParameter1dv = NULL;
PFNCGSETPARAMETER1FPROC cgSetParameter1f = NULL;
PFNCGSETPARAMETER1FVPROC cgSetParameter1fv = NULL;
PFNCGSETPARAMETER1IPROC cgSetParameter1i = NULL;
PFNCGSETPARAMETER1IVPROC cgSetParameter1iv = NULL;
PFNCGSETPARAMETER2DPROC cgSetParameter2d = NULL;
PFNCGSETPARAMETER2DVPROC cgSetParameter2dv = NULL;
PFNCGSETPARAMETER2FPROC cgSetParameter2f = NULL;
PFNCGSETPARAMETER2FVPROC cgSetParameter2fv = NULL;
PFNCGSETPARAMETER2IPROC cgSetParameter2i = NULL;
PFNCGSETPARAMETER2IVPROC cgSetParameter2iv = NULL;
PFNCGSETPARAMETER3DPROC cgSetParameter3d = NULL;
PFNCGSETPARAMETER3DVPROC cgSetParameter3dv = NULL;
PFNCGSETPARAMETER3FPROC cgSetParameter3f = NULL;
PFNCGSETPARAMETER3FVPROC cgSetParameter3fv = NULL;
PFNCGSETPARAMETER3IPROC cgSetParameter3i = NULL;
PFNCGSETPARAMETER3IVPROC cgSetParameter3iv = NULL;
PFNCGSETPARAMETER4DPROC cgSetParameter4d = NULL;
PFNCGSETPARAMETER4DVPROC cgSetParameter4dv = NULL;
PFNCGSETPARAMETER4FPROC cgSetParameter4f = NULL;
PFNCGSETPARAMETER4FVPROC cgSetParameter4fv = NULL;
PFNCGSETPARAMETER4IPROC cgSetParameter4i = NULL;
PFNCGSETPARAMETER4IVPROC cgSetParameter4iv = NULL;
PFNCGSETPARAMETERSEMANTICPROC cgSetParameterSemantic = NULL;
PFNCGSETPARAMETERSETTINGMODEPROC cgSetParameterSettingMode = NULL;
PFNCGSETPARAMETERVALUEDCPROC cgSetParameterValuedc = NULL;
PFNCGSETPARAMETERVALUEDRPROC cgSetParameterValuedr = NULL;
PFNCGSETPARAMETERVALUEFCPROC cgSetParameterValuefc = NULL;
PFNCGSETPARAMETERVALUEFRPROC cgSetParameterValuefr = NULL;
PFNCGSETPARAMETERVALUEICPROC cgSetParameterValueic = NULL;
PFNCGSETPARAMETERVALUEIRPROC cgSetParameterValueir = NULL;
PFNCGSETPARAMETERVARIABILITYPROC cgSetParameterVariability = NULL;
PFNCGSETPASSPROGRAMPARAMETERSPROC cgSetPassProgramParameters = NULL;
PFNCGSETPASSSTATEPROC cgSetPassState = NULL;
PFNCGSETPROGRAMBUFFERPROC cgSetProgramBuffer = NULL;
PFNCGSETPROGRAMOUTPUTVERTICESPROC cgSetProgramOutputVertices = NULL;
PFNCGSETPROGRAMPROFILEPROC cgSetProgramProfile = NULL;
PFNCGSETPROGRAMSTATEASSIGNMENTPROC cgSetProgramStateAssignment = NULL;
PFNCGSETSAMPLERSTATEPROC cgSetSamplerState = NULL;
PFNCGSETSAMPLERSTATEASSIGNMENTPROC cgSetSamplerStateAssignment = NULL;
PFNCGSETSEMANTICCASEPOLICYPROC cgSetSemanticCasePolicy = NULL;
PFNCGSETSTATECALLBACKSPROC cgSetStateCallbacks = NULL;
PFNCGSETSTATELATESTPROFILEPROC cgSetStateLatestProfile = NULL;
PFNCGSETSTRINGANNOTATIONPROC cgSetStringAnnotation = NULL;
PFNCGSETSTRINGPARAMETERVALUEPROC cgSetStringParameterValue = NULL;
PFNCGSETSTRINGSTATEASSIGNMENTPROC cgSetStringStateAssignment = NULL;
PFNCGSETTEXTURESTATEASSIGNMENTPROC cgSetTextureStateAssignment = NULL;
PFNCGSETUNIFORMBUFFERPARAMETERPROC cgSetUniformBufferParameter = NULL;
PFNCGUNMAPBUFFERPROC cgUnmapBuffer = NULL;
PFNCGUPDATEPASSPARAMETERSPROC cgUpdatePassParameters = NULL;
PFNCGUPDATEPROGRAMPARAMETERSPROC cgUpdateProgramParameters = NULL;
PFNCGVALIDATETECHNIQUEPROC cgValidateTechnique = NULL;

/* Implementation */

void ***
lcgVersion1_1_0000()
{
  static void **list[50] =
  {
    (void **) &cgCompileProgram,
    (void **) &cgCopyProgram,
    (void **) &cgCreateContext,
    (void **) &cgCreateProgram,
    (void **) &cgCreateProgramFromFile,
    (void **) &cgDestroyContext,
    (void **) &cgDestroyProgram,
    (void **) &cgGetArrayDimension,
    (void **) &cgGetArrayParameter,
    (void **) &cgGetArraySize,
    (void **) &cgGetError,
    (void **) &cgGetErrorCallback,
    (void **) &cgGetErrorString,
    (void **) &cgGetFirstDependentParameter,
    (void **) &cgGetFirstLeafParameter,
    (void **) &cgGetFirstParameter,
    (void **) &cgGetFirstProgram,
    (void **) &cgGetFirstStructParameter,
    (void **) &cgGetLastListing,
    (void **) &cgGetNamedParameter,
    (void **) &cgGetNextLeafParameter,
    (void **) &cgGetNextParameter,
    (void **) &cgGetNextProgram,
    (void **) &cgGetParameterBaseResource,
    (void **) &cgGetParameterDirection,
    (void **) &cgGetParameterName,
    (void **) &cgGetParameterOrdinalNumber,
    (void **) &cgGetParameterProgram,
    (void **) &cgGetParameterResource,
    (void **) &cgGetParameterResourceIndex,
    (void **) &cgGetParameterSemantic,
    (void **) &cgGetParameterType,
    (void **) &cgGetParameterValues,
    (void **) &cgGetParameterVariability,
    (void **) &cgGetProfile,
    (void **) &cgGetProfileString,
    (void **) &cgGetProgramContext,
    (void **) &cgGetProgramProfile,
    (void **) &cgGetProgramString,
    (void **) &cgGetResource,
    (void **) &cgGetResourceString,
    (void **) &cgGetType,
    (void **) &cgGetTypeString,
    (void **) &cgIsContext,
    (void **) &cgIsParameter,
    (void **) &cgIsParameterReferenced,
    (void **) &cgIsProgram,
    (void **) &cgIsProgramCompiled,
    (void **) &cgSetErrorCallback,
    NULL
  };
  return list;
}

void ***
lcgVersion1_2_0000()
{
  static void **list[53] =
  {
    (void **) &cgConnectParameter,
    (void **) &cgCreateParameter,
    (void **) &cgCreateParameterArray,
    (void **) &cgCreateParameterMultiDimArray,
    (void **) &cgDestroyParameter,
    (void **) &cgDisconnectParameter,
    (void **) &cgGetArrayType,
    (void **) &cgGetConnectedParameter,
    (void **) &cgGetConnectedToParameter,
    (void **) &cgGetEnum,
    (void **) &cgGetEnumString,
    (void **) &cgGetLastErrorString,
    (void **) &cgGetNamedProgramParameter,
    (void **) &cgGetNamedStructParameter,
    (void **) &cgGetNamedUserType,
    (void **) &cgGetNumConnectedToParameters,
    (void **) &cgGetNumParentTypes,
    (void **) &cgGetNumUserTypes,
    (void **) &cgGetParameterContext,
    (void **) &cgGetParameterIndex,
    (void **) &cgGetParameterNamedType,
    (void **) &cgGetParentType,
    (void **) &cgGetString,
    (void **) &cgGetUserType,
    (void **) &cgIsInterfaceType,
    (void **) &cgIsParameterGlobal,
    (void **) &cgIsParentType,
    (void **) &cgSetArraySize,
    (void **) &cgSetAutoCompile,
    (void **) &cgSetMatrixParameterdc,
    (void **) &cgSetMatrixParameterdr,
    (void **) &cgSetMatrixParameterfc,
    (void **) &cgSetMatrixParameterfr,
    (void **) &cgSetMultiDimArraySize,
    (void **) &cgSetParameter1d,
    (void **) &cgSetParameter1dv,
    (void **) &cgSetParameter1f,
    (void **) &cgSetParameter1fv,
    (void **) &cgSetParameter2d,
    (void **) &cgSetParameter2dv,
    (void **) &cgSetParameter2f,
    (void **) &cgSetParameter2fv,
    (void **) &cgSetParameter3d,
    (void **) &cgSetParameter3dv,
    (void **) &cgSetParameter3f,
    (void **) &cgSetParameter3fv,
    (void **) &cgSetParameter4d,
    (void **) &cgSetParameter4dv,
    (void **) &cgSetParameter4f,
    (void **) &cgSetParameter4fv,
    (void **) &cgSetParameterSemantic,
    (void **) &cgSetParameterVariability,
    NULL
  };
  return list;
}

void ***
lcgVersion1_4_0000()
{
  static void **list[133] =
  {
    (void **) &cgAddStateEnumerant,
    (void **) &cgCallStateResetCallback,
    (void **) &cgCallStateSetCallback,
    (void **) &cgCallStateValidateCallback,
    (void **) &cgCreateArraySamplerState,
    (void **) &cgCreateArrayState,
    (void **) &cgCreateEffect,
    (void **) &cgCreateEffectFromFile,
    (void **) &cgCreateProgramFromEffect,
    (void **) &cgCreateSamplerState,
    (void **) &cgCreateState,
    (void **) &cgDestroyEffect,
    (void **) &cgEvaluateProgram,
    (void **) &cgGetAnnotationName,
    (void **) &cgGetAnnotationType,
    (void **) &cgGetArrayTotalSize,
    (void **) &cgGetAutoCompile,
    (void **) &cgGetBoolStateAssignmentValues,
    (void **) &cgGetBooleanAnnotationValues,
    (void **) &cgGetDependentAnnotationParameter,
    (void **) &cgGetDependentStateAssignmentParameter,
    (void **) &cgGetEffectContext,
    (void **) &cgGetEffectParameterBySemantic,
    (void **) &cgGetErrorHandler,
    (void **) &cgGetFirstEffect,
    (void **) &cgGetFirstEffectParameter,
    (void **) &cgGetFirstError,
    (void **) &cgGetFirstLeafEffectParameter,
    (void **) &cgGetFirstParameterAnnotation,
    (void **) &cgGetFirstPass,
    (void **) &cgGetFirstPassAnnotation,
    (void **) &cgGetFirstProgramAnnotation,
    (void **) &cgGetFirstSamplerState,
    (void **) &cgGetFirstSamplerStateAssignment,
    (void **) &cgGetFirstState,
    (void **) &cgGetFirstStateAssignment,
    (void **) &cgGetFirstTechnique,
    (void **) &cgGetFirstTechniqueAnnotation,
    (void **) &cgGetFloatAnnotationValues,
    (void **) &cgGetFloatStateAssignmentValues,
    (void **) &cgGetIntAnnotationValues,
    (void **) &cgGetIntStateAssignmentValues,
    (void **) &cgGetMatrixParameterdc,
    (void **) &cgGetMatrixParameterdr,
    (void **) &cgGetMatrixParameterfc,
    (void **) &cgGetMatrixParameterfr,
    (void **) &cgGetMatrixParameteric,
    (void **) &cgGetMatrixParameterir,
    (void **) &cgGetNamedEffectParameter,
    (void **) &cgGetNamedParameterAnnotation,
    (void **) &cgGetNamedPass,
    (void **) &cgGetNamedPassAnnotation,
    (void **) &cgGetNamedProgramAnnotation,
    (void **) &cgGetNamedSamplerState,
    (void **) &cgGetNamedSamplerStateAssignment,
    (void **) &cgGetNamedState,
    (void **) &cgGetNamedStateAssignment,
    (void **) &cgGetNamedTechnique,
    (void **) &cgGetNamedTechniqueAnnotation,
    (void **) &cgGetNextAnnotation,
    (void **) &cgGetNextEffect,
    (void **) &cgGetNextPass,
    (void **) &cgGetNextState,
    (void **) &cgGetNextStateAssignment,
    (void **) &cgGetNextTechnique,
    (void **) &cgGetNumDependentAnnotationParameters,
    (void **) &cgGetNumDependentStateAssignmentParameters,
    (void **) &cgGetParameterBaseType,
    (void **) &cgGetParameterClass,
    (void **) &cgGetParameterColumns,
    (void **) &cgGetParameterRows,
    (void **) &cgGetParameterValuedc,
    (void **) &cgGetParameterValuedr,
    (void **) &cgGetParameterValuefc,
    (void **) &cgGetParameterValuefr,
    (void **) &cgGetParameterValueic,
    (void **) &cgGetParameterValueir,
    (void **) &cgGetPassName,
    (void **) &cgGetPassTechnique,
    (void **) &cgGetProgramOptions,
    (void **) &cgGetProgramStateAssignmentValue,
    (void **) &cgGetSamplerStateAssignmentParameter,
    (void **) &cgGetSamplerStateAssignmentState,
    (void **) &cgGetSamplerStateAssignmentValue,
    (void **) &cgGetStateAssignmentIndex,
    (void **) &cgGetStateAssignmentPass,
    (void **) &cgGetStateAssignmentState,
    (void **) &cgGetStateName,
    (void **) &cgGetStateResetCallback,
    (void **) &cgGetStateSetCallback,
    (void **) &cgGetStateType,
    (void **) &cgGetStateValidateCallback,
    (void **) &cgGetStringAnnotationValue,
    (void **) &cgGetStringParameterValue,
    (void **) &cgGetStringStateAssignmentValue,
    (void **) &cgGetTechniqueEffect,
    (void **) &cgGetTechniqueName,
    (void **) &cgGetTextureStateAssignmentValue,
    (void **) &cgIsAnnotation,
    (void **) &cgIsEffect,
    (void **) &cgIsParameterUsed,
    (void **) &cgIsPass,
    (void **) &cgIsState,
    (void **) &cgIsStateAssignment,
    (void **) &cgIsTechnique,
    (void **) &cgIsTechniqueValidated,
    (void **) &cgResetPassState,
    (void **) &cgSetErrorHandler,
    (void **) &cgSetLastListing,
    (void **) &cgSetMatrixParameteric,
    (void **) &cgSetMatrixParameterir,
    (void **) &cgSetParameter1i,
    (void **) &cgSetParameter1iv,
    (void **) &cgSetParameter2i,
    (void **) &cgSetParameter2iv,
    (void **) &cgSetParameter3i,
    (void **) &cgSetParameter3iv,
    (void **) &cgSetParameter4i,
    (void **) &cgSetParameter4iv,
    (void **) &cgSetParameterValuedc,
    (void **) &cgSetParameterValuedr,
    (void **) &cgSetParameterValuefc,
    (void **) &cgSetParameterValuefr,
    (void **) &cgSetParameterValueic,
    (void **) &cgSetParameterValueir,
    (void **) &cgSetPassProgramParameters,
    (void **) &cgSetPassState,
    (void **) &cgSetProgramProfile,
    (void **) &cgSetSamplerState,
    (void **) &cgSetStateCallbacks,
    (void **) &cgSetStringParameterValue,
    (void **) &cgValidateTechnique,
    NULL
  };
  return list;
}

void ***
lcgVersion1_5_0000()
{
  static void **list[34] =
  {
    (void **) &cgCreateEffectParameter,
    (void **) &cgCreateParameterAnnotation,
    (void **) &cgCreatePass,
    (void **) &cgCreatePassAnnotation,
    (void **) &cgCreateProgramAnnotation,
    (void **) &cgCreateSamplerStateAssignment,
    (void **) &cgCreateStateAssignment,
    (void **) &cgCreateTechnique,
    (void **) &cgCreateTechniqueAnnotation,
    (void **) &cgGetEffectName,
    (void **) &cgGetMatrixSize,
    (void **) &cgGetNamedEffect,
    (void **) &cgGetParameterEffect,
    (void **) &cgGetStateEnumerantName,
    (void **) &cgGetStateEnumerantValue,
    (void **) &cgGetTypeBase,
    (void **) &cgGetTypeClass,
    (void **) &cgGetTypeSizes,
    (void **) &cgSetBoolAnnotation,
    (void **) &cgSetBoolArrayStateAssignment,
    (void **) &cgSetBoolStateAssignment,
    (void **) &cgSetEffectName,
    (void **) &cgSetFloatAnnotation,
    (void **) &cgSetFloatArrayStateAssignment,
    (void **) &cgSetFloatStateAssignment,
    (void **) &cgSetIntAnnotation,
    (void **) &cgSetIntArrayStateAssignment,
    (void **) &cgSetIntStateAssignment,
    (void **) &cgSetProgramStateAssignment,
    (void **) &cgSetSamplerStateAssignment,
    (void **) &cgSetStringAnnotation,
    (void **) &cgSetStringStateAssignment,
    (void **) &cgSetTextureStateAssignment,
    NULL
  };
  return list;
}

void ***
lcgVersion1_5_0001()
{
  static void **list[16] =
  {
    (void **) &cgCombinePrograms,
    (void **) &cgCombinePrograms2,
    (void **) &cgCombinePrograms3,
    (void **) &cgCreateEffectAnnotation,
    (void **) &cgCreateEffectParameterArray,
    (void **) &cgCreateEffectParameterMultiDimArray,
    (void **) &cgCreateStateAssignmentIndex,
    (void **) &cgGetBoolAnnotationValues,
    (void **) &cgGetFirstEffectAnnotation,
    (void **) &cgGetNamedEffectAnnotation,
    (void **) &cgGetNamedSubParameter,
    (void **) &cgGetNumProgramDomains,
    (void **) &cgGetProfileDomain,
    (void **) &cgGetProgramDomainProfile,
    (void **) &cgGetStateContext,
    NULL
  };
  return list;
}

void ***
lcgVersion2_0_0000()
{
  static void **list[31] =
  {
    (void **) &cgCopyEffect,
    (void **) &cgCreateBuffer,
    (void **) &cgCreateObj,
    (void **) &cgCreateObjFromFile,
    (void **) &cgDestroyBuffer,
    (void **) &cgDestroyObj,
    (void **) &cgGetBufferSize,
    (void **) &cgGetConnectedStateAssignmentParameter,
    (void **) &cgGetLockingPolicy,
    (void **) &cgGetParameterBufferIndex,
    (void **) &cgGetParameterBufferOffset,
    (void **) &cgGetParameterResourceSize,
    (void **) &cgGetParameterResourceType,
    (void **) &cgGetParameterSettingMode,
    (void **) &cgGetProgramBuffer,
    (void **) &cgGetProgramBufferMaxIndex,
    (void **) &cgGetProgramBufferMaxSize,
    (void **) &cgGetProgramInput,
    (void **) &cgGetProgramOutput,
    (void **) &cgGetSemanticCasePolicy,
    (void **) &cgGetStringAnnotationValues,
    (void **) &cgMapBuffer,
    (void **) &cgSetBufferData,
    (void **) &cgSetBufferSubData,
    (void **) &cgSetLockingPolicy,
    (void **) &cgSetParameterSettingMode,
    (void **) &cgSetProgramBuffer,
    (void **) &cgSetSemanticCasePolicy,
    (void **) &cgUnmapBuffer,
    (void **) &cgUpdateProgramParameters,
    NULL
  };
  return list;
}

void ***
lcgVersion2_1_0000()
{
  static void **list[15] =
  {
    (void **) &cgGetCompilerIncludeCallback,
    (void **) &cgGetParameterDefaultValuedc,
    (void **) &cgGetParameterDefaultValuedr,
    (void **) &cgGetParameterDefaultValuefc,
    (void **) &cgGetParameterDefaultValuefr,
    (void **) &cgGetParameterDefaultValueic,
    (void **) &cgGetParameterDefaultValueir,
    (void **) &cgGetParameterResourceName,
    (void **) &cgGetPassProgram,
    (void **) &cgGetProgramDomainProgram,
    (void **) &cgSetCompilerIncludeCallback,
    (void **) &cgSetCompilerIncludeFile,
    (void **) &cgSetCompilerIncludeString,
    (void **) &cgUpdatePassParameters,
    NULL
  };
  return list;
}

void ***
lcgVersion2_2_0000()
{
  static void **list[15] =
  {
    (void **) &cgGetDomain,
    (void **) &cgGetDomainString,
    (void **) &cgGetMatrixParameterOrder,
    (void **) &cgGetNumStateEnumerants,
    (void **) &cgGetNumSupportedProfiles,
    (void **) &cgGetParameterClassEnum,
    (void **) &cgGetParameterClassString,
    (void **) &cgGetProfileProperty,
    (void **) &cgGetProgramDomain,
    (void **) &cgGetStateEnumerant,
    (void **) &cgGetStateLatestProfile,
    (void **) &cgGetSupportedProfile,
    (void **) &cgIsProfileSupported,
    (void **) &cgSetStateLatestProfile,
    NULL
  };
  return list;
}

void ***
lcgVersion3_0_0000()
{
  static void **list[9] =
  {
    (void **) &cgGetBehavior,
    (void **) &cgGetBehaviorString,
    (void **) &cgGetContextBehavior,
    (void **) &cgGetDependentProgramArrayStateAssignmentParameter,
    (void **) &cgGetEffectParameterBuffer,
    (void **) &cgGetNumDependentProgramArrayStateAssignmentParameters,
    (void **) &cgSetContextBehavior,
    (void **) &cgSetEffectParameterBuffer,
    NULL
  };
  return list;
}

void ***
lcgVersion3_0_0005()
{
  static void **list[3] =
  {
    (void **) &cgCombinePrograms4,
    (void **) &cgCombinePrograms5,
    NULL
  };
  return list;
}

void ***
lcgVersion3_1_0000()
{
  static void **list[12] =
  {
    (void **) &cgGetFirstUniformBufferParameter,
    (void **) &cgGetNamedEffectUniformBuffer,
    (void **) &cgGetNamedProgramUniformBuffer,
    (void **) &cgGetNamedUniformBufferParameter,
    (void **) &cgGetProfileSibling,
    (void **) &cgGetProgramOutputVertices,
    (void **) &cgGetUniformBufferBlockName,
    (void **) &cgGetUniformBufferParameter,
    (void **) &cgIsBuffer,
    (void **) &cgSetProgramOutputVertices,
    (void **) &cgSetUniformBufferParameter,
    NULL
  };
  return list;
}

LcgHandle lcgHandle = NULL;

int
lcgInit(const char *filename)
{
  lcgHandle = lcgLoadLibrary(filename);
  if (!lcgHandle)
    return 0;

  cgAddStateEnumerant = (PFNCGADDSTATEENUMERANTPROC) lcgGetProcAddress(lcgHandle, "cgAddStateEnumerant");
  cgCallStateResetCallback = (PFNCGCALLSTATERESETCALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgCallStateResetCallback");
  cgCallStateSetCallback = (PFNCGCALLSTATESETCALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgCallStateSetCallback");
  cgCallStateValidateCallback = (PFNCGCALLSTATEVALIDATECALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgCallStateValidateCallback");
  cgCombinePrograms = (PFNCGCOMBINEPROGRAMSPROC) lcgGetProcAddress(lcgHandle, "cgCombinePrograms");
  cgCombinePrograms2 = (PFNCGCOMBINEPROGRAMS2PROC) lcgGetProcAddress(lcgHandle, "cgCombinePrograms2");
  cgCombinePrograms3 = (PFNCGCOMBINEPROGRAMS3PROC) lcgGetProcAddress(lcgHandle, "cgCombinePrograms3");
  cgCombinePrograms4 = (PFNCGCOMBINEPROGRAMS4PROC) lcgGetProcAddress(lcgHandle, "cgCombinePrograms4");
  cgCombinePrograms5 = (PFNCGCOMBINEPROGRAMS5PROC) lcgGetProcAddress(lcgHandle, "cgCombinePrograms5");
  cgCompileProgram = (PFNCGCOMPILEPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgCompileProgram");
  cgConnectParameter = (PFNCGCONNECTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgConnectParameter");
  cgCopyEffect = (PFNCGCOPYEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgCopyEffect");
  cgCopyProgram = (PFNCGCOPYPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgCopyProgram");
  cgCreateArraySamplerState = (PFNCGCREATEARRAYSAMPLERSTATEPROC) lcgGetProcAddress(lcgHandle, "cgCreateArraySamplerState");
  cgCreateArrayState = (PFNCGCREATEARRAYSTATEPROC) lcgGetProcAddress(lcgHandle, "cgCreateArrayState");
  cgCreateBuffer = (PFNCGCREATEBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgCreateBuffer");
  cgCreateContext = (PFNCGCREATECONTEXTPROC) lcgGetProcAddress(lcgHandle, "cgCreateContext");
  cgCreateEffect = (PFNCGCREATEEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgCreateEffect");
  cgCreateEffectAnnotation = (PFNCGCREATEEFFECTANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgCreateEffectAnnotation");
  cgCreateEffectFromFile = (PFNCGCREATEEFFECTFROMFILEPROC) lcgGetProcAddress(lcgHandle, "cgCreateEffectFromFile");
  cgCreateEffectParameter = (PFNCGCREATEEFFECTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgCreateEffectParameter");
  cgCreateEffectParameterArray = (PFNCGCREATEEFFECTPARAMETERARRAYPROC) lcgGetProcAddress(lcgHandle, "cgCreateEffectParameterArray");
  cgCreateEffectParameterMultiDimArray = (PFNCGCREATEEFFECTPARAMETERMULTIDIMARRAYPROC) lcgGetProcAddress(lcgHandle, "cgCreateEffectParameterMultiDimArray");
  cgCreateObj = (PFNCGCREATEOBJPROC) lcgGetProcAddress(lcgHandle, "cgCreateObj");
  cgCreateObjFromFile = (PFNCGCREATEOBJFROMFILEPROC) lcgGetProcAddress(lcgHandle, "cgCreateObjFromFile");
  cgCreateParameter = (PFNCGCREATEPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgCreateParameter");
  cgCreateParameterAnnotation = (PFNCGCREATEPARAMETERANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgCreateParameterAnnotation");
  cgCreateParameterArray = (PFNCGCREATEPARAMETERARRAYPROC) lcgGetProcAddress(lcgHandle, "cgCreateParameterArray");
  cgCreateParameterMultiDimArray = (PFNCGCREATEPARAMETERMULTIDIMARRAYPROC) lcgGetProcAddress(lcgHandle, "cgCreateParameterMultiDimArray");
  cgCreatePass = (PFNCGCREATEPASSPROC) lcgGetProcAddress(lcgHandle, "cgCreatePass");
  cgCreatePassAnnotation = (PFNCGCREATEPASSANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgCreatePassAnnotation");
  cgCreateProgram = (PFNCGCREATEPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgCreateProgram");
  cgCreateProgramAnnotation = (PFNCGCREATEPROGRAMANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgCreateProgramAnnotation");
  cgCreateProgramFromEffect = (PFNCGCREATEPROGRAMFROMEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgCreateProgramFromEffect");
  cgCreateProgramFromFile = (PFNCGCREATEPROGRAMFROMFILEPROC) lcgGetProcAddress(lcgHandle, "cgCreateProgramFromFile");
  cgCreateSamplerState = (PFNCGCREATESAMPLERSTATEPROC) lcgGetProcAddress(lcgHandle, "cgCreateSamplerState");
  cgCreateSamplerStateAssignment = (PFNCGCREATESAMPLERSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgCreateSamplerStateAssignment");
  cgCreateState = (PFNCGCREATESTATEPROC) lcgGetProcAddress(lcgHandle, "cgCreateState");
  cgCreateStateAssignment = (PFNCGCREATESTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgCreateStateAssignment");
  cgCreateStateAssignmentIndex = (PFNCGCREATESTATEASSIGNMENTINDEXPROC) lcgGetProcAddress(lcgHandle, "cgCreateStateAssignmentIndex");
  cgCreateTechnique = (PFNCGCREATETECHNIQUEPROC) lcgGetProcAddress(lcgHandle, "cgCreateTechnique");
  cgCreateTechniqueAnnotation = (PFNCGCREATETECHNIQUEANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgCreateTechniqueAnnotation");
  cgDestroyBuffer = (PFNCGDESTROYBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgDestroyBuffer");
  cgDestroyContext = (PFNCGDESTROYCONTEXTPROC) lcgGetProcAddress(lcgHandle, "cgDestroyContext");
  cgDestroyEffect = (PFNCGDESTROYEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgDestroyEffect");
  cgDestroyObj = (PFNCGDESTROYOBJPROC) lcgGetProcAddress(lcgHandle, "cgDestroyObj");
  cgDestroyParameter = (PFNCGDESTROYPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgDestroyParameter");
  cgDestroyProgram = (PFNCGDESTROYPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgDestroyProgram");
  cgDisconnectParameter = (PFNCGDISCONNECTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgDisconnectParameter");
  cgEvaluateProgram = (PFNCGEVALUATEPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgEvaluateProgram");
  cgGetAnnotationName = (PFNCGGETANNOTATIONNAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetAnnotationName");
  cgGetAnnotationType = (PFNCGGETANNOTATIONTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetAnnotationType");
  cgGetArrayDimension = (PFNCGGETARRAYDIMENSIONPROC) lcgGetProcAddress(lcgHandle, "cgGetArrayDimension");
  cgGetArrayParameter = (PFNCGGETARRAYPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetArrayParameter");
  cgGetArraySize = (PFNCGGETARRAYSIZEPROC) lcgGetProcAddress(lcgHandle, "cgGetArraySize");
  cgGetArrayTotalSize = (PFNCGGETARRAYTOTALSIZEPROC) lcgGetProcAddress(lcgHandle, "cgGetArrayTotalSize");
  cgGetArrayType = (PFNCGGETARRAYTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetArrayType");
  cgGetAutoCompile = (PFNCGGETAUTOCOMPILEPROC) lcgGetProcAddress(lcgHandle, "cgGetAutoCompile");
  cgGetBehavior = (PFNCGGETBEHAVIORPROC) lcgGetProcAddress(lcgHandle, "cgGetBehavior");
  cgGetBehaviorString = (PFNCGGETBEHAVIORSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetBehaviorString");
  cgGetBoolAnnotationValues = (PFNCGGETBOOLANNOTATIONVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetBoolAnnotationValues");
  cgGetBoolStateAssignmentValues = (PFNCGGETBOOLSTATEASSIGNMENTVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetBoolStateAssignmentValues");
  cgGetBooleanAnnotationValues = (PFNCGGETBOOLEANANNOTATIONVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetBooleanAnnotationValues");
  cgGetBufferSize = (PFNCGGETBUFFERSIZEPROC) lcgGetProcAddress(lcgHandle, "cgGetBufferSize");
  cgGetCompilerIncludeCallback = (PFNCGGETCOMPILERINCLUDECALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgGetCompilerIncludeCallback");
  cgGetConnectedParameter = (PFNCGGETCONNECTEDPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetConnectedParameter");
  cgGetConnectedStateAssignmentParameter = (PFNCGGETCONNECTEDSTATEASSIGNMENTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetConnectedStateAssignmentParameter");
  cgGetConnectedToParameter = (PFNCGGETCONNECTEDTOPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetConnectedToParameter");
  cgGetContextBehavior = (PFNCGGETCONTEXTBEHAVIORPROC) lcgGetProcAddress(lcgHandle, "cgGetContextBehavior");
  cgGetDependentAnnotationParameter = (PFNCGGETDEPENDENTANNOTATIONPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetDependentAnnotationParameter");
  cgGetDependentProgramArrayStateAssignmentParameter = (PFNCGGETDEPENDENTPROGRAMARRAYSTATEASSIGNMENTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetDependentProgramArrayStateAssignmentParameter");
  cgGetDependentStateAssignmentParameter = (PFNCGGETDEPENDENTSTATEASSIGNMENTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetDependentStateAssignmentParameter");
  cgGetDomain = (PFNCGGETDOMAINPROC) lcgGetProcAddress(lcgHandle, "cgGetDomain");
  cgGetDomainString = (PFNCGGETDOMAINSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetDomainString");
  cgGetEffectContext = (PFNCGGETEFFECTCONTEXTPROC) lcgGetProcAddress(lcgHandle, "cgGetEffectContext");
  cgGetEffectName = (PFNCGGETEFFECTNAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetEffectName");
  cgGetEffectParameterBuffer = (PFNCGGETEFFECTPARAMETERBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgGetEffectParameterBuffer");
  cgGetEffectParameterBySemantic = (PFNCGGETEFFECTPARAMETERBYSEMANTICPROC) lcgGetProcAddress(lcgHandle, "cgGetEffectParameterBySemantic");
  cgGetEnum = (PFNCGGETENUMPROC) lcgGetProcAddress(lcgHandle, "cgGetEnum");
  cgGetEnumString = (PFNCGGETENUMSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetEnumString");
  cgGetError = (PFNCGGETERRORPROC) lcgGetProcAddress(lcgHandle, "cgGetError");
  cgGetErrorCallback = (PFNCGGETERRORCALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgGetErrorCallback");
  cgGetErrorHandler = (PFNCGGETERRORHANDLERPROC) lcgGetProcAddress(lcgHandle, "cgGetErrorHandler");
  cgGetErrorString = (PFNCGGETERRORSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetErrorString");
  cgGetFirstDependentParameter = (PFNCGGETFIRSTDEPENDENTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstDependentParameter");
  cgGetFirstEffect = (PFNCGGETFIRSTEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstEffect");
  cgGetFirstEffectAnnotation = (PFNCGGETFIRSTEFFECTANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstEffectAnnotation");
  cgGetFirstEffectParameter = (PFNCGGETFIRSTEFFECTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstEffectParameter");
  cgGetFirstError = (PFNCGGETFIRSTERRORPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstError");
  cgGetFirstLeafEffectParameter = (PFNCGGETFIRSTLEAFEFFECTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstLeafEffectParameter");
  cgGetFirstLeafParameter = (PFNCGGETFIRSTLEAFPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstLeafParameter");
  cgGetFirstParameter = (PFNCGGETFIRSTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstParameter");
  cgGetFirstParameterAnnotation = (PFNCGGETFIRSTPARAMETERANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstParameterAnnotation");
  cgGetFirstPass = (PFNCGGETFIRSTPASSPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstPass");
  cgGetFirstPassAnnotation = (PFNCGGETFIRSTPASSANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstPassAnnotation");
  cgGetFirstProgram = (PFNCGGETFIRSTPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstProgram");
  cgGetFirstProgramAnnotation = (PFNCGGETFIRSTPROGRAMANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstProgramAnnotation");
  cgGetFirstSamplerState = (PFNCGGETFIRSTSAMPLERSTATEPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstSamplerState");
  cgGetFirstSamplerStateAssignment = (PFNCGGETFIRSTSAMPLERSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstSamplerStateAssignment");
  cgGetFirstState = (PFNCGGETFIRSTSTATEPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstState");
  cgGetFirstStateAssignment = (PFNCGGETFIRSTSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstStateAssignment");
  cgGetFirstStructParameter = (PFNCGGETFIRSTSTRUCTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstStructParameter");
  cgGetFirstTechnique = (PFNCGGETFIRSTTECHNIQUEPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstTechnique");
  cgGetFirstTechniqueAnnotation = (PFNCGGETFIRSTTECHNIQUEANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstTechniqueAnnotation");
  cgGetFirstUniformBufferParameter = (PFNCGGETFIRSTUNIFORMBUFFERPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetFirstUniformBufferParameter");
  cgGetFloatAnnotationValues = (PFNCGGETFLOATANNOTATIONVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetFloatAnnotationValues");
  cgGetFloatStateAssignmentValues = (PFNCGGETFLOATSTATEASSIGNMENTVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetFloatStateAssignmentValues");
  cgGetIntAnnotationValues = (PFNCGGETINTANNOTATIONVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetIntAnnotationValues");
  cgGetIntStateAssignmentValues = (PFNCGGETINTSTATEASSIGNMENTVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetIntStateAssignmentValues");
  cgGetLastErrorString = (PFNCGGETLASTERRORSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetLastErrorString");
  cgGetLastListing = (PFNCGGETLASTLISTINGPROC) lcgGetProcAddress(lcgHandle, "cgGetLastListing");
  cgGetLockingPolicy = (PFNCGGETLOCKINGPOLICYPROC) lcgGetProcAddress(lcgHandle, "cgGetLockingPolicy");
  cgGetMatrixParameterOrder = (PFNCGGETMATRIXPARAMETERORDERPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixParameterOrder");
  cgGetMatrixParameterdc = (PFNCGGETMATRIXPARAMETERDCPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixParameterdc");
  cgGetMatrixParameterdr = (PFNCGGETMATRIXPARAMETERDRPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixParameterdr");
  cgGetMatrixParameterfc = (PFNCGGETMATRIXPARAMETERFCPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixParameterfc");
  cgGetMatrixParameterfr = (PFNCGGETMATRIXPARAMETERFRPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixParameterfr");
  cgGetMatrixParameteric = (PFNCGGETMATRIXPARAMETERICPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixParameteric");
  cgGetMatrixParameterir = (PFNCGGETMATRIXPARAMETERIRPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixParameterir");
  cgGetMatrixSize = (PFNCGGETMATRIXSIZEPROC) lcgGetProcAddress(lcgHandle, "cgGetMatrixSize");
  cgGetNamedEffect = (PFNCGGETNAMEDEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedEffect");
  cgGetNamedEffectAnnotation = (PFNCGGETNAMEDEFFECTANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedEffectAnnotation");
  cgGetNamedEffectParameter = (PFNCGGETNAMEDEFFECTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedEffectParameter");
  cgGetNamedEffectUniformBuffer = (PFNCGGETNAMEDEFFECTUNIFORMBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedEffectUniformBuffer");
  cgGetNamedParameter = (PFNCGGETNAMEDPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedParameter");
  cgGetNamedParameterAnnotation = (PFNCGGETNAMEDPARAMETERANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedParameterAnnotation");
  cgGetNamedPass = (PFNCGGETNAMEDPASSPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedPass");
  cgGetNamedPassAnnotation = (PFNCGGETNAMEDPASSANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedPassAnnotation");
  cgGetNamedProgramAnnotation = (PFNCGGETNAMEDPROGRAMANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedProgramAnnotation");
  cgGetNamedProgramParameter = (PFNCGGETNAMEDPROGRAMPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedProgramParameter");
  cgGetNamedProgramUniformBuffer = (PFNCGGETNAMEDPROGRAMUNIFORMBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedProgramUniformBuffer");
  cgGetNamedSamplerState = (PFNCGGETNAMEDSAMPLERSTATEPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedSamplerState");
  cgGetNamedSamplerStateAssignment = (PFNCGGETNAMEDSAMPLERSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedSamplerStateAssignment");
  cgGetNamedState = (PFNCGGETNAMEDSTATEPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedState");
  cgGetNamedStateAssignment = (PFNCGGETNAMEDSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedStateAssignment");
  cgGetNamedStructParameter = (PFNCGGETNAMEDSTRUCTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedStructParameter");
  cgGetNamedSubParameter = (PFNCGGETNAMEDSUBPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedSubParameter");
  cgGetNamedTechnique = (PFNCGGETNAMEDTECHNIQUEPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedTechnique");
  cgGetNamedTechniqueAnnotation = (PFNCGGETNAMEDTECHNIQUEANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedTechniqueAnnotation");
  cgGetNamedUniformBufferParameter = (PFNCGGETNAMEDUNIFORMBUFFERPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedUniformBufferParameter");
  cgGetNamedUserType = (PFNCGGETNAMEDUSERTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetNamedUserType");
  cgGetNextAnnotation = (PFNCGGETNEXTANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgGetNextAnnotation");
  cgGetNextEffect = (PFNCGGETNEXTEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgGetNextEffect");
  cgGetNextLeafParameter = (PFNCGGETNEXTLEAFPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNextLeafParameter");
  cgGetNextParameter = (PFNCGGETNEXTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetNextParameter");
  cgGetNextPass = (PFNCGGETNEXTPASSPROC) lcgGetProcAddress(lcgHandle, "cgGetNextPass");
  cgGetNextProgram = (PFNCGGETNEXTPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgGetNextProgram");
  cgGetNextState = (PFNCGGETNEXTSTATEPROC) lcgGetProcAddress(lcgHandle, "cgGetNextState");
  cgGetNextStateAssignment = (PFNCGGETNEXTSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgGetNextStateAssignment");
  cgGetNextTechnique = (PFNCGGETNEXTTECHNIQUEPROC) lcgGetProcAddress(lcgHandle, "cgGetNextTechnique");
  cgGetNumConnectedToParameters = (PFNCGGETNUMCONNECTEDTOPARAMETERSPROC) lcgGetProcAddress(lcgHandle, "cgGetNumConnectedToParameters");
  cgGetNumDependentAnnotationParameters = (PFNCGGETNUMDEPENDENTANNOTATIONPARAMETERSPROC) lcgGetProcAddress(lcgHandle, "cgGetNumDependentAnnotationParameters");
  cgGetNumDependentProgramArrayStateAssignmentParameters = (PFNCGGETNUMDEPENDENTPROGRAMARRAYSTATEASSIGNMENTPARAMETERSPROC) lcgGetProcAddress(lcgHandle, "cgGetNumDependentProgramArrayStateAssignmentParameters");
  cgGetNumDependentStateAssignmentParameters = (PFNCGGETNUMDEPENDENTSTATEASSIGNMENTPARAMETERSPROC) lcgGetProcAddress(lcgHandle, "cgGetNumDependentStateAssignmentParameters");
  cgGetNumParentTypes = (PFNCGGETNUMPARENTTYPESPROC) lcgGetProcAddress(lcgHandle, "cgGetNumParentTypes");
  cgGetNumProgramDomains = (PFNCGGETNUMPROGRAMDOMAINSPROC) lcgGetProcAddress(lcgHandle, "cgGetNumProgramDomains");
  cgGetNumStateEnumerants = (PFNCGGETNUMSTATEENUMERANTSPROC) lcgGetProcAddress(lcgHandle, "cgGetNumStateEnumerants");
  cgGetNumSupportedProfiles = (PFNCGGETNUMSUPPORTEDPROFILESPROC) lcgGetProcAddress(lcgHandle, "cgGetNumSupportedProfiles");
  cgGetNumUserTypes = (PFNCGGETNUMUSERTYPESPROC) lcgGetProcAddress(lcgHandle, "cgGetNumUserTypes");
  cgGetParameterBaseResource = (PFNCGGETPARAMETERBASERESOURCEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterBaseResource");
  cgGetParameterBaseType = (PFNCGGETPARAMETERBASETYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterBaseType");
  cgGetParameterBufferIndex = (PFNCGGETPARAMETERBUFFERINDEXPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterBufferIndex");
  cgGetParameterBufferOffset = (PFNCGGETPARAMETERBUFFEROFFSETPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterBufferOffset");
  cgGetParameterClass = (PFNCGGETPARAMETERCLASSPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterClass");
  cgGetParameterClassEnum = (PFNCGGETPARAMETERCLASSENUMPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterClassEnum");
  cgGetParameterClassString = (PFNCGGETPARAMETERCLASSSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterClassString");
  cgGetParameterColumns = (PFNCGGETPARAMETERCOLUMNSPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterColumns");
  cgGetParameterContext = (PFNCGGETPARAMETERCONTEXTPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterContext");
  cgGetParameterDefaultValuedc = (PFNCGGETPARAMETERDEFAULTVALUEDCPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterDefaultValuedc");
  cgGetParameterDefaultValuedr = (PFNCGGETPARAMETERDEFAULTVALUEDRPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterDefaultValuedr");
  cgGetParameterDefaultValuefc = (PFNCGGETPARAMETERDEFAULTVALUEFCPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterDefaultValuefc");
  cgGetParameterDefaultValuefr = (PFNCGGETPARAMETERDEFAULTVALUEFRPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterDefaultValuefr");
  cgGetParameterDefaultValueic = (PFNCGGETPARAMETERDEFAULTVALUEICPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterDefaultValueic");
  cgGetParameterDefaultValueir = (PFNCGGETPARAMETERDEFAULTVALUEIRPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterDefaultValueir");
  cgGetParameterDirection = (PFNCGGETPARAMETERDIRECTIONPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterDirection");
  cgGetParameterEffect = (PFNCGGETPARAMETEREFFECTPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterEffect");
  cgGetParameterIndex = (PFNCGGETPARAMETERINDEXPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterIndex");
  cgGetParameterName = (PFNCGGETPARAMETERNAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterName");
  cgGetParameterNamedType = (PFNCGGETPARAMETERNAMEDTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterNamedType");
  cgGetParameterOrdinalNumber = (PFNCGGETPARAMETERORDINALNUMBERPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterOrdinalNumber");
  cgGetParameterProgram = (PFNCGGETPARAMETERPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterProgram");
  cgGetParameterResource = (PFNCGGETPARAMETERRESOURCEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterResource");
  cgGetParameterResourceIndex = (PFNCGGETPARAMETERRESOURCEINDEXPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterResourceIndex");
  cgGetParameterResourceName = (PFNCGGETPARAMETERRESOURCENAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterResourceName");
  cgGetParameterResourceSize = (PFNCGGETPARAMETERRESOURCESIZEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterResourceSize");
  cgGetParameterResourceType = (PFNCGGETPARAMETERRESOURCETYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterResourceType");
  cgGetParameterRows = (PFNCGGETPARAMETERROWSPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterRows");
  cgGetParameterSemantic = (PFNCGGETPARAMETERSEMANTICPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterSemantic");
  cgGetParameterSettingMode = (PFNCGGETPARAMETERSETTINGMODEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterSettingMode");
  cgGetParameterType = (PFNCGGETPARAMETERTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterType");
  cgGetParameterValuedc = (PFNCGGETPARAMETERVALUEDCPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterValuedc");
  cgGetParameterValuedr = (PFNCGGETPARAMETERVALUEDRPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterValuedr");
  cgGetParameterValuefc = (PFNCGGETPARAMETERVALUEFCPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterValuefc");
  cgGetParameterValuefr = (PFNCGGETPARAMETERVALUEFRPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterValuefr");
  cgGetParameterValueic = (PFNCGGETPARAMETERVALUEICPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterValueic");
  cgGetParameterValueir = (PFNCGGETPARAMETERVALUEIRPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterValueir");
  cgGetParameterValues = (PFNCGGETPARAMETERVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterValues");
  cgGetParameterVariability = (PFNCGGETPARAMETERVARIABILITYPROC) lcgGetProcAddress(lcgHandle, "cgGetParameterVariability");
  cgGetParentType = (PFNCGGETPARENTTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetParentType");
  cgGetPassName = (PFNCGGETPASSNAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetPassName");
  cgGetPassProgram = (PFNCGGETPASSPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgGetPassProgram");
  cgGetPassTechnique = (PFNCGGETPASSTECHNIQUEPROC) lcgGetProcAddress(lcgHandle, "cgGetPassTechnique");
  cgGetProfile = (PFNCGGETPROFILEPROC) lcgGetProcAddress(lcgHandle, "cgGetProfile");
  cgGetProfileDomain = (PFNCGGETPROFILEDOMAINPROC) lcgGetProcAddress(lcgHandle, "cgGetProfileDomain");
  cgGetProfileProperty = (PFNCGGETPROFILEPROPERTYPROC) lcgGetProcAddress(lcgHandle, "cgGetProfileProperty");
  cgGetProfileSibling = (PFNCGGETPROFILESIBLINGPROC) lcgGetProcAddress(lcgHandle, "cgGetProfileSibling");
  cgGetProfileString = (PFNCGGETPROFILESTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetProfileString");
  cgGetProgramBuffer = (PFNCGGETPROGRAMBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramBuffer");
  cgGetProgramBufferMaxIndex = (PFNCGGETPROGRAMBUFFERMAXINDEXPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramBufferMaxIndex");
  cgGetProgramBufferMaxSize = (PFNCGGETPROGRAMBUFFERMAXSIZEPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramBufferMaxSize");
  cgGetProgramContext = (PFNCGGETPROGRAMCONTEXTPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramContext");
  cgGetProgramDomain = (PFNCGGETPROGRAMDOMAINPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramDomain");
  cgGetProgramDomainProfile = (PFNCGGETPROGRAMDOMAINPROFILEPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramDomainProfile");
  cgGetProgramDomainProgram = (PFNCGGETPROGRAMDOMAINPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramDomainProgram");
  cgGetProgramInput = (PFNCGGETPROGRAMINPUTPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramInput");
  cgGetProgramOptions = (PFNCGGETPROGRAMOPTIONSPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramOptions");
  cgGetProgramOutput = (PFNCGGETPROGRAMOUTPUTPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramOutput");
  cgGetProgramOutputVertices = (PFNCGGETPROGRAMOUTPUTVERTICESPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramOutputVertices");
  cgGetProgramProfile = (PFNCGGETPROGRAMPROFILEPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramProfile");
  cgGetProgramStateAssignmentValue = (PFNCGGETPROGRAMSTATEASSIGNMENTVALUEPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramStateAssignmentValue");
  cgGetProgramString = (PFNCGGETPROGRAMSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetProgramString");
  cgGetResource = (PFNCGGETRESOURCEPROC) lcgGetProcAddress(lcgHandle, "cgGetResource");
  cgGetResourceString = (PFNCGGETRESOURCESTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetResourceString");
  cgGetSamplerStateAssignmentParameter = (PFNCGGETSAMPLERSTATEASSIGNMENTPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetSamplerStateAssignmentParameter");
  cgGetSamplerStateAssignmentState = (PFNCGGETSAMPLERSTATEASSIGNMENTSTATEPROC) lcgGetProcAddress(lcgHandle, "cgGetSamplerStateAssignmentState");
  cgGetSamplerStateAssignmentValue = (PFNCGGETSAMPLERSTATEASSIGNMENTVALUEPROC) lcgGetProcAddress(lcgHandle, "cgGetSamplerStateAssignmentValue");
  cgGetSemanticCasePolicy = (PFNCGGETSEMANTICCASEPOLICYPROC) lcgGetProcAddress(lcgHandle, "cgGetSemanticCasePolicy");
  cgGetStateAssignmentIndex = (PFNCGGETSTATEASSIGNMENTINDEXPROC) lcgGetProcAddress(lcgHandle, "cgGetStateAssignmentIndex");
  cgGetStateAssignmentPass = (PFNCGGETSTATEASSIGNMENTPASSPROC) lcgGetProcAddress(lcgHandle, "cgGetStateAssignmentPass");
  cgGetStateAssignmentState = (PFNCGGETSTATEASSIGNMENTSTATEPROC) lcgGetProcAddress(lcgHandle, "cgGetStateAssignmentState");
  cgGetStateContext = (PFNCGGETSTATECONTEXTPROC) lcgGetProcAddress(lcgHandle, "cgGetStateContext");
  cgGetStateEnumerant = (PFNCGGETSTATEENUMERANTPROC) lcgGetProcAddress(lcgHandle, "cgGetStateEnumerant");
  cgGetStateEnumerantName = (PFNCGGETSTATEENUMERANTNAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetStateEnumerantName");
  cgGetStateEnumerantValue = (PFNCGGETSTATEENUMERANTVALUEPROC) lcgGetProcAddress(lcgHandle, "cgGetStateEnumerantValue");
  cgGetStateLatestProfile = (PFNCGGETSTATELATESTPROFILEPROC) lcgGetProcAddress(lcgHandle, "cgGetStateLatestProfile");
  cgGetStateName = (PFNCGGETSTATENAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetStateName");
  cgGetStateResetCallback = (PFNCGGETSTATERESETCALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgGetStateResetCallback");
  cgGetStateSetCallback = (PFNCGGETSTATESETCALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgGetStateSetCallback");
  cgGetStateType = (PFNCGGETSTATETYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetStateType");
  cgGetStateValidateCallback = (PFNCGGETSTATEVALIDATECALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgGetStateValidateCallback");
  cgGetString = (PFNCGGETSTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetString");
  cgGetStringAnnotationValue = (PFNCGGETSTRINGANNOTATIONVALUEPROC) lcgGetProcAddress(lcgHandle, "cgGetStringAnnotationValue");
  cgGetStringAnnotationValues = (PFNCGGETSTRINGANNOTATIONVALUESPROC) lcgGetProcAddress(lcgHandle, "cgGetStringAnnotationValues");
  cgGetStringParameterValue = (PFNCGGETSTRINGPARAMETERVALUEPROC) lcgGetProcAddress(lcgHandle, "cgGetStringParameterValue");
  cgGetStringStateAssignmentValue = (PFNCGGETSTRINGSTATEASSIGNMENTVALUEPROC) lcgGetProcAddress(lcgHandle, "cgGetStringStateAssignmentValue");
  cgGetSupportedProfile = (PFNCGGETSUPPORTEDPROFILEPROC) lcgGetProcAddress(lcgHandle, "cgGetSupportedProfile");
  cgGetTechniqueEffect = (PFNCGGETTECHNIQUEEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgGetTechniqueEffect");
  cgGetTechniqueName = (PFNCGGETTECHNIQUENAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetTechniqueName");
  cgGetTextureStateAssignmentValue = (PFNCGGETTEXTURESTATEASSIGNMENTVALUEPROC) lcgGetProcAddress(lcgHandle, "cgGetTextureStateAssignmentValue");
  cgGetType = (PFNCGGETTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetType");
  cgGetTypeBase = (PFNCGGETTYPEBASEPROC) lcgGetProcAddress(lcgHandle, "cgGetTypeBase");
  cgGetTypeClass = (PFNCGGETTYPECLASSPROC) lcgGetProcAddress(lcgHandle, "cgGetTypeClass");
  cgGetTypeSizes = (PFNCGGETTYPESIZESPROC) lcgGetProcAddress(lcgHandle, "cgGetTypeSizes");
  cgGetTypeString = (PFNCGGETTYPESTRINGPROC) lcgGetProcAddress(lcgHandle, "cgGetTypeString");
  cgGetUniformBufferBlockName = (PFNCGGETUNIFORMBUFFERBLOCKNAMEPROC) lcgGetProcAddress(lcgHandle, "cgGetUniformBufferBlockName");
  cgGetUniformBufferParameter = (PFNCGGETUNIFORMBUFFERPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgGetUniformBufferParameter");
  cgGetUserType = (PFNCGGETUSERTYPEPROC) lcgGetProcAddress(lcgHandle, "cgGetUserType");
  cgIsAnnotation = (PFNCGISANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgIsAnnotation");
  cgIsBuffer = (PFNCGISBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgIsBuffer");
  cgIsContext = (PFNCGISCONTEXTPROC) lcgGetProcAddress(lcgHandle, "cgIsContext");
  cgIsEffect = (PFNCGISEFFECTPROC) lcgGetProcAddress(lcgHandle, "cgIsEffect");
  cgIsInterfaceType = (PFNCGISINTERFACETYPEPROC) lcgGetProcAddress(lcgHandle, "cgIsInterfaceType");
  cgIsParameter = (PFNCGISPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgIsParameter");
  cgIsParameterGlobal = (PFNCGISPARAMETERGLOBALPROC) lcgGetProcAddress(lcgHandle, "cgIsParameterGlobal");
  cgIsParameterReferenced = (PFNCGISPARAMETERREFERENCEDPROC) lcgGetProcAddress(lcgHandle, "cgIsParameterReferenced");
  cgIsParameterUsed = (PFNCGISPARAMETERUSEDPROC) lcgGetProcAddress(lcgHandle, "cgIsParameterUsed");
  cgIsParentType = (PFNCGISPARENTTYPEPROC) lcgGetProcAddress(lcgHandle, "cgIsParentType");
  cgIsPass = (PFNCGISPASSPROC) lcgGetProcAddress(lcgHandle, "cgIsPass");
  cgIsProfileSupported = (PFNCGISPROFILESUPPORTEDPROC) lcgGetProcAddress(lcgHandle, "cgIsProfileSupported");
  cgIsProgram = (PFNCGISPROGRAMPROC) lcgGetProcAddress(lcgHandle, "cgIsProgram");
  cgIsProgramCompiled = (PFNCGISPROGRAMCOMPILEDPROC) lcgGetProcAddress(lcgHandle, "cgIsProgramCompiled");
  cgIsState = (PFNCGISSTATEPROC) lcgGetProcAddress(lcgHandle, "cgIsState");
  cgIsStateAssignment = (PFNCGISSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgIsStateAssignment");
  cgIsTechnique = (PFNCGISTECHNIQUEPROC) lcgGetProcAddress(lcgHandle, "cgIsTechnique");
  cgIsTechniqueValidated = (PFNCGISTECHNIQUEVALIDATEDPROC) lcgGetProcAddress(lcgHandle, "cgIsTechniqueValidated");
  cgMapBuffer = (PFNCGMAPBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgMapBuffer");
  cgResetPassState = (PFNCGRESETPASSSTATEPROC) lcgGetProcAddress(lcgHandle, "cgResetPassState");
  cgSetArraySize = (PFNCGSETARRAYSIZEPROC) lcgGetProcAddress(lcgHandle, "cgSetArraySize");
  cgSetAutoCompile = (PFNCGSETAUTOCOMPILEPROC) lcgGetProcAddress(lcgHandle, "cgSetAutoCompile");
  cgSetBoolAnnotation = (PFNCGSETBOOLANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgSetBoolAnnotation");
  cgSetBoolArrayStateAssignment = (PFNCGSETBOOLARRAYSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetBoolArrayStateAssignment");
  cgSetBoolStateAssignment = (PFNCGSETBOOLSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetBoolStateAssignment");
  cgSetBufferData = (PFNCGSETBUFFERDATAPROC) lcgGetProcAddress(lcgHandle, "cgSetBufferData");
  cgSetBufferSubData = (PFNCGSETBUFFERSUBDATAPROC) lcgGetProcAddress(lcgHandle, "cgSetBufferSubData");
  cgSetCompilerIncludeCallback = (PFNCGSETCOMPILERINCLUDECALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgSetCompilerIncludeCallback");
  cgSetCompilerIncludeFile = (PFNCGSETCOMPILERINCLUDEFILEPROC) lcgGetProcAddress(lcgHandle, "cgSetCompilerIncludeFile");
  cgSetCompilerIncludeString = (PFNCGSETCOMPILERINCLUDESTRINGPROC) lcgGetProcAddress(lcgHandle, "cgSetCompilerIncludeString");
  cgSetContextBehavior = (PFNCGSETCONTEXTBEHAVIORPROC) lcgGetProcAddress(lcgHandle, "cgSetContextBehavior");
  cgSetEffectName = (PFNCGSETEFFECTNAMEPROC) lcgGetProcAddress(lcgHandle, "cgSetEffectName");
  cgSetEffectParameterBuffer = (PFNCGSETEFFECTPARAMETERBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgSetEffectParameterBuffer");
  cgSetErrorCallback = (PFNCGSETERRORCALLBACKPROC) lcgGetProcAddress(lcgHandle, "cgSetErrorCallback");
  cgSetErrorHandler = (PFNCGSETERRORHANDLERPROC) lcgGetProcAddress(lcgHandle, "cgSetErrorHandler");
  cgSetFloatAnnotation = (PFNCGSETFLOATANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgSetFloatAnnotation");
  cgSetFloatArrayStateAssignment = (PFNCGSETFLOATARRAYSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetFloatArrayStateAssignment");
  cgSetFloatStateAssignment = (PFNCGSETFLOATSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetFloatStateAssignment");
  cgSetIntAnnotation = (PFNCGSETINTANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgSetIntAnnotation");
  cgSetIntArrayStateAssignment = (PFNCGSETINTARRAYSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetIntArrayStateAssignment");
  cgSetIntStateAssignment = (PFNCGSETINTSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetIntStateAssignment");
  cgSetLastListing = (PFNCGSETLASTLISTINGPROC) lcgGetProcAddress(lcgHandle, "cgSetLastListing");
  cgSetLockingPolicy = (PFNCGSETLOCKINGPOLICYPROC) lcgGetProcAddress(lcgHandle, "cgSetLockingPolicy");
  cgSetMatrixParameterdc = (PFNCGSETMATRIXPARAMETERDCPROC) lcgGetProcAddress(lcgHandle, "cgSetMatrixParameterdc");
  cgSetMatrixParameterdr = (PFNCGSETMATRIXPARAMETERDRPROC) lcgGetProcAddress(lcgHandle, "cgSetMatrixParameterdr");
  cgSetMatrixParameterfc = (PFNCGSETMATRIXPARAMETERFCPROC) lcgGetProcAddress(lcgHandle, "cgSetMatrixParameterfc");
  cgSetMatrixParameterfr = (PFNCGSETMATRIXPARAMETERFRPROC) lcgGetProcAddress(lcgHandle, "cgSetMatrixParameterfr");
  cgSetMatrixParameteric = (PFNCGSETMATRIXPARAMETERICPROC) lcgGetProcAddress(lcgHandle, "cgSetMatrixParameteric");
  cgSetMatrixParameterir = (PFNCGSETMATRIXPARAMETERIRPROC) lcgGetProcAddress(lcgHandle, "cgSetMatrixParameterir");
  cgSetMultiDimArraySize = (PFNCGSETMULTIDIMARRAYSIZEPROC) lcgGetProcAddress(lcgHandle, "cgSetMultiDimArraySize");
  cgSetParameter1d = (PFNCGSETPARAMETER1DPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter1d");
  cgSetParameter1dv = (PFNCGSETPARAMETER1DVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter1dv");
  cgSetParameter1f = (PFNCGSETPARAMETER1FPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter1f");
  cgSetParameter1fv = (PFNCGSETPARAMETER1FVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter1fv");
  cgSetParameter1i = (PFNCGSETPARAMETER1IPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter1i");
  cgSetParameter1iv = (PFNCGSETPARAMETER1IVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter1iv");
  cgSetParameter2d = (PFNCGSETPARAMETER2DPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter2d");
  cgSetParameter2dv = (PFNCGSETPARAMETER2DVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter2dv");
  cgSetParameter2f = (PFNCGSETPARAMETER2FPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter2f");
  cgSetParameter2fv = (PFNCGSETPARAMETER2FVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter2fv");
  cgSetParameter2i = (PFNCGSETPARAMETER2IPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter2i");
  cgSetParameter2iv = (PFNCGSETPARAMETER2IVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter2iv");
  cgSetParameter3d = (PFNCGSETPARAMETER3DPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter3d");
  cgSetParameter3dv = (PFNCGSETPARAMETER3DVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter3dv");
  cgSetParameter3f = (PFNCGSETPARAMETER3FPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter3f");
  cgSetParameter3fv = (PFNCGSETPARAMETER3FVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter3fv");
  cgSetParameter3i = (PFNCGSETPARAMETER3IPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter3i");
  cgSetParameter3iv = (PFNCGSETPARAMETER3IVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter3iv");
  cgSetParameter4d = (PFNCGSETPARAMETER4DPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter4d");
  cgSetParameter4dv = (PFNCGSETPARAMETER4DVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter4dv");
  cgSetParameter4f = (PFNCGSETPARAMETER4FPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter4f");
  cgSetParameter4fv = (PFNCGSETPARAMETER4FVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter4fv");
  cgSetParameter4i = (PFNCGSETPARAMETER4IPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter4i");
  cgSetParameter4iv = (PFNCGSETPARAMETER4IVPROC) lcgGetProcAddress(lcgHandle, "cgSetParameter4iv");
  cgSetParameterSemantic = (PFNCGSETPARAMETERSEMANTICPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterSemantic");
  cgSetParameterSettingMode = (PFNCGSETPARAMETERSETTINGMODEPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterSettingMode");
  cgSetParameterValuedc = (PFNCGSETPARAMETERVALUEDCPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterValuedc");
  cgSetParameterValuedr = (PFNCGSETPARAMETERVALUEDRPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterValuedr");
  cgSetParameterValuefc = (PFNCGSETPARAMETERVALUEFCPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterValuefc");
  cgSetParameterValuefr = (PFNCGSETPARAMETERVALUEFRPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterValuefr");
  cgSetParameterValueic = (PFNCGSETPARAMETERVALUEICPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterValueic");
  cgSetParameterValueir = (PFNCGSETPARAMETERVALUEIRPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterValueir");
  cgSetParameterVariability = (PFNCGSETPARAMETERVARIABILITYPROC) lcgGetProcAddress(lcgHandle, "cgSetParameterVariability");
  cgSetPassProgramParameters = (PFNCGSETPASSPROGRAMPARAMETERSPROC) lcgGetProcAddress(lcgHandle, "cgSetPassProgramParameters");
  cgSetPassState = (PFNCGSETPASSSTATEPROC) lcgGetProcAddress(lcgHandle, "cgSetPassState");
  cgSetProgramBuffer = (PFNCGSETPROGRAMBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgSetProgramBuffer");
  cgSetProgramOutputVertices = (PFNCGSETPROGRAMOUTPUTVERTICESPROC) lcgGetProcAddress(lcgHandle, "cgSetProgramOutputVertices");
  cgSetProgramProfile = (PFNCGSETPROGRAMPROFILEPROC) lcgGetProcAddress(lcgHandle, "cgSetProgramProfile");
  cgSetProgramStateAssignment = (PFNCGSETPROGRAMSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetProgramStateAssignment");
  cgSetSamplerState = (PFNCGSETSAMPLERSTATEPROC) lcgGetProcAddress(lcgHandle, "cgSetSamplerState");
  cgSetSamplerStateAssignment = (PFNCGSETSAMPLERSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetSamplerStateAssignment");
  cgSetSemanticCasePolicy = (PFNCGSETSEMANTICCASEPOLICYPROC) lcgGetProcAddress(lcgHandle, "cgSetSemanticCasePolicy");
  cgSetStateCallbacks = (PFNCGSETSTATECALLBACKSPROC) lcgGetProcAddress(lcgHandle, "cgSetStateCallbacks");
  cgSetStateLatestProfile = (PFNCGSETSTATELATESTPROFILEPROC) lcgGetProcAddress(lcgHandle, "cgSetStateLatestProfile");
  cgSetStringAnnotation = (PFNCGSETSTRINGANNOTATIONPROC) lcgGetProcAddress(lcgHandle, "cgSetStringAnnotation");
  cgSetStringParameterValue = (PFNCGSETSTRINGPARAMETERVALUEPROC) lcgGetProcAddress(lcgHandle, "cgSetStringParameterValue");
  cgSetStringStateAssignment = (PFNCGSETSTRINGSTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetStringStateAssignment");
  cgSetTextureStateAssignment = (PFNCGSETTEXTURESTATEASSIGNMENTPROC) lcgGetProcAddress(lcgHandle, "cgSetTextureStateAssignment");
  cgSetUniformBufferParameter = (PFNCGSETUNIFORMBUFFERPARAMETERPROC) lcgGetProcAddress(lcgHandle, "cgSetUniformBufferParameter");
  cgUnmapBuffer = (PFNCGUNMAPBUFFERPROC) lcgGetProcAddress(lcgHandle, "cgUnmapBuffer");
  cgUpdatePassParameters = (PFNCGUPDATEPASSPARAMETERSPROC) lcgGetProcAddress(lcgHandle, "cgUpdatePassParameters");
  cgUpdateProgramParameters = (PFNCGUPDATEPROGRAMPARAMETERSPROC) lcgGetProcAddress(lcgHandle, "cgUpdateProgramParameters");
  cgValidateTechnique = (PFNCGVALIDATETECHNIQUEPROC) lcgGetProcAddress(lcgHandle, "cgValidateTechnique");

  return 1;
}

void
lcgList(const char *prefix, FILE *out)
{
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgAddStateEnumerant", cgAddStateEnumerant ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCallStateResetCallback", cgCallStateResetCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCallStateSetCallback", cgCallStateSetCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCallStateValidateCallback", cgCallStateValidateCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCombinePrograms", cgCombinePrograms ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCombinePrograms2", cgCombinePrograms2 ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCombinePrograms3", cgCombinePrograms3 ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCombinePrograms4", cgCombinePrograms4 ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCombinePrograms5", cgCombinePrograms5 ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCompileProgram", cgCompileProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgConnectParameter", cgConnectParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCopyEffect", cgCopyEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCopyProgram", cgCopyProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateArraySamplerState", cgCreateArraySamplerState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateArrayState", cgCreateArrayState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateBuffer", cgCreateBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateContext", cgCreateContext ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateEffect", cgCreateEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateEffectAnnotation", cgCreateEffectAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateEffectFromFile", cgCreateEffectFromFile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateEffectParameter", cgCreateEffectParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateEffectParameterArray", cgCreateEffectParameterArray ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateEffectParameterMultiDimArray", cgCreateEffectParameterMultiDimArray ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateObj", cgCreateObj ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateObjFromFile", cgCreateObjFromFile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateParameter", cgCreateParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateParameterAnnotation", cgCreateParameterAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateParameterArray", cgCreateParameterArray ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateParameterMultiDimArray", cgCreateParameterMultiDimArray ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreatePass", cgCreatePass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreatePassAnnotation", cgCreatePassAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateProgram", cgCreateProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateProgramAnnotation", cgCreateProgramAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateProgramFromEffect", cgCreateProgramFromEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateProgramFromFile", cgCreateProgramFromFile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateSamplerState", cgCreateSamplerState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateSamplerStateAssignment", cgCreateSamplerStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateState", cgCreateState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateStateAssignment", cgCreateStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateStateAssignmentIndex", cgCreateStateAssignmentIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateTechnique", cgCreateTechnique ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgCreateTechniqueAnnotation", cgCreateTechniqueAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgDestroyBuffer", cgDestroyBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgDestroyContext", cgDestroyContext ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgDestroyEffect", cgDestroyEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgDestroyObj", cgDestroyObj ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgDestroyParameter", cgDestroyParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgDestroyProgram", cgDestroyProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgDisconnectParameter", cgDisconnectParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgEvaluateProgram", cgEvaluateProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetAnnotationName", cgGetAnnotationName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetAnnotationType", cgGetAnnotationType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetArrayDimension", cgGetArrayDimension ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetArrayParameter", cgGetArrayParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetArraySize", cgGetArraySize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetArrayTotalSize", cgGetArrayTotalSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetArrayType", cgGetArrayType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetAutoCompile", cgGetAutoCompile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetBehavior", cgGetBehavior ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetBehaviorString", cgGetBehaviorString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetBoolAnnotationValues", cgGetBoolAnnotationValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetBoolStateAssignmentValues", cgGetBoolStateAssignmentValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetBooleanAnnotationValues", cgGetBooleanAnnotationValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetBufferSize", cgGetBufferSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetCompilerIncludeCallback", cgGetCompilerIncludeCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetConnectedParameter", cgGetConnectedParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetConnectedStateAssignmentParameter", cgGetConnectedStateAssignmentParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetConnectedToParameter", cgGetConnectedToParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetContextBehavior", cgGetContextBehavior ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetDependentAnnotationParameter", cgGetDependentAnnotationParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetDependentProgramArrayStateAssignmentParameter", cgGetDependentProgramArrayStateAssignmentParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetDependentStateAssignmentParameter", cgGetDependentStateAssignmentParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetDomain", cgGetDomain ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetDomainString", cgGetDomainString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetEffectContext", cgGetEffectContext ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetEffectName", cgGetEffectName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetEffectParameterBuffer", cgGetEffectParameterBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetEffectParameterBySemantic", cgGetEffectParameterBySemantic ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetEnum", cgGetEnum ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetEnumString", cgGetEnumString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetError", cgGetError ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetErrorCallback", cgGetErrorCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetErrorHandler", cgGetErrorHandler ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetErrorString", cgGetErrorString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstDependentParameter", cgGetFirstDependentParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstEffect", cgGetFirstEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstEffectAnnotation", cgGetFirstEffectAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstEffectParameter", cgGetFirstEffectParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstError", cgGetFirstError ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstLeafEffectParameter", cgGetFirstLeafEffectParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstLeafParameter", cgGetFirstLeafParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstParameter", cgGetFirstParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstParameterAnnotation", cgGetFirstParameterAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstPass", cgGetFirstPass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstPassAnnotation", cgGetFirstPassAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstProgram", cgGetFirstProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstProgramAnnotation", cgGetFirstProgramAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstSamplerState", cgGetFirstSamplerState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstSamplerStateAssignment", cgGetFirstSamplerStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstState", cgGetFirstState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstStateAssignment", cgGetFirstStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstStructParameter", cgGetFirstStructParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstTechnique", cgGetFirstTechnique ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstTechniqueAnnotation", cgGetFirstTechniqueAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFirstUniformBufferParameter", cgGetFirstUniformBufferParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFloatAnnotationValues", cgGetFloatAnnotationValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetFloatStateAssignmentValues", cgGetFloatStateAssignmentValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetIntAnnotationValues", cgGetIntAnnotationValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetIntStateAssignmentValues", cgGetIntStateAssignmentValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetLastErrorString", cgGetLastErrorString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetLastListing", cgGetLastListing ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetLockingPolicy", cgGetLockingPolicy ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixParameterOrder", cgGetMatrixParameterOrder ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixParameterdc", cgGetMatrixParameterdc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixParameterdr", cgGetMatrixParameterdr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixParameterfc", cgGetMatrixParameterfc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixParameterfr", cgGetMatrixParameterfr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixParameteric", cgGetMatrixParameteric ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixParameterir", cgGetMatrixParameterir ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetMatrixSize", cgGetMatrixSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedEffect", cgGetNamedEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedEffectAnnotation", cgGetNamedEffectAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedEffectParameter", cgGetNamedEffectParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedEffectUniformBuffer", cgGetNamedEffectUniformBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedParameter", cgGetNamedParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedParameterAnnotation", cgGetNamedParameterAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedPass", cgGetNamedPass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedPassAnnotation", cgGetNamedPassAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedProgramAnnotation", cgGetNamedProgramAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedProgramParameter", cgGetNamedProgramParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedProgramUniformBuffer", cgGetNamedProgramUniformBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedSamplerState", cgGetNamedSamplerState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedSamplerStateAssignment", cgGetNamedSamplerStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedState", cgGetNamedState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedStateAssignment", cgGetNamedStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedStructParameter", cgGetNamedStructParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedSubParameter", cgGetNamedSubParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedTechnique", cgGetNamedTechnique ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedTechniqueAnnotation", cgGetNamedTechniqueAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedUniformBufferParameter", cgGetNamedUniformBufferParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNamedUserType", cgGetNamedUserType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextAnnotation", cgGetNextAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextEffect", cgGetNextEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextLeafParameter", cgGetNextLeafParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextParameter", cgGetNextParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextPass", cgGetNextPass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextProgram", cgGetNextProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextState", cgGetNextState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextStateAssignment", cgGetNextStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNextTechnique", cgGetNextTechnique ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumConnectedToParameters", cgGetNumConnectedToParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumDependentAnnotationParameters", cgGetNumDependentAnnotationParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumDependentProgramArrayStateAssignmentParameters", cgGetNumDependentProgramArrayStateAssignmentParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumDependentStateAssignmentParameters", cgGetNumDependentStateAssignmentParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumParentTypes", cgGetNumParentTypes ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumProgramDomains", cgGetNumProgramDomains ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumStateEnumerants", cgGetNumStateEnumerants ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumSupportedProfiles", cgGetNumSupportedProfiles ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetNumUserTypes", cgGetNumUserTypes ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterBaseResource", cgGetParameterBaseResource ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterBaseType", cgGetParameterBaseType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterBufferIndex", cgGetParameterBufferIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterBufferOffset", cgGetParameterBufferOffset ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterClass", cgGetParameterClass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterClassEnum", cgGetParameterClassEnum ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterClassString", cgGetParameterClassString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterColumns", cgGetParameterColumns ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterContext", cgGetParameterContext ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterDefaultValuedc", cgGetParameterDefaultValuedc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterDefaultValuedr", cgGetParameterDefaultValuedr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterDefaultValuefc", cgGetParameterDefaultValuefc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterDefaultValuefr", cgGetParameterDefaultValuefr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterDefaultValueic", cgGetParameterDefaultValueic ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterDefaultValueir", cgGetParameterDefaultValueir ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterDirection", cgGetParameterDirection ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterEffect", cgGetParameterEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterIndex", cgGetParameterIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterName", cgGetParameterName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterNamedType", cgGetParameterNamedType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterOrdinalNumber", cgGetParameterOrdinalNumber ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterProgram", cgGetParameterProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterResource", cgGetParameterResource ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterResourceIndex", cgGetParameterResourceIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterResourceName", cgGetParameterResourceName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterResourceSize", cgGetParameterResourceSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterResourceType", cgGetParameterResourceType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterRows", cgGetParameterRows ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterSemantic", cgGetParameterSemantic ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterSettingMode", cgGetParameterSettingMode ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterType", cgGetParameterType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterValuedc", cgGetParameterValuedc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterValuedr", cgGetParameterValuedr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterValuefc", cgGetParameterValuefc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterValuefr", cgGetParameterValuefr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterValueic", cgGetParameterValueic ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterValueir", cgGetParameterValueir ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterValues", cgGetParameterValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParameterVariability", cgGetParameterVariability ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetParentType", cgGetParentType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetPassName", cgGetPassName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetPassProgram", cgGetPassProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetPassTechnique", cgGetPassTechnique ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProfile", cgGetProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProfileDomain", cgGetProfileDomain ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProfileProperty", cgGetProfileProperty ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProfileSibling", cgGetProfileSibling ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProfileString", cgGetProfileString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramBuffer", cgGetProgramBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramBufferMaxIndex", cgGetProgramBufferMaxIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramBufferMaxSize", cgGetProgramBufferMaxSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramContext", cgGetProgramContext ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramDomain", cgGetProgramDomain ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramDomainProfile", cgGetProgramDomainProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramDomainProgram", cgGetProgramDomainProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramInput", cgGetProgramInput ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramOptions", cgGetProgramOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramOutput", cgGetProgramOutput ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramOutputVertices", cgGetProgramOutputVertices ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramProfile", cgGetProgramProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramStateAssignmentValue", cgGetProgramStateAssignmentValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetProgramString", cgGetProgramString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetResource", cgGetResource ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetResourceString", cgGetResourceString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetSamplerStateAssignmentParameter", cgGetSamplerStateAssignmentParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetSamplerStateAssignmentState", cgGetSamplerStateAssignmentState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetSamplerStateAssignmentValue", cgGetSamplerStateAssignmentValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetSemanticCasePolicy", cgGetSemanticCasePolicy ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateAssignmentIndex", cgGetStateAssignmentIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateAssignmentPass", cgGetStateAssignmentPass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateAssignmentState", cgGetStateAssignmentState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateContext", cgGetStateContext ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateEnumerant", cgGetStateEnumerant ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateEnumerantName", cgGetStateEnumerantName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateEnumerantValue", cgGetStateEnumerantValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateLatestProfile", cgGetStateLatestProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateName", cgGetStateName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateResetCallback", cgGetStateResetCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateSetCallback", cgGetStateSetCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateType", cgGetStateType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStateValidateCallback", cgGetStateValidateCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetString", cgGetString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStringAnnotationValue", cgGetStringAnnotationValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStringAnnotationValues", cgGetStringAnnotationValues ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStringParameterValue", cgGetStringParameterValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetStringStateAssignmentValue", cgGetStringStateAssignmentValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetSupportedProfile", cgGetSupportedProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetTechniqueEffect", cgGetTechniqueEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetTechniqueName", cgGetTechniqueName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetTextureStateAssignmentValue", cgGetTextureStateAssignmentValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetType", cgGetType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetTypeBase", cgGetTypeBase ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetTypeClass", cgGetTypeClass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetTypeSizes", cgGetTypeSizes ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetTypeString", cgGetTypeString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetUniformBufferBlockName", cgGetUniformBufferBlockName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetUniformBufferParameter", cgGetUniformBufferParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGetUserType", cgGetUserType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsAnnotation", cgIsAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsBuffer", cgIsBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsContext", cgIsContext ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsEffect", cgIsEffect ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsInterfaceType", cgIsInterfaceType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsParameter", cgIsParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsParameterGlobal", cgIsParameterGlobal ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsParameterReferenced", cgIsParameterReferenced ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsParameterUsed", cgIsParameterUsed ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsParentType", cgIsParentType ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsPass", cgIsPass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsProfileSupported", cgIsProfileSupported ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsProgram", cgIsProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsProgramCompiled", cgIsProgramCompiled ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsState", cgIsState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsStateAssignment", cgIsStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsTechnique", cgIsTechnique ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgIsTechniqueValidated", cgIsTechniqueValidated ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgMapBuffer", cgMapBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgResetPassState", cgResetPassState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetArraySize", cgSetArraySize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetAutoCompile", cgSetAutoCompile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetBoolAnnotation", cgSetBoolAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetBoolArrayStateAssignment", cgSetBoolArrayStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetBoolStateAssignment", cgSetBoolStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetBufferData", cgSetBufferData ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetBufferSubData", cgSetBufferSubData ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetCompilerIncludeCallback", cgSetCompilerIncludeCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetCompilerIncludeFile", cgSetCompilerIncludeFile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetCompilerIncludeString", cgSetCompilerIncludeString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetContextBehavior", cgSetContextBehavior ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetEffectName", cgSetEffectName ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetEffectParameterBuffer", cgSetEffectParameterBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetErrorCallback", cgSetErrorCallback ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetErrorHandler", cgSetErrorHandler ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetFloatAnnotation", cgSetFloatAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetFloatArrayStateAssignment", cgSetFloatArrayStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetFloatStateAssignment", cgSetFloatStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetIntAnnotation", cgSetIntAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetIntArrayStateAssignment", cgSetIntArrayStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetIntStateAssignment", cgSetIntStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetLastListing", cgSetLastListing ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetLockingPolicy", cgSetLockingPolicy ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetMatrixParameterdc", cgSetMatrixParameterdc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetMatrixParameterdr", cgSetMatrixParameterdr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetMatrixParameterfc", cgSetMatrixParameterfc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetMatrixParameterfr", cgSetMatrixParameterfr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetMatrixParameteric", cgSetMatrixParameteric ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetMatrixParameterir", cgSetMatrixParameterir ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetMultiDimArraySize", cgSetMultiDimArraySize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter1d", cgSetParameter1d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter1dv", cgSetParameter1dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter1f", cgSetParameter1f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter1fv", cgSetParameter1fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter1i", cgSetParameter1i ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter1iv", cgSetParameter1iv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter2d", cgSetParameter2d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter2dv", cgSetParameter2dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter2f", cgSetParameter2f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter2fv", cgSetParameter2fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter2i", cgSetParameter2i ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter2iv", cgSetParameter2iv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter3d", cgSetParameter3d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter3dv", cgSetParameter3dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter3f", cgSetParameter3f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter3fv", cgSetParameter3fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter3i", cgSetParameter3i ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter3iv", cgSetParameter3iv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter4d", cgSetParameter4d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter4dv", cgSetParameter4dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter4f", cgSetParameter4f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter4fv", cgSetParameter4fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter4i", cgSetParameter4i ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameter4iv", cgSetParameter4iv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterSemantic", cgSetParameterSemantic ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterSettingMode", cgSetParameterSettingMode ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterValuedc", cgSetParameterValuedc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterValuedr", cgSetParameterValuedr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterValuefc", cgSetParameterValuefc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterValuefr", cgSetParameterValuefr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterValueic", cgSetParameterValueic ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterValueir", cgSetParameterValueir ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetParameterVariability", cgSetParameterVariability ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetPassProgramParameters", cgSetPassProgramParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetPassState", cgSetPassState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetProgramBuffer", cgSetProgramBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetProgramOutputVertices", cgSetProgramOutputVertices ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetProgramProfile", cgSetProgramProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetProgramStateAssignment", cgSetProgramStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetSamplerState", cgSetSamplerState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetSamplerStateAssignment", cgSetSamplerStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetSemanticCasePolicy", cgSetSemanticCasePolicy ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetStateCallbacks", cgSetStateCallbacks ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetStateLatestProfile", cgSetStateLatestProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetStringAnnotation", cgSetStringAnnotation ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetStringParameterValue", cgSetStringParameterValue ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetStringStateAssignment", cgSetStringStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetTextureStateAssignment", cgSetTextureStateAssignment ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgSetUniformBufferParameter", cgSetUniformBufferParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgUnmapBuffer", cgUnmapBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgUpdatePassParameters", cgUpdatePassParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgUpdateProgramParameters", cgUpdateProgramParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgValidateTechnique", cgValidateTechnique ? "found" : "missing");
}

void
lcgDestroy(void)
{
  if (lcgHandle)
  {
    lcgFreeLibrary(lcgHandle);
    lcgHandle = NULL;
  }
}
