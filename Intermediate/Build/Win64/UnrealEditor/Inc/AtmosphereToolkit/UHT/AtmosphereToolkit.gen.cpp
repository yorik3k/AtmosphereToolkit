// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AtmosphereToolkit/Public/AtmosphereToolkit.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAtmosphereToolkit() {}

// Begin Cross Module References
ATMOSPHERETOOLKIT_API UClass* Z_Construct_UClass_UAtmospherePreset();
ATMOSPHERETOOLKIT_API UClass* Z_Construct_UClass_UAtmospherePreset_NoRegister();
ATMOSPHERETOOLKIT_API UScriptStruct* Z_Construct_UScriptStruct_FAtmospherePresetData();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
UPackage* Z_Construct_UPackage__Script_AtmosphereToolkit();
// End Cross Module References

// Begin ScriptStruct FAtmospherePresetData
static_assert(std::is_polymorphic<FAtmospherePresetData>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FAtmospherePresetData cannot be polymorphic unless super FTableRowBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_AtmospherePresetData;
class UScriptStruct* FAtmospherePresetData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_AtmospherePresetData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_AtmospherePresetData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAtmospherePresetData, (UObject*)Z_Construct_UPackage__Script_AtmosphereToolkit(), TEXT("AtmospherePresetData"));
	}
	return Z_Registration_Info_UScriptStruct_AtmospherePresetData.OuterSingleton;
}
template<> ATMOSPHERETOOLKIT_API UScriptStruct* StaticStruct<FAtmospherePresetData>()
{
	return FAtmospherePresetData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FAtmospherePresetData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============================================\n// PRESSET DATA STRUCT\n// ============================================\n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PRESSET DATA STRUCT" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PresetName_MetaData[] = {
		{ "Category", "Preset" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunIntensity_MetaData[] = {
		{ "Category", "Sun" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunTemperature_MetaData[] = {
		{ "Category", "Sun" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunRotation_MetaData[] = {
		{ "Category", "Sun" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogDensity_MetaData[] = {
		{ "Category", "Fog" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Ex.Fog category\n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ex.Fog category" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogMaxOpacity_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogHeightFalloff_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogStartDistance_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableVolumetricFog_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogColor_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyLightIntensity_MetaData[] = {
		{ "Category", "Sky" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/// \n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExposureBias_MetaData[] = {
		{ "Category", "PPV" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/// <summary>\n/// Post Process Volume\n/// </summary>\n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "<summary>\nPost Process Volume\n</summary>" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Saturation_MetaData[] = {
		{ "Category", "PPV" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Contrast_MetaData[] = {
		{ "Category", "PPV" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FTextPropertyParams NewProp_PresetName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SunIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SunTemperature;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SunRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogMaxOpacity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogHeightFalloff;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogStartDistance;
	static void NewProp_bEnableVolumetricFog_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableVolumetricFog;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FogColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SkyLightIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ExposureBias;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Saturation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Contrast;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAtmospherePresetData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_PresetName = { "PresetName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, PresetName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PresetName_MetaData), NewProp_PresetName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SunIntensity = { "SunIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, SunIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunIntensity_MetaData), NewProp_SunIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SunTemperature = { "SunTemperature", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, SunTemperature), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunTemperature_MetaData), NewProp_SunTemperature_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SunRotation = { "SunRotation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, SunRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunRotation_MetaData), NewProp_SunRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogDensity = { "FogDensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, FogDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogDensity_MetaData), NewProp_FogDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogMaxOpacity = { "FogMaxOpacity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, FogMaxOpacity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogMaxOpacity_MetaData), NewProp_FogMaxOpacity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogHeightFalloff = { "FogHeightFalloff", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, FogHeightFalloff), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogHeightFalloff_MetaData), NewProp_FogHeightFalloff_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogStartDistance = { "FogStartDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, FogStartDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogStartDistance_MetaData), NewProp_FogStartDistance_MetaData) };
void Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_bEnableVolumetricFog_SetBit(void* Obj)
{
	((FAtmospherePresetData*)Obj)->bEnableVolumetricFog = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_bEnableVolumetricFog = { "bEnableVolumetricFog", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FAtmospherePresetData), &Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_bEnableVolumetricFog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableVolumetricFog_MetaData), NewProp_bEnableVolumetricFog_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogColor = { "FogColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, FogColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogColor_MetaData), NewProp_FogColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SkyLightIntensity = { "SkyLightIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, SkyLightIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyLightIntensity_MetaData), NewProp_SkyLightIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_ExposureBias = { "ExposureBias", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, ExposureBias), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExposureBias_MetaData), NewProp_ExposureBias_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_Saturation = { "Saturation", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, Saturation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Saturation_MetaData), NewProp_Saturation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_Contrast = { "Contrast", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAtmospherePresetData, Contrast), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Contrast_MetaData), NewProp_Contrast_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_PresetName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SunIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SunTemperature,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SunRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogMaxOpacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogHeightFalloff,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogStartDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_bEnableVolumetricFog,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_FogColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_SkyLightIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_ExposureBias,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_Saturation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewProp_Contrast,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AtmosphereToolkit,
	Z_Construct_UScriptStruct_FTableRowBase,
	&NewStructOps,
	"AtmospherePresetData",
	Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::PropPointers),
	sizeof(FAtmospherePresetData),
	alignof(FAtmospherePresetData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FAtmospherePresetData()
{
	if (!Z_Registration_Info_UScriptStruct_AtmospherePresetData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_AtmospherePresetData.InnerSingleton, Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_AtmospherePresetData.InnerSingleton;
}
// End ScriptStruct FAtmospherePresetData

// Begin Class UAtmospherePreset Function ApplyPresetData
struct Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics
{
	struct AtmospherePreset_eventApplyPresetData_Parms
	{
		FAtmospherePresetData Data;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Atmosphere Toolkit" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Data;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AtmospherePreset_eventApplyPresetData_Parms, Data), Z_Construct_UScriptStruct_FAtmospherePresetData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Data_MetaData), NewProp_Data_MetaData) }; // 3923972822
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::NewProp_Data,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAtmospherePreset, nullptr, "ApplyPresetData", nullptr, nullptr, Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::AtmospherePreset_eventApplyPresetData_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::AtmospherePreset_eventApplyPresetData_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAtmospherePreset::execApplyPresetData)
{
	P_GET_STRUCT_REF(FAtmospherePresetData,Z_Param_Out_Data);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAtmospherePreset::ApplyPresetData(Z_Param_Out_Data);
	P_NATIVE_END;
}
// End Class UAtmospherePreset Function ApplyPresetData

// Begin Class UAtmospherePreset Function ApplyToCurrentLevel
struct Z_Construct_UFunction_UAtmospherePreset_ApplyToCurrentLevel_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Actions" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAtmospherePreset_ApplyToCurrentLevel_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAtmospherePreset, nullptr, "ApplyToCurrentLevel", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAtmospherePreset_ApplyToCurrentLevel_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAtmospherePreset_ApplyToCurrentLevel_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UAtmospherePreset_ApplyToCurrentLevel()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAtmospherePreset_ApplyToCurrentLevel_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAtmospherePreset::execApplyToCurrentLevel)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyToCurrentLevel();
	P_NATIVE_END;
}
// End Class UAtmospherePreset Function ApplyToCurrentLevel

// Begin Class UAtmospherePreset Function GetPresetRowNames
struct Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics
{
	struct AtmospherePreset_eventGetPresetRowNames_Parms
	{
		TArray<FName> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Atmosphere Toolkit" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AtmospherePreset_eventGetPresetRowNames_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAtmospherePreset, nullptr, "GetPresetRowNames", nullptr, nullptr, Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::AtmospherePreset_eventGetPresetRowNames_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::AtmospherePreset_eventGetPresetRowNames_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAtmospherePreset::execGetPresetRowNames)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FName>*)Z_Param__Result=UAtmospherePreset::GetPresetRowNames();
	P_NATIVE_END;
}
// End Class UAtmospherePreset Function GetPresetRowNames

// Begin Class UAtmospherePreset
void UAtmospherePreset::StaticRegisterNativesUAtmospherePreset()
{
	UClass* Class = UAtmospherePreset::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ApplyPresetData", &UAtmospherePreset::execApplyPresetData },
		{ "ApplyToCurrentLevel", &UAtmospherePreset::execApplyToCurrentLevel },
		{ "GetPresetRowNames", &UAtmospherePreset::execGetPresetRowNames },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAtmospherePreset);
UClass* Z_Construct_UClass_UAtmospherePreset_NoRegister()
{
	return UAtmospherePreset::StaticClass();
}
struct Z_Construct_UClass_UAtmospherePreset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============================================\n// DATA ASSET FOR SAVED PRESSETS\n// ============================================\n" },
#endif
		{ "IncludePath", "AtmosphereToolkit.h" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "DATA ASSET FOR SAVED PRESSETS" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunIntensity_MetaData[] = {
		{ "Category", "Sun" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/// <summary>\n/// Sun\n/// </summary>\n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "<summary>\nSun\n</summary>" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunTemperature_MetaData[] = {
		{ "Category", "Sun" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunRotation_MetaData[] = {
		{ "Category", "Sun" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogDensity_MetaData[] = {
		{ "Category", "Fog" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Ex.Fog category\n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ex.Fog category" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogMaxOpacity_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogHeightFalloff_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogStartDistance_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableVolumetricFog_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogColor_MetaData[] = {
		{ "Category", "Fog" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyLightIntensity_MetaData[] = {
		{ "Category", "Sky" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/// <summary>\n/// Sky\n/// </summary>\n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "<summary>\nSky\n</summary>" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExposureBias_MetaData[] = {
		{ "Category", "PPV" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/// <summary>\n/// Post Process Volume\n/// </summary>\n" },
#endif
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "<summary>\nPost Process Volume\n</summary>" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Saturation_MetaData[] = {
		{ "Category", "PPV" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Contrast_MetaData[] = {
		{ "Category", "PPV" },
		{ "ModuleRelativePath", "Public/AtmosphereToolkit.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SunIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SunTemperature;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SunRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogMaxOpacity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogHeightFalloff;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogStartDistance;
	static void NewProp_bEnableVolumetricFog_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableVolumetricFog;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FogColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SkyLightIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ExposureBias;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Saturation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Contrast;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAtmospherePreset_ApplyPresetData, "ApplyPresetData" }, // 1607280487
		{ &Z_Construct_UFunction_UAtmospherePreset_ApplyToCurrentLevel, "ApplyToCurrentLevel" }, // 3925678619
		{ &Z_Construct_UFunction_UAtmospherePreset_GetPresetRowNames, "GetPresetRowNames" }, // 2395206964
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAtmospherePreset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SunIntensity = { "SunIntensity", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, SunIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunIntensity_MetaData), NewProp_SunIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SunTemperature = { "SunTemperature", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, SunTemperature), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunTemperature_MetaData), NewProp_SunTemperature_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SunRotation = { "SunRotation", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, SunRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunRotation_MetaData), NewProp_SunRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogDensity = { "FogDensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, FogDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogDensity_MetaData), NewProp_FogDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogMaxOpacity = { "FogMaxOpacity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, FogMaxOpacity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogMaxOpacity_MetaData), NewProp_FogMaxOpacity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogHeightFalloff = { "FogHeightFalloff", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, FogHeightFalloff), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogHeightFalloff_MetaData), NewProp_FogHeightFalloff_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogStartDistance = { "FogStartDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, FogStartDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogStartDistance_MetaData), NewProp_FogStartDistance_MetaData) };
void Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_bEnableVolumetricFog_SetBit(void* Obj)
{
	((UAtmospherePreset*)Obj)->bEnableVolumetricFog = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_bEnableVolumetricFog = { "bEnableVolumetricFog", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UAtmospherePreset), &Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_bEnableVolumetricFog_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableVolumetricFog_MetaData), NewProp_bEnableVolumetricFog_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogColor = { "FogColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, FogColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogColor_MetaData), NewProp_FogColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SkyLightIntensity = { "SkyLightIntensity", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, SkyLightIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyLightIntensity_MetaData), NewProp_SkyLightIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_ExposureBias = { "ExposureBias", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, ExposureBias), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExposureBias_MetaData), NewProp_ExposureBias_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_Saturation = { "Saturation", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, Saturation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Saturation_MetaData), NewProp_Saturation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_Contrast = { "Contrast", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAtmospherePreset, Contrast), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Contrast_MetaData), NewProp_Contrast_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAtmospherePreset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SunIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SunTemperature,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SunRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogMaxOpacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogHeightFalloff,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogStartDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_bEnableVolumetricFog,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_FogColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_SkyLightIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_ExposureBias,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_Saturation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAtmospherePreset_Statics::NewProp_Contrast,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAtmospherePreset_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAtmospherePreset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_AtmosphereToolkit,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAtmospherePreset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAtmospherePreset_Statics::ClassParams = {
	&UAtmospherePreset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UAtmospherePreset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UAtmospherePreset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAtmospherePreset_Statics::Class_MetaDataParams), Z_Construct_UClass_UAtmospherePreset_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAtmospherePreset()
{
	if (!Z_Registration_Info_UClass_UAtmospherePreset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAtmospherePreset.OuterSingleton, Z_Construct_UClass_UAtmospherePreset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAtmospherePreset.OuterSingleton;
}
template<> ATMOSPHERETOOLKIT_API UClass* StaticClass<UAtmospherePreset>()
{
	return UAtmospherePreset::StaticClass();
}
UAtmospherePreset::UAtmospherePreset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAtmospherePreset);
UAtmospherePreset::~UAtmospherePreset() {}
// End Class UAtmospherePreset

// Begin Registration
struct Z_CompiledInDeferFile_FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FAtmospherePresetData::StaticStruct, Z_Construct_UScriptStruct_FAtmospherePresetData_Statics::NewStructOps, TEXT("AtmospherePresetData"), &Z_Registration_Info_UScriptStruct_AtmospherePresetData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAtmospherePresetData), 3923972822U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAtmospherePreset, UAtmospherePreset::StaticClass, TEXT("UAtmospherePreset"), &Z_Registration_Info_UClass_UAtmospherePreset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAtmospherePreset), 3403611257U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_1176373125(TEXT("/Script/AtmosphereToolkit"),
	Z_CompiledInDeferFile_FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_UE_Projects_codePrj_Plugins_AtmosphereToolkit_Source_AtmosphereToolkit_Public_AtmosphereToolkit_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
