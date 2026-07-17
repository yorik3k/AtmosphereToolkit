// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AtmosphereToolkit.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAtmospherePresetData;
#ifdef ATMOSPHERETOOLKIT_AtmosphereToolkit_generated_h
#error "AtmosphereToolkit.generated.h already included, missing '#pragma once' in AtmosphereToolkit.h"
#endif
#define ATMOSPHERETOOLKIT_AtmosphereToolkit_generated_h

#define FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAtmospherePresetData_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FTableRowBase Super;


template<> ATMOSPHERETOOLKIT_API UScriptStruct* StaticStruct<struct FAtmospherePresetData>();

#define FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_66_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetPresetRowNames); \
	DECLARE_FUNCTION(execApplyPresetData); \
	DECLARE_FUNCTION(execApplyToCurrentLevel);


#define FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_66_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAtmospherePreset(); \
	friend struct Z_Construct_UClass_UAtmospherePreset_Statics; \
public: \
	DECLARE_CLASS(UAtmospherePreset, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AtmosphereToolkit"), NO_API) \
	DECLARE_SERIALIZER(UAtmospherePreset)


#define FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_66_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAtmospherePreset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UAtmospherePreset(UAtmospherePreset&&); \
	UAtmospherePreset(const UAtmospherePreset&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAtmospherePreset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAtmospherePreset); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAtmospherePreset) \
	NO_API virtual ~UAtmospherePreset();


#define FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_63_PROLOG
#define FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_66_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_66_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_66_INCLASS_NO_PURE_DECLS \
	FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_66_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ATMOSPHERETOOLKIT_API UClass* StaticClass<class UAtmospherePreset>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
