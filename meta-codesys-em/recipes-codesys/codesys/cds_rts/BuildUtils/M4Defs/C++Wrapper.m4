divert(-1)
% -----------------------------------
% This file generates the C++ wrapper files
%	Version 3.1.3.0
% -----------------------------------
# The following lines ("DO NOT MODIFY...") generate a message in the destination file.
# This comment is not aimed at this file.
divert`'dnl
/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/
include(`Util.m4')
divert(-1)

changecom(`%')

% -----------------------------
% Define some diverts that gather information about some special features
% and initialize those diversions
% -----------------------------
define(`GEN_INCLUDE', `ifelse(`$1', `', `', `#include "`$1'"')'))dnl

define(`COMPONENT_SOURCES',dnl
`_FOREACH(`GEN_INCLUDE', $@)dnl'
divert
)
define(`EXTERNAL_SOURCES',`dnl')
define(`EXTERNAL_INCLUDES',`dnl')
define(`CONTRIB_SOURCES',`dnl')
define(`CONTRIB_INCLUDES',`dnl')
divert(-1)

define(`SET_COMPONENT_NAME',`define(`_COMPONENT_NAME',`$1')
divert
')

define(`COMPONENT_INCLUDES',`dnl')dnl
define(`COMPONENT_SYSSOURCES',`dnl')dnl
define(`REF_ITF',`dnl')dnl
define(`COMPONENT_VERSION',`dnl')dnl
define(`COMPONENT_VENDORID',`dnl')dnl
define(`CATEGORY',`dnl')dnl
define(`USE_ITF',`dnl')dnl
define(`TASK',`dnl')dnl
define(`TASKPREFIX',`dnl')dnl
define(`TASKPLACEHOLDER',`dnl')dnl
define(`OPTIONAL_IMPORTS',`dnl')dnl
define(`REQUIRED_IMPORTS',`dnl')dnl
define(`IMPLEMENT_QUERY_INTERFACE',`dnl')dnl

define(`SET_INTERFACE_NAME',`define(`_INTERFACE_NAME',`I'`$1')
divert
divert(-1)')

define(`DEF_API',`
divert
divert(-1)')

define(`DEF_STATIC_API',`
divert
divert(-1)')

define(DEF_CREATEITF_API_STANDARD_CAll, `ifelse(`$1',`void',`$2(`'_EXTRACT_PARAM_LIST(`$3'))',`h`'_COMPONENT_NAME = $2(`'_EXTRACT_PARAM_LIST(`$3'))');')

define(DEF_CREATEITF_API_STANDARD, `dnl
DEF_CREATEITF_API_STANDARD_CAll(`$1', `$2', `$3')
	if (h`'_COMPONENT_NAME == RTS_INVALID_HANDLE)
	{
		DeleteInstance((IBase *)('_INTERFACE_NAME` *)this);
		return RTS_INVALID_HANDLE;
	}dnl
')

define(DEF_CREATEITF_API_SYSTASKCREATE, `dnl
DEF_CREATEITF_API_STANDARD(`$1', `$2', `$3')
	SYS_TASK_INFO *pTask = (SYS_TASK_INFO *)h`'_COMPONENT_NAME;
	pTask->TP.hTask = (RTS_HANDLE)this;
	pTask->pCppInstance = (RTS_IEC_BYTE *)this;dnl
')

define(DEF_CREATEITF_API_CMPIECTASKCREATE, `dnl
DEF_CREATEITF_API_STANDARD(`$1', `$2', `$3')
	Task_Desc *pTaskDesc = (Task_Desc *)h`'_COMPONENT_NAME;
	pTaskDesc->pCppInstance = (RTS_IEC_BYTE *)this;dnl
')

define(DEF_CREATEITF_API_SYSTIMERCREATE, `dnl
DEF_CREATEITF_API_STANDARD(`$1', `$2', `$3')
	SYS_TIMER_INFO *pTimer = SysTimerGetInfo(h`'_COMPONENT_NAME, pResult);
	pTimer->pCppInstance = (RTS_IEC_BYTE *)this;dnl
')

define(`DEF_CREATEITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	ifelse($3, `SysTimerCreateEvent', `DEF_CREATEITF_API_SYSTIMERCREATE(`$1', `$3', `$4')', `ifelse($3, `SysTimerCreateCallback', `DEF_CREATEITF_API_SYSTIMERCREATE(`$1', `$3', `$4')', `ifelse($3, `SysTimerCreateCallback2', `DEF_CREATEITF_API_SYSTIMERCREATE(`$1', `$3', `$4')', `ifelse($3, `IecTaskCreate', `DEF_CREATEITF_API_CMPIECTASKCREATE(`$1', `$3', `$4')', `ifelse($3, `SysTaskCreate', `DEF_CREATEITF_API_SYSTASKCREATE(`$1', `$3', `$4')', `ifelse($3, `SysTaskCreate2', `DEF_CREATEITF_API_SYSTASKCREATE(`$1', `$3', `$4')', `DEF_CREATEITF_API_STANDARD(`$1', `$3', `$4')')')')')')')
	return (RTS_HANDLE)this;
}
divert(-1)')

define(`DEF_DELETEITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`'_EXTRACT_PARAM_LIST(`$4'))',`dnl
RTS_RESULT Result = $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'));
	DeleteInstance((IBase *)('_INTERFACE_NAME` *)this);
	return Result;dnl
	')
}
divert(-1)')

define(`DEF_HANDLEITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))',`return $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))');
}
divert(-1)')

define(`DEF_HANDLEITF_API2',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))',`return $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))');
}
divert(-1)')

define(`DEF_HANDLEITF_API_OWNCPP',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	CPP_IMPLEMENTATION_`'$3
}
divert(-1)')

define(`DEF_CREATECLASSITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	ifelse(`$1',`void',`$3(`'_EXTRACT_PARAM_LIST(`$4'))',`h`'_COMPONENT_NAME = $3(`'_EXTRACT_PARAM_LIST(`$4'))');
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(`'_INTERFACE_NAME *)this, ITFID_`'_INTERFACE_NAME, NULL);
	Release();
	return h;
}
divert(-1)')

define(`DEF_CREATECLASSITF2_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	ifelse(`$1',`void',`$3(`'_EXTRACT_PARAM_LIST(`$4'))',`h`'_COMPONENT_NAME = $3(`'_EXTRACT_PARAM_LIST(`$4'))');
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(`'_INTERFACE_NAME *)this, ITFID_`'_INTERFACE_NAME, NULL);
	Release();
	return h;
}
divert(-1)')

define(`DEF_PRODUCECLASSITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_ITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))',`return $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))');
}
divert(-1)')

define(`DEF_PRODUCECLASSITF_API_OWNCPP',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	CPP_IMPLEMENTATION_`'$3
}
divert(-1)')


define(`DEF_DELETECLASSITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'));
	DeleteInstance((IBase *)('_INTERFACE_NAME` *)this);',`dnl
RTS_RESULT Result = $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'));
	DeleteInstance((IBase *)('_INTERFACE_NAME` *)this);
	return Result');
}
divert(-1)')

define(`DEF_DELETECLASSITF2_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'));
	DeleteInstance((IBase *)('_INTERFACE_NAME` *)this);',`dnl
RTS_RESULT Result = $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'));
	DeleteInstance((IBase *)('_INTERFACE_NAME` *)this);
	return Result');
}
divert(-1)')

define(`DEF_CLASSITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))',`return $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))');
}
divert(-1)')

define(`DEF_RETURNHANDLECLASSITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3(_CONCAT(`_MAKE_HANDLEITF_PARAMLIST',_TRIM(`$4')))
{
	ifelse(`$1',`void',`$3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))',``h'_COMPONENT_NAME = $3(`h'_COMPONENT_NAME`'_EXTRACT_PARAM_LIST_HANDLE(`$4'))');
	return `h'_COMPONENT_NAME;
}
divert(-1)')

define(`DEF_STATICITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	ifelse(`$1',`void',`$3(`'_EXTRACT_PARAM_LIST(`$4'))',`return $3(`'_EXTRACT_PARAM_LIST(`$4'))');
}
divert(-1)')

define(DEF_ITF_API_STANDARD, `ifelse(`$1',`void',`$2(`'_EXTRACT_PARAM_LIST(`$3'));',`return $2(`'_EXTRACT_PARAM_LIST(`$3'));')')

define(DEF_ITF_API_SYSTASKGETCURRENT, `dnl
RTS_RESULT Result = SysTaskGetCurrent(phTask);
	if (Result == ERR_OK && phTask != NULL && *phTask != RTS_INVALID_HANDLE)
	{
		SYS_TASK_INFO *pTaskInfo = (SYS_TASK_INFO *)*phTask;
		*phTask = (RTS_HANDLE)pTaskInfo->pCppInstance;
	}
	return Result;dnl
')

define(DEF_ITF_API_CMPIECTASKGETCURRENT, `dnl
RTS_HANDLE hCurrentTask = IecTaskGetCurrent(pResult);
	if (hCurrentTask != RTS_INVALID_HANDLE)
	{
		Task_Desc *pTaskDesc = (Task_Desc *)hCurrentTask;
		return (RTS_HANDLE)pTaskDesc->pCppInstance;
	}
	return RTS_INVALID_HANDLE;dnl
')

define(DEF_ITF_API_CMPIECTASKGETFIRST, `dnl
RTS_HANDLE hTask = IecTaskGetFirst(pszAppName,pResult);
	if (hTask != RTS_INVALID_HANDLE)
	{
		Task_Desc *pTaskDesc = (Task_Desc *)hTask;
		return (RTS_HANDLE)pTaskDesc->pCppInstance;
	}
	return RTS_INVALID_HANDLE;')

define(DEF_ITF_API_CMPIECTASKGETNEXT, `dnl
RTS_HANDLE hPrev = GetHandleOfCppInstance(hPrevIecTask);
	if (hPrev == RTS_INVALID_HANDLE)
		return RTS_INVALID_HANDLE;
	
	RTS_HANDLE hTask = IecTaskGetNext(pszAppName, hPrev, pResult);
	if (hTask != RTS_INVALID_HANDLE)
	{
		Task_Desc *pTaskDesc = (Task_Desc *)hTask;
		return (RTS_HANDLE)pTaskDesc->pCppInstance;
	}
	return RTS_INVALID_HANDLE;')

define(DEF_ITF_API_VARPARAMETER, `RTS_RESULT Result;
	va_list argList;
	va_start(argList, `'_EXTRACT_VARIABLEPARAMETER_FORMAT(`$3'));
	ifelse(`$1',`void',`$2Arg(`'_EXTRACT_PARAM_LIST(`$3'));',`Result = $2Arg(`'_EXTRACT_PARAM_LIST(`$3')&argList);
	va_end(argList);
	return Result;')');

define(`DEF_ITF_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	ifelse(_HAS_VARIABLEPARAMETER(`$4'), -1, `ifelse($3, `IecTaskGetFirst', `DEF_ITF_API_CMPIECTASKGETFIRST(`$1', `$3', `$4')', `ifelse($3, `IecTaskGetNext', `DEF_ITF_API_CMPIECTASKGETNEXT(`$1', `$3', `$4')', `ifelse($3, `IecTaskGetCurrent', `DEF_ITF_API_CMPIECTASKGETCURRENT(`$1', `$3', `$4')', `ifelse($3, `SysTaskGetCurrent', `DEF_ITF_API_SYSTASKGETCURRENT(`$1', `$3', `$4')', `DEF_ITF_API_STANDARD(`$1', `$3', `$4')')')')')', `DEF_ITF_API_VARPARAMETER(`$1', `$3', `$4')')
}
divert(-1)')

define(`DEF_ITF_API_OWNCPP',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	CPP_IMPLEMENTATION_`'$3
}
divert(-1)')

define(`DEF_ITF_API2',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	CPP_IMPLEMENTATION_`'$3
}
divert(-1)')

define(`DEF_ITF_GLOBAL_API',`
divert
$1 $2 C`'_COMPONENT_NAME::I$3$4
{
	ifelse(_HAS_VARIABLEPARAMETER(`$4'), -1, `ifelse($3, `IecTaskGetFirst', `DEF_ITF_API_CMPIECTASKGETFIRST(`$1', `$3', `$4')', `ifelse($3, `IecTaskGetNext', `DEF_ITF_API_CMPIECTASKGETNEXT(`$1', `$3', `$4')', `ifelse($3, `IecTaskGetCurrent', `DEF_ITF_API_CMPIECTASKGETCURRENT(`$1', `$3', `$4')', `ifelse($3, `SysTaskGetCurrent', `DEF_ITF_API_SYSTASKGETCURRENT(`$1', `$3', `$4')', `DEF_ITF_API_STANDARD(`$1', `$3', `$4')')')')')', `DEF_ITF_API_VARPARAMETER(`$1', `$3', `$4')')
}
divert(-1)')

define(`GEN_ITF', `
divert(-1)
include($1)
divert
')

define(`IMPLEMENT_ITF',`dnl
_FOREACH(`GEN_ITF', $@)dnl
divert
')

define(`IMPLEMENT_CPP_ITF',`dnl
IMPLEMENT_ITF($@)
divert
')
